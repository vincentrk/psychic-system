#ifndef CONFIG_H__
#define CONFIG_H__

/* Configure the DSP and GPP task devision. */
/* To enable a configuration uncomment it and comment out the other configurations */
/* The default is to run only on the GPP */

/* Run partially on the DSP and partially on the GPP (load sharing) */
//#define DSP_CALSHIFT
//#define DSP_CALSHIFT_PARTIAL 3

/* Run callshift only on the DSP */
//#define DSP_CALSHIFT

#endif
