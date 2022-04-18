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
#ifndef __HAWKER_H__
#define __HAWKER_H__

#define VERSION_STRING "0.2"

#define DEFAULT_STACKSIZE (1024*1024)
#define DEFAULT_HOSTNAME "hawker.local"

#define DEFAULT_MEM_LIMIT  (-1)
#define DEFAULT_CPU_PCT 100

#define ERROR(fmt, args...) fprintf(stderr, "HAWKER ERROR: " fmt, ##args)
#define ERRSTR(fmt, args...) fprintf(stderr, "HAWKER ERROR: " fmt ": %s\n", ##args, strerror(errno))
#define DEBUG(fmt, args...) printf("HAWKER DEBUG: " fmt, ##args)


struct parms {
        int pipefd[2];
        char * img;
        char * cmd;
        char **argv;

        int cpu_pct;
        long mem_limit;
};

#endif
