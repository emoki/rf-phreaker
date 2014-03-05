#include "rf_phreaker/umts_analysis/umts_bch_decoder.h"
#include "rf_phreaker/umts_analysis/umts_types.h"
#include "rf_phreaker/common/exception_types.h"
#include <boost/lexical_cast.hpp>
#include <math.h>
#include <ippvm.h>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <iomanip>

using namespace layer_3_information;

umts_bch_decoder::umts_bch_decoder(const umts_config &config, const /*cpich_table_container &*/Ipp32fc* cpich_table)
: kdelaylength(21)
, cpichtemplate(cpich_table)
, bit_stream_counter_(0)
, successful_decodes_(0)
, clock_rate_(config.clock_rate())
, signal_sampling_rate_(config.sampling_rate())
, target_sampling_rate_(19200000)
{
	umts_signal_filter_.set_zero_delay(true);
	umts_signal_filter_.set_up_down_factor_based_on_sampling_rates(signal_sampling_rate_, target_sampling_rate_);
	umts_signal_filter_.set_taps(5121);

	up_factor_ = umts_signal_filter_.up_factor();
	down_factor_ = umts_signal_filter_.down_factor();	

	signal_over_sampling_rate_ = (double)up_factor_ / down_factor_;
	
	cpich_resample_factor_ = 5; // Represents the rate above umts chip rate at which we are processing.  So 3.84 * (5) = 19.2.

	signallength = config.max_signal_length()/* - ((config.max_signal_length() * up_factor_ / down_factor_) % down_factor_)*/;
	resamplelength = signallength * up_factor_ / down_factor_; 

	std::vector<layer_3_information::pdu_element_type> elements;

	elements.push_back(layer_3_information::pdu_element_type::umts_mib);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib1);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib3);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib4);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib11);
	elements.push_back(layer_3_information::pdu_element_type::umts_sib11_bis);

	asn1_decoder_.specify_sibs_for_decoding(&elements.at(0), elements.size());

	int cpichcodes=512, cpichupphase=0, cpichsamples=38400,  /*i=0,*/ hdelaylength=128; 
	int upsamplelength=10240/*, scr*/, peakindex=0, offset=0, numberframes=0, peakthreshold=-10, cpichupfactor=5;
	//int nf = 4;
	int nf = UMTS_DECODE_FRAME_NUM_MAX;
	int	shift=0, count=0, n=0, /*j=0, p=0, q=0, k=0,*/ m=0, cchsamples=256, cchlength=10, slot=15, fframeno=150;
	int w1length=17, cframeno=150, nfc1=15, nfc2=9, nfc3=3, idx=1, tticonstant=269, /*kdelaylength=21,*/ kdlength=10;
	int pvec=30, sc1=256, sc2=7, bitc=8, crcconst1=246, crcconst2=261, bit=15, stsize=16, slsize=256, hdlength=64;
	int peakposition=0, esamples=20, samplesmargin=10;


	

	consolidated_bit_stream_.resize(34);

	
	powertemp=0; 
	sst=0;
	sft=0; 
	slt=0; 
	sll=0; 
	sfl=0; 
	sil=0; 
	sct=0;
	seg_count=0;
	seg_idx=0;
	intialvalue=1.0;
	twopi=(Ipp32f)(44.0/7.0);
	pi = (Ipp32f)(22.0 / 7.0);
	piby4 = (Ipp32f)(22.0 / 28.0);
	sfn= 0xFFFF;
	pl=0;
	as=0;
	bs=0;
	cs=0;
	ds=0;
	accconstant=4.0;
	
	hammingsignal = ippsMalloc_32fc(signallength);
	kaiserresample = ippsMalloc_32fc(resamplelength);
	shortkaiserresample = ippsMalloc_32fc(upsamplelength+esamples);
	signalscrcorr = ippsMalloc_32fc(upsamplelength+esamples);
	cpichcode = ippsMalloc_32fc(cpichsamples);
	upsamplecpich = ippsMalloc_32fc(upsamplelength);
	tempmul = ippsMalloc_32fc(cchlength);
	multemp = ippsMalloc_32fc(cchsamples);
	lmulmean0 = ippsMalloc_32fc(cchlength);
	lmulmean1 = ippsMalloc_32fc(cchlength);
	emulmean0 = ippsMalloc_32fc(cchlength);
	emulmean1 = ippsMalloc_32fc(cchlength);
	omulmean0 = ippsMalloc_32fc(cchlength);
	omulmean1 = ippsMalloc_32fc(cchlength);
	tempearlyslot = ippsMalloc_32fc(cchsamples);
	tempontimeslot = ippsMalloc_32fc(cchsamples);
	templateslot = ippsMalloc_32fc(cchsamples);
	meanearly = ippsMalloc_32fc(cchlength);
	meanontime = ippsMalloc_32fc(cchlength);
	meanlate = ippsMalloc_32fc(cchlength);
	slotarray = ippsMalloc_32fc(cpichsamples*cpich_resample_factor_/slot);
	earlyslot = ippsMalloc_32fc(cpichsamples/slot);
	ontimeslot = ippsMalloc_32fc(cpichsamples/slot);
	lateslot = ippsMalloc_32fc(cpichsamples/slot);
	tempcpich = ippsMalloc_32fc(w1length);
	tempccpch = ippsMalloc_32fc(w1length);
	tempw1 = ippsMalloc_32fc(w1length);
	tmul = ippsMalloc_32fc(w1length);
	tti = ippsMalloc_32fc(tticonstant+1);
	kfilterdelay = ippsMalloc_32fc(kdelaylength);
	hfilterdelay = ippsMalloc_32fc(hdelaylength);
	expfreq = ippsMalloc_32fc((nf+2)*cchlength*slot);
	cplxf = ippsMalloc_32fc((nf+2)*cchlength*slot);
	y1 = ippsMalloc_32fc((nf+2)*cchlength*slot);
	y2 = ippsMalloc_32fc((nf+2)*cchlength*slot);
	e1 = ippsMalloc_32fc((nf+2)*cchlength*slot);
	ccpchref = ippsMalloc_32fc((nf+2)*cchlength*slot);
	cpich = ippsMalloc_32fc((nf+2)*cchlength*slot);
	ccpch = ippsMalloc_32fc((nf+2)*cchlength*slot);
	expccpch = ippsMalloc_32fc((nf+2)*cchlength*slot);
	ccpcheqin = ippsMalloc_32fc((nf+2)*cchlength*slot);
	ccpchcplx = ippsMalloc_32fc((nf+2)*cchlength*slot);
	ccpcheqout = ippsMalloc_32fc((nf+2)*cchlength*slot);
	ccpchs2 = ippsMalloc_32fc(((nf+2)*cchlength*slot)-cframeno);
	inputsignal = ippsMalloc_32fc(resamplelength+(cpichsamples*cpich_resample_factor_));
		
	realtemp = ippsMalloc_32f(w1length);
	imagtemp = ippsMalloc_32f(w1length);
	magsignal = ippsMalloc_32f(signallength);
	realfilter = ippsMalloc_32f(signallength);
	imagfilter = ippsMalloc_32f(signallength);
	abscpich = ippsMalloc_32f(upsamplelength);
	realcpich = ippsMalloc_32f(upsamplelength);
	imagcpich = ippsMalloc_32f(upsamplelength);
	abscorr = ippsMalloc_32f(upsamplelength+esamples);
	avgsignal = ippsMalloc_32f(resamplelength);
	absearly = ippsMalloc_32f(cchlength);
	absontime = ippsMalloc_32f(cchlength);
	abslate = ippsMalloc_32f(cchlength);
	ttireal = ippsMalloc_32f(tticonstant+1);
	ttiimag = ippsMalloc_32f(tticonstant+1);
	dd2n = ippsMalloc_32f(2*(tticonstant+1));
	absdd2n = ippsMalloc_32f(2*(tticonstant+1));
	ddf0 = ippsMalloc_32f(tticonstant+1);
	ddf1 = ippsMalloc_32f(tticonstant+1);
	ddf0temp = ippsMalloc_32f(tticonstant+1);
	ddf1temp = ippsMalloc_32f(tticonstant+1);
	ddf01 = ippsMalloc_32f(tticonstant+1);
	ddf11 = ippsMalloc_32f(tticonstant+1);
	ddtti = ippsMalloc_32f(2*(tticonstant+1));
	se = ippsMalloc_32f(tticonstant+1);
	e = ippsMalloc_32f((int)boost::math::round((double)accconstant));
	etemp = ippsMalloc_32f(2);
	ac = ippsMalloc_32f(2);
	cpichcodereal = ippsMalloc_32f(cpichsamples);
	cpichcodeimag = ippsMalloc_32f(cpichsamples);
	anglesub = ippsMalloc_32f(((nf+2)*cchlength*slot)-fframeno);
	indexsqr = ippsMalloc_32f(((nf+2)*cchlength*slot)-fframeno);
	mulindang = ippsMalloc_32f(((nf+2)*cchlength*slot)-fframeno);
	realf = ippsMalloc_32f((nf+2)*cchlength*slot);
	imagf = ippsMalloc_32f((nf+2)*cchlength*slot);
	ccpchreal = ippsMalloc_32f((nf+2)*cchlength*slot);
	ccpchimag = ippsMalloc_32f((nf+2)*cchlength*slot);
	ccpchangle = ippsMalloc_32f((nf+2)*cchlength*slot);
	realccpch = ippsMalloc_32f((nf+2)*cchlength*slot);
	imagccpch2 = ippsMalloc_32f((nf+2)*cchlength*slot);
	imagccpch1 = ippsMalloc_32f((nf+2)*cchlength*slot);
	cpichangle = ippsMalloc_32f(((nf+2)*cchlength*slot)-fframeno);
	cpichindex = ippsMalloc_32f(((nf+2)*cchlength*slot)-fframeno);
	
	s2 = ippsMalloc_8u(sc1+1);
	r = ippsMalloc_8u(bitc+1);     
	perm = ippsMalloc_8u(pvec);
	sd = ippsMalloc_8u(tticonstant+1);
	dec = ippsMalloc_8u(tticonstant+1);
	decoded_bcch_stream = ippsMalloc_8u((tticonstant+1)*UMTS_DECODE_FRAME_NUM_MAX);
	rn = ippsMalloc_8u(crcconst2-crcconst1);
	rm = ippsMalloc_8u(crcconst2-crcconst1);
	s1 = ippsMalloc_8u(sc1+1);

	sl = (unsigned int*)malloc(slsize * sizeof(unsigned int));
	st = (unsigned int*)malloc(stsize * sizeof(unsigned int));
	
	if(hammingsignal == NULL || kaiserresample == NULL || signalscrcorr == NULL || cpichcode == NULL || 
		upsamplecpich == NULL || tempmul == NULL || multemp == NULL || lmulmean0 == NULL || lmulmean1 == NULL || emulmean0 == NULL || 
		emulmean1 == NULL || omulmean0 == NULL || omulmean1 == NULL || tempearlyslot == NULL || tempontimeslot == NULL || 
		templateslot == NULL || meanearly == NULL || meanontime == NULL || meanlate == NULL || slotarray == NULL || 
		earlyslot == NULL || ontimeslot == NULL || lateslot == NULL || tempcpich == NULL || tempccpch == NULL || tempw1 == NULL || 
		tmul == NULL || tti == NULL || kfilterdelay == NULL || hfilterdelay == NULL || expfreq == NULL || cplxf == NULL || 
		y1 == NULL || y2 == NULL || e1 == NULL || ccpchref == NULL || cpich == NULL || ccpch == NULL || expccpch == NULL || 
		ccpcheqin == NULL || ccpchcplx == NULL || ccpcheqout == NULL || ccpchs2 == NULL || inputsignal == NULL || 
		realtemp == NULL || imagtemp == NULL || magsignal == NULL || realfilter == NULL || imagfilter == NULL || 
		abscpich == NULL || realcpich == NULL || imagcpich == NULL || abscorr == NULL || avgsignal == NULL || 
		absearly == NULL || absontime == NULL || abslate == NULL || ttireal == NULL || ttiimag == NULL || dd2n == NULL || 
		absdd2n == NULL || ddf0 == NULL || ddf1 == NULL || ddf0temp == NULL || ddf1temp == NULL || ddf01 == NULL || 
		ddf11 == NULL || ddtti == NULL || 	se == NULL || e == NULL || etemp == NULL || ac == NULL || cpichcodereal == NULL || 
		cpichcodeimag == NULL || anglesub == NULL || indexsqr == NULL || mulindang == NULL || realf == NULL || imagf == NULL || 
		ccpchreal == NULL || ccpchimag == NULL || ccpchangle == NULL || realccpch == NULL || imagccpch2 == NULL || 
		imagccpch1 == NULL || cpichangle == NULL || cpichindex == NULL || s2 == NULL || r == NULL || perm == NULL || 
		sd == NULL || dec == NULL || rn == NULL || rm == NULL || s1 == NULL || sl == NULL || st == NULL || 
		shortkaiserresample == NULL)
		throw rf_phreaker::umts_analysis_error("Memory allocation error while constructing umts bch decoder.\n");  




	value = -1.0;
	val0.re = 1.0;
	val0.im = 0.0;
	val1.re = -1.0;
	val1.im = 0.0;
	cplxphase.re = 0;
	d.re = (1/sqrt(2.0f));
	d.im = (1 / sqrt(2.0f));
	mulcon.re = 0.05f;
	mulcon.im = 0.0f;
	perm[0] = 0; perm[1] = 12; perm[2] = 25; perm[3] = 6; perm[4] = 18; perm[5] = 3;
	perm[6] = 15; perm[7] = 26; perm[8] = 9; perm[9] = 22; perm[10] = 2; perm[11] = 13;
	perm[12] = 24; perm[13] = 7; perm[14] = 19; perm[15] = 4; perm[16] = 16; perm[17] = 29;
	perm[18] = 10; perm[19] = 21; perm[20] = 1; perm[21] = 14; perm[22] = 27; perm[23] = 8;
	perm[24] = 20; perm[25] = 5; perm[26] = 17; perm[27] = 28; perm[28] = 11; perm[29] = 23;
	
	ippsZero_8u(s1, (sc1+1));
	ippsZero_8u(s2, (sc2+1));
	ippsZero_8u(r, (bitc+1));
	ippsZero_32f(realccpch, ((nf+2)*cchlength*slot));
	ippsZero_32fc(y1, ((nf+2)*cchlength*slot));
	ippsZero_32fc(y2, ((nf+2)*cchlength*slot));
	ippsZero_32fc(e1, ((nf+2)*cchlength*slot));	
	ippsZero_32fc(kfilterdelay, kdelaylength);
	ippsZero_32fc(&(hfilterdelay[hdlength]), hdlength);
	ippsZero_32f(realf, ((nf+2)*cchlength*slot));
	ippsSet_32f(-piby4, imagccpch1, ((nf+2)*cchlength*slot));
	ippsSet_32f(piby4, imagccpch2, ((nf+2)*cchlength*slot));
	
	for(int i=0; i<(cchsamples/2); i++)
	{	
		cch1cplx = ippsMalloc_32fc(cchlength);
		
		if(cch1cplx == NULL)
			throw rf_phreaker::umts_analysis_error("Memory allocation error while constructing umts bch decoder.\n");

		ippsSet_32fc(val0, cch1cplx, cchlength);
		cchv1.push_back(cch1cplx);
	}
	
	for(int i=(cchsamples/2); i<cchsamples; i++)
	{	
		cch1cplx = ippsMalloc_32fc(cchlength);
		
		if(cch1cplx == NULL)
			throw rf_phreaker::umts_analysis_error("Memory allocation error while constructing umts bch decoder.\n");

		ippsSet_32fc(val1, cch1cplx, cchlength);
		cchv1.push_back(cch1cplx);
	}
	
	for(int i=0; i<cchsamples; i++)
	{
		cch0cplx = ippsMalloc_32fc(cchlength);
		earlycplx = ippsMalloc_32fc(cchlength);
		ontimecplx = ippsMalloc_32fc(cchlength);
		latecplx = ippsMalloc_32fc(cchlength);
		latem0cplx = ippsMalloc_32fc(cchlength);
		latem1cplx = ippsMalloc_32fc(cchlength);
		earlym0cplx = ippsMalloc_32fc(cchlength);
		earlym1cplx = ippsMalloc_32fc(cchlength);
		ontimem0cplx = ippsMalloc_32fc(cchlength);
		ontimem1cplx = ippsMalloc_32fc(cchlength);

		if(cch0cplx== NULL || earlycplx== NULL || ontimecplx== NULL || latecplx== NULL || latem0cplx== NULL ||
			latem1cplx== NULL || earlym0cplx== NULL || earlym1cplx== NULL || ontimem0cplx== NULL || ontimem1cplx== NULL)
			throw rf_phreaker::umts_analysis_error("Memory allocation error while constructing umts bch decoder.\n");

		ippsSet_32fc(val0, cch0cplx, cchlength);
		cchv0.push_back(cch0cplx);
		rsearlyslot.push_back(earlycplx);
		rsontimeslot.push_back(ontimecplx);
		rslateslot.push_back(latecplx);
		latemul0.push_back(latem0cplx);
		latemul1.push_back(latem1cplx);
		earlymul0.push_back(earlym0cplx);
		earlymul1.push_back(earlym1cplx);
		ontimemul0.push_back(ontimem0cplx);
		ontimemul1.push_back(ontimem1cplx);
	}

	for(int i=0; i<w1length; i++)
	{
		w1cplx = ippsMalloc_32fc((nf+2)*cchlength*slot);
	
		if(w1cplx == NULL)
			throw rf_phreaker::umts_analysis_error("Memory allocation error within w1 while constructing UMTS BCH Decoder.\n");

		ippsZero_32fc(w1cplx, ((nf+2)*cchlength*slot));
		w1.push_back(w1cplx);
	}
	
	for(int i=0; i<(nfc2+1); i++)
	{
		acplx = ippsMalloc_32fc(nfc1*(nf-1));
	
		if(acplx == NULL)
			throw rf_phreaker::umts_analysis_error("Memory allocation error within acplx while constructing UMTS BCH Decoder.\n");

		a.push_back(acplx);
	}

	for(int i=0; i<=bitc; i++)
	{
		ds1cplx = ippsMalloc_32f(pvec);
		ds2cplx = ippsMalloc_32f(pvec);
		ds01cplx = ippsMalloc_32f(pvec);
		ds02cplx = ippsMalloc_32f(pvec);

		if(ds1cplx == NULL || ds2cplx == NULL || ds01cplx == NULL || ds02cplx == NULL)
			throw rf_phreaker::umts_analysis_error("Memory allocation error within ds01 while constructing UMTS BCH Decoder.\n");

		ds01.push_back(ds1cplx);
		ds11.push_back(ds2cplx);
		ds02.push_back(ds01cplx);
		ds12.push_back(ds02cplx);
	}
	
	for(int i=0; i<=sc1; i++)
	{
		svcplx = ippsMalloc_8u(sc2+1);
		acccplx = ippsMalloc_32f(tticonstant+1);

		if(svcplx == NULL || acccplx == NULL)
			throw rf_phreaker::umts_analysis_error("Memory allocation error within acc while constructing UMTS BCH Decoder.\n");

		ippsZero_8u(svcplx, (sc2+1));
		ippsSet_32f(accconstant, acccplx, (tticonstant+1));
		sv.push_back(svcplx);
		if(acccplx[tticonstant] != 4)
			throw rf_phreaker::umts_analysis_error("Error!!!!");
		acc.push_back(acccplx);
	}
		
	// encoder
