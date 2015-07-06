// standard header files
#include <cstdlib>
#include <string.h>
#include <cmath>
#include <time.h>

#if defined _DEBUG
	#include <cstdio>
	#include <conio.h>
	#include <direct.h>
#endif

// my custom header files
#include "rf_phreaker/gsm_analysis/gsm_analysis_interface.h"
#include "rf_phreaker/gsm_analysis/netstart.h"
#include "rf_phreaker/gsm_analysis/ns_fcch.h"
#include "rf_phreaker/gsm_analysis/ns_sync.h"

// for performance measurement, declare clocks which will not be used in Release version
#ifdef _DEBUG
clock_t startTime, endTime;
double timeDiff;
#endif

//TODO: should data_offset be in GSMStruct?  or just set it to 0 and not use it?
// static int bGsmInitialized = 0;
//int data_offset = 0;


//*****************************************************************************
// Release memory allocated as array of arrays,
// i.e. ffts and pwr spectrum windows
//*****************************************************************************
void mem_cleanup( int num_windows, DATASTRUCT **windows ) {
	int i;

	if( windows != NULL ) {
		// free the actual windows
		for( i = 0; i < num_windows; i++ ) {
			if( windows[i] != NULL ) {
				FREETYPE( windows[i] );
				windows[i] = NULL;
			}
		}
		// free the index array
		free( windows );
		windows = NULL;
	}
}

/*****************************************************************************
*
* mem_cleanup_gsm()
*
* Function to clean-up memory allocated for the GSMStruct.
****************************************************************************/
void mem_cleanup_gsm( GSMStruct *s ) {
   int i;

	// fft_windows
	if( s->fft_windows != NULL ) {
		for( i = 0; i < s->num_windows; i++ ) {
			if( s->fft_windows[i] != NULL ) {
				FREETYPE( s->fft_windows[i] );
				s->fft_windows[i] = NULL;
			}
		}
		free( s->fft_windows );
		s->fft_windows = NULL;
	}

	// ps_windows
	if( s->ps_windows != NULL ) {
		for( i = 0; i < s->num_windows; i++ ) {
			if( s->ps_windows[i] != NULL ) {
				FREETYPE( s->ps_windows[i] );
				s->ps_windows[i] = NULL;
			}
		}
		free( s->ps_windows );
		s->ps_windows = NULL;
	}

	if ( s->avg_ps != NULL )
	{
		FREETYPE( s->avg_ps );
		s->avg_ps = NULL;
	}

	if ( s->data != NULL )
	{
		FREETYPE( s->data );
		s->data = NULL;
	}

	if ( s->fcch_s.searchwin != NULL )
	{
		free( s->fcch_s.searchwin );
		s->fcch_s.searchwin = NULL;
	}

	delete s->sync_processor;
	s->sync_processor = NULL;
//	mem_cleanup_sync( &s->sync_s.mem );

	return;
} // end of mem_cleanup_gsm()

//*****************************************************************************
// Allocate memory to be created as array of arrays,
// i.e. ffts and pwr spectrum windows
//*****************************************************************************
DATASTRUCT** create_windows( int num_windows, int window_size )
{
	DATASTRUCT **windows;
	int i;

	// create the index array for the new windows
	windows = reinterpret_cast<DATASTRUCT**>( calloc(num_windows, sizeof(DATASTRUCT *)) );
	if ( windows == NULL )
	{
		return( NULL );
	}

	// create space for the overlapping new windows
	for( i = 0; i < num_windows; i++ ) {
		if( (windows[i] = ALLOCSTRUCT( window_size )) == NULL )
		{
			mem_cleanup( num_windows, windows );
			return( NULL );
		}
	}
	return( windows );
}


