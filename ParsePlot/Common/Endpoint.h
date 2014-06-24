//	Endpoint.h - definitions for the Endpoint base class
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

#ifndef	_ENDPOINT_H_
#define	_ENDPOINT_H_

#include "syntrolib_global.h"
#include "SyntroDefs.h"
#include "SyntroPlatform.h"
#include "Hello.h"
#include "SyntroLink.h"

#define	ENDPOINT_STATE_MAX		256										// max bytes in state message (including trailing zero)

#define	ENDPOINT_BACKGROUND_INTERVAL	(SYNTRO_CLOCKS_PER_SEC)			// this is the polling interval
#define	ENDPOINT_DE_INTERVAL			(SYNTRO_CLOCKS_PER_SEC * 10)	// background DE update interval
#define	ENDPOINT_CONNWAIT				(1 * SYNTRO_CLOCKS_PER_SEC)		// interval between connection attempts
#define ENDPOINT_MULTICAST_TIMEOUT		(10 * SYNTRO_CLOCKS_PER_SEC)	// 10 second timeout for unacked multicast send

//-------------------------------------------------------------------------------------------
//	Service structure defs

//	SYNTRO_SERVICE_INFO is used to maintain information about a local and remote services

typedef struct
{
	bool inUse;												// true if this service slot is in use
	bool enabled;											// true if the service is operating
	bool local;												// true if this is a local service, false if remote
	int serviceType;										// service type code
	int serviceData;										// the int valude that the appClient can set

	bool removingService;									// true if disabling due to service removal
	SYNTRO_SERVPATH	servicePath;							// the path of the service
	int destPort;											// destination port for outgoing messages
	SYNTRO_CLOCK_TYPE tLastLookup;							// time of last lookup (for timeout purposes)
	SYNTRO_CLOCK_TYPE tLastLookupResponse;					// time of last lookup response (for timeout purposes)
	int closingRetries;										// number of times a close has been retried
	int	state;												// state of the service
	SYNTRO_SERVICE_LOOKUP serviceLookup;					// the lookup structure

	unsigned char lastReceivedSeqNo;						// sequence number on last received multicast message
	unsigned char nextSendSeqNo;							// the number to use on the next sent multicast message
	unsigned char lastReceivedAck;							// the last ack received
	SYNTRO_CLOCK_TYPE lastSendTime;						// time the last multicast frame was sent
} SYNTRO_SERVICE_INFO;


//	local service state defs

enum SYNTRO_LOCAL_SERVICE_STATE
{
	SYNTRO_LOCAL_SERVICE_STATE_INACTIVE = 0,				// no subscribers
	SYNTRO_LOCAL_SERVICE_STATE_ACTIVE						// one or more subscribers
};

//	remote service state defs

enum SYNTRO_REMOTE_SERVICE_STATE
{
	SYNTRO_REMOTE_SERVICE_STATE_NOTINUSE = 0,				// indicates remote service port is not in use
	SYNTRO_REMOTE_SERVICE_STATE_LOOK,						// requests a lookup on a service
	SYNTRO_REMOTE_SERVICE_STATE_LOOKING,					// outstanding lookup
	SYNTRO_REMOTE_SERVICE_STATE_REGISTERED,					// successfully registered
	SYNTRO_REMOTE_SERVICE_STATE_REMOVE,						// request to remove a remote service registration
	SYNTRO_REMOTE_SERVICE_STATE_REMOVING					// remove request has been sent
};


//	SYNTRO_CFS_STREAM is used to maintain state about an open SyntroCFS stream

typedef struct
{
	bool inUse;												// true if being used
	int clientHandle;										// the index of this entry
	int storeHandle;										// the stream handle returned by the stream open
	bool openInProgress;									// true if an open request is in progress
	SYNTRO_CLOCK_TYPE openReqTime;							// when the open request was sent
	bool open;												// true if stream open
	bool readInProgress;									// true if a read has been issued
	SYNTRO_CLOCK_TYPE readReqTime;							// when the read request was sent
	bool closeInProgress;									// true if a close has been issued
	SYNTRO_CLOCK_TYPE closeReqTime;							// when the close request was sent
	SYNTRO_CLOCK_TYPE lastKeepAliveSent;					// the time the last keep alive was sent
	SYNTRO_CLOCK_TYPE lastKeepAliveReceived;				// the time the last keep alive was received
} SYNTRO_CFS_STREAM;


