#pragma once

#include "rf_phreaker/umts_layer_3_decoder/umts_layer_3_decoder.h"
#include "rf_phreaker/umts_analysis/umts_config.h"
#include "rf_phreaker/umts_analysis/cpich_table_container.h"
#include "rf_phreaker/fir_filter/fir_filter.h"
#include "ipps.h"
#include <vector>

#define UMTS_DECODE_FRAME_NUM_MAX                 16

class umts_bch_decoder
{
public:
	umts_bch_decoder(const cpich_table_container &cpich_table, const umts_config &config);
	~umts_bch_decoder(void);

	int process(const Ipp32fc *umts_signal, int signal_length, int cpich, int start_of_frame, layer_3_information::umts_bcch_bch_message_aggregate& bchinfo, int packetnum);

	bool convert_to_bitstream(int startofframe);

private:
	
	unsigned int bintodec(unsigned __int8 *bitarray, unsigned __int8 size);


	unsigned int pl, sfn, sil, sct, *st, *sl, powertemp, crc16, rm16, sft, sst, slt, sll, sfl, as, bs, cs, ds, seg_idx, seg_count;
	int err;
	int kdelaylength;
	const Ipp32fc* cpichtemplate;
	const Ipp32fc* kaiserfilter;
	Ipp32fc *inputsignal, *signalscrcorr, *cpichcode, *upsamplecpich, scrcode;
	Ipp32fc *hammingfilter, *hammingsignal, *kaiserresample, *tti, *kfilterdelay;
	Ipp32fc val0, val1, *tempmul, *multemp, *lmulmean0, *lmulmean1, *cpich, *ccpch, *meanearly, *hfilterdelay;
	Ipp32fc *emulmean0, *emulmean1, *omulmean0, *omulmean1, *slotarray, *earlyslot, *ontimeslot, *lateslot, *meanlate;
	Ipp32fc *tempearlyslot, *tempontimeslot, *templateslot, *meanontime, *cch0cplx, *cch1cplx, *latecplx;
	Ipp32fc *latem0cplx, *latem1cplx, *earlym0cplx, *earlym1cplx, *ontimem0cplx, *ontimem1cplx, *earlycplx;
	Ipp32fc *ontimecplx, *expfreq, *cplxf, cplxphase, expphase, *tempccpch, *ccpcheqout, *acplx, *ccpchs2, mulcon;
	Ipp32fc *ccpchcplx, *expccpch, *ccpcheqin, *ccpchref, *y1, *y2, *e1, *w1cplx, *tempcpich, *tempw1, *tmul, d;
	Ipp32fc *shortkaiserresample;
			
	Ipp32f *magsignal, *realfilter, *imagfilter, *cpichcodereal, *cpichcodeimag, *realtemp, value, meansignal;
	Ipp32f *abscorr, *realcpich, *imagcpich, *abscpich, *avgsignal, *imagtemp, cpichsum, meanavg, peakvalue;
	Ipp32f *absearly, *absontime, *abslate, *cpichangle, *cpichindex, earlymean, ontimemean, latemean;
	Ipp32f *anglesub, *indexsqr, *mulindang, intialvalue, freq, indexmean, anglemean, sqrmean, mulmean;
	Ipp32f *imagf, *realf, cpichsub, phase, twopi, pi, temp1ddtti, temp2ddtti;
	Ipp32f *ccpchreal, *ccpchimag, *ccpchangle, *realccpch, *imagccpch2, piby4, emin;
	Ipp32f *se, *e, *etemp, *ac;
	Ipp32f *ds1cplx, *ddf0, *ddf1, *dd2n, *absdd2n, *ttireal, *ttiimag, meandd2n, fc, po, fl, temp1;
	Ipp32f *ddf0temp, *ddf1temp, *ds2cplx, *ddf01, *ddf11, *ddtti, *ds01cplx, *ds02cplx, *acccplx, accconstant;
	Ipp32f temp3ddtti, temp4ddtti, *imagccpch1;
	
	Ipp8u *s1, *s2, *r, *rm, *svcplx, *perm, *dec, *sd, *rn, temp, idx1, idx2, sr1, sr5, sr12;
	Ipp8u *decoded_bcch_stream,num_decoded_bcch_stream_; 
	
	IppsFIRState_32fc *kaiserstate, *hammingstate;
				
	std::vector<Ipp32fc*> rsearlyslot, rsontimeslot, rslateslot, latemul0, latemul1, earlymul0, earlymul1, ontimemul0;
	std::vector<Ipp32fc*> ontimemul1, cchv0, cchv1, w1, a;
	std::vector<Ipp32f*> ds01, ds02, ds11, ds12, acc;
	std::vector<Ipp8u*> sv;
	std::vector<Ipp32fc*>::iterator latemulit0, latemulit1, earlymulit0, earlymulit1, ontimemulit0, ontimemulit1;
	std::vector<Ipp32fc*>::iterator cchv0it, cchv1it, rsearlyslotit, rsontimeslotit, rslateslotit, w1it, ait;
	std::vector<Ipp8u*>::iterator svit;
	std::vector<Ipp32f*>::iterator ds01it, ds02it, ds11it, ds12it, accit;

	int signallength;
	int resamplelength;

	void output_ascii_hex_string(const layer_3_information::umts_bcch_bch_message_aggregate& bchinfo);

	void output_binary_string(const layer_3_information::umts_bcch_bch_message_aggregate& bchinfo);

	int bit_stream_counter_;

	void consolidate_bit_stream(unsigned char bit_stream_index);

	std::vector<uint8_t> consolidated_bit_stream_;

	umts_asn1_decoder asn1_decoder_;

	int successful_decodes_;

	double sample_rate_;

	double clock_rate_;

	double over_sampling_rate_;

	rf_phreaker::fir_filter filter_;

	int up_factor_;
	int down_factor_;
	int cpich_resample_factor_;
};
