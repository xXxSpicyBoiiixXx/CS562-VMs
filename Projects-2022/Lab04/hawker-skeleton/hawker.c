/* 
 * This file is part of the Hawker container engine developed by
 * the HExSA Lab at Illinois Institute of Technology.
 *
 * Copyright (c) 2018, Kyle C. Hale <khale@cs.iit.edu>
 *
 * All rights reserved.
 *
 * Author: Kyle C. Hale <khale@cs.iit.edu>
 *
 * This is free software.  You are permitted to use,
 * redistribute, and modify it as specified in the 
 * file "LICENSE.txt".
 */
#define _GNU_SOURCE
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <signal.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/sysmacros.h>
#include <sys/mount.h>
#include <sys/prctl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>


#include "hawker.h"
#include "net.h"
#include "img.h"

static pid_t child_pid = -1;



static void
set_child_pid (long pid)
{
    child_pid = pid;
}


static int
check_or_create_file (char * path, mode_t mode)
{
    if (access(path, F_OK) != 0) {
        int fd = open(path, O_CREAT, mode);
        close(fd);
    }

    return 0;
}

static int
check_or_create_dir (char * path, mode_t mode)
{
    if (access(path, F_OK) != 0) {
        if (mkdir(path, mode) != 0) {
            ERRSTR("Could not create %s", path);
            return -1;
        }
    }

    return 0;
}

static int
mount_vfs_dirs (void)
{
    check_or_create_dir("/sys", 0555);

    if (mount("none", "/sys", "sysfs", MS_NOSUID | MS_NODEV | MS_NOEXEC | MS_RDONLY, "") != 0) {
        ERRSTR("couldn't mount sysfs");
        return -1;
    }

    check_or_create_dir("/tmp", 0777);

    if (mount("tmpfs", "/tmp", "tmpfs", MS_NOSUID | MS_NODEV, "") != 0) {
        ERRSTR("couldn't mount tmpfs");
        return -1;
    }

    check_or_create_dir("/proc", 0555);

    if (mount("none", "/proc", "proc", MS_NOSUID | MS_NODEV | MS_NOEXEC, "") != 0) {
        ERRSTR("couldn't mount procfs");
        return -1;
    }

    return 0;
}


static int
check_or_create_chdev (char * base, char * node, mode_t mode, unsigned maj, unsigned min)
{
    char path[PATH_MAX];

    snprintf(path, PATH_MAX, "%s/%s", base, node);

    if (access(path, F_OK) != 0) {
        dev_t dev = makedev(maj, min);
        if (mknod(path, S_IFCHR | mode, dev) != 0) {
            ERRSTR("couldn't create device node for '%s'", path);
            return -1;
        }
    }

    return 0;
}


static int
make_dev_nodes (char * base)
{
    char base_path[PATH_MAX];
    char pts_path[PATH_MAX];

    snprintf(base_path, PATH_MAX, "%s/dev", base);
    snprintf(pts_path, PATH_MAX, "%s/dev/pts", base);

    check_or_create_dir(base_path, 0755);

    if (mount("tmpfs", base_path, "tmpfs", MS_NOSUID | MS_STRICTATIME, "mode=755,size=65536k") != 0) {
        ERRSTR("couldn't mount /dev for container");
        return -1;
    }

    check_or_create_chdev(base_path, "tty", 0666, 5, 0);
    check_or_create_chdev(base_path, "console", 0622, 5, 1);
    check_or_create_chdev(base_path, "ptmx", 0666, 5, 2);
    check_or_create_chdev(base_path, "null", 0666, 1, 3);
    check_or_create_chdev(base_path, "zero", 0666, 1, 5);
    check_or_create_chdev(base_path, "random", 0444, 1, 8);
    check_or_create_chdev(base_path, "urandom", 0444, 1, 9);

    check_or_create_dir(pts_path, 0620);

    if (mount("devpts", pts_path, "devpts", MS_NOSUID | MS_NOEXEC, "mode=620,ptmxmode=666") != 0) {
        ERRSTR("couldn't mount devpts for container");
        return -1;
    }

    return 0;
}


