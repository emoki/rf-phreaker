//
//  BladeDevice.h
//  bladeXcode
//
//  Created by Cameron on 3/30/14.
//  Copyright (c) 2014 Cameron. All rights reserved.
//

#ifndef __bladeXcode__BladeDevice__
#define __bladeXcode__BladeDevice__

#include <string>
#include "libbladeRF.h"

namespace rf_phreaker { namespace gps_comm {

    class BladeDevice
    {
    public:
    	enum GPIODirection
    	{
    		GPIO_IN = 0,
    		GPIO_OUT = 1
    	};
    private:
		bool isIndirect;	//whether or not an open device was provided on construction (true), or not(false).
    	bool null;
        std::string serial;
        
        bladerf* handle;
        bladerf_devinfo devinfo;
        bool isOpen;
        bladerf_module activeModule;
        
        // could make a template later... not really needed now though
        bool getbit(uint32_t field, int i); // from zero
        uint32_t setbit(uint32_t field, int i, bool val);

    public:
        BladeDevice();
        BladeDevice(bladerf* open_device);		// this is really only here because this is a wrapper class
        										// and wrapping an already open pointer can be really useful
        ~BladeDevice();
        BladeDevice(const BladeDevice& ref);	//copy

        std::string getSerial();
        bladerf_devinfo getInfo();

        void load(bladerf_devinfo& devinfo);
        bool open();
        bool close();
        void loadFPGAImage(std::string path);
        void setActiveModule(bladerf_module module);  // all subsequent function
        												// calls that rely on a module will use this one

        uint32_t 	getXBGPIO();						//returns register
        bool	 	getXBGPIO(uint32_t index);			//returns bit, index start @ 1
        void 		setXBGPIO(uint32_t val);			//sets register
        void 		setXBGPIO(uint32_t index, bool val);	//sets bit, index start @ 1


        uint32_t 	getXBGPIODir();
        bool	 	getXBGPIODir(uint32_t index);
        void 		setXBGPIODir(uint32_t val);
        void 		setXBGPIODir(uint32_t index, bool val);

        uint32_t 	getConfigGPIO();
        bool	 	getConfigGPIO(uint32_t index);
        void 		setConfigGPIO(uint32_t val);
        void 		setConfigGPIO(uint32_t index, bool val);

        uint8_t xboardSPIRead();
        void xboardSPIWrite(uint8_t val);

        uint32_t xboardUARTRead();
        void xboardUARTWrite(char val);
        void xboardUARTBaud(uint16_t baud);
        uint32_t xboardUARTHasData();

        bladerf* getHandle();
        uint32_t getSampleRate();
        void setModuleState(bladerf_module module, bool state);
        void setFrequency( uint32_t f);
        uint32_t setBandwidth(uint32_t bw);
        uint32_t getFrequency( );
        uint32_t getBandwidth( );

    };
}}

#endif /* defined(__bladeXcode__BladeDevice__) */