//*****************************************************************************
// Create overlapping windows (for ffts) and apply a windowing function
// 28 Jan 2008: Use rectangular window, i.e. no window function applied
//*****************************************************************************
int ApplyWindowing( DATASTRUCT *data, int datasize,
	DATASTRUCT** windows, int window_size,
	int num_windows, int step_size )
{
	int i, WinStart;

	// make sure the window list exists
	if( windows == NULL ) {
		// windows must be pre-allocated
		return(0);
	}

	// copy the original data into the overlapping windows
	// and apply the windowing function
//	WinStart = data_offset;
	WinStart = (int)ceil(DATA_OFFSET_GSMBITS * 4/*s->nspb*/);
	WinStart = (int)(window_size * 1.5f);
	for( i = 0; i < num_windows; i++ ) {
		// make sure the data doesn't go out of bounds
		if( WinStart + window_size > datasize ) break;

		// make sure the current window exists
		if( windows[i] == NULL ) {
			// windows must be pre-allocated
			return(0);
		}
		// window the data
		// Rectangular window means no window function needed
		//VECTMULT( WinCoeffs, &data[WinStart], windows[i], window_size );

		// Copy memory into separate windows
		memcpy(windows[i], &data[WinStart], window_size * sizeof(DATASTRUCT));
		WinStart += step_size;
	}
	return(i);
}