for(int i=1; i<=sc1; i++)
	{
		ippsXor_8u(&(r[1]), &(r[2]), &temp, 1);
		ippsXor_8u_I(&(r[3]), &temp, 1);
		ippsXor_8u_I(&(r[5]), &temp, 1);
		ippsXor_8u_I(&(r[7]), &temp, 1);
		ippsXor_8u(&(r[8]), &temp, &(s1[i]), 1);
		ippsXor_8u(&(r[2]), &(r[3]), &temp, 1);
		ippsXor_8u_I(&(r[4]), &temp, 1);
		ippsXor_8u(&(r[8]), &temp, &(s2[i]), 1);
		ippsMulC_8u_Sfs(&(s2[i]), (Ipp8u)(2), &temp, 1, 0);
		ippsAdd_8u_Sfs(&(s1[i]), &temp, &(sv[i][1]), 1, 0);
		ippsSubCRev_8u_Sfs(&(sv[i][1]), (Ipp8u)(3), &(sv[i][2]), 1, 0);
		temp1 = (Ipp32f)(i);
		ippsSubC_32f_I((Ipp32f)(1.0), &temp1, 1);
		ippsDivC_32f_I((Ipp32f)(2.0), &temp1, 1);
		ippsFloor_32f(&temp1, &fl, 1);
		ippsConvert_32f8u_Sfs(&fl, &(sv[i][3]), 1, ippRndNear, 0);
		ippsAddC_8u_Sfs(&(sv[i][3]), (Ipp8u)(128), &(sv[i][4]), 1, 0);
		
		if(i<129)
		{
			temp = (Ipp8u)(i);
			ippsSubC_8u_ISfs((Ipp8u)(1), &temp, 1, 0);
			ippsMulC_8u_Sfs(&temp, (Ipp8u)(2), &(sv[i][5]), 1, 0);
			ippsAddC_8u_Sfs(&(sv[i][5]), (Ipp8u)(1), &(sv[i][6]), 1, 0);				
			ippsZero_8u(&(sv[i][7]), 1);
		}
		else
		{
			temp1 = (Ipp32f)(i);
			ippsSubC_32f_I((Ipp32f)(1.0), &temp1, 1);
			ippsMulC_32f_I((Ipp32f)(2.0), &temp1, 1);
			ippsSubC_32f_I((Ipp32f)(256.0), &temp1, 1);
			ippsConvert_32f8u_Sfs(&temp1, &(sv[i][5]), 1, ippRndFinancial, 0);
			ippsAddC_32f_I((Ipp32f)(1.0), &temp1, 1);
			ippsConvert_32f8u_Sfs(&temp1, &(sv[i][6]), 1, ippRndFinancial, 0);
			ippsSet_8u((Ipp8u)(1), &(sv[i][7]), 1);
		}

		for(int j=1; j<=8; j++)
		{
			temp = (Ipp8u)(j);
			ippsSubCRev_8u_ISfs((Ipp8u)(8), &temp, 1, 0);
			ippsConvert_8u32f(&temp, &fc, 1);
			ippsSet_32f((Ipp32f)(2.0), &temp1, 1);
			ippsPowx_32f_A24(&temp1, fc, &po, 1);
			temp1 = (Ipp32f)(i);
			ippsDivC_32f_I(po, &temp1, 1);
			ippsFloor_32f (&temp1, &fl, 1);
			ippsConvert_32f8u_Sfs(&fl, &temp, 1, ippRndFinancial, 0);
			r[j] = temp%2;
		}
	}
	


	//IppStatus stat = ippsFIRMRInitAlloc_32fc(&kaiserstate, kaiserfilter, kaiserlength, up_factor_, 0, down_factor_, 0, kfilterdelay);
	//if(stat != ippStsNoErr)
	//	throw rf_phreaker::umts_analysis_error("Error creating Kaiserfilter for UMTS BCH Decoder.\n");
}

