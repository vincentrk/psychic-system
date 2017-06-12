
/*  ----------------------------------- OS Specific Headers           */
#include <stdio.h>
#include <stdlib.h>
#include "dsplink.h"

extern "C" {
/*  ----------------------------------- DSP/BIOS Link                 */

/*  ----------------------------------- Application Header            */
#include "pool_notify.h"

}

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
    DSP_STATUS status;

    if (argc != 3) {
        printf ("Usage : %s <absolute path of DSP executable> "
                "<Buffer Size> <number of transfers>\n",
                argv [0]) ;
        return -1;
    }

    dspExecutable    = argv [1] ;
    strBufferSize    = argv [2] ;

    status = pool_notify_Init (dspExecutable,
            strBufferSize) ;
    if (!DSP_SUCCEEDED(status))
    {
        return -1;
    }

    status = pool_notify_Execute (0) ;

    pool_notify_Delete(0);

    return 0 ;
}
