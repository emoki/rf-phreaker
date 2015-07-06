#if !defined _GSM_ANALYSIS_DATA_H
#define _GSM_ANALYSIS_DATA_H


// Return values
// NOTE: as a convention in GsmAnalysis, all errors < 0 are FATAL
// while errors > 0 might indicate partial loss of function, but are not fatal.
enum GsmAnalysisError {
	GSM_ANALYSIS_NO_ERROR =				0,
	GSM_INIT_OUT_OF_MEMORY =			-1,
	// gsm_analysis() called but not initialized successfully
	GSM_ANALYSIS_NOT_INITIALIZED =		-2,
	GSM_ANALYSIS_WIN_ALLOC_ERROR =		-3,
	GSM_ANALYSIS_ADD_ROW_ERROR =		-4,
	GSM_ANALYSIS_SYNC_MEMORY_ALLOC =	-5,
	GSM_ANALYSIS_SYNC_LPF_ERROR =		-6,
	GSM_ANALYSIS_CGI_INIT_ERROR =		-7,
	// Undefined errors should never happen unless there is a bug in the code
	GSM_UNDEFINED_ERROR =				-1001,
	GSM_FCCH_UNDEFINED_ERROR =			-1002,
	GSM_SYNC_UNDEFINED_ERROR =			-1003,
	// GsmInit() was previously called and completed successfully
	GSM_INIT_ALREADY_INITIALIZED =		1,
	GSM_INIT_ERROR_READING_TEMPLATES =	2,
	GSM_INIT_ERROR_READING_WIN_COEFFS =	3,
	// could not create or change to DebugFiles sub-directory (only valid in DEBUG build)
	GSM_ANALYSIS_DATASIZE_ERROR =		4,
	GSM_ANALYSIS_NULL_INPUT =			5,
	GSM_ANALYSIS_BSIC_INIT_ERROR =		6,
	GSM_DEBUG_FILES_DIRECTORY_ERROR =	1001
};

//#define GSM_ANALYSIS_INIT_ERROR_MSG				"GSM Analysis: Init error"
//#define GSM_ANALYSIS_WIN_ALLOC_ERROR_MSG		"GSM Analysis: Window allocation error"
//#define GSM_ANALYSIS_WIN_CREATION_ERROR_MSG		"GSM Analysis: Window creation error"
//#define GSM_ANALYSIS_FCCH_ERROR_MSG				"GSM Analysis: FCCH detection error"
//#define GSM_ANALYSIS_SYNC_ERROR_MSG				"GSM Analysis: Sync detection error"
//#define GSM_ANALYSIS_COLOR_CODE_ERROR_MSG		"GSM Analysis: Color-code detection error"
//#define GSM_ANALYSIS_UNDEFINED_ERROR_MSG		"GSM Analysis: Undefined error"


typedef struct {
	__int8			bProcTime;
	__int8			bBSIC;
	__int8			bCGI;
	__int8			bXCorr;
} SuGSMDebugSettings;



#define GSM_ANALYSIS_MAX_C2I		1000
#define GSM_ANALYSIS_DEFAULT_C2I	(1.0/GSM_ANALYSIS_MAX_C2I)

// TODO: move GSM_BCCH_TYPE into GsmTypes.h
// and also consider moving TDMA Frame Number, BSIC, CGI
typedef unsigned __int8 GSM_BCCH_DATA_TYPE[23];
enum GsmAnalysisMeasurementInfoMask
{
	SyncBurstDecoded		= 0x1,
	CGIDecoded				= 0x2,
	BcchBurstDecoded		= 0x4,
	Reserved_01				= 0x8000
};
typedef struct {
	// GSM channel parameters / metrics
	int         ChannelIndex;
	int         IFFreq;
	double      ChannelPower;
	// metrics determined during FCCH search
	int         FCCH_FreqIndex;
	int         FCCH_PeakFreq;
	double      FCCH_PeakPower;
	double      BandPow;
	double      SidePow;
	int         FCCH_Win;
	int         Sync_Win;
	// metrics from fcch/sync corr algorithm
	double      RMSCorrPower;
	double      NormSyncCorr;
	double		C_I_Ratio;
	int         SyncSampleNum;
	// parameters decoded if a strong sync is detected
	int					BSIC;
	int					TDMAFrameNumber;
	int					MCC;
	int					MNC;
	int					LAC;
	int					CellID;
	GSM_BCCH_DATA_TYPE	BcchOctets;
	// Shows information related to the processing of the measurement:
	// See the bit mask values defined in GsmAnalysisMeasurementInfoMask.
	// If the associated bit is set, the stated condition is true.
	unsigned __int16	MeasurementInfo;
}
GsmAnalysisDataType;

typedef struct _OutputNode {
   GsmAnalysisDataType	data;
   struct _OutputNode	*next;
} gsm_analysis_output_list;


#endif