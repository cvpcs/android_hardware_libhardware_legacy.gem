//*********************************************************************************
//
//                    Motorola Confidential Proprietary
//
//                Advanced Technology and Software Operations
//              (c) Copyright Motorola 2009, All Rights Reserved
//
// Revision History:
//                            Modification     Tracking
// Author            Date         Number     Description of Changes
// -------------  ----------    ----------   --------------------------------------
// W36255         08/28/2009    LIBtt10910   Initial Version
// W30208         09/09/2009    LIBtt15449   Integrated inspection comments
//
//********************************************************************************
//
// gps_mot_ext.cpp for Motorola A-GPS
//
//*********************************************************************************

#include <hardware_legacy/mot_agps_ext.h>
#include <cutils/properties.h>

#define LOG_TAG "libhardware_legacy"
#include <utils/Log.h>
#include "qemu.h"

extern MotAgpsInterface* gps_get_agps_hardware_interface();


static const MotAgpsInterface*  sMotAgpsInterface = NULL;

static void
agps_find_hardware( void )
{
#ifdef HAVE_GPS_HARDWARE
    sMotAgpsInterface = gps_get_agps_hardware_interface();
#endif
    if (!sMotAgpsInterface)
        LOGD("no AGPS hardware on this device\n");
}

const MotAgpsInterface*
agps_get_interface()
{
    if (sMotAgpsInterface == NULL)
         agps_find_hardware();

    return sMotAgpsInterface;
}
