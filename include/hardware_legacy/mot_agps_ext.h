/**********************************************************************************
*
*                     Motorola Confidential Proprietary
*
*                 Advanced Technology and Software Operations
*               (c) Copyright Motorola 2009, All Rights Reserved
*
* Revision History:
*                             Modification     Tracking
* Author            Date         Number     Description of Changes
*--------------  ----------    ----------   --------------------------------------
* W36255         08/28/2009    LIBtt10910   Initial Version
* W30208         09/09/2009    LIBtt15449   Integrated inspection comments
* W30208         10/05/2009    LIBtt21617   Support NV gps lock
*
**********************************************************************************
*
* mot_agps_ext.h for Motorola A-GPS
*
**********************************************************************************/

#if defined(__DEVICE_shadow__) || defined(__DEVICE_droid2__)

#ifndef _AHARDWARE_GPS_H
#define _AHARDWARE_GPS_H

#include "gps.h"

#include <stdint.h>

#if __cplusplus
extern "C" {
#endif

typedef uint16_t MotAGpsPositionMode;

/** Milliseconds since January 1, 1970 */
typedef int64_t GpsUtcTime;

/** maximum number of Space Vehicles for gps_sv_status_callback */
#define GPS_MAX_SVS 32

/** Requested mode for GPS operation. */
// IMPORTANT: Note that the following values must match
// constants in GpsLocationProvider.java.
/** Mode for running GPS standalone (no assistance). */

#define GPS_POSITION_MODE_STANDALONE    0
/** AGPS MS-Based mode. */
#define GPS_POSITION_MODE_MS_BASED      1
/** AGPS MS-Assisted mode. */
#define GPS_POSITION_MODE_MS_ASSISTED   2

/** GPS engine lock values that match the ones in loc_api_common.h */
#define GPS_LOCK_NONE   1
#define GPS_LOCK_MI     2
#define GPS_LOCK_MT     3
#define GPS_LOCK_ALL    4
#define GPS_LOCK_MAX    268435456

/** GPS status event values. */
typedef uint16_t GpsStatusValue;
// IMPORTANT: Note that the following values must match
// constants in GpsLocationProvider.java.
/** GPS status unknown. */
#define GPS_STATUS_NONE             0
/** GPS has begun navigating. */
#define GPS_STATUS_SESSION_BEGIN    1
/** GPS has stopped navigating. */
#define GPS_STATUS_SESSION_END      2
/** GPS has powered on but is not navigating. */
#define GPS_STATUS_ENGINE_ON        3
/** GPS is powered off. */
#define GPS_STATUS_ENGINE_OFF       4
/** Invalid GPS Parameter */
#define GPS_INVALID_PARAMETER       5


/** Flags to indicate which values are valid in a GpsLocation. */
typedef uint16_t GpsLocationFlags;
// IMPORTANT: Note that the following values must match
// constants in GpsLocationProvider.java.
/** GpsLocation has valid latitude and longitude. */
#define GPS_LOCATION_HAS_LAT_LONG   0x0001
/** GpsLocation has valid altitude. */
#define GPS_LOCATION_HAS_ALTITUDE   0x0002
/** GpsLocation has valid speed. */
#define GPS_LOCATION_HAS_SPEED      0x0004
/** GpsLocation has valid bearing. */
#define GPS_LOCATION_HAS_BEARING    0x0008
/** GpsLocation has valid accuracy. */
#define GPS_LOCATION_HAS_ACCURACY   0x0010

/** Flags used to specify which aiding data to delete
    when calling delete_aiding_data(). */
typedef uint16_t GpsAidingData;
// IMPORTANT: Note that the following values must match
// constants in GpsLocationProvider.java.
#define GPS_DELETE_EPHEMERIS        0x0001
#define GPS_DELETE_ALMANAC          0x0002
#define GPS_DELETE_POSITION         0x0004
#define GPS_DELETE_TIME             0x0008
#define GPS_DELETE_IONO             0x0010
#define GPS_DELETE_UTC              0x0020
#define GPS_DELETE_HEALTH           0x0040
#define GPS_DELETE_SVDIR            0x0080
#define GPS_DELETE_SVSTEER          0x0100
#define GPS_DELETE_SADATA           0x0200
#define GPS_DELETE_RTI              0x0400
#define GPS_DELETE_CELLDB_INFO      0x8000
#define GPS_DELETE_ALL              0xFFFF

/** AGPS type */
typedef uint16_t AGpsType;
#define AGPS_TYPE_SUPL          1  /* not applicable to CDMA */
#define AGPS_TYPE_C2K           2 /* Use this for CDMA */

/** AGPS status event values. */
typedef uint16_t AGpsStatusValue;
/** GPS requests data connection for AGPS. */
#define GPS_REQUEST_AGPS_DATA_CONN  1
/** GPS releases the AGPS data connection. */
#define GPS_RELEASE_AGPS_DATA_CONN  2
/** AGPS data connection initiated */
#define GPS_AGPS_DATA_CONNECTED     3
/** AGPS data connection completed */
#define GPS_AGPS_DATA_CONN_DONE     4
/** AGPS data connection failed */
#define GPS_AGPS_DATA_CONN_FAILED   5

/** Presents GPS Fix Rate */
typedef struct {
	/* Number of fixes */
	int  num_fix;
	/* Time between fixes */
	int	 time_between_fixes;
} GpsFixRate;

/** Presents GPS QOS */
typedef struct {
	/* Accuracy in meters */
	int  accuracy;
	/* Desired Performance response quality in terms of time seconds */
	int	 performance;
} GpsQOS;

/** Callback with location information. */
typedef void (* gps_location_callback)(GpsLocation* location);

/** Callback with status information. */
typedef void (* gps_status_callback)(GpsStatus* status);

/** Callback with SV status information. */
typedef void (* gps_sv_status_callback)(GpsSvStatus* sv_info);

/** Callback with AGPS status information. */
typedef void (* agps_status_callback)(AGpsStatus* status);


/** GPS callback structure. */
typedef struct {
        gps_location_callback location_cb;
        gps_status_callback status_cb;
        gps_sv_status_callback sv_status_cb;
	agps_status_callback agps_status_cb;
} MotAGpsCallbacks;



/********************** Motorola Interface Start **********************************/
/** Extended interface for Motorola Verizon AGPS support. */
typedef struct {
    /**
     * Opens the interface and provides the callback routines
     * to the implemenation of this interface.
     */
    int   (*init)( MotAGpsCallbacks* callbacks );

    /** Starts navigating. */
    int   (*start)( void );

    /** Stops navigating. */
    int   (*stop)( void );

    /** Closes the interface. */
    void  (*cleanup)( void );

	/**
     * Sets the IP address and port for the AGPS server .
     */
    int  (*set_server)(AGpsType type, const char* hostname, int port);
	/**
     * fix_frequency represents the time between fixes in seconds.
     * Set fix_frequency to zero for a single-shot fix.
     */
    int   (*set_gps_config)(MotAGpsPositionMode mode, GpsQOS qos, GpsFixRate fixrate);

    /**
     * Specifies that the next call to start will not use the
     * information defined in the flags. GPS_DELETE_ALL is passed for
     * a cold start.
     */
    void  (*delete_aiding_data)(GpsAidingData flags);

    /**
     * Set GPS engine lock in NV.
     */
   int   (*set_engine_lock)(int engine_lock);

    /**
     * Notifies that a data connection is available and sets
     * the name of the APN to be used for SUPL.
     */
    int  (*data_conn_open)( const char* apn );
    /**
     * Notifies that the AGPS data connection has been closed.
     */
    int  (*data_conn_closed)();
    /**
     * Notifies that a data connection is not available for AGPS.
     */
    int  (*data_conn_failed)();

} MotAgpsInterface;

/********************** Motorola Interface End ***********************************/


/** Returns the hardware Motorola AGPS interface. */
const MotAgpsInterface* agps_get_hardware_interface();

#if __cplusplus
}  // extern "C"
#endif

#endif  // _AHARDWARE_GPS_H

#endif  // device_shadow || device_droid2
