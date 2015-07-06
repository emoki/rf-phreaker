#pragma once

//TODO: research if we can go ahead and totally delete the 32-bit time_t
//#define _USE_32BIT_TIME_T

#include "ipp.h"


#   define DATASTRUCT      Ipp32fc
#   define DATATYPE        Ipp32f
#   define ALLOCSTRUCT     ippsMalloc_32fc
#	define ALLOCTYPE       ippsMalloc_32f
#	define ALLOCTAPS       ippsMalloc_64f
#   define CROSSCORR       ippsCrossCorr_32fc
#   define MAG             ippsMagnitude_32fc
#   define MEAN            ippsMean_32f
#   define NORMALIZE       ippsNormalize_32fc
#   define WINHANN         nspsWinHann
#   define FFT             ippsFFTFwd_CToC_32fc_I
#   define DFT             ippsDFTFwd_CToC_32fc
#   define POWERSPECTR     ippsPowerSpectr_32fc

#	define GET_LPF_FIR		ippsFIRGenLowpass_64f
#	define FREETYPE			ippsFree

#   define BPFTAPS         fbpftaps
#   define LPFTAPS         flpftaps


#define TAPTYPE            Ipp64f

#define REALPART(d)        ((d).re)
#define IMAGPART(d)        ((d).im)


// general macros
// e - Changed on June 8th 2009.  Debugging SL difference.
// Dhaval: SPL project has it right already ...
//   I wonder why this needed to be changed back?
//#define ROUND(a)  ( (int)((a) + 0.5) )
#define ROUND(a)  ( (int)((a) < 0 ? (a) - 0.5 : (a) + 0.5) )


/*****************************************************************************/
// These define which debug files are written
#ifdef _DEBUG
	#define LOTSAFILES 0
	#define XCORRFILES 0
	#define CCFILES 0
	#define MYTESTFILE 0
	#define VERBOSE 0
	#define FCCHVERBOSE 0
	#define FFTVERBOSE 0
#else
	#define LOTSAFILES 0
	#define XCORRFILES 0
	#define CCFILES 0
	#define MYTESTFILE 0
	#define VERBOSE 0
	#define FCCHVERBOSE 0
	#define FFTVERBOSE 0
#endif
/*****************************************************************************/
#include "rf_phreaker/gsm_analysis/gsm_defs.h"
#define _NETSTART_DECIMATION
#ifdef _NETSTART_DECIMATION
	#define _NETSTART_HW_DECIMATION_FACTOR	2
#else
	#define _NETSTART_HW_DECIMATION_FACTOR	1
#endif

#define NETSTART_SAMPLING_RATE_HZ			(RF_PHREAKER_SAMPLING_RATE_HZ/_NETSTART_HW_DECIMATION_FACTOR)
#define NETSTART_SAMPLES_PER_GSM_BIT		(NETSTART_SAMPLING_RATE_HZ / GSM_BIT_RATE)
#define NETSTART_SNAPSHOT_MAX_NUM_SAMPLES	(RF_PHREAKER_SNAPSHOT_MAX_NUM_GSM_BITS * NETSTART_SAMPLES_PER_GSM_BIT)

#define SIDE_BW         10000
#define SIDE_OFFSET     1000
#define CARRIER_BW      25000
#define	AVG_POWER_BW	100000
#define IF_FREQ         0
// Start windowing at DATA_OFFSET (in number of GSM bits), not at 0,
// in order to allow selection of corr data prior to the found window
// Modified 20 June 2010, Dhaval Dave
// If offset is not at least one burst in length, it is then possible
// that a partial fcch could be found with a combined corr of 0.5-ish.
// This would be reported as a potentially valid fcch/sync, but with a timing
// offset from the "real" fcch/sync that could be as much as 0.05 frames.
// Thus, set offset = at least one burst = 156 bits.
#define DATA_OFFSET_GSMBITS		(GSM_BURST_LEN_BITS)
// Choose windows to include MIN_INPUT_LEN number of GSM bits
// which guarantees at least one full FCCH burst to occur
#define MIN_INPUT_GSMBITS	(12.5 * GSM_BITS_PER_FRAME)


typedef struct _TemplateType {
	DATASTRUCT *data;
	int    length;
} TemplateType;

typedef struct _TemplateStruct {
	TemplateType fcch;
	TemplateType sync;
	TemplateType dummy;
	TemplateType ts[8];
} TemplateStruct;

/*****************************************************************************/

/* other headers to include in all netstart files */
#include "rf_phreaker/gsm_analysis/gsm_analysis_data.h"

#include "rf_phreaker/gsm_analysis/ns_row.h"
#include "rf_phreaker/gsm_analysis/ns_sync.h"
#include "rf_phreaker/gsm_analysis/ns_sp.h"
#include "rf_phreaker/gsm_analysis/ns_fcch.h"


extern SuGSMDebugSettings GsmDebugSettings;

typedef struct {
   int            datalength;
   int            datasize;
   int            step_size;
   int            time_size;
   int            fft_size;
   int            ps_size;
   int            downfac;
   int            upfac;
   int            fs;
   int            window_offset;
   int            num_windows;
   DATATYPE       blocksize;
   DATATYPE       fcch_th2;
   DATATYPE       fcch_th3;
   bool           ProcessBCCH;
   unsigned int  *FreqToProcess;
   unsigned int   NumFreqs;
   DATATYPE       tb;
   DATATYPE       nspb;
   DATASTRUCT   **fft_windows;
   DATATYPE     **ps_windows;
   DATATYPE      *avg_ps;
   short         *filedata;
   DATASTRUCT      *data;
   TemplateStruct templates;
   FCCHStruct     fcch_s;
   SyncStruct     sync_s;
   GsmSyncProcessor *sync_processor;
   gsm_analysis_output_list    *head_row;
} GSMStruct;
