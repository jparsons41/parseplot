//	Hello.h - Definitions for the SyntroHAL MFC Hello Class
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

#ifndef _HELLO_H_
#define _HELLO_H_

#include "syntrolib_global.h"
#include "HelloDefs.h"
#include "SyntroPlatform.h"
#include "SyntroThread.h"

typedef struct
{
	bool	bInUse;											// true if entry being used
	HELLO	sHello;											// received hello
	char	pIPAddr[SYNTRO_IPSTR_LEN];						// a convenient string form of address
	SYNTRO_CLOCK_TYPE	nLastHello;							// time of last hello
} HELLOENTRY;


class	CSyntroSocket;

class SYNTROLIB_EXPORT CHello : public CSyntroThread
{
	Q_OBJECT

public:
	CHello();
	~CHello();

	void	sendHelloBeacon();								// sends a hello to SyntroControls to elicit a response
	void	sendHelloBeaconResponse(HELLO *hello);			// responds to a beacon
	char	*getHelloEntry(int index);						// gets a formatted string version of the hello entry
	void	copyHelloEntry(int index, HELLOENTRY *dest);	// gets a copy of the HELLOENTRY data structure at index

//--------------------------------------------
//	These variables should be changed on startup to get the desired behaviour

	CSyntroThread	*m_pParentThread;	// this is set with the parent thred's ID if messages are required

	int			m_nHelloChannels;		// number of channels to send hellos on (only for SyntroControl)
	int			m_nInstance;			// the specific instance (added to SOCKET_HELLO to get listen socket)
	int			m_nSocketFlags;			// set to 1 for ruse socket number

//--------------------------------------------

//	The lock should always be used when processing the HelloArray

	HELLOENTRY		m_helloArray[SYNTRO_MAX_CONNECTEDCOMPONENTS];
	CSyntroMutex	m_lock;				// for access to the hello array


	bool 	InitThread();
	void 	ExitThread();
	bool	ProcessMessage(CSyntroThreadMsg* pMsg);
	bool	FindComponent(HELLOENTRY *pRes, SYNTRO_UID *pUID, int nRM, int nOM);
	bool	FindComponent(HELLOENTRY *pRes, char *pCompName, char *pCompType, int nRM, int nOM);

signals:
	void	helloDisplayEvent(CHello *hello);

protected:

	void	ProcessHello();
	void	DeleteEntry(HELLOENTRY *pH);
	bool	MatchHello(HELLO *a, HELLO *b);
	void	ProcessTimers();
	void	SendHello();

	HELLO	m_sRXHello;
	char	m_pIpAddr[SYNTRO_MAX_NONTAG];				
	unsigned int	m_nPort;
	CSyntroSocket	*m_pHelloSocket;
};

#endif // _HELLO_H_
