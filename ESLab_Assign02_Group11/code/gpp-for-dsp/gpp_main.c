/*  ----------------------------------- OS Specific Headers           */
#include <stdio.h>
#include <stdlib.h>

/*  ----------------------------------- DSP/BIOS Link                 */
#include <dsplink.h>

/*  ----------------------------------- Application Header            */
#include <pool_notify.h>

/** ============================================================================
 *  @func   main
 *
 *  @desc   Entry point for the application
 *
 *  @modif  None
 *  ============================================================================
 */
int main (int argc, char ** argv)
{
    Char8 * dspExecutable    = NULL ;
    Char8 * strBufferSize    = NULL ;

    if (argc != 3) {
        printf ("Usage : %s <absolute path of DSP executable> "
           "<Buffer Size> <number of transfers>\n",
           argv [0]) ;
    }
    else {
        dspExecutable    = argv [1] ;
        strBufferSize    = argv [2] ;

        pool_notify_Main (dspExecutable,
                          strBufferSize) ;
    }

    return 0 ;
}