//	SYNTROCFS_CLIENT_EPINFO is used to maintain SyntroCFS stream info for an endpoint

typedef struct
{
	bool inUse;												// true if in use
	bool dirInProgress;										// true if a directory request is in progress
	SYNTRO_CLOCK_TYPE dirReqTime;							// when the last dir request was sent
	SYNTRO_CFS_STREAM	cfsStream[SYNTROCFS_MAX_CLIENT_STREAMS];	// the stream info
} SYNTROCFS_CLIENT_EPINFO;

//-------------------------------------------------------------------------------------------
//	The CEndpoint class itself
//

class SYNTROLIB_EXPORT CEndpoint : public CSyntroThread
{
	Q_OBJECT

public:
	CEndpoint(QObject *parent, QSettings *settings, qint64 backgroundInterval);
	virtual ~CEndpoint();

	virtual bool InitThread();
	void ExitThread();
	bool ProcessMessage(CSyntroThreadMsg *msg);

//	EndpointBackground should be called more than once per second to handle activities such as refreshing
//	remote service lookups.

	void	EndpointBackground();

//	EnpointClientMessage should be called to handle thread message from the SyntroSocket.
//	Returns true if the message has been processed.

	bool	EndpointSocketMessage(CSyntroThreadMsg *msg);

//	This routine returns a string for the status of the SyntroLink

	char	*GetLinkState();

//	This functions return a pointer to the Hello object

	CHello *GetHelloObject();

//	requestDirectory sends a directory request to SyntroControl

	void requestDirectory();

signals:
	void receiveData(int slot, int bytes);
	void setServiceName(int slot, QString name);


protected:

//----------------------------------------------------------
//	
//	Client level services

//	clientLoadServices loads services from the client settings area.
//	They will all be enabled or disabled on creation based on the enabled flag supplied.
//	Returns true if it went ok, *serviceCOunt is the number of services loaded, *serviceStart
//	is the servicePort of the first service loaded.

	bool clientLoadServices(bool enabled, int *serviceCount, int *serviceStart);

//	clientAddService adds a service to the Endpoint's service list. When enabled, for a local service (local = true)
//	Endpoint will then process the service as a local multicast producer or E2E endpoint depending
//	on the serviceType setting (SERVICETYPE_MULTICAST or SERVICETYPE_E2E). For a remote service
//	(local = false), for multicast Endpoint will try to lookup and register for the service stream.
//	For E2E, Endpoint will try to obtain the UID and port number of the service.
//
//	The function returns -1 if there was an error. Otherwise, it is the service port allocated
//	to this service.
//	
//	The initial service enable state is set by the enabled flag on the call.

	int		clientAddService(QString servicePath, int serviceType, bool local, bool enabled = true);

//	clientSetServiceData allows an integer value to be set in the service entry

	bool	clientSetServiceData(int servicePort, int value);

//	clientGetServiceData retrieves the integer previously set in a service entry
//	Note that there is no easy way on indicating an error except by returning -1
//	so ideally -1 should not be a valid value!

	int		clientGetServiceData(int servicePort);

//	clientEnableService activates a previously stopped service. Returns false if error.

	bool	clientEnableService(int servicePort);

//	clientDisableService deactivates a previously enabled service. Return false if error.

	bool	clientDisableService(int servicePort);

//	clientIsServiceEnabled returns enabled state

	bool	clientIsServiceEnabled(int servicePort);

//	remove a service from the array. Returns true if ok, false if error.

	bool	clientRemoveService(int servicePort);

//	clientIsServiceActive returns true if the service is in a data transfer state. For local multicast,
//	this means there are subscribers to the service. For remote multicast, this means that this
//	port is registered for the requested service. For remote E2E, this means that the lookup for the
//	destination service has succeeded.

	bool	clientIsServiceActive(int servicePort);

//	clientGetServicePath returns the path of the service

	QString clientGetServicePath(int servicePort);

//	clientGetServiceType returns the type of the service

	int		clientGetServiceType(int servicePort);

//	clientIsServiceLocal return true if local, false if remote

	bool	clientIsServiceLocal(int servicePort);

//	clientGetRemoteServiceState returns the current state of the remote service. This is the more general
//	version of RemoteServiceAvailable, which only determines if it is registered or not.
//	The returned value is one of SYNTRO_REMOTE_SERVICE_STATE.