umts_bch_decoder::~umts_bch_decoder(void)
{
	ippsFree(hammingsignal);
	ippsFree(kaiserresample);
	ippsFree(shortkaiserresample);
	ippsFree(signalscrcorr);
	ippsFree(cpichcode);
	ippsFree(upsamplecpich);
	ippsFree(tempmul);
	ippsFree(multemp);
	ippsFree(lmulmean0);
	ippsFree(lmulmean1);
	ippsFree(emulmean0);
	ippsFree(emulmean1);
	ippsFree(omulmean0);
	ippsFree(omulmean1);
	ippsFree(tempearlyslot);
	ippsFree(tempontimeslot);
	ippsFree(templateslot);
	ippsFree(meanearly);
	ippsFree(meanontime);
	ippsFree(meanlate);
	ippsFree(slotarray);
	ippsFree(earlyslot);
	ippsFree(ontimeslot);
	ippsFree(lateslot);
	ippsFree(tempcpich);
	ippsFree(tempccpch);
	ippsFree(tempw1);
	ippsFree(tmul);
	ippsFree(tti);
	ippsFree(kfilterdelay);
	ippsFree(hfilterdelay);
	ippsFree(expfreq);
	ippsFree(cplxf);
	ippsFree(y1);
	ippsFree(y2);
	ippsFree(e1);
	ippsFree(ccpchref);
	ippsFree(cpich);
	ippsFree(ccpch);
	ippsFree(expccpch);
	ippsFree(ccpcheqin);
	ippsFree(ccpchcplx);
	ippsFree(ccpcheqout);
	ippsFree(ccpchs2);
	ippsFree(inputsignal);
	ippsFree(realtemp);
	ippsFree(imagtemp);
	ippsFree(magsignal);
	ippsFree(realfilter);
	ippsFree(imagfilter);
	ippsFree(abscpich);
	ippsFree(realcpich);
	ippsFree(imagcpich);
	ippsFree(abscorr);
	ippsFree(avgsignal);
	ippsFree(absearly);
	ippsFree(absontime);
	ippsFree(abslate);
	ippsFree(ttireal);
	ippsFree(ttiimag);
	ippsFree(dd2n);
	ippsFree(absdd2n);
	ippsFree(ddf0);
	ippsFree(ddf1);
	ippsFree(ddf0temp);
	ippsFree(ddf1temp);
	ippsFree(ddf01);
	ippsFree(ddf11);
	ippsFree(ddtti);
	ippsFree(se);
	ippsFree(e);
	ippsFree(etemp);
	ippsFree(ac);
	ippsFree(cpichcodereal);
	ippsFree(cpichcodeimag);
	ippsFree(anglesub);
	ippsFree(indexsqr);
	ippsFree(mulindang);
	ippsFree(realf);
	ippsFree(imagf);
	ippsFree(ccpchreal);
	ippsFree(ccpchimag);
	ippsFree(ccpchangle);
	ippsFree(realccpch);
	ippsFree(imagccpch2);
	ippsFree(imagccpch1);
	ippsFree(cpichangle);
	ippsFree(cpichindex);
	ippsFree(s2);
	ippsFree(r);
	ippsFree(perm);
	ippsFree(sd);
	ippsFree(dec);
	ippsFree(rn);
	ippsFree(rm);
	ippsFree(s1);
	
	//ippsFIRFree_32fc(kaiserstate);
		
	for(cchv1it=cchv1.begin(); cchv1it!=cchv1.end(); cchv1it++)
		ippsFree(*cchv1it);
	cchv1.clear();

	for(cchv0it=cchv0.begin(); cchv0it!=cchv0.end(); cchv0it++)
		ippsFree(*cchv0it);
	cchv0.clear();

	for(rsearlyslotit=rsearlyslot.begin(); rsearlyslotit!=rsearlyslot.end(); rsearlyslotit++)
		ippsFree(*rsearlyslotit);
	rsearlyslot.clear();

	for(rsontimeslotit=rsontimeslot.begin(); rsontimeslotit!=rsontimeslot.end(); rsontimeslotit++)
		ippsFree(*rsontimeslotit);
	rsontimeslot.clear();

	for(rslateslotit=rslateslot.begin(); rslateslotit!=rslateslot.end(); rslateslotit++)
		ippsFree(*rslateslotit);
	rslateslot.clear();

	for(latemulit0=latemul0.begin(); latemulit0!=latemul0.end(); latemulit0++)
		ippsFree(*latemulit0);
	latemul0.clear();
	
	for(latemulit1=latemul1.begin(); latemulit1!=latemul1.end(); latemulit1++)
		ippsFree(*latemulit1);
	latemul1.clear();

	for(earlymulit0=earlymul0.begin(); earlymulit0!=earlymul0.end(); earlymulit0++)
		ippsFree(*earlymulit0);
	earlymul0.clear();
	
	for(earlymulit1=earlymul1.begin(); earlymulit1!=earlymul1.end(); earlymulit1++)
		ippsFree(*earlymulit1);
	earlymul1.clear();
	
	for(ontimemulit0=ontimemul0.begin(); ontimemulit0!=ontimemul0.end(); ontimemulit0++)
		ippsFree(*ontimemulit0);
	ontimemul0.clear();
				
	for(ontimemulit1=ontimemul1.begin(); ontimemulit1!=ontimemul1.end(); ontimemulit1++)
		ippsFree(*ontimemulit1);
	ontimemul1.clear();

	for(w1it=w1.begin(); w1it!=w1.end(); w1it++)
		ippsFree(*w1it);
	w1.clear();

	for(ait=a.begin(); ait!=a.end(); ait++)
		ippsFree(*ait);
	a.clear();

	for(ds01it=ds01.begin(); ds01it!=ds01.end(); ds01it++)
		ippsFree(*ds01it);
	ds01.clear();

	for(ds02it=ds02.begin(); ds02it!=ds02.end(); ds02it++)
		ippsFree(*ds02it);
	ds02.clear();

	for(ds11it=ds11.begin(); ds11it!=ds11.end(); ds11it++)
		ippsFree(*ds11it);
	ds11.clear();

	for(ds12it=ds12.begin(); ds12it!=ds12.end(); ds12it++)
		ippsFree(*ds12it);
	ds12.clear();

	for(svit=sv.begin(); svit!=sv.end(); svit++)
		ippsFree(*svit);
	sv.clear();

	for(accit=acc.begin(); accit!=acc.end(); accit++)
		ippsFree(*accit);
	acc.clear();

	free(sl);
	free(st);

}

