/* ========================================================================= */
/*                                                                           */
/*   TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                           */
/*   NAME                                                                    */
/*       tsc                                                                 */
/*                                                                           */
/*   PLATFORM                                                                */
/*       C64xPLUS                                                            */
/*                                                                           */
/*   USAGE                                                                   */
/*       These routines are C callable, and have the following C prototypes: */
/*                                                                           */
/*           void TSC_enable();                                              */
/*           long long TSC_read();                                           */
/*                                                                           */
/*   DESCRIPTION                                                             */
/*       TSC_enable: Enables the Time Stamp Counter                          */
/*       TSC_read:   Reads the Time Stamp Counter and returns 64-bit count   */
/*                                                                           */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2004 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */

#ifndef _TSC_H_
#define _TSC_H_

void TSC_enable();
long long TSC_read();

#endif /* _TSC_H_ */

/* ========================================================================= */
/*   End of file:  tsc                                                       */
/* ------------------------------------------------------------------------- */
/*             Copyright (c) 2004 Texas Instruments, Incorporated.           */
/*                            All Rights Reserved.                           */
/* ========================================================================= */
