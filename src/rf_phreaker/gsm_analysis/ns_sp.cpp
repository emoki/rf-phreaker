#include <cstdio>
#include <cstdlib>
#include <cmath>
#include "rf_phreaker/gsm_analysis/netstart.h"


static DATATYPE MagArray[65536];
static unsigned int MagArrLen = sizeof(MagArray)/sizeof(MagArray[0]);


DATATYPE AvgRMS( DATASTRUCT *data, unsigned int length )
{
	DATATYPE norm_factor;

	if( data == NULL ) return -1;
	if ( length > MagArrLen ) return -2;

	// get the mean of the magnitude of the array
	POWERSPECTR( data, MagArray, length );
	MEAN( MagArray, length, &norm_factor, ippAlgHintAccurate );
	ippsSqrt_32f_I( &norm_factor, 1 );

	return norm_factor;
} // end of AvgRMS()



/*****************************************************************************
*
* normalizeRMS()
*
* Function to normalize an array of DATASTRUCT elements by the value of
* the average magnitude of the elements of the array.
******************************************************************************/
DATATYPE normalizeRMS( DATASTRUCT *data, unsigned int length )
{
	DATATYPE norm_factor;
	const DATASTRUCT ZeroOffset = {0,0};

	if( data == NULL ) {
		return -1;
	}

	if ( length > MagArrLen ) return -2;

	// get the mean of the magnitude of the array
	POWERSPECTR( data, MagArray, length );
	MEAN( MagArray, length, &norm_factor, ippAlgHintAccurate );
	ippsSqrt_32f_I( &norm_factor, 1 );
	if( norm_factor == 0.0 ) {
		norm_factor = 1.0;
		return -3;
	}

	// normalize each element by this factor
	NORMALIZE( data, data, length, ZeroOffset, norm_factor );

	return norm_factor;
} // end of normalizeRMS()


void normalizeEach( DATASTRUCT *data, unsigned int length )
{
	unsigned int i;

	if( (data == NULL) || (length <= 0) ) return;

	// TODO: set up to re-allocate MagArray if needed
	if ( length > MagArrLen ) return;
	//MagArray = calloc( length, sizeof( DATATYPE ) );
	//if (MagArray != NULL) {
	//	// get the magnitude of each element

	MAG( data, MagArray, length );

	// Normalize each record to a magnitude of 1
	for ( i=0; i<length; i++ ) {
		if ( MagArray[i] != 0 ) {
			REALPART( data[i] ) /= MagArray[i];
			IMAGPART( data[i] ) /= MagArray[i];
		}
	}
	return;
} // end of normalizeEach()


/*****************************************************************************/
/*
* fft()
*
* Function to take the fft of the time windows.
*/
// TODO: check return values when calling FFT functions
// also allow debug ONLY in DEBUG build
void fft( unsigned int num_windows, unsigned int win_size, DATASTRUCT **windows )
{
	if ( !win_size ) throw GSM_UNDEFINED_ERROR;

	IppsFFTSpec_C_32fc *gsmFFTSpec;

	unsigned int order = (int)ceil( (log((float)win_size) / log(2.f)) );
	if ( ippsFFTInitAlloc_C_32fc(&gsmFFTSpec, order, IPP_FFT_NODIV_BY_ANY, ippAlgHintAccurate) != ippStsNoErr )
		throw GSM_UNDEFINED_ERROR;

	for( unsigned int i = 0; i < num_windows; i++ ) {
		// TODO:: use external work buffer in stead of NULL as parm3
		FFT( windows[i], gsmFFTSpec, NULL );
#if FFTVERBOSE > 0
		char OutFileName[] = "DebugFiles\\FFT_WIN_0000.bin";
		//position of "0000" part of filename
		char *FileNumPos = strstr(OutFileName, "0000");
		sprintf(FileNumPos, "%04i.bin", i);
		fnwrite(windows[i], sizeof(DATASTRUCT), win_size, OutFileName);
#endif
	}
	ippsFFTFree_C_32fc(gsmFFTSpec);
} // end of fft()


/*****************************************************************************/
/*
* dft()
*
* Function to take the dft of the time windows.
* This should be used instead of fft() if the order is not
* an integer power of 2.
*/
//void dft( int num_windows, int win_size, void **windows ) {
//   int i;
//   int order;
//   
//   order = (int)ceil( win_size );
//   
//   /* initialize twiddle tables */
//   DFT( NULL, NULL, order, NSP_Init );
//   
//   /* now perform the actual fft */
//   for( i = 0; i < num_windows; i++ ) {
//      DFT( (windows[i]), windows[i], order, NSP_Forw );
//   }
//   
//   /* clear twiddle tables */
//   DFT( NULL, NULL, order, NSP_Free );
//
//   return;
//} /* end of dft() */


