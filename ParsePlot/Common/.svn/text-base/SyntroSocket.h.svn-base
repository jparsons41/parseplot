// 	SyntroSocket.h - definitions for the CSyntroSocket class
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

#ifndef _SYNTROSOCKET_H
#define _SYNTROSOCKET_H

#include "SyntroDefs.h"
#include "SyntroPlatform.h"
#include "SyntroThread.h"

//	Define the standard socket types if necessary

#ifndef	SOCK_STREAM
#define	SOCK_STREAM		0
#define	SOCK_DGRAM		1
#define	SOCK_SERVER		2
#endif

class SYNTROLIB_EXPORT CSyntroSocket : public QObject
{
	Q_OBJECT

public:
	CSyntroSocket();
	CSyntroSocket(CSyntroThread	*pThread);
	virtual ~CSyntroSocket();

	void	SetThread(CSyntroThread *pThread);
	int		getConnectionID();								// returns the allocated connection ID
	void	SetConnectMsg(int nMsg);
	void	SetAcceptMsg(int nMsg);
	void	SetCloseMsg(int nMsg);
	void	SetReceiveMsg(int nMsg);
	void	SetSendMsg(int nMsg);
    bool    EnableBroadcast(int nFlag);
	bool	SetReceiveBufSize(int nSize);
	bool	SetSendBufSize(int nSize);
	int		SendTo(const void *lpBuf, int nBufLen, int nHostPort, char *pHost = NULL);
	int		ReceiveFrom(void *lpBuf, int nBufLen, char *pIpAddr, unsigned int *pnPort, int nFlags = 0);
	int		Create(int nSocketPort, int nSocketType, int nFlags = 0);
	bool	Connect(char *pAddr, int nPort);
	bool	Accept(CSyntroSocket& cSock, char *pIpAddr, int *pnPort);
	bool	Close();
	int		Listen();
	int		Receive(void *lpBuf, int nBufLen);
	int		Send(void *lpBuf, int nBufLen);
	int		PendingDatagramSize();

public slots:
	void	OnConnect();
	void	OnAccept();
	void	OnClose();
	void	OnReceive();
	void	OnSend(qint64 nBytes);
	void	OnError(QAbstractSocket::SocketError socketError);
	void	OnState(QAbstractSocket::SocketState socketState);

protected:
	CSyntroThread	*m_pOwnerThread;
	int m_connectionID;
	int					m_nSockType;				// the socket type
	int					m_nSockPort;				// the socket port number
	QUdpSocket			*m_pUdpSocket;
	QTcpSocket			*m_pTcpSocket;
	QTcpServer			*m_pServer;

	void	ClearSocket();							// clear up all socket fields
	int		m_nOnConnectMsg;
	int		m_nOnAcceptMsg;
	int		m_nOnCloseMsg;
	int		m_nOnReceiveMsg;
	int		m_nOnSendMsg;

	int		m_nState;								// last reported socket state

};

#endif // _SYNTROSOCKET_H