	int		clientGetRemoteServiceState(int servicePort);

//	clientGetRemoteServiceUID returns a pointer to the remote service's UID. Returns NULL if not in valid state

	SYNTRO_UID	*clientGetRemoteServiceUID(int servicePort);

//	clientGetServiceDestPort returns the port to which messages should be sent. Returns -1 if not in valid state

	int		clientGetServiceDestPort(int servicePort);

//	clientGetLastSendTime returns the time at which a message was last sent

	qint64	clientGetLastSendTime(int servicePort);

//	clientIsConnected returns true if the SyntroLink is up.

	bool clientIsConnected();

//	these functions are called by the app client to build and send messages

	bool clientClearToSend(int clientPort);				// returns true if can send on a local multicast service
	SYNTRO_EHEAD *clientBuildMessage(int clientPort, int length); // for multicast and remote E2E services
	SYNTRO_EHEAD *clientBuildLocalE2EMessage(int clientPort, 
						SYNTRO_UID *destUID, int destPort, int length); // for local E2E services

	bool clientSendMessage(int clientPort, 
								SYNTRO_EHEAD *message, 
								int length,
								int priority = SYNTROLINK_LOWPRI);
	bool clientSendMulticastAck(int clientPort);			// acks a received multicast message

//----------------------------------------------------------
//	Client app overrides
//
//	these functions can be overriden by the app client

//	appClientInit is called just before CEndpoint starts its timer and runs normally
//	the client can use this for final initialization as the service array has been loaded.

	virtual void appClientInit() {}

//	appClientExit is called when the app is exiting.

	virtual void appClientExit() {}

//	appClientReceiveMulticast is called to allow the app client to process a multicast message
//	length is the length of data after the Syntro_EHEAD. The message must be free()ed when
//	no longer needed.

	virtual void appClientReceiveMulticast(int servicePort, SYNTRO_EHEAD *message, int length);

//	appClientReceiveMulticastAck is called to allow the app client to process a multicast ack message
//	length is the length of data after the Syntro_EHEAD. The message must be free()ed when
//	no longer needed.

	virtual void appClientReceiveMulticastAck(int servicePort, SYNTRO_EHEAD *message, int length);	

//	appClientReceiveE2E is called to allow the app client to process an end to end message
//	length is the length of data after the Syntro_EHEAD. The message must be free()ed when
//	no longer needed.

	virtual void appClientReceiveE2E(int servicePort, SYNTRO_EHEAD *message, int length);	

//	appClientConnected is called when the SyntroLink has been established

	virtual void appClientConnected() { return; }						

//	appClientClosed is callled if the SyntroLink has been closed.

	virtual void appClientClosed() {return; }							

//	appClientHeartbeat is called when a heartbeat is received

	virtual void appClientHeartbeat(SYNTRO_HEARTBEAT *heartbeat, int length);

//	appClientReceiveDirectory is able to process a directory response

	virtual void appClientReceiveDirectory(SYNTRO_DIRECTORY_RESPONSE *directory, int length);

//	appClientBackground is called every background interval timer tick and
//	can be used for any background processing that may be necessary

	virtual void appClientBackground() { return; }							

//	appClientProcessThreadMessage can be used by the app client to receive
//	SyntroThread inter-thread messages that have been posted by another thread.
//	Return true if processed message in the appClient.

	virtual bool appClientProcessThreadMessage(CSyntroThreadMsg *) { return false; }

//----------------------------------------------------------

//	This points to the settings class for this app

	QSettings *m_pSettings;

	SYNTRO_UID m_UID;

//	These routines are used to send messages across the SyntroLink. 
//	** NOTE ** message data should have been malloced as it will be held and freed by SyntroLink.

	bool	SyntroSendMessage(int nCmd, SYNTRO_MESSAGE *pSM, int nLen, int nPri); // ditto

//	An easy way of acking a multicast message. The nSP
//	is the service port index so that details like UID can be picked up.

	void	SendMulticastAck(int nSP, int nSeq);		// sends back an ack to the endpoint

//	An easy way of acking a received SYNTRO_EHEAD with an E2E type in it

	void	SendE2EAck(SYNTRO_EHEAD *pOH);					// sends an E2E ack back

//	ForceDE forces an immediate DE send (well at next Endpoint background call anyway)
	
	void	ForceDE();

//	SentDE checks to see if a DE has been sent ona connection. No data should be sent
//	on a connection unless this returns true.

