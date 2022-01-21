#include <rc.h>
#include <base.h>
#include <ines.h>
#include <shell.h>
#include <fileio.h>
#include <memory.h>

// From NES 
#include <nes/ppu.h>
#include <new/io_reg.h>

#include <SDL2/SDL.h>

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdnoreturn.h>

#include <getopt.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h> 

#define NES_NTSC_SYSCLK (236.25 / 11. * 1000000) 

// static const uint8_t                             add additional constants later 
// static const uint8_t 


static inline int rom_load(FILE * nonnull f, const char * nonnull path, reset_manager_t * nonnull rm, mos6502_t * nonnull cpu) { 
    int retcode = 0; 
    
    memory_t * cartrom = memory_new(rm, 0x6000, false); 
        
    if(!cartrom) { 
        retcode = -1; 
        goto ret; 
    }

    if((retcode = try_fread(f, path, cartrom -> bytes, cartrom -> size))) { 
        retcode = -1; 
        goto release_cartrom; 
    }

    memory_map(cartrom, cpu -> bus, 0xA000, (uint16_t)cartrom -> size, 0); 

    memory_t * ram = memory_new(rm, 32768, true); 

    if(!ram) { 
        retcode = -1; 
        goto release_cartrom; 
    }

    memory_map(ram, cpu -> bus, 0, (uint16_t) ram -> size, 0); 
    rc_release(ram); 

release_cartrom: 
        rc_release(cartrom); 

ret:
        return retcode;    
}

static inline int load_rom(const char * nonnull path, reset_manager_t * nonnull rm, mos6502_t * nonnull cpu, const char * nonnull palette_path, const char * nonnull cscheme_path, int scale) { 
    
}