///*****************************************************************************/
//
///*
//* power_spectrum()
//*
//* Function to calculate the power spectrum of the fft windows.
//* Allocates memory for the power spectrum windows.
//*/
//DATATYPE** power_spectrum( int num_windows, int ps_size, DATASTRUCT **fft_windows ) {
//   DATATYPE **ps_windows;
//   int i;
//   
//	// create the index array for the ps windows
//	if( (ps_windows = calloc( num_windows, sizeof( DATATYPE * ) )) == NULL )
//	{
//		return(NULL);
//	}
//   
//	// allocate the window space for the power spectrum
//	for( i = 0; i < num_windows; i++ ) {
//		if( (ps_windows[i] = calloc( ps_size, sizeof(DATATYPE) )) == NULL )
//		{
//			return(NULL);
//		}
//	}
//   
//	// get the power spectrum for each window
//	for( i = 0; i < num_windows; i++ )
//	{
//		POWERSPECTR( fft_windows[i], ps_windows[i], ps_size );
//	}
//   
//	return( ps_windows );
//} // end of power_spectrum() */

/*****************************************************************************/

/*
* power_spectrum2()
*
* Function to calculate the power spectrum of the fft windows.
* Does NOT allocate space for the power spectrum windows.
*/
int power_spectrum2( int num_windows, int ps_size,
	DATASTRUCT **fft_windows, DATATYPE **ps_windows )
{
	int i;

	// expect ps_windows index array to exist
	if( ps_windows == NULL )
	{
		return -1;
	}
   
	// get the power spectrum for each window
	for( i = 0; i < num_windows; i++ ) {
		// expect ps_windows[i] to already exist
		if( ps_windows[i] == NULL )
		{
			return -2;
		}
		// calculate the power spectrum of the current window
		POWERSPECTR( fft_windows[i], ps_windows[i], ps_size );
	}   
   return 0;
} // end of power_spectrum2()

/*
* power_spectrum_avg2()
*
* Function to calculate the average power spectrum across all
* power spectrum windows.
* Does NOT allocate memory for the average power spectrum data.
*/
int power_spectrum_avg2( int num_windows, int ps_size,
	DATATYPE** ps_windows, DATATYPE *avg_ps )
{
	double tmp;
	int i, j;
   
	// expect avg_ps index array to exist
	if( avg_ps == NULL )
	{
		return -1;
	}

	// take average power spectrum for each bin
	for( i = 0; i < ps_size; i++ )
	{
		tmp = 0.0;
		// sum the bins
		for( j = 0; j < num_windows; j++ )
		{
			tmp += (double)ps_windows[j][i];
		}
		// take the average of each bin
		avg_ps[i] = (DATATYPE)(tmp / num_windows);
	}
	return 0;
} // end of power_spectrum_avg2()

void DownCvtToBaseband(const DATASTRUCT *In, DATASTRUCT *Out,
					   unsigned int Len, unsigned int SampFreq, int FreqShift)
{
// TODO: make pi a function of atan or acos
	const double pi = 3.1415926535;

	unsigned int i;
	double w0, w, w_delta;
	DATATYPE cosw, sinw;

	w0 = 2.0 * pi * (double)(-FreqShift);
	w_delta = w0 / (double)SampFreq;

	for ( i = 0, w=0.0; i < Len; i++, w+=w_delta )
	{
		cosw = (DATATYPE)cos(w);
		sinw = (DATATYPE)sin(w);
		REALPART(Out[i]) = REALPART(In[i]) * (DATATYPE)cos(w)
			- IMAGPART(In[i]) * (DATATYPE)sin(w);
		IMAGPART(Out[i]) = REALPART(In[i]) * (DATATYPE)sin(w)
			+ IMAGPART(In[i]) * (DATATYPE)cos(w);
	}
}


/*****************************************************************************/
/*
* d2f()
*
* Function to convert an array from doubles to floats.
* Necessary if doing fft's in floats instead of doubles.
*/
//void d2f( double *d, float *f, int length ) {
//   int i;
//
//   /* visit each element */
//   for( i = 0; i < length; i++ ) {
//      f[i] = (float)d[i];
//   }
//
//   return;
//} /* end of d2f() */
