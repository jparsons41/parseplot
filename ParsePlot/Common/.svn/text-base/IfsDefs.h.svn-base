#ifndef IFSDEFS_H
#define IFSDEFS_H

#include <stdint.h>
#include "SyntroLib.h"
#include "gpsdCommon.h"

//	Major Record type values

//#define	FIREFLY_RECORD_TYPE_EOIR		(SYNTRO_RECORD_TYPE_USER + 0)
//#define	FIREFLY_RECORD_TYPE_ACOUSTIC	(SYNTRO_RECORD_TYPE_USER + 1)

//	FIREFLY_RECORD - used to transfer FIREFLY samples
//
//	This structure follows the SYNTRO_EHEAD structure. Immediately following this structure
//	is a FIREFLY_BLOCK.
//  This is the last record information that the Syntro system needs to know about.
//  The data after this is treated as a blob.

//typedef struct
//{
 //   SYNTRO_RECORD_HEADER syntroRecordHeader;	// the record type header (must always be first)
 //   SYNTRO_UC4 recordSize;						// FIREFLY_BLOCK.headerSize + FIREFLY_BLOCK.datasize
//} FIREFLY_RECORD;

//  IFS_BLOCK - used to transfer IFS samples
//
//  This structure follows the FIREFLY_RECORD structure.
//  Immediately following this structure is the data in planar format
//  This is all FireFly specific, invisible to Syntro.

// this number must be incremented if this structure or struct gpsData change
// try to maintain 32-bit alignment for compatibility without pragma pack

//#define FIREFLY_HEADER_VERSION 1
//#define DATATYPE_EOIR 0
//#define DATATYPE_ACOUSTIC 1

typedef struct
{
    char magic[4];
    char version[8];        //starts a 4
    char sensorLocation[24];    //starts at 12
    char sensorName[24];        //starts at 36
    float calibrationLevel;     //starts at 50
    char calibrationDate[32];

//    uint32_t headerSize;			// = sizeof(FIREFLY_BLOCK)
//    uint32_t headerVersion;			// meta-info for future compatibility

//    char componentName[40];			// component name on Syntro network
//    uint32_t dataType;				// 0 = eoir, 1 = acoustic
//    uint32_t sequence;				// starts at zero every run and increments for each block

//    uint32_t acousticDecimationLevel;

//    // driver configuration
//    uint32_t adcMode;
//    uint32_t mcbspClkDiv;

//    // these are bit masks representing the eight channel assignments, no overlap allowed
//    uint32_t eoirChannels;			// example 0x03, ch 1-2
//    uint32_t acousticChannels;		// example 0xfc, ch 3-8

//    // gps info, these are all null terminated ASCII fields, see gpsdCommon.h
//    struct gpsData gpsData;

//    // these three values relate UTC time to kernel timestamp time
//    uint32_t correlationSecs;
//    uint32_t correlationUSecs;
//    uint64_t correlationTimestamp;

//    // sample times for this block

//    uint64_t lastTimestamp;			// the timestamp on the last sample in this block
//    uint64_t nanoSecondsPerSample;	// for extrapolating the timestamp for each sample

//    // some convenience values, both can be derived
//    uint32_t numChannels;
//    uint32_t numSamplesPerChannel;

//    uint32_t dataSize;		// = numChannels * numSamplesPerChannel * sizeof(uint32_t)

    // data follows directly after this header
    // the data is planar, i.e. the samples for each channel are contiguous
    // the planes are in numerical ascending order
} IFS_FILE_BLOCK;



typedef struct
{
  char magic[4];
  char version[8];
  uint32_t utm;
 // char *gpsDate;
 // char *gpsTime;
//  char *latitude;
 // char *latHemi;
 // char *longitude;
 // char *longHemi;
//  char *MSL;
 // char *adcName;
 // float mainSamplingRate;
 // float auxSamplingRate;
  char test[52];
  uint16_t mainNumSamples;
  uint16_t auxNumSamples;
  uint16_t flgSPIXferCnt;
  uint16_t humid_RH;
  uint16_t humid_TMP;
  uint16_t dig_V;
  uint16_t dig_Vmin;
  uint16_t dig_Vmx;
  uint16_t dig_P;
  uint16_t dig_Pmn;
  uint16_t dig_Pmx;
  uint16_t ana_V;
  uint16_t ana_Vmin;
  uint16_t ana_Vmx;
  uint32_t tv_sec;
  uint32_t tv_nsec;
  uint16_t ana_P;
  uint16_t ana_Pmn;
  uint16_t ana_Pmx;
  uint16_t FreqCnt;
  uint16_t mcuHBok;
  uint16_t flgSpixferCnt;
  uint16_t HumidSensorFault;
  uint16_t digFlt;
  uint16_t anaFlt;
  uint16_t spare1;
  uint16_t spare2;
  uint16_t spare3;
  char 	numSats[24];


//    uint32_t headerSize;			// = sizeof(FIREFLY_BLOCK)
//    uint32_t headerVersion;			// meta-info for future compatibility

//    char componentName[40];			// component name on Syntro network
//    uint32_t dataType;				// 0 = eoir, 1 = acoustic
//    uint32_t sequence;				// starts at zero every run and increments for each block

//    uint32_t acousticDecimationLevel;

//    // driver configuration
//    uint32_t adcMode;
//    uint32_t mcbspClkDiv;

//    // these are bit masks representing the eight channel assignments, no overlap allowed
//    uint32_t eoirChannels;			// example 0x03, ch 1-2
//    uint32_t acousticChannels;		// example 0xfc, ch 3-8

//    // gps info, these are all null terminated ASCII fields, see gpsdCommon.h
//    struct gpsData gpsData;

//    // these three values relate UTC time to kernel timestamp time
//    uint32_t correlationSecs;
//    uint32_t correlationUSecs;
//    uint64_t correlationTimestamp;

//    // sample times for this block

//    uint64_t lastTimestamp;			// the timestamp on the last sample in this block
//    uint64_t nanoSecondsPerSample;	// for extrapolating the timestamp for each sample

//    // some convenience values, both can be derived
//    uint32_t numChannels;
//    uint32_t numSamplesPerChannel;

//    uint32_t dataSize;		// = numChannels * numSamplesPerChannel * sizeof(uint32_t)

    // data follows directly after this header
    // the data is planar, i.e. the samples for each channel are contiguous
    // the planes are in numerical ascending order
} IFS_BLOCK;



//	FireFly setting strings for config file

//#define	FIREFLY_PARAMS_EOIRSTREAMNAME		"StreamEOIR"
//#define	FIREFLY_PARAMS_ACOUSTICSTREAMNAME	"StreamAcoustic"

//#define FIREFLY_PARAMS_EOIR_CHANNEL_LIST		"EOIRChannelList"
//#define FIREFLY_PARAMS_ACOUSTIC_CHANNEL_LIST	"AcousticChannelList"
//#define FIREFLY_PARAMS_CHANNEL					"Channel"

//#define FIREFLY_PARAMS_SIMULATION_MODE				"SimulationMode"
//#define FIREFLY_PARAMS_ACOUSTIC_DECIMATION_LEVEL	"AcousticDecimationLevel"
//#define FIREFLY_PARAMS_MCBSP_CLOCK_DIVISOR			"McBSPClockDivisor"
//#define FIREFLY_PARAMS_ADC_MODE						"ADCMode"
//#define FIREFLY_PARAMS_DEVICE_BLOCKS_PER_SYNTRO_REC	"DeviceBlocksPerSyntroRec"










#endif // IFSDEFS_H



