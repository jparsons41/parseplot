//	SyntroUtils.h - definitions for common Syntro utilities
//
//  Copyright (c) 2012 Pansenti, LLC.
//	
//  This file is part of SyntroLib
//
//  SyntroLib is free software: you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  SyntroLib is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public License
//  along with SyntroLib.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef		_SYNTROUTILS_H_
#define		_SYNTROUTILS_H_

#include "syntrolib_global.h"
#include "SyntroDefs.h"
#include "HelloDefs.h"
#include "SyntroPlatform.h"


//		Syntro standard settings entries

#define	SYNTRO_RUNTIME_PATH				"runtimePath"				// runtime path
#define	SYNTRO_RUNTIME_RUNMODE			"runtimeRunMode"			// the mode of operation
#define	SYNTRO_RUNTIME_REQINSTANCE		"runtimeReqInstance"		// the apps' requested instance (this is used in initialization only)
#define	SYNTRO_RUNTIME_INSTANCE			"runtimeInstance"			// the apps' instance (this is the actual runtime instance)
#define	SYNTRO_RUNTIME_ADAPTER			"runtimeAdapter"			// ethernet adapter

//	Standard operating parameter entries

#define	SYNTRO_PARAMS_COMPNAME			"componentName"				// name of the component (part of the service path)
#define	SYNTRO_PARAMS_COMPTYPE			"componentType"				// app type of the component
#define	SYNTRO_PARAMS_CONTROLNAME		"controlName"				// name of the SyntroControl to connect to
#define	SYNTRO_PARAMS_HBINTERVAL		"heartbeatInterval"			// time between sent heartbeats
#define	SYNTRO_PARAMS_HBTIMEOUT			"heartbeatTimeout"			// number of hb intervals without hb before timeout

//	Standard stream entries

#define SYNTRO_PARAMS_STREAM_SOURCES	"streamSources"
#define SYNTRO_PARAMS_STREAM_SOURCE		"source"

//	Standard entries for SyntroClient
//
//	"local" services are those published by this client.
//	"remote" services are those to which this client subscribes
//	Each array entry consists of a name, local or remote and type for a service

#define	SYNTRO_PARAMS_CLIENT_SERVICES		"clientServices"		// the array containing the service names, location and types
#define	SYNTRO_PARAMS_CLIENT_SERVICE_NAME	"clientServiceName"		// the name of a service
#define	SYNTRO_PARAMS_CLIENT_SERVICE_TYPE	"clientServiceType"		// multicast or E2E
#define	SYNTRO_PARAMS_CLIENT_SERVICE_LOCATION "clientServiceLocation" // local or remote

#define SYNTRO_PARAMS_SERVICE_LOCATION_LOCAL  "local"				// local service
#define SYNTRO_PARAMS_SERVICE_LOCATION_REMOTE "remote"				// remote service

#define SYNTRO_PARAMS_SERVICE_TYPE_MULTICAST	"multicast"			// the multicast service type string
#define SYNTRO_PARAMS_SERVICE_TYPE_E2E			"E2E"				// the E2E service type string

//	Standard SyntroCFS entries

#define	SYNTRO_PARAMS_CFS_STORES		"CFSStores"					// SyntroCFS stores array
#define	SYNTRO_PARAMS_CFS_STORE			"CFSStore"					// the entries

class	CEndpoint;
class	CSyntroSocket;

// used globally within SyntroLib, need to fix this or hide it
extern	SYNTRO_HEARTBEAT	gMyHeartbeat;				// the global Heartbeat structure for this Component
// non-SyntroLib users should use this only
SYNTROLIB_EXPORT SYNTRO_HEARTBEAT getMyHeartbeat();

extern	SYNTRO_COMPTYPE		gMyCompType;				// my component type
extern	CSyntroSocket		*gpHelloSocket;				// the listening hello socket 

SYNTROLIB_EXPORT void ComponentInit(QSettings *pSettings);
SYNTROLIB_EXPORT void ComponentCleanup();

SYNTROLIB_EXPORT bool checkConsoleModeFlag(int argc, char *argv[]);	// checks if console mode, sets gbConsoleMode and returns state
SYNTROLIB_EXPORT void InitgMyData(QSettings *pSettings);	// inits the global structures
SYNTROLIB_EXPORT SYNTRO_UID getMyUID();
SYNTROLIB_EXPORT const char* getMyDE();
SYNTROLIB_EXPORT void DESetup();									// sets up the directory entry
SYNTROLIB_EXPORT void DEComplete();								// called to complete the DE
SYNTROLIB_EXPORT bool DEAddValue(const char *pTag, const char *pValue);		// adds a string value to the end of the DE