static int
add_root_user (void)
{
    // TODO: we should actually check for "root" in /etc/group
    if (access("/etc/group", F_OK) != 0) {

        check_or_create_dir("/etc", 0755);
        check_or_create_file("/etc/group", 0644);

        if (system("addgroup -g 0 root") != 0) {
            ERRSTR("could not add group");
            return -1;
        }

        check_or_create_file("/etc/passwd", 0644);

        // don't create password, don't create homedir
        if (system("adduser -D -H -G root -u 0 root") != 0) {
            ERRSTR("could not add root user");
            return -1;
        }

    }

    return 0;
}


extern char ** environ;

static char **
setup_env (void)
{
    char * path  = "PATH=/bin:/usr/bin:/usr/local/bin:/usr/sbin:/usr/local/sbin";
    char * user  = "USER=root";
    char ** envp = calloc(sizeof(char*)*3, 1);

    if (!envp) {
        ERROR("Could not allocate environment ptr\n");
        return NULL;
    }

    envp[0] = strndup(path, strnlen(path, PATH_MAX));
    envp[1] = strndup(user, strnlen(user, PATH_MAX));

    if (!envp[0]) {
        ERRSTR("Could not copy PATH variable");
        goto out_err;
    }

    envp[2] = NULL;

    putenv(path);

    return envp;

out_err:
    free(envp);
    return NULL;
}


static int
pty_setup ()
{
    if (setsid() < 0) {
        ERRSTR("couldn't become session leader");
        return -1;
    }

    int cons_fd = open("/dev/console", O_RDWR);

    if (cons_fd < 0) {
        ERRSTR("couldn't open console");
        return -1;
    }

    if (ioctl(cons_fd, TIOCSCTTY, 0) < 0) {
        ERRSTR("Couldn't set console as controlling terminal");
        return -1;
    }

    int fd = posix_openpt(O_RDWR);

    if (fd < 0) {
        ERRSTR("couldn't get pty pair");
        return - 1;
    }

    char * slave = ptsname(fd);

    printf("got slave %s\n", slave);

    if (grantpt(fd) != 0) {
        ERRSTR("Coudln't grant terminal ownership");
        return -1;
    }

    if (unlockpt(fd) != 0) {
        ERRSTR("Couldn't unlock terminal slave");
        return -1;
    }


    int slavefd = open(slave, O_RDWR);

    if (slavefd < 0) {
        ERRSTR("Couldn't open terminal slave");
        return -1;
    }


    close(slavefd);
    close(fd);



    return 0;
}


/* 
 * This is the (child) container process. By the time it invokes the user command
 * specified (using execvpe()), it will be in a fully isolated container
 * environment.
 */
static int 
child_exec (void * arg)
{
        struct parms *p           = (struct parms*)arg;
        const char * new_hostname = DEFAULT_HOSTNAME;
        char c;
        char ** envp;

        // if our parent dies and doesn't kill us
        // explicitly, we should also die, instead of hanging
        // around. Note that this is not POSIX-compliant, 
        // so it will only work on Linux.
        prctl(PR_SET_PDEATHSIG, SIGKILL);

        close(p->pipefd[1]); // close write end of our pipe

        // wait for the parent to hangup its write end of the pipe,
        // signaling that we can now start the container stuff.
        if (read(p->pipefd[0], &c, 1) != 0) {
            ERRSTR("read from pipe in child returned nonzero status");
            exit(EXIT_FAILURE);
        }

        close(p->pipefd[0]); // close read end of the pipe, we're done with it

        // FILL ME IN: our parent should now have set things up properly
        // We need to:
        // (1) change our root to the new directory for the image
        // (2) actually move into that root
        // (3) change our hostname
        // (4) execute the command that the user gave us

        // should never reach here
        exit(EXIT_FAILURE);
}


