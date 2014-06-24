//	HelloDefs.h - Definitions for the SyntroSoft Hello system
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

#ifndef _HELLODEFS_H
#define _HELLODEFS_H

#include "SyntroDefs.h"

//--------------------------------------------------------------------------------
//	The Hello data structure

#define	INSTANCE_CONTROL			0			// the instance for SyntroControl
#define	INSTANCE_EXEC				1			// instance for SyntroExec
#define	INSTANCE_DYNAMIC			-1			// for a non core app, this means that instance is dynamic
#define	INSTANCE_COMPONENT			2			// instance of first component

#define	SOCKET_HELLO				8040		// socket to use is this plus the instance

#define	HELLO_SYNC0		0xff					// the sync bytes
#define	HELLO_SYNC1		0xa5
#define	HELLO_SYNC2		0x5a
#define	HELLO_SYNC3		0x11

#define	HELLO_SYNC_LEN	4						// 4 bytes in sync

#define	HELLO_BEACON	2						// a beacon event (SyntroControl only)
#define	HELLO_UP		1						// state in hello state message
#define	HELLO_DOWN		0						// as above

//	Run Mode codes

#define	RUN_MODE_UNKNOWN	0					// this is only used as an error return
#define	RUN_MODE_RUN		1					// always run the program
#define	RUN_MODE_PRIMARY	2					// primary mode
#define	RUN_MODE_BACKUP		3					// backup mode
#define	RUN_MODE_NEVER		4					// never run the program
#define	RUN_MODE_IGNORE		5					// Exec doesn't control it

#define	RUN_MODE_COUNT		6					// number of modes

//	Operating mode (reported by the software component at runtime)

#define	OPER_MODE_ACTIVE	1					// component is currently in active mode
#define	OPER_MODE_STANDBY	2					// component is currnet in standby mode

typedef struct
{
	unsigned char	pHelloSync[HELLO_SYNC_LEN];// a 4 byte code to check synchronisation (HELLO_SYNC)
	SYNTRO_IPADDR	pIPAddr;					// device IP address
	SYNTRO_UID		cUID;						// Component UID
	SYNTRO_COMPNAME	pCompName;					// the component name of the sender
	SYNTRO_COMPTYPE	pCompType;					// the component type of the sender
	unsigned char	nRM;						// run mode
	unsigned char	nOM;						// operating mode
	SYNTRO_UC2		nInterval;					// heartbeat send interval
} HELLO;

//	SYNTRO_HEARTBEAT is the type sent on the SyntroLink. It is the hello but with the SYNTRO_MESSAGE header

typedef struct
{
	SYNTRO_MESSAGE	cSM;						// the SyntroLink header
	HELLO			cHello;						// the hello itself
} SYNTRO_HEARTBEAT;

#define	HELLO_INTERVAL		(2 * SYNTRO_CLOCKS_PER_SEC) // send a hello every 2 seconds
#define	HELLO_LIFETIME		(4 * HELLO_INTERVAL)	// HELLO entry timeout = 4 retries

#endif	// _HELLODEFS_H
