//
//  BladeContext.h
//  bladeXcode
//
//  Created by Cameron on 3/30/14.
//  Copyright (c) 2014 Cameron. All rights reserved.
//

#ifndef __bladeXcode__BladeContext__
#define __bladeXcode__BladeContext__

#include <vector>
#include <libbladeRF.h>


namespace rf_phreaker { namespace gps_comm {

    class BladeContext
    {
    private:
        bladerf_devinfo* plist;
        std::vector<bladerf_devinfo> devlist;
    public:
        BladeContext();
        //no copy constructor...
        ~BladeContext();
        
        std::vector<bladerf_devinfo>& getDeviceList();
        void printDeviceInfo(bladerf_devinfo& device);
    };
    
}} 

#endif /* defined(__bladeXcode__BladeContext__) */