//	This function provides a way of determining if the ack window is open for message transfers.
//	Give it the sequence number of a message to be sent and the last received ack and
//	it returns true if it's ok, false if not.

SYNTROLIB_EXPORT bool IsSendOK(unsigned char nSendSeq, unsigned char nAckSeq);

//	CreateEHEAD creates a SYNTRO_EHEAD structure along with nLen extra bytes for application data

SYNTROLIB_EXPORT SYNTRO_EHEAD *CreateEHEAD(SYNTRO_UID *pSUID, int nSPort, SYNTRO_UID *pDUID, int nDPortm, unsigned char nSeq, int nLen); 

//	SwapEHead swaps UIDs and port numbers and makes it easy to respond to a received message

SYNTROLIB_EXPORT void SwapEHead(SYNTRO_EHEAD *pEH);				// swaps UIDs and port numbers

//	IP Address functions

SYNTROLIB_EXPORT char *DisplayIPAddr(SYNTRO_IPADDR pAddr);		// non-reentrant returns string version of IP
SYNTROLIB_EXPORT void ConvertIPStringToIPAddr(char *pIPStr, SYNTRO_IPADDR pIPAddr);	// converts a string IP address to internal
SYNTROLIB_EXPORT bool IPZero(SYNTRO_IPADDR pAddr);				// returns true if address all zeroes
SYNTROLIB_EXPORT bool IPLoopback(SYNTRO_IPADDR pAddr);			// returns true if address is 127.0.0.1

//	UID manipulation functions

SYNTROLIB_EXPORT void UIDSTRtoUID(SYNTRO_UIDSTR pS, SYNTRO_UID *pD);		// converts a string UID to a binary
SYNTROLIB_EXPORT void UIDtoUIDSTR(SYNTRO_UID *pS, SYNTRO_UIDSTR pD);		// converts a binary UID to a string
SYNTROLIB_EXPORT void MakeUIDSTR(SYNTRO_UIDSTR pDst, SYNTRO_MACADDRSTR pMac, int nInstance); // Fills in the UID
SYNTROLIB_EXPORT char *DisplayUID(SYNTRO_UID *pUID);				// non-rentrant return string version of UID
SYNTROLIB_EXPORT bool CompareUID(SYNTRO_UID *pa, SYNTRO_UID *pb);	// compares two UIDS
SYNTROLIB_EXPORT bool UIDHigher(SYNTRO_UID *pa, SYNTRO_UID *pb);	// returns true if pa > pb numerically
SYNTROLIB_EXPORT void SwapUID(SYNTRO_UID *pa, SYNTRO_UID *pb);		// swaps the UID contents

//	Syntro type conversion functions

SYNTROLIB_EXPORT int ConvertUC4ToInt(SYNTRO_UC4 pUC4);			// converts a 4 byte array to an integer
SYNTROLIB_EXPORT void ConvertIntToUC4(int nInt, SYNTRO_UC4 pUC4);	// converts an integer to a four byte array
SYNTROLIB_EXPORT int ConvertUC2ToInt(SYNTRO_UC2 pUC2);			// converts a 2 byte array to a signed integer
SYNTROLIB_EXPORT int ConvertUC2ToUInt(SYNTRO_UC2 pUC2);			// converts a 2 byte array to an unsigned integer
SYNTROLIB_EXPORT void ConvertIntToUC2(int nInt, SYNTRO_UC2 pUC2);	// converts an integer to a two byte array
SYNTROLIB_EXPORT void CopyUC2(SYNTRO_UC2 pDst, SYNTRO_UC2 pSrc);	// copies a SYNTRO_UC2 field


SYNTROLIB_EXPORT const char *GetRunModeString(int nType);		// converts a run mode (e.g. RUN_MODE_PRIMARY) into a string
SYNTROLIB_EXPORT void CrackServicePath(char *pSrvPath, char *pRegionName, char *pCompName, char *pSrvName); // breaks a service path into its constituent bits

SYNTROLIB_EXPORT QSettings *loadStandardSettings(const char *productType, QStringList arglist);

#endif		//_SYNTROUTILS_H_