int umts_bch_decoder::process(const Ipp32fc *umtssignal, int signal_length, int scr, int startofframe, umts_bcch_bch_message_aggregate& bchinfo)
{
	sfn=layer_3_information::not_decoded_32;

	if(signal_length < signallength)
		throw rf_phreaker::umts_analysis_error("UMTS BCH decoder error.  Signal length is too small to process layer 3.");

	int esamples = 20;
	// variable declaration
	//int hamminglength=129, kaiserlength=5121;
	int /*down_factor_=2, */cpichcodes=512, cpichupphase=0, cpichsamples=38400, /*cpich_resample_factor_=5,*/ payl=0; 
	int upsamplelength=10240, /*scr,*/ peakindex=0, offset=0, numberframes=0,peakthreshold=-10;
	//int nf = 4;
	int nf = UMTS_DECODE_FRAME_NUM_MAX;
	int	shift=0, count=0, n=0, /*j=0, p=0, q=0, k=0, i=0*/ m=0, cchsamples=256, cchlength=10, slot=15, fframeno=150;
	int w1length=17, cframeno=150, nfc1=15, nfc2=9, nfc3=3, idx=1, tticonstant=269, delaylength=21, dlength=10;
	int pvec=30, sc1=256, sc2=7, bitc=8, crcconst1=246, crcconst2=261, bit=15, stsize=16, slsize=256;
	int peakposition=0, samplesmargin=10, /*jk=0,*/ plmnl=0;


	powertemp=0; 
	sft=0; 
	slt=0; 
	sll=0; 
	sfl=0; 
	sil=0; 
	sct=0;
	seg_idx = 0;
	seg_count = 0;
	intialvalue=1.0;
	twopi=(44.0f/7.0f);
	pi=(22.0f/7.0f);
	piby4=(22.0f/28.0f);
	crc16=0;
	rm16=0;
	pl=0;
	as=0;
	bs=0;
	cs=0;
	ds=0;
	accconstant=4.0;

	ippsZero_8u(s1, (sc1+1));
	ippsZero_8u(s2, (sc2+1));
	ippsZero_8u(r, (bitc+1));
	ippsZero_32f(realccpch, ((nf+2)*cchlength*slot));
	ippsZero_32fc(y1, ((nf+2)*cchlength*slot));
	ippsZero_32fc(y2, ((nf+2)*cchlength*slot));
	ippsZero_32fc(e1, ((nf+2)*cchlength*slot));	
	//ippsZero_32f(realf, ((nf+2)*cchlength*slot));
	//ippsSet_32f(-piby4, imagccpch1, ((nf+2)*cchlength*slot));
	//ippsSet_32f(piby4, imagccpch2, ((nf+2)*cchlength*slot));

	// Bug Fix:  Zero out entire acc matrix.  Otherwise matrix will slowly populate with NaN stopping all subsequent decodes from occurring.
	// This should only be done upon entry to process.  The acc matrix is used within a for loop that uses the past results.
	for(int i = 0; i < 257; i++)
		ippsZero_32f(&acc[i][0], 270);

	// taking average value
	ippsMagnitude_32fc(umtssignal, magsignal, signallength);
	ippsSqr_32f_I(magsignal, signallength);
	ippsMean_32f(magsignal, signallength, &meansignal, ippAlgHintAccurate);
	ippsSqrt_32f_I(&meansignal, 1);

	// normalization
	ippsCplxToReal_32fc(umtssignal, realfilter, imagfilter, signallength);
	ippsDivC_32f_I(meansignal, realfilter, signallength);
	ippsDivC_32f_I(meansignal, imagfilter, signallength);
	ippsRealToCplx_32f(realfilter, imagfilter, hammingsignal, signallength);

	umts_signal_filter_.filter(hammingsignal, kaiserresample, signallength / down_factor_);

	// taking scrambling code array from cpich template
	ippsCopy_32fc(&(cpichtemplate[scr*cpichsamples]), cpichcode, cpichsamples);
	
	// upsampling of the cpich template
	ippsSampleUp_32fc(cpichcode, (upsamplelength / cpich_resample_factor_), upsamplecpich, (&upsamplelength), cpich_resample_factor_, (&cpichupphase));

	ippsCplxToReal_32fc(cpichcode, cpichcodereal, cpichcodeimag, cpichsamples);
	ippsMulC_32f_I(value, cpichcodeimag, cpichsamples);
	ippsRealToCplx_32f(cpichcodereal, cpichcodeimag, cpichcode, cpichsamples);

	//Added to decode all the BCCH Frames - Raj
	if(convert_to_bitstream(startofframe))
	{
		for(int bit_stream_index=0;bit_stream_index < num_decoded_bcch_stream_;bit_stream_index++)
		{
			consolidate_bit_stream(bit_stream_index);
			umts_bcch_bch_message_aggregate tmp_bch(bchinfo);
			asn1_decoder_.decode_bcch_bch_message(&consolidated_bit_stream_[0], consolidated_bit_stream_.size(), 4, tmp_bch);
			bchinfo.update_info(tmp_bch);
		}
	}

	//std::cout << successful_decodes_ << "\t";

	return 0;
}	

