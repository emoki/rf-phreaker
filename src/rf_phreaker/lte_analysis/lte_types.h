#ifndef __VARTYPEDEFS_H__
#define __VARTYPEDEFS_H__

// Status flags
#define GPSNOTLOCKED 0x01
#define DEADRECKONINGPRESENT 0x02
#define EXTERNALGPSLOCKED 0x04

#define NOT_DECODED_16 (0xFFFF)
#define NOT_DECODED_32 (0xFFFFFFFF)

#define MCC_NOT_DECODED NOT_DECODED_16
#define MNC_NOT_DECODED NOT_DECODED_16
#define LAC_NOT_DECODED NOT_DECODED_16
#define CID_NOT_DECODED NOT_DECODED_32
#define SYSTEM_FRAME_NOT_DECODED NOT_DECODED_16

typedef unsigned __int32 CID_TYPE;

typedef unsigned __int16 SYSTEMFRAMENUMBERTYPE;

typedef unsigned __int32 FREQHZTYPE;
typedef unsigned __int8 ARFCNBANDTYPE;
typedef unsigned __int16 ARFCNTYPE; 

typedef unsigned __int32 DASGROUPCODETYPE;

typedef unsigned __int16 EARFCNTYPE;
typedef unsigned __int16 CELLIDTYPE;
typedef unsigned __int16 PHYSICALCELLIDTYPE;
typedef double CORRELATIONTYPE;
typedef double FRAMEBOUNDRYTYPE;
typedef unsigned __int8 PSCHIDTYPE;
typedef unsigned __int8 SSCHIDTYPE;
enum CYCLICPREFIX
{
	Normal = 1,
	Extended = 2
};
typedef unsigned __int32 CARRIERBANDWIDTHTYPE;
typedef unsigned __int16 DELAYSPREADTYPE;
typedef unsigned __int16 SUBCARRIERSPACING;

typedef float LATITUDETYPE;
typedef float LONGITUDETYPE;
typedef unsigned __int16 HWIDTYPE;
typedef unsigned __int32 RECORDNUMTYPE;
typedef unsigned __int16 UARFCNTYPE;
typedef float CARRIERFREQTYPE;
typedef float CARRIERSLTYPE;
typedef unsigned __int64 MICROFRAMESRXTYPE;
typedef unsigned __int64 CHIPSRXTYPE;
typedef float PSCH_ECIOTYPE;
typedef unsigned __int16 CPICHTYPE;
typedef __int8 CPICH_RSCPTYPE;
typedef float CPICH_ECIOTYPE;
typedef bool STTDTYPE;
typedef unsigned __int16 MCCTYPE;
typedef unsigned __int16 MNCTYPE;
typedef unsigned __int16 LACTYPE;
typedef unsigned __int16 CELLIDTYPE;
typedef unsigned __int32 LTE_CELLIDTYPE;
typedef unsigned __int32 FLAGTYPE;
typedef unsigned __int32 MCCSTRUCT;
typedef unsigned __int32 MNCSTRUCT;
typedef float ECIOTYPE;

typedef unsigned __int64 TIMESINCE1970TYPE;
typedef unsigned __int16 NUMFREQBINSTYPE;
typedef unsigned __int32 FREQSTEPSIZEHZTYPE;
typedef unsigned __int32 FREQBINSIZEHZTYPE;
typedef unsigned __int32 FREQTYPEHZ;

typedef unsigned __int16 BCCHTYPE;
typedef unsigned __int8 BSICTYPE;
typedef unsigned __int32 TDMAFRAMENUMTYPE;
typedef unsigned __int64 FREQUENCYHZTYPE;
typedef __int64 TIMESINCE1970;  // compatible with time_t


typedef unsigned __int8 HEADERTYPE;
typedef unsigned __int8 SUBCOMMAND;
typedef unsigned __int8 PLLINTTYPE;
typedef unsigned __int8 PLLFRACTTYPE;
typedef unsigned __int16 GAINTYPE;
typedef unsigned __int8 RFBANDTYPE;
typedef unsigned __int8 RFOSCBANDTYPE;
typedef unsigned __int8 RFSTATUSTYPE;
typedef unsigned __int8 DIGITALSTATUSTYPE;
typedef unsigned __int32 RECORDSIZETYPE;
typedef unsigned __int8 BUFFERTYPE;

typedef unsigned __int8 FPGAREVISIONTYPE;
typedef __int64 LASTDELTATIMETYPE;
typedef unsigned __int64 LONGCOUNTERLATCHEDTYPE;
typedef unsigned __int16 GPSSTATUSTYPE;
typedef unsigned __int8 TRACKSATTYPE;
typedef unsigned __int8 VISIBLESATTYPE;
typedef unsigned __int16 HEADINGTYPE;
typedef float SPEEDTYPE;
typedef unsigned __int32 HEIGHTTYPE;
typedef float LONGITUDETYPE;
typedef float LATITUDETYPE;
typedef unsigned __int8 SECONDSTYPE;
typedef unsigned __int8 MINUTESTYPE;
typedef unsigned __int8 HOURSTYPE;
typedef unsigned __int16 YEARTYPE;
typedef unsigned __int8 DAYTYPE;
typedef unsigned __int8 MONTHTYPE;
typedef __int16 IQDATA;

struct DATASAMPLE
{
	IQDATA I;
	IQDATA Q;
};

struct ComplexFloat
{
	float re;
	float im;
};


#endif