	bool	SentDE();


//-------------------------------------------------------------------------------------------
//	SyntroCFS API definitions
//

//	CFSAddEP adds an endpoint number to be trapped for SyntroCFS processing

	void CFSAddEP(int remoteServiceEP);						// adds an endpoint index for SyntroCFS processing

//	CFSAddEP adds an endpoint number to be trapped for SyntroCFS processing

	void CFSDeleteEP(int remoteServiceEP);					// deletes an endpoint index for SyntroCFS processing

//	CFSDir is called to obtain a list of sources available from a specific SyntroCFS store
//	Note that only one request can be outstanding for each SyntroCFS EP. The request will be timed out if no response
//	is seen in a defined time. In other words, after a call to CFSDir, the client must wait until
//	CFSDirResponse is called before trying again - a call to CFSDirResponse is guaranteed in all
//	circumstances.

	void CFSDir(int remoteServiceEP);						// requests a list of available streams from the SyntroCFS 

//	CFSDirReponse is called when a response is obtained or the request fails
//	responseCode contains the SyntroCFS response code, streamNames will contain the names of structured streams

	virtual void CFSDirResponse(int remoteServiceEP, unsigned int responseCode, QStringList streamNames); 

//	CFSOpen is called to open a stream from a SyntroCFS store.
//	The function returns the local handle allocated to the stream.
//	If -1 is returned, this means that too many streams are open already.

	int CFSOpen(int remoteServiceEP, QString streamName);

//	CFSOpenResponse is called when a response is obtained or the open request fails in some way
//	responseCode contains the response code which can be success or error. If success, the stream
//	is open for stream operations.
//	If successful, handle contains the local handle to be used for future operations on the open stream.
//	If unsuccessful, the handle return is the handle that was returned by the call to CFSOpen. However,
//	the slot has been returned and so the handle is no longer available for use.

	virtual void CFSOpenResponse(int remoteServiceEP, unsigned int responseCode, int handle);

//	CFSClose is called when it's time to close a stream and release the local handle.
//	If there's a local error, CFSClose returns false and there will be no call to CFSCloseResponse.
//	If it return true, the request has been issued and a subsequent call to CFSCloseResponse is
//	guaranteed in all cases.

	bool CFSClose(int remoteServiceEP, int handle);

//	CFSCloseResponse is called when a close operation has completed.
//	No matter what the responseCode, the handle is no longer available and the stream
//	can be considered closed.

	virtual void CFSCloseResponse(int remoteServiceEP, unsigned int responseCode, int handle);

//	CFSKeepAliveTimeout is called when an active stream is timed out due to a lack of
//	keep alive responses. The slot is closed and this call informs the client that the stream
//	is no longer available.

	virtual void CFSKeepAliveTimeout(int remoteServiceEP, int handle);

//	CFSReadAtIndex is called to read the record at the specified index
//	It will return true if the read was issued or else return false if
//	the read could not be issued.

	bool CFSReadAtIndex(int remoteServiceEP,int handle, unsigned int recordIndex);

//	CFSReadAtIndexResponse is called when a CFSReadAtIndex completes or else returns an error
//	pSRH is a pointer to returned data (if the responseCode is SYNTROCFS_SUCCESS) and the
//	client must free this memory when it no longer needs it.

	virtual void CFSReadAtIndexResponse(int remoteServiceEP, int handle, unsigned int recordIndex, unsigned int responseCode, SYNTRO_RECORD_HEADER *pSRH);

//-------------------------------------------------------------------------------------------

private:
	CHello *m_pHello;										// Hello task (only used in local mode)

	bool m_bRemote;											// true if remote domain
	bool m_bSentDE;											// if a DE has been sent yet on this connection

	SYNTRO_CLOCK_TYPE m_tBackground;						// used to keep track of background polling
	SYNTRO_CLOCK_TYPE m_tDETimer;							// used to send DEs
	SYNTRO_SERVICE_INFO m_serviceInfo[SYNTRO_MAX_SERVICESPERCOMPONENT];	// my service array
	QMutex m_serviceLock;									// to control access to the service array

	char m_pIPAddr[SYNTRO_IPSTR_LEN];						// the IP address string for the target SyntroControl
	int m_nPort;											// the port to use for the connection
	char m_pControlName[SYNTRO_MAX_COMPNAME];				// component name for the target SyntroControl
	HELLOENTRY m_cHE;										// the HelloEntry we are using