bool umts_bch_decoder::convert_to_bitstream(int startofframe)
{	
	bool successful_decode = false;

	if(startofframe - signal_over_sampling_rate_ * N_TOTAL_CHIPS_CPICH  > 0)
		startofframe -= (int)boost::math::round(signal_over_sampling_rate_* N_TOTAL_CHIPS_CPICH);

	int esamples = 20;
	int hamminglength=129, kaiserlength=5121;
	int cpichcodes=512, cpichupphase=0, cpichsamples=38400, payl=0; 
	int upsamplelength=10240, /*scr,*/ peakindex=0, offset=0, numberframes=0, nf = 4, peakthreshold=-10;
	int	shift=0, count=0, schip, n=0, /*j=0, p=0, q=0, k=0, i=0*/ m=0, cchsamples=256, cchlength=10, slot=15,fframeno= 0;// fframeno=150;
	int w1length=17, cframeno=150, nfc1=15, nfc2=9, nfc3=3, idx=1, tticonstant=269, delaylength=21, dlength=10;
	int pvec=30, sc1=256, sc2=7, bitc=8, crcconst1=246, crcconst2=261, bit=15, stsize=16, slsize=256;
	int peakposition=0, samplesmargin=10, /*jk=0,*/ plmnl=0, cpichupfactor=5;


	powertemp=0; 
	sft=0; 
	slt=0; 
	sll=0; 
	sfl=0; 
	sil=0; 
	sct=0;
	seg_idx = 0;
	seg_count = 0;
	intialvalue=1.0;
	twopi=(44.0f/7.0f);
	pi=(22.0f/7.0f);
	piby4=(22.0f/28.0f);
	crc16=0;
	rm16=0;
	pl=0;
	as=0;
	bs=0;
	cs=0;
	ds=0;
	accconstant=4.0;
	num_decoded_bcch_stream_ = 0;
	
	ippsZero_32f(realf, ((nf+2)*cchlength*slot));
	ippsSet_32f(-piby4, imagccpch1, ((nf+2)*cchlength*slot));
	ippsSet_32f(piby4, imagccpch2, ((nf+2)*cchlength*slot));


	//-------------------------
	// cross correlation of the upsampled signal with upsampled cpich scrambling code array and taking absoulte of that
	peakposition = (startofframe * up_factor_ / down_factor_);

	// Bug Fix:  samplesmargin should not be greater than peakposition to ensure no access violation occurs.
	if(samplesmargin > peakposition)
		samplesmargin = peakposition;

	ippsCopy_32fc(&kaiserresample[peakposition-samplesmargin], shortkaiserresample, (upsamplelength+esamples));
	ippsCrossCorr_32fc(upsamplecpich, upsamplelength, shortkaiserresample, (upsamplelength+esamples), signalscrcorr, (upsamplelength+esamples), 0);
	ippsMagnitude_32fc(signalscrcorr, abscorr, (upsamplelength+esamples));
	ippsMaxIndx_32f(abscorr, (upsamplelength+esamples), &peakvalue, &peakindex);
	offset = peakindex+peakposition-samplesmargin;

	// Bug Fix:  offset should not be greater than cpichsamples * cpich_resample_factor_
	if(offset > cpichsamples * cpich_resample_factor_)
		offset -= cpichsamples * cpich_resample_factor_;

	{
		Ipp32fc *tmp_kaiser_resample = kaiserresample;
		int tmp_resample_length = resamplelength;

		ippsZero_32fc(inputsignal, ((cpichsamples*cpich_resample_factor_)-offset));
		ippsCopy_32fc(tmp_kaiser_resample, &inputsignal[(cpichsamples*cpich_resample_factor_)-offset], tmp_resample_length);
		numberframes = (tmp_resample_length+(cpichsamples*cpich_resample_factor_)-offset)/(cpichsamples*cpich_resample_factor_);

		// using number of frames and slots we are finding the cpich and ccpch arrays
		for(int i=0; i<=(numberframes+1); i++)
		{
			for(int j=0; j<slot; j++)
			{
				schip = (cpichsamples*cpich_resample_factor_*i) + ((cpichsamples*cpich_resample_factor_/slot)*j) + shift;
				// We decode more frames with this commented
				//if((j==0) && (i!=0) ){				//	  
				//       ippsCopy_32fc(&inputsignal[schip], shortkaiserresample, (upsamplelength));
		  //             ippsCrossCorr_32fc(upsamplecpich, upsamplelength, shortkaiserresample, (upsamplelength), signalscrcorr, (upsamplelength), 0);
		  //             ippsMagnitude_32fc(signalscrcorr, abscorr, (upsamplelength));
		  //             ippsMaxIndx_32f(abscorr, (upsamplelength+esamples), &peakvalue, &peakindex);
		  //             offset = peakindex - samplesmargin;
				//	    if((offset>0) && (offset < 128))
				//		   schip = schip + offset;
				//}
				
				// checking if schip is greater than some value or not
				if(schip > ((tmp_resample_length+(cpichsamples*cpich_resample_factor_)-offset+1)-(cpichsamples*cpich_resample_factor_/slot)))
					j=slot;
				else
				{
					// taking some values of input signal (only 2560)
					ippsCopy_32fc(&(inputsignal[schip]), slotarray, (cpichsamples*cpich_resample_factor_/slot));
					m=0;

					for(int p=0; p<(cpichsamples*cpich_resample_factor_/slot);)
					{
						//copying the those 2560 values into a different arrays depending on early, ontime and late timing
						ippsCopy_32fc(&(slotarray[p+1]), &(earlyslot[m]), 1);
						ippsCopy_32fc(&(slotarray[p+2]), &(ontimeslot[m]), 1);
						ippsCopy_32fc(&(slotarray[p+3]), &(lateslot[m]), 1);
						p=p+5;
						m++;
					}

					// multiplying those three arrays with scrambling code array
					ippsMul_32fc_I(&(cpichcode[(cpichsamples/slot)*j]), earlyslot, (cpichsamples/slot));
					ippsMul_32fc_I(&(cpichcode[(cpichsamples/slot)*j]), ontimeslot, (cpichsamples/slot));
					ippsMul_32fc_I(&(cpichcode[(cpichsamples/slot)*j]), lateslot, (cpichsamples/slot));

					// making the multiplied arrays into 256 by 10 matrix in next 3 for loops
					for(int p=0; p<cchlength; p++)
					{
						for(int q=0; q<cchsamples; q++)
							ippsCopy_32fc(&(earlyslot[p*cchsamples+q]), &(rsearlyslot[q][p]), 1);
					}	
									
					for(int p=0; p<cchlength; p++)
					{
						for(int q=0; q<cchsamples; q++)
							ippsCopy_32fc(&(ontimeslot[p*cchsamples+q]), &(rsontimeslot[q][p]), 1);
					}

					for(int p=0; p<cchlength; p++)
					{
						for(int q=0; q<cchsamples; q++)
							ippsCopy_32fc(&(lateslot[p*cchsamples+q]), &(rslateslot[q][p]), 1);
					}
				
					// calculating mean of those three reshaped arrays
					for(int k=0; k<cchlength; k++)
					{
						for(int p=0; p<cchsamples; p++)
						{
							ippsCopy_32fc(&(rsearlyslot[p][k]), &(tempearlyslot[p]), 1);
							ippsCopy_32fc(&(rsontimeslot[p][k]), &(tempontimeslot[p]), 1);
							ippsCopy_32fc(&(rslateslot[p][k]), &(templateslot[p]), 1);
						}
						ippsMean_32fc(tempearlyslot, cchsamples, &(meanearly[k]), ippAlgHintAccurate);
						ippsMean_32fc(tempontimeslot, cchsamples, &(meanontime[k]), ippAlgHintAccurate);
						ippsMean_32fc(templateslot, cchsamples, &(meanlate[k]), ippAlgHintAccurate);
					}

					ippsMagnitude_32fc(meanearly, absearly, cchlength);
					ippsMagnitude_32fc(meanontime, absontime, cchlength);
					ippsMagnitude_32fc(meanlate, abslate, cchlength);
					ippsMean_32f(absearly, cchlength, &earlymean, ippAlgHintAccurate);
					ippsMean_32f(absontime, cchlength, &ontimemean, ippAlgHintAccurate);
					ippsMean_32f(abslate, cchlength, &latemean, ippAlgHintAccurate);

					// checking the three conditions to create cpich and ccpch arrays
					if((latemean > ontimemean) && (latemean > earlymean))
					{
						count = count+1;
						shift = shift+1;

						// multiplying cchv0 and cchv1 with reshaped arrays to calculate mean and copying them into cpich and
						// ccpch arrays
						for(int p=0; p<cchsamples; p++)
							ippsMul_32fc(&(cchv0[p][0]), &(rslateslot[p][0]), &(latemul0[p][0]), cchlength);
					
						for(int k=0; k<cchlength; k++)
						{
							for(int p=0; p<cchsamples; p++)
								ippsCopy_32fc(&(latemul0[p][k]), &(multemp[p]), 1);
							
							ippsMean_32fc(multemp, cchsamples, &(lmulmean0[k]), ippAlgHintAccurate);
						}

						ippsCopy_32fc(lmulmean0, &(cpich[n]), cchlength);

						for(int p=0; p<cchsamples; p++)
							ippsMul_32fc(&(cchv1[p][0]), &(rslateslot[p][0]), &(latemul1[p][0]), cchlength);
								
						for(int k=0; k<cchlength; k++)
						{
							for(int p=0; p<cchsamples; p++)
								ippsCopy_32fc(&(latemul1[p][k]), &(multemp[p]), 1);
							
							ippsMean_32fc(multemp, cchsamples, &(lmulmean1[k]), ippAlgHintAccurate);
						}

						ippsCopy_32fc(lmulmean1, &(ccpch[n]), cchlength);
						n=n+cchlength;
					}
					else if((earlymean > ontimemean) && (earlymean > latemean))
					{
						count = count+1;
						shift = shift-1;
					
						// multiplying cchv0 and cchv1 with reshaped arrays to calculate mean and copying them into cpich and
						// ccpch arrays
						for(int p=0; p<cchsamples; p++)
							ippsMul_32fc(&(cchv0[p][0]), &(rsearlyslot[p][0]), &(earlymul0[p][0]), cchlength);
					
						for(int k=0; k<cchlength; k++)
						{
							for(int p=0; p<cchsamples; p++)
								ippsCopy_32fc(&(earlymul0[p][k]), &(multemp[p]), 1);
							
							ippsMean_32fc(multemp, cchsamples, &(emulmean0[k]), ippAlgHintAccurate);
						}

						ippsCopy_32fc(emulmean0, &(cpich[n]), cchlength);

						for(int p=0; p<cchsamples; p++)
							ippsMul_32fc(&(cchv1[p][0]), &(rsearlyslot[p][0]), &(earlymul1[p][0]), cchlength);
										
						for(int k=0; k<cchlength; k++)
						{
							for(int p=0; p<cchsamples; p++)
								ippsCopy_32fc(&(earlymul1[p][k]), &(multemp[p]), 1);
						
							ippsMean_32fc(multemp, cchsamples, &(emulmean1[k]), ippAlgHintAccurate);
						}

						ippsCopy_32fc(emulmean1, &(ccpch[n]), cchlength);
						n=n+cchlength;
					}
					else
					{
						// multiplying cchv0 and cchv1 with reshaped arrays to calculate mean and copying them into cpich and
						// ccpch arrays
						for(int p=0; p<cchsamples; p++)
							ippsMul_32fc(&(cchv0[p][0]), &(rsontimeslot[p][0]), &(ontimemul0[p][0]), cchlength);
					
						for(int k=0; k<cchlength; k++)
						{
							for(int p=0; p<cchsamples; p++)
								ippsCopy_32fc(&(ontimemul0[p][k]), &(multemp[p]), 1);
							
							ippsMean_32fc(multemp, cchsamples, &(omulmean0[k]), ippAlgHintAccurate);
						}

						ippsCopy_32fc(omulmean0, &(cpich[n]), cchlength);

						for(int p=0; p<cchsamples; p++)
							ippsMul_32fc(&(cchv1[p][0]), &(rsontimeslot[p][0]), &(ontimemul1[p][0]), cchlength);
										
						for(int k=0; k<cchlength; k++)
						{
							for(int p=0; p<cchsamples; p++)
								ippsCopy_32fc(&(ontimemul1[p][k]), &(multemp[p]), 1);
							
							ippsMean_32fc(multemp, cchsamples, &(omulmean1[k]), ippAlgHintAccurate);
						}
					
						ippsCopy_32fc(omulmean1, &(ccpch[n]), cchlength);
						n=n+cchlength;
					}
				}
			}
		}

		n = 150;
		for(int fn=0;fn<numberframes;fn++)
       {

		// calculating phase angle
		ippsPhase_32fc(&(cpich[(fframeno+fn)*150]), cpichangle, n-fframeno);
			
		// adding +/-2*pi for jump greater than pi radians between consecutive elements
		for(int i=0; i<n-fframeno-1; i++)
		{
			ippsSub_32f(&(cpichangle[i]), &(cpichangle[i+1]), &cpichsub, 1);

			if(cpichsub >= pi)
				ippsSubC_32f_I(twopi, &(cpichangle[i+1]), 1);
			else if (cpichsub <= -pi)
				ippsAddC_32f_I(twopi, &(cpichangle[i+1]), 1); 
		}
		
		// calculating frequency error
		for(int i=0; i<n-fframeno; i++)
			ippsSet_32f(intialvalue+i, &(cpichindex[i]), 1);
		
		ippsMean_32f(cpichangle, n-fframeno, &anglemean, ippAlgHintAccurate);
		ippsMean_32f(cpichindex, n-fframeno, &indexmean, ippAlgHintAccurate);
		ippsSubC_32f(cpichangle, anglemean, anglesub, n-fframeno);
		ippsSubC_32f_I(indexmean, cpichindex, n-fframeno);
		ippsSqr_32f(cpichindex, indexsqr, n-fframeno);
		ippsMul_32f(cpichindex, anglesub, mulindang, n-fframeno);
		ippsMean_32f(indexsqr, n-fframeno, &sqrmean, ippAlgHintAccurate);
		ippsMean_32f(mulindang, n-fframeno, &mulmean, ippAlgHintAccurate);
		freq = mulmean/sqrmean;

		// correcting cpich frequency error
		ippsSet_32f(-freq, imagf, n);
		
		for(int i=0; i<n; i++)
			ippsMulC_32f_I((Ipp32f)(i + 1), &(imagf[i]), 1);
		
		ippsRealToCplx_32f(realf, imagf, cplxf, n);
		ippsExp_32fc_A24(cplxf, expfreq, n);
		ippsMul_32fc_I(expfreq, &(cpich[(fframeno+fn)*150]), n);

		// calculating phase error
		ippsPhase_32fc(&(cpich[(fframeno+fn)*150]), cpichangle, n-fframeno);
			
		for(int i=0; i<n-fframeno-1; i++)
		{
			ippsSub_32f(&(cpichangle[i]), &(cpichangle[i+1]), &cpichsub, 1);

			if(cpichsub >= pi)
				ippsSubC_32f_I(twopi, &(cpichangle[i+1]), 1);
			else if (cpichsub <= -pi)
				ippsAddC_32f_I(twopi, &(cpichangle[i+1]), 1); 
		}

		ippsMean_32f(cpichangle, n-fframeno, &phase, ippAlgHintAccurate);

		// correcting cpich phase error
		cplxphase.im = -(phase-piby4);
		ippsExp_32fc_A24(&cplxphase, &expphase, 1);
		ippsMulC_32fc_I(expphase, &(cpich[(fframeno+fn)*150]), n);
		
		// correcting ccpch frequency and phase error
		ippsAddC_32f_I(-(phase-piby4), imagf, n);
		ippsRealToCplx_32f(realf, imagf, cplxf, n);
		ippsExp_32fc_A24(cplxf, expfreq, n);
		ippsMul_32fc_I(expfreq,&(ccpch[(fframeno+fn)*150]), n);
		
	   }
		// Replaces phy_equalize matlab function.  Equivalent to reshape matlab..
		int ccpch_position = 0;
		for(int i = 0; i < nfc1*nfc2*numberframes; i += 9)
		{
			//ippsCopy_32fc(&ccpch[151 + ccpch_position ], &ccpchs2[i], 9);
			ippsCopy_32fc(&ccpch[ccpch_position+1], &ccpchs2[i], 9);
			ccpch_position += 10;
		}

		// BCH decoding
		// check first hypothesis
		// display(' ');
		// display('   BCH DECODING ');
		// display('Testing TTI Alignment 1 ');
		//nfc3 = 4;
		
		//while(idx <= (nfc1*nfc2*nfc3)-tticonstant)
		while(idx <= (nfc1*nfc2*numberframes)-tticonstant)
		{
			ippsCopy_32fc(&(ccpchs2[idx-1]), tti, (tticonstant+1));
			ippsReal_32fc(tti, ttireal, (tticonstant+1));
			ippsImag_32fc(tti, ttiimag, (tticonstant+1));

			for(int i=0; i<(tticonstant+1); i++)
			{
				ippsCopy_32f(&(ttireal[i]), &(dd2n[2*i]), 1);
				ippsCopy_32f(&(ttiimag[i]), &(dd2n[(2*i)+1]), 1);
			}

			// normalize
			ippsAbs_32f(dd2n, absdd2n, (2*(tticonstant+1)));
			ippsMean_32f(absdd2n, (2*(tticonstant+1)), &meandd2n, ippAlgHintAccurate);
			ippsDivC_32f_I(meandd2n, dd2n, (2*(tticonstant+1)));

			// frame parsing
			ippsCopy_32f(dd2n, ddf0, (tticonstant+1));
			ippsCopy_32f(&(dd2n[tticonstant+1]), ddf1, (tticonstant+1));
			
			if((tticonstant+1) != 270)
			{
				;
			}
			else if (2*(tticonstant+1) != 540)
			{
				;
			}
			else
			{
				for(int i=0; i<=bitc; i++)
				{
					for(int j=0; j<pvec; j++)
					{
						ippsCopy_32f(&(ddf0[i+(j*(bitc+1))]), &(ds01[i][j]), 1);
						ippsCopy_32f(&(ddf1[i+(j*(bitc+1))]), &(ds11[i][j]), 1);
					}
				}
				
				for(int i=0; i<=bitc; i++)
				{
					for(int j=0; j<pvec; j++)
					{
						ippsCopy_32f(&(ds01[i][perm[j]]), &(ds02[i][j]),  1);
						ippsCopy_32f(&(ds11[i][perm[j]]), &(ds12[i][j]),  1);
					}
				}

				for(int i=0; i<=bitc; i++)
				{
					for(int j=0; j<pvec; j++)
					{
						ippsCopy_32f(&(ds02[i][j]), &(ddf01[(i*pvec)+j]), 1);
						ippsCopy_32f(&(ds12[i][j]), &(ddf11[(i*pvec)+j]), 1);
					}
				}
			
				for(int i=0; i<(tticonstant+1); i++)
				{
					ippsCopy_32f(&(ddf01[i]), &(ddtti[2*i]), 1);
					ippsCopy_32f(&(ddf11[i]), &(ddtti[(2*i)+1]), 1);
				}
					
				// decoder
				ippsZero_32f(&(acc[0][0]), 1);
				ippsZero_32f(&(acc[128][0]), 1);
				ippsZero_8u(sd, (tticonstant+1));
				ippsZero_32f(se, (tticonstant+1));


				for(int i=0; i<(tticonstant+1); i++)
				{
					ippsSubCRev_32f(&(ddtti[2*i]), (Ipp32f)(1.0), &temp1ddtti, 1);
					ippsSqr_32f_I(&temp1ddtti, 1);
					ippsSubCRev_32f(&(ddtti[(2*i)+1]), (Ipp32f)(1.0), &temp2ddtti, 1);
					ippsSqr_32f_I(&temp2ddtti, 1);
					ippsAdd_32f(&temp1ddtti, &temp2ddtti, &(e[0]), 1);
					ippsSubCRev_32f(&(ddtti[(2*i)+1]), (Ipp32f)(-1.0), &temp3ddtti, 1);
					ippsSqr_32f_I(&temp3ddtti, 1);
					ippsAdd_32f(&temp1ddtti, &temp3ddtti, &(e[1]), 1);
					ippsSubCRev_32f(&(ddtti[2*i]), (Ipp32f)(-1.0), &temp4ddtti, 1);
					ippsSqr_32f_I(&temp4ddtti, 1);
					ippsAdd_32f(&temp4ddtti, &temp2ddtti, &(e[2]), 1);
					ippsAdd_32f(&temp4ddtti, &temp3ddtti, &(e[3]), 1);

					for(int j=1; j<=(sc1/2); j++)
					{
						ippsCopy_8u(&(sv[(sv[j][5])+1][1]), &idx1, 1);
						ippsCopy_8u(&(sv[(sv[j][6])+1][1]), &idx2, 1);
						
						if(i==0)
						{
							ippsCopy_32f(&(e[idx1]), &(etemp[0]), 1);
							ippsCopy_32f(&(e[idx2]), &(etemp[1]), 1);
							ippsMin_32f(etemp, 2, &emin);
							ippsAddC_32f_I(emin, &(acc[j-1][i]), 1);
						}
						else
						{
							ippsAddC_32f(&(acc[sv[j][5]][i-1]), e[idx1], &(ac[0]), 1);
							ippsAddC_32f(&(acc[sv[j][6]][i-1]), e[idx2], &(ac[1]), 1);
							ippsMin_32f(ac, 2, &(acc[j-1][i]));
						}
					}

					for(int j=((sc1/2)+1); j<=sc1; j++)
					{
						ippsCopy_8u(&(sv[(sv[j][5])+1][2]), &idx1, 1);
						ippsCopy_8u(&(sv[(sv[j][6])+1][2]), &idx2, 1);
						
						if(i==0)
						{
							ippsCopy_32f(&(e[idx1]), &(etemp[0]), 1);
							ippsCopy_32f(&(e[idx2]), &(etemp[1]), 1);
							ippsMin_32f(etemp, 2, &emin);
							ippsAddC_32f_I(emin, &(acc[j-1][i]), 1);
						}
						else
						{
							ippsAddC_32f(&(acc[sv[j][5]][i-1]), e[idx1], &(ac[0]), 1);
							ippsAddC_32f(&(acc[sv[j][6]][i-1]), e[idx2], &(ac[1]), 1);
							ippsMin_32f(ac, 2, &(acc[j-1][i]));
						}
					}
				}

				// path traceback				
				ippsSet_8u(1, dec, (tticonstant+1));
				ippsCopy_32f(&(acc[0][tticonstant]), &(se[tticonstant]), 1);
				ippsZero_8u(&(dec[tticonstant]), 1);

				for(int i=(tticonstant-1); i>=0; i--)
				{
					if((acc[sv[(sd[i+1])+1][5]][i]) < (acc[sv[(sd[i+1])+1][6]][i]))
					{
						ippsCopy_32f(&(acc[sv[(sd[i+1])+1][5]][i]), &(se[i]), 1);
						ippsCopy_8u(&(sv[(sd[i+1])+1][5]), &(sd[i]), 1);
					}
					else
					{
						ippsCopy_32f(&(acc[sv[(sd[i+1])+1][6]][i]), &(se[i]), 1);
						ippsCopy_8u(&(sv[(sd[i+1])+1][6]), &(sd[i]), 1);
					}
					ippsCopy_8u(&(sv[(sd[i])+1][7]), &(dec[i]), 1);
				}
			
				crc16 = 0;
				rm16 = 0;
				err = 0;
				// crc error check
				crc16 = bintodec((&(dec[crcconst1])), (bitc*2));
				ippsZero_8u(rn, (bitc*2));
				
				for(int i=0; i<crcconst1; i++)
				{
					ippsXor_8u(&(dec[i]), &(rn[15]), &sr1, 1);
					ippsXor_8u(&sr1, &(rn[4]), &sr5, 1);
					ippsXor_8u(&sr1, &(rn[11]), &sr12, 1);
					ippsMove_8u(rn, &(rm[1]), ((bitc*2)-1));
					ippsCopy_8u(&sr1, &(rm[0]), 1);
					ippsCopy_8u(&sr5, &(rm[5]), 1);
					ippsCopy_8u(&sr12, &(rm[12]), 1);
					ippsMove_8u(rm, rn, (bitc*2));
				}

				rm16 = bintodec((&(rm[0])), (bitc*2)); 
				err = crc16 - rm16;

				if(err == 0)
				{
					
				   // idx=idx+tticonstant+1;
					successful_decode = true;
					num_decoded_bcch_stream_++;
					ippsCopy_8u(dec,
						        &decoded_bcch_stream[(num_decoded_bcch_stream_-1)*(tticonstant+1)],
								(tticonstant+1));

					++successful_decodes_;
				}
				else
				{
					//if(idx == 1)
					if(successful_decode == false)
					{
						idx = idx-135;
						//idx = idx+135;
					}
					else
					{
						;
					}
				}
				//idx=idx+270;
				idx=idx+tticonstant+1;
			}
		}
	}					

	return successful_decode;
}