//*****************************************************************************
// Main processing entry point.  Three step process:
//		- Get FFTs (or DFTs) and power spectrum of all windows
//		- Call the FCCH analysis routine
//		- Call the SYNC analysis routine
//*****************************************************************************
int gsm_analysis( GSMStruct *s ) {

	int i, j;
	double blocksize;
	int datasize;
	unsigned int num_windows;
	int window_offset;
	int time_size;
	unsigned int fft_size;
	int ps_size;
	int fs;

	// data from original WCTS data file
	short *filedata;

	// data converted to float/double
	DATASTRUCT *data = NULL;
	// Windowed data/FFT's
	DATASTRUCT **fft_windows = NULL;
	// Power spectrum of the FFT's
	DATATYPE **ps_windows = NULL;
	DATATYPE *avg_ps = NULL;

	// Added 13 May 2008 for the purpose of subtracting the DC component
	// TODO:: remove this if/when the DC issue is solved
	DATASTRUCT AvgDC;

//#if LOTSAFILES > 0
//   char outname[ 100 ];
//#endif
	DATATYPE fcch_th2;
	DATATYPE fcch_th3;

	enum GsmAnalysisError errFlag;

	errFlag = GSM_UNDEFINED_ERROR;

	// If s==NULL or if memory has not been allocated (fftwindows, avgps, etc.),
	// we should get an Access Violation exception.

	// copy variables from input structure
	blocksize = s->blocksize;
	datasize = s->datasize;
	time_size = s->time_size;
	fft_size = s->fft_size;
	ps_size = s->ps_size;
	fs = s->fs;
	fcch_th2 = s->fcch_th2;
	fcch_th3 = s->fcch_th3;
	window_offset = s->window_offset;
	num_windows = s->num_windows;

	fft_windows = s->fft_windows;
	ps_windows = s->ps_windows;
	avg_ps = s->avg_ps;
	filedata = s->filedata;
	data = s->data;

	// subtract out the DC component to aid in processing
	//TODO: remove this subtraction when/if the "DC problem" is solved

	// convert the file data to real and complex formats
	// in preparation for correlations
	// TODO: use ippCopy to do this

	// "filedata[]" is short int data (*short).  If this pointer exists,
	// then we convert the filedata[] to Ipp32fc and subtract the DC.
	// Otherwise, the IQ data is already in data[] with DC subtracted,
	// and we just use that directly.
	if ( filedata != NULL )
	{
		AvgDC.re = AvgDC.im = 0;
	#ifdef _DEBUG
		startTime = clock();
		for( i=0, j=0; i < s->datasize; i++, j++ ) {
			data[i].re = (DATATYPE)filedata[j++];
			data[i].im = (DATATYPE)filedata[j];
			AvgDC.re += data[i].re;
			AvgDC.im += data[i].im;
		}
		endTime = clock();
		timeDiff = (double)(endTime - startTime)/CLK_TCK;
	#else
		for( i=0, j=0; i < s->datasize; i++, j++ ) {
			data[i].re = (DATATYPE)filedata[j++];
			data[i].im = (DATATYPE)filedata[j];
			AvgDC.re += data[i].re;
			AvgDC.im += data[i].im;
		}
	#endif

		AvgDC.re /= s->datasize;
		AvgDC.im /= s->datasize;
		ippsSubC_32fc_I(AvgDC, data, s->datasize);
	}


	// Divide the data in windows in preparation for FFT's
#ifdef _DEBUG
	startTime = clock();
	num_windows = ApplyWindowing(
		data, s->datalength,
		fft_windows, fft_size,
		num_windows, window_offset);
	endTime = clock();
	timeDiff = (double)(startTime - endTime)/CLK_TCK;
#else
	num_windows = ApplyWindowing(
		data, datasize,
		fft_windows, fft_size,
		num_windows, window_offset);
#endif
	if ( num_windows <= 0 ) return(GSM_ANALYSIS_WIN_ALLOC_ERROR);

//#if LOTSAFILES > 0
//	// write file data out for testing
//	fnwrite( data, sizeof(DATATYPE), datasize, "c_data.bin" );
//	write_mat( "time_windows.mat", fft_windows, 0, fft_size, num_windows );
//#endif

	// take the fft of each window
#ifdef _DEBUG
	startTime = clock();
	fft( num_windows, fft_size, fft_windows );
	endTime = clock();
	timeDiff = (double)(startTime - endTime)/CLK_TCK;
#else
	fft( num_windows, fft_size, fft_windows );
#endif

//#if LOTSAFILES > 0
//	for( i = 0; i < num_windows; i++ ) {
//		sprintf( outname, "fft_window_%d.bin", i );
//		fnwrite( fft_windows[i], sizeof(DATASTRUCT), fft_size/2, outname );
//	}
//	write_mat( "fft_windows.mat", fft_windows, 1, fft_size/2, num_windows );
//#endif

	// calculate the power spectrum
#ifdef _DEBUG
	startTime = clock();
	if ( power_spectrum2( num_windows, ps_size, fft_windows, ps_windows ) != 0 )
		return GSM_UNDEFINED_ERROR;
	endTime = clock();
	timeDiff = (double)(startTime - endTime)/CLK_TCK;
#else
	if ( power_spectrum2( num_windows, ps_size, fft_windows, ps_windows ) != 0 )
		return GSM_UNDEFINED_ERROR;
#endif
   
//#if LOTSAFILES > 0
//	write_mat( "ps_windows.mat", ps_windows, 0, ps_size, num_windows );
//#endif

	// get averages for the power spectrum windows
	if ( power_spectrum_avg2( num_windows, ps_size, ps_windows, avg_ps ) != 0 )
		return GSM_UNDEFINED_ERROR;

//#if LOTSAFILES > 0
//	fnwrite( avg_ps, sizeof(DATATYPE), num_windows, "avg_ps.bin" );
//#endif

	// FCCH processing
	// Pass along the IFs that should be processed,
	// and set the actual number of fft windows as determined earlier during ApplyWindows
	s->fcch_s.NumFreqs = s->NumFreqs;
	s->fcch_s.Freq = s->FreqToProcess;
	s->fcch_s.num_windows = num_windows;
	s->fcch_s.fcch_th2 = s->fcch_th2;
	s->head_row = fcch( &s->fcch_s );
	errFlag = s->fcch_s.error;
	if( errFlag < 0 ) return (errFlag);
	// if the sync datasize is 0, that means we have previously set up gsm_processor
	// to not do any sync processing, i.e. use as a sweeper only.
	if ( s->sync_processor )
	{
		//s->sync_s.num_windows = num_windows;
		//s->sync_s.datasize = s->datalength;
		//s->sync_s.blocksize = s->blocksize;
		//s->sync_s.data = data;
		//s->sync_s.tb = s->tb;
		s->sync_processor->sync_analysis( s->data, s->datalength,
			s->fcch_th2, s->fcch_th3, s->ProcessBCCH, s->head_row );
	}

	return(errFlag);
}