	// heartbeat system defs

	SYNTRO_CLOCK_TYPE m_lastHeartbeatSent;					// time last heartbeat sent
	SYNTRO_CLOCK_TYPE m_heartbeatSendInterval;				// interval between sent timeouts
	SYNTRO_CLOCK_TYPE m_heartbeatTimeoutPeriod;				// period of missed received heartbeats before timeout
	SYNTRO_CLOCK_TYPE m_lastHeartbeatReceived;				// when the last heartbeat was received
	
	bool m_bConnected;										// true if connection active
	bool m_bConnectInProgress;								// true if in middle of connecting the SyntroLink
	bool m_bGotHeartbeat;									// true if at least one heartbeat received
	int	 m_nOM;												// latest reported operating mode
	CSyntroSocket *m_pSock;
	CSyntroLink	*m_pSCL;
	CSyntroMutex *m_pRXLock;								// receive data processing lock
	SYNTRO_CLOCK_TYPE m_tConnWait;							// timer between connection attempts
	char m_pState[ENDPOINT_STATE_MAX];						// the state message

	void UpdateState(const char *pMsg);						// sets the new state message
	bool SyntroConnect();
	void SyntroClose();
	void ProcessReceivedData();
	void serviceInit();										// init processing for services
	void serviceBackground();								// background processing for services
	void SendRemoteServiceLookup(SYNTRO_SERVICE_INFO *remoteService); // send a lookup request message
	void ProcessServiceActivate(SYNTRO_SERVICE_ACTIVATE *serviceActivate);// handles a service activate request
	void ProcessLookupResponse(SYNTRO_SERVICE_LOOKUP *pSSL);// handles the response to a service lookup

	void ProcessMulticast(SYNTRO_EHEAD *pMC, int nLen, int dstPort); // process a multicast message
	void ProcessMulticastAck(SYNTRO_EHEAD *pMC, int nLen, int dstPort);	// process a multicast ack message
	void ProcessE2E(SYNTRO_EHEAD *pE2E, int nLen, int dstPort); // process an end to end message message
	void EndpointConnected();						// called when connection is made
	void EndpointClosed();							// called when the connection has been closed
	void EndpointHeartbeat(SYNTRO_HEARTBEAT *pSH, int nLen); // called when a heartbeat is received

	SYNTRO_CLOCK_TYPE m_backgroundInterval;					// the background interval to use

	void buildDE();											// build a new DE

	void Cleanup();											// cleans up service entries after connection is lost
	void LinkCloseCleanup();								// do what needs to be done when the SyntroLink goes down


//-------------------------------------------------------------------------------------------
//	SyntroCFS API variables and local functions
//
	void CFSInit();										// set up for run
	SYNTRO_EHEAD *CFSBuildRequest(int remoteServiceEP, int length);	// generate a request buffer with length bytes after CFS header
	void CFSBackground();								// the background function
	bool CFSProcessMessage(SYNTRO_EHEAD *pE2E, int nLen, int dstPort); // see if it is a SyntroCFS messages and process
	void CFSProcessDirResponse(SYNTRO_CFSHEADER *cfsHdr, int dstPort);	// process a stream directory response
	void CFSProcessOpenResponse(SYNTRO_CFSHEADER *cfsHdr, int dstPort);	// process a stream open response
	void CFSProcessCloseResponse(SYNTRO_CFSHEADER *cfsHdr, int dstPort);	// process a stream close response
	void CFSProcessKeepAliveResponse(SYNTRO_CFSHEADER *cfsHdr, int dstPort);	// process a keep alive response
	void CFSProcessReadAtIndexResponse(SYNTRO_CFSHEADER *cfsHdr, int dstPort);	// process a read at index response

	void CFSSendKeepAlive(int remoteServiceEP, SYNTRO_CFS_STREAM *scs);		// sends a keep alive on an open stream
	void CFSTimeoutKeepAlive(int remoteServiceEP, SYNTRO_CFS_STREAM *scs);	// handles a keep alive timeout

	SYNTROCFS_CLIENT_EPINFO cfsEPInfo[SYNTRO_MAX_SERVICESPERCOMPONENT];	// the SyntroCFS EP info array


//-------------------------------------------------------------------------------------------
};
#endif	//_ENDPOINT_H
