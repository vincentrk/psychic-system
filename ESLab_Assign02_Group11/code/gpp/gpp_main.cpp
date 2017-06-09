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
int dsp_main (int argc, char ** argv)
{
    Char8 * dspExecutable    = NULL ;
    Char8 * strBufferSize    = NULL ;
    Char8 * inFile           = NULL ;

    if (argc != 3) {
        printf ("Usage : %s <absolute path of DSP executable> "
           "<Buffer Size> <input file>\n",
           argv [0]) ;
    }
    else {
        dspExecutable    = argv [1] ;
        strBufferSize    = argv [2] ;
        inFile           = argv [3] ;

        pool_notify_Main (dspExecutable,
                          strBufferSize, inFile) ;
    }

    return 0 ;
}