/*****************************************************************************
*
* gsm_init()
*
* Initialize variables in the GSMStruct.  This should be called ONCE only.
/****************************************************************************/
int gsm_init( GSMStruct *s ) {

	int i;

	// If it appears that memory has already been allocated,
	// don't re-do the init.
	if ( s->fft_windows )
	{
		return (GSM_INIT_ALREADY_INITIALIZED);
	}

#if defined _DEBUG
	// Create directory for Debug files if needed
	if ( _chdir(".\\DebugFiles") == 0 )
	{
		if ( _chdir("..") != 0 ) return(GSM_DEBUG_FILES_DIRECTORY_ERROR);
	}
	else {
		if ( _mkdir("DebugFiles") != 0 ) return(GSM_DEBUG_FILES_DIRECTORY_ERROR);
	}
#endif

//	data_offset = (int)ceil(DATA_OFFSET_GSMBITS * s->nspb);
	unsigned int min_input_len = (int)ceil(MIN_INPUT_GSMBITS * s->nspb);
	if ( s->sync_s.sync_size == 0 )
	{
		min_input_len = s->datasize;
	}

	// TODO: re-do the logic on how all these are created
	s->window_offset = s->step_size;
//	s->num_windows = (int)ceil( (DATATYPE)(s->datalength-data_offset-s->fft_size) / s->window_offset );
	s->num_windows = (int)ceil( (DATATYPE)(min_input_len) / s->window_offset );

	// create_windows will call mem_cleanup_gsm() if there was an error
	s->fft_windows = create_windows( s->num_windows, s->fft_size + 1 );
	if ( s->fft_windows == NULL ) return (GSM_INIT_OUT_OF_MEMORY);


	// create the index array for the ps windows
	s->ps_windows = reinterpret_cast<DATATYPE **>(malloc( s->num_windows * sizeof( DATATYPE * ) ));
	if( s->ps_windows == NULL ) {
		mem_cleanup_gsm(s);
		return(GSM_INIT_OUT_OF_MEMORY);
	}

	// allocate the window space for the power spectrum
	for( i = 0; i < s->num_windows; i++ )
	{
		s->ps_windows[i] = ALLOCTYPE( s->ps_size  );
		if( s->ps_windows[i] == NULL ) {
			mem_cleanup_gsm(s);
			return(GSM_INIT_OUT_OF_MEMORY);
		}
	}

	// allocate memory for the power spectrum averages
	s->avg_ps = ALLOCTYPE( s->ps_size );
	if( s->avg_ps == NULL )
	{
		mem_cleanup_gsm(s);
		return(GSM_INIT_OUT_OF_MEMORY);
	}

	// allocate memory for the type converted file data
	s->data = ALLOCSTRUCT( s->datasize );
	if( s->data == NULL )
	{
		mem_cleanup_gsm(s);
		return(GSM_INIT_OUT_OF_MEMORY);
	}

	// initialize the FCCHStruct
	s->fcch_s.error = GSM_ANALYSIS_NO_ERROR;
	s->fcch_s.fs = s->fs;
	s->fcch_s.fft_size = s->fft_size;
	s->fcch_s.avg_ps = s->avg_ps;
	s->fcch_s.num_windows = s->num_windows;
	s->fcch_s.num_overlap = (float)s->blocksize / (float)s->window_offset;
	s->fcch_s.ps_windows = s->ps_windows;
	s->fcch_s.fcch_th1 = (float)pow(10,s->fcch_s.fcch_th1/10);
	s->fcch_s.fcch_th2 = s->fcch_th2;
	s->fcch_s.searchwin = reinterpret_cast<SearchType *>( malloc( sizeof( SearchType ) * s->num_windows) );
	if( s->fcch_s.searchwin == NULL ) {
		mem_cleanup_gsm(s);
		return(GSM_INIT_OUT_OF_MEMORY);
	}

	// initialize the SyncStruct
	if ( s->sync_s.sync_size != 0 )
	{
		s->sync_s.t = &(s->templates);
		s->sync_s.num_windows = s->num_windows;
		s->sync_s.step_size = s->step_size;
		s->sync_s.tb = s->tb;
		s->sync_s.fs = s->fs;
		s->sync_s.nspb = s->nspb;
		s->sync_s.data = s->data;
		s->sync_s.datasize = s->datalength;
		s->sync_s.window_offset = s->window_offset;
		s->sync_s.blocksize = s->blocksize;
		s->sync_s.window_size = s->fft_size;
//		s->sync_processor = new GsmSyncProcessor(s->templates, s->fs, s->upfac, s->downfac, s->blocksize, s->step_size);
		s->sync_processor = new GsmSyncProcessor(&(s->sync_s), s->upfac, s->downfac);
	}
	else
	{
		s->sync_processor = NULL;
	}

	return(GSM_ANALYSIS_NO_ERROR);
} // end of gsm_init()


