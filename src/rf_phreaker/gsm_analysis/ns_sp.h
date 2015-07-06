
int decimate_vector( DATASTRUCT *src, int src_len, DATASTRUCT *dst, int dst_len,
                    int factor );
int decimate( TemplateType *src, TemplateType *dst, int factor );
DATATYPE AvgRMS( DATASTRUCT *data, unsigned int length );
DATATYPE normalizeRMS( DATASTRUCT *data, unsigned int length );
void normalizeEach( DATASTRUCT *data, unsigned int length );

void fft( unsigned int num_windows, unsigned int win_size, DATASTRUCT **windows );

int power_spectrum2( int num_windows, int ps_size, DATASTRUCT **fft_windows,
                     DATATYPE **ps_windows );
int power_spectrum_avg2( int num_windows, int ps_size, DATATYPE** ps_windows,
                         DATATYPE *avg_ps );

// Functions to downconvert WIND Catcher Recorder data to baseband
// Can specify a specific lowpass filter to use, or don't specify
// to use the internally generated LPF as we pre-determined (based on known sample rate)
//void DownCvtToBaseband(const DATASTRUCT *In, DATASTRUCT *Out, unsigned int Len,
//					   unsigned int SampFreq, int FreqShift,
//					   const DATATYPE *LPFtaps, int LPFLen);
void DownCvtToBaseband(const DATASTRUCT *In, DATASTRUCT *Out, unsigned int Len,
					   unsigned int SampFreq, int FreqShift);