unsigned int umts_bch_decoder::bintodec(unsigned __int8 *bitarray, unsigned __int8 size)
{
	unsigned int decimal_num = 0;

	for(int i = 0; i < size; i++)
	{
		decimal_num = decimal_num << 1;
		decimal_num |= bitarray[i];
	}

	return decimal_num;
}

void umts_bch_decoder::output_ascii_hex_string(const umts_bcch_bch_message_aggregate& bchinfo)
{
	std::string filename("wcmda_bit_stream.bat");

	std::ofstream file(filename.c_str(), std::ios_base::app);

	if(!file)
		throw rf_phreaker::umts_analysis_error("Unable to open debug file for ascii output of wcdma bit stream.");

	//file << "bit_stream_" << bit_stream_counter_++ << "\t";
	file << "\"C:\\Program Files (x86)\\Decoder\\Decoder.exe\" RRC.BCCH.BCH ";

	for(uint32_t bit_stream_position = 0; bit_stream_position < consolidated_bit_stream_.size(); bit_stream_position++)
	{
		file << std::setw(2) << std::setfill('0') <<   std::hex << (uint32_t)consolidated_bit_stream_[bit_stream_position]; // Cast to an uint32_t so it outputs properly in hex.
	}
	
	file << std::dec << "\n::\t" << bchinfo.unique_sector_key_ << "\t" << bchinfo.system_frame_number_ << "\t" << bchinfo.mcc_ << "\t" << bchinfo.mnc_ << "\t" << bchinfo.lac_ << "\t" << bchinfo.cid_;

	file << std::endl;
}

