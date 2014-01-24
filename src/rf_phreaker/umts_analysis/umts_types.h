#ifndef __UMTSDEFS_H__
#define __UMTSDEFS_H__

#define N_SLOTS_PER_FRAME	(15)
#define FRAME_PERIOD_SEC	(0.01)					// Frame duration in seconds
#define SLOT_PERIOD_SEC		(FRAME_PERIOD_SEC/N_SLOTS_PER_FRAME)	// Slot duration in seconds
#define N_CHIPS_PER_TIMESLOT	2560
#define N_TOTAL_CHIPS_CPICH		N_CHIPS_PER_TIMESLOT * N_SLOTS_PER_FRAME
#define N_CPICH_CODES 512
#define N_CHIPS_PER_PSCH 256

#define N_CODE_GROUPS 64
#define N_PSCHSSCH_SAMPLES 325
#define N_SECSYNC_CHANNELS 16

#define UMTS_BCCH_TTI_BITSIZE        270





// alpha anl defs.h
// These defines are hard-coded parameters for the Alpha/Beta processing
// TODO: put them into Umts.cpp when we finalize!
//Num chips per part for corrs in Alpha/Beta
#define N_CHIPS_ALPHA_CORR			3584
#define N_CHIPS_BETA_CORR			3456//3328//4608 //TODO:: don't forget to change this back to 2048
// Num samples per part of corr
#define N_SAMP_ALPHA_CORR			((int)(N_CHIPS_ALPHA_CORR*OSR))
#define N_SAMP_BETA_CORR			((int)(N_CHIPS_BETA_CORR*OSR))
// Number of parts over which corrs are non-coherently combined
#define N_PARTS_ALPHA_CORR			1
#define N_PARTS_BETA_CORR			3 //TODO:: don't forget to change this back to 4?
#define N_SLOTS_PER_BETA_PACKET		/*5*/4	
#define N_BETA_PACKETS_PER_DATA		5  
#define BETA_NOMINAL_CORR_SPREAD	5 // 8
#define ALPHA_START_CORR_SPREAD		5

#define MAXLENCORRSEGMENT 4608
#define MAXNUMCORRSEGMENTS 6

#define N_CAND_POS_CPICH_CORR		(200)		// (200) Number of candidate positions selected from correlations of 512 p-scr. codes, where
#define N_CAND_PER_SCR_CODE			(10)		// (10)    multiple candidate-positions may correspond to a single P-scr-code
#define N_SAMP_MAX_CORR_SPREAD		(20)			// Number of samples correlation is spread on each side


#define UMTS_CHANNEL_RESAMPLE_FILTER_LEN 128
#define UMTS_CHANNEL_FILTER_LEN 64


#endif
#endif