static int 
write_proc_file (char * filp_fmt, char * str, long pid)
{
    char buf[PATH_MAX];
    int fd;

    snprintf(buf, PATH_MAX, filp_fmt, pid);

    fd = open(buf, O_WRONLY);

    if (fd < 0) {
        ERRSTR("Could not open file (%s)", buf);
        return -1;
    }

    if (write(fd, str, strlen(str)) != strlen(str)) {
        ERRSTR("Could not write string (%s)", str);
        close(fd);
        return -1;
    }

    close(fd);

    return 0;
}


static void
version ()
{
    printf("hawker %s\n", VERSION_STRING);
}


static void
usage (char * prog)
{
    printf("\n\thawker -- the container engine\n\n");

    printf("\tDescription\n");
    printf("\t\thawker is a minimal container engine.\n");
    printf("\t\tIt creates a container and runs the\n");
    printf("\t\tspecified command inside of it.\n\n");

    printf("\tUsage: %s [OPTIONS] IMAGE COMMAND [ARG...]\n", prog);

    printf("\n\tOptions:\n");

    printf("\t\t  -c, ---cpu-share <percentage> : percent of CPU to give to container (from 0 to 100); default=100\n");
    printf("\t\t  -m, ---mem-limit <limit-in-bytes> : max amount of memory that the container can use\n");
    printf("\t\t  -C, --clear-cache : clear all cached container images\n");
    printf("\t\t  -h, ---help : display this message\n");
    printf("\t\t  -v, --version : display the version number and exit\n");

    printf("\n");
}


static void
parse_args (int argc, char **argv, struct parms * p)
{
        int cpu_pct    = DEFAULT_CPU_PCT;
        long mem_limit = DEFAULT_MEM_LIMIT;
        int optidx     = 0;
        char c;

        while (1) {

            static struct option lopts[] = {
                {"cpu-share", required_argument, 0, 'c'},
                {"mem-limit", required_argument, 0, 'm'},
                {"clear-cache", no_argument, 0, 'C'},
                {"help", no_argument, 0, 'h'},
                {"version", no_argument, 0, 'v'},
                {0, 0, 0, 0}
            };

            c = getopt_long(argc, argv, "+c:m:Chv", lopts, &optidx);

            if (c == -1) {
                break;
            }

            switch (c) {
                case 'c':
                    cpu_pct = atoi(optarg);
                    break;
                case 'C':
                    hkr_clear_img_cache();
                    exit(EXIT_SUCCESS);
                case 'm':
                    mem_limit = atol(optarg);
                    break;
                case 'h':
                    usage(argv[0]);
                    exit(EXIT_SUCCESS);
                case 'v':
                    version();
                    exit(EXIT_SUCCESS);
                case '?':
                    break;
                default:
                    printf("?? getopt returned character code 0%o ??\n", c);
            }
        }

        if (optind < argc) {
            p->img = argv[optind++];
        } else {
            usage(argv[0]);
            exit(EXIT_SUCCESS);
        }

        if (optind < argc) {
            p->cmd = argv[optind];
        } else {
            usage(argv[0]);
            exit(EXIT_SUCCESS);
        }

        p->argv      = &argv[optind];
        p->mem_limit = mem_limit;
        p->cpu_pct   = cpu_pct;
}


static inline void
construct_cgroup_path (char * buf, size_t len, long pid, char * subdir)
{
    memset(buf, 0, len);
    snprintf(buf, len, "/sys/fs/cgroup/%s/hawker/%ld", subdir, pid);
}


static inline void
construct_cgroup_subpath (char * buf, size_t len, long pid, char * subdir, char * subent)
{
    memset(buf, 0, len);
    snprintf(buf, len, "/sys/fs/cgroup/%s/hawker/%ld/%s", subdir, pid, subent);
}


