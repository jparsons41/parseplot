//	SyntroThread.h - definitions for the SyntroThread class
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

#ifndef		_SYNTROTHREAD_H_
#define		_SYNTROTHREAD_H_

#include "SyntroPlatform.h"
#include "SyntroDefs.h"	

//	Inter-thread message defs

#define	TERMINATE_THREAD_MESSAGE		(0)							// send to threads when time to terminate

//	Endpoint socket messages

#define	ENDPOINT_ONCONNECT_MESSAGE		(1)							// Endpoint socket messages
#define	ENDPOINT_ONCLOSE_MESSAGE		(2)	
#define	ENDPOINT_ONRECEIVE_MESSAGE		(3)	
#define	ENDPOINT_ONSEND_MESSAGE			(4)	

#define	ENDPOINT_MESSAGE_START			ENDPOINT_ONCONNECT_MESSAGE	// start of endpoint message range
#define	ENDPOINT_MESSAGE_END			ENDPOINT_ONSEND_MESSAGE		// end of endpoint message range

#define	SYNTROTHREAD_TIMER_MESSAGE		(5)							// message used by the SyntroThread timer

#define	HELLO_ONRECEIVE_MESSAGE			(6)							// used for received hello messages
#define	HELLO_STATUS_CHANGE_MESSAGE		(7)							// send to owner when hello status changes for a device

//	This code is the first that can be used by any specific application

#define	SYNTRO_MSTART					(8)							// This is where application specific codes start

//	The CSyntroThreadMsg data structure - this is what is passed in the task's message queue

class SYNTROLIB_EXPORT CSyntroThreadMsg : public QEvent
{
public:
	CSyntroThreadMsg(QEvent::Type nEvent);
	int		nMessage;
	int		wParam;
	void	*lParam;
};


class SYNTROLIB_EXPORT CSyntroThread : public QThread
{
	Q_OBJECT
public:
	CSyntroThread();
	virtual ~CSyntroThread();

	void			PostThreadMessage(int nMessage, int wParam, void *lParam);	// post a message to the thread
	void			ResumeThread();					// this must be called to get thread going
	bool			IsRunning();					// returns true if task no exiting
	char			m_pName[SYNTRO_MAX_NONTAG];		// the task name - for debugging mostly

protected:

	virtual	bool 	ProcessMessage(CSyntroThreadMsg* pMsg);
	virtual bool	InitThread();					// called by resume thread internally
	virtual void	ExitThread();					// called to end the thread's existence
	virtual void	run();							// this is the real thread routine
	bool			m_bRun;							// true if time to execute Run

	int				m_nEvent;						// the event used for Syntro thread message

	bool			eventFilter(QObject *obj, QEvent *event);

};


#endif		//_SYNTROTHREAD_H_