//	SyntroPlatform.h - Qt Platform-specific definitions for SyntroLib
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

#ifndef	_SYNTROPLATFORM_H
#define	_SYNTROPLATFORM_H

//	Qt inlcudes

#include <qmutex.h>
#include <qabstractsocket.h>
#include <qtcpserver.h>
#include <qudpsocket.h>
#include <qtcpsocket.h>
#include <qthread.h>
#include <qapplication.h>
#include <qstringlist.h>
#include <qqueue.h>
#include <qevent.h>
#include <qnetworkinterface.h>
#include <qdatetime.h>
#include <qsettings.h>
#include <qlabel.h>

#include <SyntroLog.h>
#include <SyntroUtils.h>

#ifndef NULL
#define	NULL		0
#endif

#define	ASSERT(x)	Q_ASSERT(x)

//	Init and shutdown functions - these must only be called in CEndpoint and SyntroControl!! 

SYNTROLIB_EXPORT void PlatformInit();
SYNTROLIB_EXPORT void PlatformExit();	

//	Debug message and error display macros

#ifdef _DEBUG
#define	TRACE0(x) qDebug("%s", x)

#define	TRACE1(x, y) {qDebug(x, y);}

#define	TRACE2(x, y, z) {qDebug(x, y, z);}

#define	TRACE3(x, y, z, a) {qDebug(x, y, z, a);}
#else
#define	TRACE0(x) 

#define	TRACE1(x, y) 

#define	TRACE2(x, y, z) 

#define	TRACE3(x, y, z, a)
#endif

#if 0
#define	EXECLOG0(x) { if (syntroLog) syntroLog->logError(x); TRACE0(x); }
#define	EXECLOG1(x, y)  { if (syntroLog) syntroLog->logError(x, y); TRACE1(x, y);}
#define	EXECLOG2(x, y, z)  { if (syntroLog) syntroLog->logError(x, y, z); TRACE2(x, y, z);}
#define	EXECLOG3(x, y, z, a)  { if (syntroLog) syntroLog->logError(x, y, z, a); TRACE3(x, y, z, a);}
#else
#define	EXECLOG0(x) { logDebug(x); TRACE0(x); }
#define	EXECLOG1(x, y)  { logDebug(x, y); TRACE1(x, y);}
#define	EXECLOG2(x, y, z)  { logDebug(x, y, z); TRACE2(x, y, z);}
#define	EXECLOG3(x, y, z, a)  { logDebug(x, y, z, a); TRACE3(x, y, z, a);}
#endif

//		Task yield

#define	SyntroYield()	yieldCurrentThread();

//		Mutex

#define	CSyntroMutex	QMutex

//		64 bit int type

typedef	qint64	SYNTRO_INT64;

//		Syntro clock related definitions
//
//		This uses the underlying Qt functions to handle system time related functions

#define	SYNTRO_CLOCK_TYPE			qint64						// the type of variable used for system time functions

#define	SYNTRO_CLOCKS_PER_SEC	((qint64)1000)

#define	SYNTRO_SYSTEMTIME	QDateTime							// the date and time used for timestamps

// Callers typically pass SyntroClock() for now
SYNTROLIB_EXPORT bool SyntroTimerExpired(qint64 now, qint64 start, qint64 interval);


#define	SyntroSleep(x)	msleep(x)

typedef	int	SYNTRO_TIMERID_TYPE;

//		SYNTRO_TIMER_CALLBACK creates a callback for use with a timer.
//		name	=	the name of the callback function
//
//		Note - callbacks may not be required in some implementations but the macro must
//		be present as it defines the var that holds the timer ID.

#define	SYNTRO_TIMER_CALLBACK(name) SYNTRO_TIMERID_TYPE (name ## TID);


////	SYNTRO_SET_TIMER creates a timer
//
//      name	=	name of timer (and sometimes callback function name - call back function not used here
//		iv		=	interval in units of mS
//
//		When the timer fires, a SYNTROTHREAD_TIMER_MESSAGE is generated and passed to the ProcessMessage() routine.
//		The timer id is contain in the lParam of the pMsg.

#define	SYNTRO_SET_TIMER(name, iv) (name ## TID) = startTimer(iv)

//		SYNTRO_KILL_TIMER kills an existing timer
//		name = the name of the timer

#define	SYNTRO_KILL_TIMER(name) killTimer(name ## TID)

//	SYNTRO_KILL_THREAD sends a TERMINATE_THREAD_MESSAGE to a thread
//	tip is the thread instance pointer (which is set to NULL at the end)

#define	SYNTRO_KILL_THREAD(tip) {if (tip != NULL){tip->PostThreadMessage(TERMINATE_THREAD_MESSAGE, 0, 0);} tip = NULL;}

//	SYNTRO_END_THREAD should be used in a thread in response to receiving a TERMINATE_THREAD_MESSAGE.
//	Calls ExitThread() (which is user-supplied) and then exit(). 


#define	SYNTRO_END_THREAD	{m_bRun = false; ExitThread(); exit();}


SYNTROLIB_EXPORT bool GetMyIPAddress(QSettings *pSettings);		// gets my IP address from first or known IP adaptor

//	Timestamp functions

SYNTROLIB_EXPORT char *TimestampToString(SYNTRO_TIMESTAMP *pTS);	// get a display version of a Syntro timestamp
SYNTROLIB_EXPORT char *TimestampToString(SYNTRO_SYSTEMTIME *ptTimestamp);// get a display version of a timestamp
SYNTROLIB_EXPORT void SetSyntroTimestamp(SYNTRO_TIMESTAMP *pTS);	// sets a timestamp value from system time
SYNTROLIB_EXPORT void GetSyntroTimestamp(SYNTRO_TIMESTAMP *pTS, SYNTRO_SYSTEMTIME *pTime); // converts a Syntro timestamp to SYSTEMTIME
SYNTROLIB_EXPORT QString timestampToDateString(SYNTRO_TIMESTAMP *timestamp);
SYNTROLIB_EXPORT QString timestampToTimeString(SYNTRO_TIMESTAMP *timestamp);
SYNTROLIB_EXPORT QDateTime SyntroTimestampToQDateTime(SYNTRO_TIMESTAMP *timestamp);

//	Information for the network address in use

QHostAddress getMyBroadcastAddress();
QHostAddress getMySubnetAddress();
QHostAddress getMyNetMask();
bool isInMySubnet(SYNTRO_IPADDR IPAddr);

#endif 	// _SYNTROPLATFORM_H
