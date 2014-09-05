//
//  BladeContext.cpp
//  bladeXcode
//
//  Created by Cameron on 3/30/14.
//  Copyright (c) 2014 Cameron. All rights reserved.
//


#include <memory>
#include <iostream>

#include "BladeContext.h"
#include "BladeError.h"

using namespace std;
using namespace rf_phreaker::gps_comm;

BladeContext::BladeContext() : plist(0)
{
    
}
BladeContext::~BladeContext()
{
    if(this->plist)
    {
        bladerf_free_device_list(this->plist);
    }
    
    cout << "BLADERF CONTEXT CLEANUP." << endl;
}

std::vector<bladerf_devinfo>& BladeContext::getDeviceList()
{
    if(!this->plist)
    {
        bladerf_devinfo* list;
        int ndev = bladerf_get_device_list(&list);
        if(ndev < 0)
        {
        	//no devices found...
        	cout << "No BladeRF devices found." << endl;
            //BladeError::check(ndev);	//don't throw error on no devices found, it's not critical.
        	ndev = 0;
        }
        else
        {
        	this->plist = list;
        }

        this->devlist = vector<bladerf_devinfo>(list, list + ndev);  // copy all the items into the context list.
    }
    return this->devlist;
}
void BladeContext::printDeviceInfo(bladerf_devinfo& device)
{
	cout << "  Serial: \t\t" << device.serial << endl;
	cout << "  USB BUS: \t\t" << (int)device.usb_bus << endl;
	cout << "  USB ADDR: \t\t" << (int)device.usb_addr << endl;
	cout << "  INSTANCE: \t\t" << (int)device.instance << endl;
	cout << "  BACKEND: \t\t" << (int)device.backend;
	cout << "  (";
    switch(device.backend){
        case BLADERF_BACKEND_ANY:
            cout << "ANY"; break;
        case BLADERF_BACKEND_LINUX:
            cout << "LINUX"; break;
        case BLADERF_BACKEND_LIBUSB:
            cout << "LIBUSB"; break;
        case BLADERF_BACKEND_DUMMY:
            cout << "DUMMY"; break;
        default: cout << "UNKNOWN";
    }
	cout << ")" << endl;
}