static void
make_cgroup_subdir(long pid, char * subdir)
{
    char path[PATH_MAX];
    construct_cgroup_path(path, PATH_MAX, pid, subdir);

    // does it already exist?
    if (access(path, F_OK) == 0) {
        return;
    }

    if (mkdir(path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0) {
        ERRSTR("Could not create cgroup dir for '%s' (Did you run the setup script?)", subdir);
        exit(EXIT_FAILURE);
    }
}


static void
remove_cgroup_subdir(long pid, char * subdir)
{
    char path[PATH_MAX];

    construct_cgroup_path(path, PATH_MAX, pid, subdir);

    // dir isn't there
    if (access(path, F_OK) != 0) {
        return;
    }

    if (rmdir(path) != 0) {
        ERRSTR("Could not remove cgroup dir");
        exit(EXIT_FAILURE);
    }
}


static void
setup_cgroup_dirs (long pid)
{
    make_cgroup_subdir(pid, "cpuacct");
    make_cgroup_subdir(pid, "memory");
}


static void
cleanup_cgroup_dirs (long pid)
{
    remove_cgroup_subdir(pid, "cpuacct");
    remove_cgroup_subdir(pid, "memory");
}


#define MAX_CGROUP_LEN 64


static void 
set_cgroup_file_val (long pid, char * subdir, char * subent, unsigned val, int append)
{
    char path[PATH_MAX];
    char val_str[MAX_CGROUP_LEN];
    int fd;
    int flags = O_RDWR;

    construct_cgroup_subpath(path, PATH_MAX, pid, subdir, subent);

    if (append) {
        flags |= O_APPEND;
    } else {
        flags |= O_TRUNC;
    }

    fd = open(path, O_RDWR | O_TRUNC);

    if (fd < 0) {
        ERRSTR("Could not open cgroup path (%s)", path);
        exit(EXIT_FAILURE);
    }

    memset(val_str, 0, MAX_CGROUP_LEN);
    snprintf(val_str, MAX_CGROUP_LEN, "%u", val);

    if (write(fd, val_str, strnlen(val_str, MAX_CGROUP_LEN)) != strnlen(val_str, MAX_CGROUP_LEN)) {
        ERRSTR("Could not write to shares dir");
        exit(EXIT_FAILURE);
    }

    close(fd);
}


static inline void
assign_pid_to_cgroup (long pid, char * subdir) 
{
    set_cgroup_file_val(pid, subdir, "tasks", (unsigned long)pid, 1);
}


static inline void
set_cgroup_val (long pid, unsigned long val, char * subdir, char * subent, int append)
{
    set_cgroup_file_val(pid, subdir, subent, val, append);
    assign_pid_to_cgroup(pid, subdir);
}


// uses the completely fair scheduler (CFS) subsystem
static inline void
set_cpu_share (long pid, unsigned long share)
{
    unsigned long period = 1000000;
    unsigned long quota;

    // truncate, we can't get more than 1024
    if (share > 100) {
        share = 100;
    }

    quota  = (period / 100) * share;

    set_cgroup_file_val(pid, "cpuacct", "cpu.cfs_quota_us", quota, 0);
    set_cgroup_file_val(pid, "cpuacct", "cpu.cfs_period_us", period, 0);
    assign_pid_to_cgroup(pid, "cpuacct");
}


static inline void
set_mem_limit (long pid, long limit)
{
    // only set the mem limit if the user asked
    if (limit > 0) {
        set_cgroup_val(pid, (unsigned long)limit, "memory", "memory.limit_in_bytes", 0);
    }
}


static void
cleanup (void)
{
    cleanup_cgroup_dirs(child_pid);
}

static void 
death_handler (int sig)
{
    kill(child_pid, SIGKILL);
    // if we don't wait for the child to
    // completely die here, cgroups won't let us remove
    // the subdirectories
    waitpid(child_pid, NULL, 0);
    cleanup();
}

static void
set_child_user_maps (long pid, unsigned from, unsigned to)
{
    char map[PATH_MAX];

    snprintf(map, PATH_MAX, "%u %u 1", from, to);

    // http://man7.org/linux/man-pages/man7/user_namespaces.7.html 
    write_proc_file("/proc/%ld/uid_map", map, pid);
    write_proc_file("/proc/%ld/setgroups", "deny", pid);
    write_proc_file("/proc/%ld/gid_map", map, pid);
}


int 
main (int argc, char **argv)
{
        void * child_stack = NULL;
        unsigned stk_sz    = DEFAULT_STACKSIZE;
        struct parms p;
        int clone_flags;
        pid_t pid;

        // get our network subsystem going
        if (hkr_net_init() != 0) {
            ERROR("Could not initialize network subsystem\n");
            exit(EXIT_FAILURE);
        }

        // create a cache for our container images
        if (hkr_img_cache_init() != 0) {
            ERROR("Could not create hawker image cache\n");
            exit(EXIT_FAILURE);
        }

        parse_args(argc, argv, &p);

        // if the image isn't cached, we need to download it
        if (!hkr_img_exists(p.img)) {

            printf("Unable to find image '%s' locally\n", p.img);

            // we get it in the form of a .txz file
            if (hkr_net_get_img(p.img) != 0) {
                ERROR("Image '%s' not found in hawker repository\n", p.img);
                exit(EXIT_FAILURE);
            }

            // now extract it into our cache dir
            if (hkr_img_extract(p.img) != 0) {
                ERROR("Could not extract compressed image (%s)\n", p.img);
                exit(EXIT_FAILURE);
            }

        }

        // we have to do this as the parent, only root has
        // ability to create device nodes using mknod()
        if (make_dev_nodes(hkr_get_img(p.img)) != 0) {
            ERROR("Could not create device nodes\n");
            exit(EXIT_FAILURE);
        }

        // FILL ME IN: we need to add flags to clone
        // to setup namespaces properly, you should create
        // new UTS, PID, user, mountpoint, network, and IPC 
        // namespaces. See man 3 clone if in doubt.
        // The SIGCHILD indicates the signal which should
        // be delivered to the parent process when the
        // child exits (if does, indeed, exit);
        clone_flags = SIGCHLD;

        // FILL ME IN: when we create a new process using clone(), we
        // must give the new process a stack. We are in charge of allocating
        // that stack. We could either use malloc() or mmap() here. 
        // malloc() is of course easier, but mmap() gives us more control
        // over the characteristics of that memory.

        // FILL ME IN: remove this when you get a stack set up
        exit(EXIT_SUCCESS);

        // we'll use this pipe for communicating with the child
        if (pipe(p.pipefd) != 0) {
            ERRSTR("Could not create pipe");
            exit(EXIT_FAILURE);
        }

        // We must now call clone and get a pid back. We must pass
        // in the stack we allocated, its size, the flags for the clone, and an argument
        // to pass to the function. The result of this call is 
        // that our child_exec function will be run in another
        // process. Clone will give us the child's
        // PID as a return value. -1 means it encountered an error.
        pid = clone(child_exec, child_stack + stk_sz, clone_flags, &p);
        if (pid < 0) {
                ERRSTR("Clone failed");
                exit(EXIT_FAILURE);
        }

        set_child_pid(pid);

        // FILL ME IN: we have to setup the PID namespace now
        // This will involve writing /proc/<PID>/uid_map, gid_map

        // BEGIN RESOURCE CONTROL SETUP
        
        // I'm setting up these cgroup directories for you. You'll
        // need to modify files within these to actually control the cgroups
        setup_cgroup_dirs(pid);

        // we must clean these cgroup dirs up if the process exits,
        // so we make sure here that we'll catch user interrupts (^C)
        signal(SIGINT, death_handler);

        // FILL ME IN: 
        // we must set the relative amount of CPU
        // this process will get and the maximum amount of 
        // memory it can use (in bytes). We use the values
        // passed to us in p.cpu_pct and p.mem_limit, and
        // translate those into the cgroup file entries
            
        // we hang up both ends of the pipe to let the child
        // know that we've written the appropriate files. It 
        // can then continue. Note that we could also do this
        // with signal()
        close(p.pipefd[0]); // close read end of pipe
        close(p.pipefd[1]); // close write end of pipe

        // wait on child to exit
        waitpid(pid, NULL, 0);

        // goodbye
        exit(EXIT_SUCCESS);
}
