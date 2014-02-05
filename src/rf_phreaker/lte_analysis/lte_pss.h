#pragma once

#include "Ipp.h"


#define LTE_NUM_PSS		3
#define LTE_MAX_SAMPLE_RATE_KHZ			30720


class LtePrimarySyncSequence
{
public:
	LtePrimarySyncSequence(unsigned int SampleRatekHz=1920);
	~LtePrimarySyncSequence();
	const Ipp32fc* operator[](int idx) const {return m_SeqT[idx];}
	unsigned int GetSeqLength() const {return m_SeqLen;}
	const Ipp32fc* GetSeqT(int idx) const {return m_SeqT[idx];}
	Ipp32fc* GetBufferT(int idx) const {return m_SeqT[idx];}
	Ipp32fc* GetBufferF(int idx) const {return m_SeqF[idx];}
	const Ipp32fc* GetSeqF(int idx) const {return m_SeqF[idx];}
	void Scale(const Ipp32fc& Scalar);
protected:
	static const int m_ZCRoots[LTE_NUM_PSS];
	static const int m_ZCLen;
	unsigned int m_SampleRateHz;
	unsigned int m_SeqLen;
	Ipp32fc *m_SeqT[LTE_NUM_PSS], *m_SeqF[LTE_NUM_PSS];
};

