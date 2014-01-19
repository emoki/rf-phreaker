#ifndef __VARTYPEDEFS_H__
#define __VARTYPEDEFS_H__

#include <stdint.h>

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

typedef uint32_t CID_TYPE;

typedef uint16_t SYSTEMFRAMENUMBERTYPE;

typedef uint32_t FREQHZTYPE;
typedef uint8_t ARFCNBANDTYPE;
typedef uint16_t ARFCNTYPE;

typedef uint32_t DASGROUPCODETYPE;

typedef uint16_t EARFCNTYPE;
typedef uint16_t CELLIDTYPE;
typedef uint16_t PHYSICALCELLIDTYPE;
typedef double CORRELATIONTYPE;
typedef double FRAMEBOUNDRYTYPE;
typedef uint8_t PSCHIDTYPE;
typedef uint8_t SSCHIDTYPE;
enum CYCLICPREFIX
{
	Normal = 1,
	Extended = 2
};
typedef uint32_t CARRIERBANDWIDTHTYPE;
typedef uint16_t DELAYSPREADTYPE;
typedef uint16_t SUBCARRIERSPACING;

typedef float LATITUDETYPE;
typedef float LONGITUDETYPE;
typedef uint16_t HWIDTYPE;
typedef uint32_t RECORDNUMTYPE;
typedef uint16_t UARFCNTYPE;
typedef float CARRIERFREQTYPE;
typedef float CARRIERSLTYPE;
typedef uint64_t MICROFRAMESRXTYPE;
typedef uint64_t CHIPSRXTYPE;
typedef float PSCH_ECIOTYPE;
typedef uint16_t CPICHTYPE;
typedef int8_t CPICH_RSCPTYPE;
typedef float CPICH_ECIOTYPE;
typedef bool STTDTYPE;
typedef uint16_t MCCTYPE;
typedef uint16_t MNCTYPE;
typedef uint16_t LACTYPE;
typedef uint16_t CELLIDTYPE;
typedef uint32_t LTE_CELLIDTYPE;
typedef uint32_t FLAGTYPE;
typedef uint32_t MCCSTRUCT;
typedef uint32_t MNCSTRUCT;
typedef float ECIOTYPE;

typedef uint64_t TIMESINCE1970TYPE;
typedef uint16_t NUMFREQBINSTYPE;
typedef uint32_t FREQSTEPSIZEHZTYPE;
typedef uint32_t FREQBINSIZEHZTYPE;
typedef uint32_t FREQTYPEHZ;

typedef uint16_t BCCHTYPE;
typedef uint8_t BSICTYPE;
typedef uint32_t TDMAFRAMENUMTYPE;
typedef uint64_t FREQUENCYHZTYPE;
typedef int64_t TIMESINCE1970;  // compatible with time_t


typedef uint8_t HEADERTYPE;
typedef uint8_t SUBCOMMAND;
typedef uint8_t PLLINTTYPE;
typedef uint8_t PLLFRACTTYPE;
typedef uint16_t GAINTYPE;
typedef uint8_t RFBANDTYPE;
typedef uint8_t RFOSCBANDTYPE;
typedef uint8_t RFSTATUSTYPE;
typedef uint8_t DIGITALSTATUSTYPE;
typedef uint32_t RECORDSIZETYPE;
typedef uint8_t BUFFERTYPE;

typedef uint8_t FPGAREVISIONTYPE;
typedef int64_t LASTDELTATIMETYPE;
typedef uint64_t LONGCOUNTERLATCHEDTYPE;
typedef uint16_t GPSSTATUSTYPE;
typedef uint8_t TRACKSATTYPE;
typedef uint8_t VISIBLESATTYPE;
typedef uint16_t HEADINGTYPE;
typedef float SPEEDTYPE;
typedef uint32_t HEIGHTTYPE;
typedef float LONGITUDETYPE;
typedef float LATITUDETYPE;
typedef uint8_t SECONDSTYPE;
typedef uint8_t MINUTESTYPE;
typedef uint8_t HOURSTYPE;
typedef uint16_t YEARTYPE;
typedef uint8_t DAYTYPE;
typedef uint8_t MONTHTYPE;
typedef int16_t IQDATA;

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
