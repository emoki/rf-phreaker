/*
 * BladeGPS.h
 *
 *  Created on: Jul 23, 2014
 *      Author: ck
 */

#ifndef BLADEGPS_H_
#define BLADEGPS_H_



// minwindef.h has these defined for some reason...
#ifdef IN
	#undef IN
#endif
#ifdef OUT
	#undef OUT
#endif




#include "BladeRF.hpp"
#include <string>


namespace rf_phreaker { namespace gps_comm {

class FrontEndBoard {
public:
	enum ControlPin
		{
			GPS_ON_OFF	=19,
			GPS_WAKEUP	=17,
			GPS_RESET	=18,
			GPS_PPS		=1,
			GPS_RX		=4,
			GPS_TX		=3,
			SPI_CS		=2,
			CSx_BAND_X1	=7,
			CSx_BAND_X2	=6,
			CSx_BAND_X3	=5,
			SW_CHx_V1	=11,
			SW_CHx_V2	=10,
			SW_CHx_V3	=9,
			SW_CHx_V4	=8,
			SW_HIGH_X1	=27,
			SW_HIGH_X2	=26,
			SW_HIGH_X3	=25

		};

private:
	GpsComm& blade;
public:
	FrontEndBoard(GpsComm& blade);
	virtual ~FrontEndBoard();

	void setPin(ControlPin p, bool state);			// sets gpio pins by name
	void setGPIO(uint32_t gpio_index, bool state);	// sets pins by index, starting at 1
	bool getPin(ControlPin p);			// gets gpio pins by name
	bool getGPIO(uint32_t gpio_index);	// gets pins by index, starting at 1


	void setFilterChannel(uint32_t v, bool on);
	void setFilterBand(uint32_t x, bool on);
	void setFilterHigh(uint32_t x, bool on);

	GpsComm& getBlade();

};

}}

#endif /* BLADEGPS_H_ */
