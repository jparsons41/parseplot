//	FireFlyDefs.h - Definitions for the FireFly system
//
//


#ifndef _FIREFLYDEFSOLD_H
#define _FIREFLYDEFSOLD_H

#include <stdint.h>
#include "SyntroLib.h"
#include "gpsdCommonOld.h"

typedef struct
{
        uint32_t headerSizeOld;			// = sizeof(FIREFLY_BLOCK)
        uint32_t headerVersionOld;			// meta-info for future compatibility
		
        char componentNameOld[40];			// component name on Syntro network
        uint32_t dataTypeOld;				// 0 = eoir, 1 = acoustic
        uint32_t sequenceOld;				// starts at zero every run and increments for each block

        uint32_t acousticDecimationLevelOld;

	// driver configuration
        uint32_t adcModeOld;
        uint32_t mcbspClkDivOld;

	// these are bit masks representing the eight channel assignments, no overlap allowed
        uint32_t eoirChannelsOld;			// example 0x03, ch 1-2
        uint32_t acousticChannelsOld;		// example 0xfc, ch 3-8


        // gps info, these are all null terminated ASCII fields, see gpsdCommonOld.h
        struct gpsDataOld gpsDataOld;

	// these three values relate UTC time to kernel timestamp time
        uint32_t correlationSecsOld;
        uint32_t correlationUSecsOld;
        uint64_t correlationTimestampOld;

	// sample times for this block
		
        uint64_t lastTimestampOld;			// the timestamp on the last sample in this block
        uint64_t nanoSecondsPerSampleOld;	// for extrapolating the timestamp for each sample

	// some convenience values, both can be derived
        uint32_t numChannelsOld;
        uint32_t numSamplesPerChannelOld;

        uint32_t dataSizeOld;		// = numChannels * numSamplesPerChannel * sizeof(uint32_t)

	// data follows directly after this header
	// the data is planar, i.e. the samples for each channel are contiguous
	// the planes are in numerical ascending order
} FIREFLY_BLOCK_OLD;

#endif	// _FIREFLYDEFSOLD

