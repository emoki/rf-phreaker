#if !defined _NS_FCCH_H
#define _NS_FCCH_H


// TODO: total num freqs is ... ?18-ish?
#define NUMCARRIERFREQS 19


typedef struct _SearchType {
   DATATYPE     peak;
   DATATYPE     sidepow_metric;
   DATATYPE     bandpow_metric;
   int          pos;
   int          win;
} SearchType;

typedef struct _FCCHStruct {
   GsmAnalysisError		error;
   int					fs;
   int					fft_size;
   DATATYPE				*avg_ps;
   unsigned int         num_windows;
   float				num_overlap;
   DATATYPE				**ps_windows;
   DATATYPE				fcch_th1;
   DATATYPE				fcch_th2;
   SearchType			*searchwin;
   unsigned int			NumFreqs;
   unsigned int			*Freq;
} FCCHStruct;


gsm_analysis_output_list* fcch( FCCHStruct *data );

#endif
