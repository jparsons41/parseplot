//	SyntroLink.h - Definitions for the Syntro link layer
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

#pragma once

//	The internal version of SYNTROMESSAGE

class SYNTROLIB_EXPORT CSyntroMessage
{
public:
	CSyntroMessage(void);
	~CSyntroMessage(void);

	SYNTRO_MESSAGE		*m_pMsg;			// message buffer pointer
	int					m_nLen;				// total length
	CSyntroMessage		*m_pNext;			// pointer to next in chain
	int					m_nBytesLeft;		// bytes left to be received or sent
	unsigned char		*m_pPtr;			// pointer in m_pMsg while receiving or transmitting

//	for receive

	int					m_nCmd;				// the current command
};


//	The CSyntroLink class itself

class SYNTROLIB_EXPORT CSyntroLink
{
public:
	CSyntroLink(void);
	~CSyntroLink(void);

	void	Send(int nCmd, int nLen, int nPri, SYNTRO_MESSAGE *pSM);
	bool	Receive(int nPri, int *pnCmd, int *pnLen, SYNTRO_MESSAGE **ppSM);

	int		TryReceiving(CSyntroSocket *pSock);
	int		TrySending(CSyntroSocket *pSock);

protected:

	void		ClearTXQueue();
	void		ClearRXQueue();
	void		ResetReceive(int nPri);
	void		FlushReceive(CSyntroSocket *pSock);
	CSyntroMessage	*GetTXHead(int nPri);
	CSyntroMessage	*GetRXHead(int nPri);
	void		AddToTXQueue(CSyntroMessage *pCSM, int nPri);
	void		AddToRXQueue(CSyntroMessage *pCSM, int nPri);
	void		ComputeChecksum(SYNTRO_MESSAGE *pSM);
	bool		CheckChecksum(SYNTRO_MESSAGE *pSM);

	CSyntroMessage	*m_pCSMTXHead[SYNTROLINK_PRIORITIES];			// head of transmit list
	CSyntroMessage	*m_pCSMTXTail[SYNTROLINK_PRIORITIES];			// tail of transmit list
	CSyntroMessage	*m_pCSMRXHead[SYNTROLINK_PRIORITIES];			// head of receive list
	CSyntroMessage	*m_pCSMRXTail[SYNTROLINK_PRIORITIES];			// tail of receive list

	CSyntroMessage	*m_pTXIP[SYNTROLINK_PRIORITIES];				// in progress TX object
	CSyntroMessage	*m_pRXIP[SYNTROLINK_PRIORITIES];				// in progress RX object
	bool			m_bRXSM;				// true if waiting for SYNTROMESSAGE header
	unsigned char	*m_pRXIPMsgPtr;			// pointer into message header
	int				m_nRXIPBytesLeft;
	SYNTRO_MESSAGE	m_cSM;					// for receive
	int				m_nRXIPPri;				// the current priority being received

	CSyntroMutex		*m_pRXLock;
	CSyntroMutex		*m_pTXLock;

};
