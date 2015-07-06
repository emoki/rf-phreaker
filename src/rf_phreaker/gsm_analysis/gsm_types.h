#ifndef _GSM_TYPES_H
#define _GSM_TYPES_H

#include <cmath>

typedef unsigned __int16	GSM_MCC_Type;
typedef unsigned __int16	GSM_MNC_Type;
typedef unsigned __int16	GSM_LAC_Type;
typedef unsigned __int16	GSM_CellID_Type;
typedef unsigned __int16	GSM_BCCH_Type;
typedef unsigned __int8		GSM_BSIC_Type;


typedef __int32 _GSM_FN_Type;
typedef double _GSM_FN_Type_D;

// Max allowed is 51*26*2048
#define FN_MAX 2715648

class TDMAFrameNumber {
// Any modifications done to this class should take into account the fact that
// the standard "%" operator, as well as the integer "/" operator, are
// implementation-dependent in how they deal with negative numbers.  As such,
// this class was initially designed (July 2004) to use the "normalize()"
// function to ensure proper operation.
// Also note that the operator int() type conversion does NOT call normalize(),
// unlike most of the other operators.  The reason is that users of this class
// should not have to realize that a simple type conversion actually modifies the
// internal data members.  However, perhaps no one really cares.  [ Dhaval Dave' ]
protected:
	_GSM_FN_Type FN;
	inline void normalize() { if ( FN < 0 ) FN += FN_MAX; }
public:
	TDMAFrameNumber( int FrameNum=0 ) {
		FN = (FrameNum % FN_MAX);   normalize(); }
	TDMAFrameNumber(unsigned int T1, unsigned int T2, unsigned int T3) {
		FN = 0;

		if((T1 > 2048) || (T2 > 25) || (T3 > 4)) return;

		int iT1 = (int)T1;
		int iT2 = (int)T2;
		int iT3 = (int)T3 * 10 + 1;

		// Change 1/10/2005: Add 26 to the subtraction to avoid % of negative
		int TMod = (iT3 - iT2 + 26) % 26;
		FN = (iT3 + (51 * TMod) + (51 * 26 * iT1));
	}
	bool IsSync() const { return (((FN % 51) % 10) == 1); }
	bool IsFC() const { return (((FN % 51) % 10) == 0); }
	TDMAFrameNumber ClosestSync() const {
		if(IsSync()) return *this;

		int Mod = FN % 51;
		if(Mod == 0) return TDMAFrameNumber(FN + 1);
		Mod %= 10;
		if(Mod == 0) return TDMAFrameNumber(FN + 1);
		if(Mod <= 6) return TDMAFrameNumber(FN - Mod + 1);
		else return TDMAFrameNumber(FN + 11 - Mod);
	}

	// overloaded operators
	// Note that '+' and '-' call the ctor, so normalize() will execute
	void operator=(int n) { FN = n % FN_MAX;   normalize(); }
	void operator +=(int n) { FN += n;  FN %= FN_MAX;  normalize(); }
	void operator -=(int n) { FN -= n;  FN %= FN_MAX;  normalize(); }
	TDMAFrameNumber operator +(int n) const { return TDMAFrameNumber((int)FN + n); }
	TDMAFrameNumber operator -(int n) const { return TDMAFrameNumber((int)FN - n); }
	operator int() const { return (int)FN; }
};

#endif
