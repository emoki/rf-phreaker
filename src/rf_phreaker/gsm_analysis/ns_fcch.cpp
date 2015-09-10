#include <cstdlib>
#include <cmath>
#include "rf_phreaker/gsm_analysis/netstart.h"
#include "rf_phreaker/gsm_analysis/ns_fcch.h"


/* comparisons for qsort() */
int compare_peak( const void *arg1, const void *arg2 );
int compare_sidepow( const void *arg1, const void *arg2 );
int compare_bandpow( const void *arg1, const void *arg2 );



gsm_analysis_output_list* fcch( FCCHStruct *s ) {

	// Freq offset from GSM carrier center freq where we expect the FCCH to occur
	// Approximately 67.7kHz
	const float fcch_offset = GSM_FCCH_FREQ_OFFSET_HZ;

	unsigned int i, j;
	int k, pos, min, max, win;
	int min80, max80, min88, max88;
	int iFreqSearchBins, EliminatorSize;
	int IFFreqOffset;

	int row_count = 0;

	gsm_analysis_output_list *head = NULL;
	gsm_analysis_output_list *current_row = NULL;
	gsm_analysis_output_list *prev_row = NULL;

	unsigned int NumCarriers;
	DATATYPE highest_peak = 0;
	int peak_index = -1;

	DATATYPE fcch_th1;

	SearchType *searchwin;
	int window;
	unsigned int peak_count;
	unsigned int sidepow_count;

	DATATYPE sidepow, bandpow;
	DATATYPE mytmp;

	int sidepow_offset, sidebw, carrier_bw, AvgPow_bw;

	DATATYPE bin_size;
	int dup_offset80, dup_offset88;

	DATATYPE **ps_windows;
	DATATYPE *tmp_window;

	int carrier_freqs[NUMCARRIERFREQS];
	int carrier_bins[NUMCARRIERFREQS];
	int fcch_bins[NUMCARRIERFREQS];


	/*************** FCCH detection ********************/
	// reset the error indicator
	s->error = GSM_ANALYSIS_NO_ERROR;

	searchwin = s->searchwin;

	// TODO: put these into an init function
	// because they will be constant within one application instance
	// Or maybe we can init during gsm_init()
	// and/or also as static const
	bin_size = (DATATYPE)s->fs / (s->fft_size);
	sidepow_offset = (int)ceil(SIDE_OFFSET / bin_size) + 1;
	sidebw = (int)ceil( SIDE_BW / bin_size );
	carrier_bw = (int)ceil( CARRIER_BW / bin_size );
	AvgPow_bw = (int)ceil( AVG_POWER_BW / bin_size );
	dup_offset80 = (int)ROUND(s->num_overlap * 80);
	dup_offset88 = (int)ROUND(s->num_overlap * 88);
	EliminatorSize = (int) ROUND( s->num_overlap/2.f );
	iFreqSearchBins = (int) (ceil(RF_PHREAKER_MAX_FREQ_OFFSET/bin_size));

	// TODO: delete freq_offset when the function is fully integrated
	IFFreqOffset = s->NumFreqs;
	s->NumFreqs = 0;

	// calculate the carrier frequencies at IF
	for (i=0; i<s->NumFreqs; i++) {
		if ( s->Freq[i] == 0 ) break;
	}
	NumCarriers = i;
	if ( (NumCarriers == 0) || (NumCarriers > NUMCARRIERFREQS) ) {
		NumCarriers = NUMCARRIERFREQS;
		for( i=0; i<NumCarriers; i++ ) {
			// TODO: figure out what the LOWEST IF freq offset is
			// It is 1.8MHz, assuming IF Offset is between 0->175 kHz.
			// Note that the "0th" carrier_freq is the LOWEST freq, i.e.
			// the one that is at the most negative IF
			carrier_freqs[i] = (i * 200000) + IF_FREQ + RF_PHREAKER_LOWEST_IF + IFFreqOffset;
//			carrier_freqs[i] = (i * GSM_CHANNEL_SPACING_HZ) + IF_FREQ + RF_PHREAKER_LOWEST_IF + GSM_IF_OFFSET;
		}
	}
	else {
		//TODO: should never get here ... yet (i.e. until we re-instate freq selection)
		NumCarriers = 0;
		//for( i=0; i<NumCarriers; i++ ) {
		//	carrier_freqs[i] = (s->Freq[i]);
		//}
		// TODO: system which allows us to only process desired freqs
		// set undesired freqs to something out of range as below
		// carrier_freqs[i] = RF_PHREAKER_LOWEST_IF - GSM_CHANNEL_SPACING_HZ;
	}
	
	// find the fft bins that correspond to the carrier freqs
	// Note that freqTODO: does freq = PI correspond to carrier at +PI or -PI?
	// Dhaval Dave:  I THINK it's -PI, because then there would be fft_size/2
	// positive freq samples, and also fft_size/2 negative freq samples (I include
	// freq = 0 as a positive freq, and freq=PI => freq_bin = fft_size/2).
	for( i = 0; i < NumCarriers; i++ ) {
		carrier_bins[i] = ROUND( (float)carrier_freqs[i] / bin_size );
		fcch_bins[i] = ROUND( ((float)carrier_freqs[i]+fcch_offset)/bin_size);
		if ( carrier_bins[i] < 0 ) {
			carrier_bins[i] += s->fft_size;
			fcch_bins[i] += s->fft_size;
		}
	}

	// find strongest fcch peak in power spectrum
	ps_windows = s->ps_windows;
	for( i = 0; i < s->num_windows; i++ ) {
		tmp_window = ps_windows[i];
		for( j = 0; j < NumCarriers; j++ ) {
			// if the carrier_freq is out of bounds, it's because
			// we've set it that way to avoid processing it
			if ( carrier_freqs[j] < RF_PHREAKER_LOWEST_IF ) continue;
			min = fcch_bins[j] - iFreqSearchBins;
			max = fcch_bins[j] + iFreqSearchBins;
			for( pos = min; pos <= max; pos++ ) {
				if( tmp_window[ pos ] > highest_peak ) {
					peak_index = pos;
					highest_peak = tmp_window[ peak_index ];
				}
			} // end for pos
		} // end for carrier freqs
	} // end for windows

	// first fcch threshold, s->fcch_th1 dB lower than peak
	fcch_th1 = (DATATYPE)(highest_peak/s->fcch_th1);

	for( i = 0; i < NumCarriers; i++ )
	{
		// if the carrier_freq is out of bounds, it's because
		// we've set it that way to avoid processing it
		if ( carrier_freqs[i] < RF_PHREAKER_LOWEST_IF ) continue;

		// reset counters
		peak_count = 0;
		sidepow_count = 0;

		// clear old search window values
		for( j = 0; j < s->num_windows; j++ ) {
			searchwin[j].peak = 0.0;
			searchwin[j].sidepow_metric = -1.0;
			searchwin[j].bandpow_metric = -1.0;
			searchwin[j].pos = 0;
			searchwin[j].win = j;
		}

		// search for peaks around the fcch offset from the current carrier freq
		min = fcch_bins[i] - iFreqSearchBins;
		max = fcch_bins[i] + iFreqSearchBins;
		for( j = 0; j < s->num_windows; j++ ) {
			for( pos = min; pos <= max; pos++ ) {
				// keep the highest ps value in the search area
				if( searchwin[j].peak < s->ps_windows[j][pos] ) {
					searchwin[j].peak = s->ps_windows[j][pos];
					searchwin[j].pos = pos;
				}
			}
		}

		// sort searchwin in descending order of peaks
		qsort( (void *)searchwin, (size_t)s->num_windows, sizeof( SearchType ), compare_peak );

		// check at-most the 25 highest peaks
		for( j = 0; j < 25; j++ ) {
			// check the peak against the first threshold */
			if( searchwin[j].peak <= fcch_th1 ) {
				// did not pass.  all remaining peaks are lower than this one
				// so break out of the loop
				break;
			 }

			// compute sidepow (new method using dB)
			sidepow = 0;
			window = searchwin[j].win;
			max = searchwin[j].pos - sidepow_offset;
			min = max - sidebw;
			for( k = min; k <= max; k++ ) {
				sidepow += (float)log10(s->ps_windows[window][k]);
			} 
			min = searchwin[j].pos + sidepow_offset;
			max = min + sidebw;
			for( k = min; k <= max; k++ ) {
				sidepow += (float)log10(s->ps_windows[window][k]);
			}
			sidepow /= ((DATATYPE)2.0*(sidebw+1));

			// compute band power
			// To ensure that indexer 'k' >= 0, add fft_size to negative values
			bandpow = 0.0;
			min = carrier_bins[i] - carrier_bw;
			max = carrier_bins[i] + carrier_bw;
			for( k = min; k <= max; k++ ) {
				bandpow += s->ps_windows[window][(k+s->fft_size) % s->fft_size];
			} 
			bandpow /= (DATATYPE)((2*carrier_bw)+1.0);

			// sidepow metric: new metric in dB requires a subtraction
			// instead of division
			searchwin[j].sidepow_metric = (DATATYPE)log10(searchwin[j].peak) - sidepow;
			searchwin[j].bandpow_metric = searchwin[j].peak / bandpow;

			// check against fcch_th2
			if( searchwin[j].bandpow_metric <= s->fcch_th2 ) {
				// did not pass, skip to the next iteration of the for() loop
				continue;
			}
			sidepow_count++;
		} // end for j(0..25)

		// save number of peaks that passed the peak threshold
		peak_count = j;
      
		if( (peak_count == 0) || (sidepow_count == 0) ) {
			// nothing passed the sidepow threshold, so go to next carrier
			continue;
		}

		// sort peak_count elements of searchwin in descending order of bandpows
		qsort( (void *)searchwin, (size_t)peak_count, sizeof( SearchType ), compare_bandpow );


		// check the peaks that passed the threshold
		for( j = 0; j < sidepow_count; j++ ) {
			window = searchwin[j].win;
			if( window < 0 ) {
				// skip current window, as it has been eliminated
				continue;
			}

			// eliminate neighbors
			// Note that windows are eliminated by checking the peaks
			// that have a lower magnitude of bandpow than the current peak.
			// Then a "lower bandpow" peak is eliminated if it
			// falls inside the "kill zone".
			min80 = (window - dup_offset80);
			max80 = (window + dup_offset80);
			min88 = (window - dup_offset88);
			max88 = (window + dup_offset88);
			for( k = (int)j+1; k < (int)sidepow_count; k++ ) {
				win = searchwin[k].win;
				/* check if lower bandpow windows are adjacent or 80 bursts away */
				// Eliminate windows that are within +/- 1 GSM burst of the current window,
				// or within +/- 1 GSM burst of the window that is 80 bursts away from the current,
				// or within +/- 1 GSM burst of the window that is 88 bursts away from the current
				if( (win >= window - EliminatorSize) && (win <= window + EliminatorSize) )
				{
					// eliminate the window from future consideration
					searchwin[k].win = -1;
				}
			}

			// add a new output row
			if( (head = add_row( head )) == NULL ) {
				s->error = GSM_ANALYSIS_ADD_ROW_ERROR;
				return( head );
			}
			prev_row = current_row;
			if( (current_row = last_row( head )) == NULL ) {
				// SHOULD NEVER GET HERE!!!  IT'S IMPOSSIBLE!!!
				// TODO: do extensive testing to verify this is impossible; then delete.
				s->error = GSM_FCCH_UNDEFINED_ERROR;
				return( head );
			}
			row_count++;

			// store power of peak
			current_row->data.FCCH_PeakPower = 10*log10(searchwin[j].peak);
			// store freq index of fcch burst
			current_row->data.FCCH_FreqIndex = searchwin[j].pos;
			current_row->data.ChannelIndex = carrier_bins[i];

// Changed this part to report the theoretical frequencies, NOT
// the "actual" as determined by the fft bin.  Note the fft bin #
// method may be more inaccurate because of freq quantization, whereas
// we don't expect drift and doppler to account for much difference
			current_row->data.IFFreq = carrier_freqs[i];
//			ROUND( (searchwin[j].pos * bin_size) - fcch_offset );
			current_row->data.FCCH_PeakFreq = carrier_freqs[i]+ (int)(fcch_offset+0.5);

			// store carrier IF freq
			// store power in dB of carrier
			// To ensure that indexer 'k' >= 0, add fft_size to negative values
			min = carrier_bins[i] - AvgPow_bw;
			max = carrier_bins[i] + AvgPow_bw;
			mytmp = 0;
			for( k = min; k <= max; k++ ) {
				mytmp += s->avg_ps[(k+s->fft_size) % s->fft_size];
			}
			//mytmp /= (2 * AvgPow_bw + 1);
			mytmp = (Ipp32f)(mytmp / pow(s->fft_size, 2.0));
			current_row->data.ChannelPower = mytmp;

			// store time block where found
			current_row->data.FCCH_Win = window;

			// SYNC window = FCCH window + 8 bursts
			current_row->data.Sync_Win = window + (int)(8.f*s->num_overlap);
			current_row->data.BandPow = searchwin[j].bandpow_metric;
			current_row->data.SidePow = 10 * searchwin[j].sidepow_metric;

		} //end of sidepow count for() loop
	} // end of carrier freq for() loop
	return( head );
}


//************************************************************************
// comparison test for sorting peaks in _reverse_ order
int compare_peak( const void *arg1, const void *arg2 )
{
	if( ((SearchType *)arg2)->peak > ((SearchType *)arg1)->peak )
		return 1;
	else if( ((SearchType *)arg2)->peak < ((SearchType *)arg1)->peak )
		return -1;
	else return 0;
}


//*************************************************************************
// comparison test for sorting sidepow metrics in _reverse_ order
int compare_sidepow( const void *arg1, const void *arg2 )
{
	if( ((SearchType *)arg2)->sidepow_metric > ((SearchType *)arg1)->sidepow_metric )
		return 1;
	else if( ((SearchType *)arg2)->sidepow_metric < ((SearchType *)arg1)->sidepow_metric )
		return -1;
	else return 0;
}



//**************************************************************************
// comparison test for sorting bandpow metrics in _reverse_ order
int compare_bandpow( const void *arg1, const void *arg2 ) {
	if( ((SearchType *)arg2)->bandpow_metric > ((SearchType *)arg1)->bandpow_metric )
		return 1;
	else if( ((SearchType *)arg2)->bandpow_metric < ((SearchType *)arg1)->bandpow_metric )
		return -1;
	else return 0;
}