void umts_bch_decoder::output_binary_string(const umts_bcch_bch_message_aggregate& bchinfo)
{
	std::string filename("wcmda_bit_stream");
	filename.append(boost::lexical_cast<std::string>(bit_stream_counter_++)).append(".bin");

	std::ofstream file(filename.c_str(), std::ios_base::binary);

	if(!file)
		throw rf_phreaker::umts_analysis_error("Unable to open debug file for ascii output of wcdma bit stream.");

	file.write((char*)&bchinfo.unique_sector_key_, sizeof(bchinfo.unique_sector_key_));

	for(uint32_t bit_stream_position = 0; bit_stream_position < consolidated_bit_stream_.size(); bit_stream_position++)
	{
		file.write((const char*)&consolidated_bit_stream_[bit_stream_position], sizeof(uint8_t));
	}
}

void umts_bch_decoder::consolidate_bit_stream(unsigned char bit_stream_index)
{	
	memset(&consolidated_bit_stream_[0], 0, consolidated_bit_stream_.size());

	for(uint32_t bit_stream_position = 0; bit_stream_position < consolidated_bit_stream_.size(); bit_stream_position++)
	{
		//consolidated_bit_stream_[bit_stream_position] = (uint8_t)bintodec(&dec[bit_stream_position*8], 8);
	    consolidated_bit_stream_[bit_stream_position] = (uint8_t)bintodec(&decoded_bcch_stream[(UMTS_BCCH_TTI_BITSIZE*bit_stream_index)+(bit_stream_position*8)], 8); 
	}
}
