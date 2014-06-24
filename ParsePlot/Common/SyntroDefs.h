//	SyntroDefs.h - Definitions for the Syntro system
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

#ifndef _SYNTRODEFS_H
#define _SYNTRODEFS_H

//-------------------------------------------------------------------------------------------
//	Physical constants
//

#define	SYNTRO_PI	(3.14159265358979323846)

#define	SYNTRO_GRAVITY	(float)(9.80655)			// g in m/s

//-------------------------------------------------------------------------------------------
//	The defines below are the most critical Syntro system definitions.
//

//	Syntro constants

#define	SYNTRO_HEARTBEAT_INTERVAL		1			// default heartbeatinterval in seconds 
#define	SYNTRO_HEARTBEAT_TIMEOUT		5			// default number of missed heartbeats before timeout

#define	SYNTRO_SERVICE_LOOKUP_INTERVAL		(5 * SYNTRO_CLOCKS_PER_SEC)	// 5 seconds interval between service lookup requests

#define	SYNTRO_PRIMARY_SOCKET_LOCAL		1661		// socket for the primary SyntroControl
#define	SYNTRO_BACKUP_SOCKET_LOCAL		1662		// socket for the backup SyntroControl

#define	SYNTRO_MAX_CONNECTEDCOMPONENTS	256			// maximum directly connected components to a component
#define	SYNTRO_MAX_CONNECTIONIDS		(SYNTRO_MAX_CONNECTEDCOMPONENTS * 2) // used to uniquely identify sockets
#define	SYNTRO_MAX_COMPONENTSPERDEVICE	32			// maximum number of components assigned to a single device
#define	SYNTRO_MAX_SERVICESPERCOMPONENT	32			// max number of services in a component	
#define	SYNTRO_MAX_MMAPS	(SYNTRO_MAX_CONNECTEDCOMPONENTS * SYNTRO_MAX_SERVICESPERCOMPONENT * SYNTRO_MAX_COMPONENTSPERDEVICE)
													// max possible multicast maps
#define	SYNTRO_WORLD_MAX_STRING	100000				// maximum config string size

//	Syntro message size maximums

#define SYNTRO_MESSAGE_MAX			0x40000

#define	SYNTROARM_MESSAGE_MAX		1460			// max size for ARM processors

#define	SP_SYNTRO_MESSAGE_MAX		192				// maximum for small processors (not including SYNTRO_MESSAGE header or SYNTRO_EHEAD header)

#define SYNTRO_PARAM_MAX			128				// parameter chunk size for config deployment

//-------------------------------------------------------------------------------------------
//	IP related definitions

#define	SYNTRO_IPSTR_LEN		16			// size to use for IP string buffers (xxx.xxx.xxx.xxx plus 0)

#define	SYNTRO_IPADDR_LEN		4			// 4 byte IP address
typedef unsigned char SYNTRO_IPADDR[SYNTRO_IPADDR_LEN] ;	// a convenient type for IP addresses

//-------------------------------------------------------------------------------------------
//	Some general purpose typedefs - used esepcially for transferring values greater than
//	8 bits across the network. Assumes processor has 32 bit ints!
//

typedef	unsigned char SYNTRO_UC2[2];		// an array of two unsigned chars
typedef	unsigned char SYNTRO_UC4[4];		// an array of four unsigned chars

//-------------------------------------------------------------------------------------------
//	Some useful defines for MAC addresses
//

#define	SYNTRO_MACADDR_LEN	6				// length of a MAC address

typedef unsigned char SYNTRO_MACADDR[SYNTRO_MACADDR_LEN];	// a convenient type for MAC addresses
#define	SYNTRO_MACADDRSTR_LEN		(SYNTRO_MACADDR_LEN*2+1)	// the hex string version
typedef	char SYNTRO_MACADDRSTR[SYNTRO_MACADDRSTR_LEN];

//-------------------------------------------------------------------------------------------
//	The Syntro UID (Unique Identifier) consists of a 6 byte MAC address (or equivalent)
//	along with a two byte instance number to ensure uniqueness on a device.
//

typedef	struct
{
	SYNTRO_MACADDR		pMacAddr;			// the MAC address
	SYNTRO_UC2			nInstance;			// the instance number
} SYNTRO_UID;

//	These defs are for a string version of the SYNTRO_UID

#define	SYNTRO_UIDSTR_LEN	(sizeof(SYNTRO_UID) * 2 + 1)	// length of string version as hex pairs plus 0
typedef char SYNTRO_UIDSTR[SYNTRO_UIDSTR_LEN];		// and for the string version

//-------------------------------------------------------------------------------------------
//	Service Path Syntax
//
//	When a component wishes to communicate with a service on another component, it needs to locate it using
//	a service path string. This is mapped by SyntroControl into a UID and port number. 
//	The service string can take various forms (note that case is important):
//
//	Form 1 -	Service Name. In this case, the service path is simply the service name. SyntroControl will
//				look up the name and stop at the first service with a matching name. for example, if the
//				service name is "video", the service path would be "video".
//
//	Form 2 -	Component name and service name. The service path is the component name, then "/" and
//				then the service name. SyntroControl will only match the service name against
//				the component with the specified component name. For example, if the service name is "video"
//				and the component name is "WebCam", the service path would be "WebCam/video". "*" is a wildcard
//				so that "*/video" is equivalent to "video".
//
//	Form 3 -	Region name, component name and service name. The service path consists of a region name, then
//				a "/", then the cmoponent name, then a "/" and then the sevice name. As an example, if the 
//				region name is "Robot1", the component name "WebCam" and the service name "video", the
//				service path would be "Robot1/WebCam/video". Again, "*" is a wildcard for regions and
//				components so that "Robot1/*/video" would match the first service called "video" found in region
//				"Robot1".

//	Config and Directory related definitions
//

#define	SYNTRO_SERVICEPATH_SEP		'/'			// the separator character

#define	SYNTRO_MAX_TAG			256				// maximum length of tag string (including 0 at end)
#define	SYNTRO_MAX_NONTAG		1024			// max length of value (including 0 at end)

#define	SP_SYNTRO_MAX_TAG		32				// maximum length of tag string for small processors
#define	SP_SYNTRO_MAX_NONTAG	32				// max length of value string for small processors

#define	SYNTRO_MAX_COMPNAME		32				// max length of a zero-terminated component name
#define	SYNTRO_MAX_COMPTYPE		32				// max length of a zero-terminated component type
#define	SYNTRO_MAX_SERVNAME		32				// max length of a service name
#define	SYNTRO_MAX_REGIONNAME	32				// max length of a region name
#define	SYNTRO_MAX_SERVPATH		128				// this is max size of the NULL terminated path for service paths

typedef	char	SYNTRO_SERVNAME[SYNTRO_MAX_SERVNAME];	// the service type
typedef	char	SYNTRO_REGIONNAME[SYNTRO_MAX_REGIONNAME];	// the region name type
typedef	char	SYNTRO_COMPNAME[SYNTRO_MAX_COMPNAME];	// the node name type
typedef	char	SYNTRO_COMPTYPE[SYNTRO_MAX_COMPTYPE];	// the component type type

typedef char	SYNTRO_SERVPATH[SYNTRO_MAX_SERVPATH];	// the service path type

//-------------------------------------------------------------------------------------------
//	SyntroCore Component Type defs

#define	COMPTYPE_CONTROL		"SyntroControl"	// the component name of SyntroControl
#define	COMPTYPE_EXEC			"SyntroExec"	// the component name for SyntroExec

//-------------------------------------------------------------------------------------------
//	SyntroControl Directory Entry Tag Defs
//
//	A directory record as transmitted betweeen components and SyntroControls looks like:
//
//<CMP>
//<UID>xxxxxxxxxxxxxxxxxx</UID>
//<NAM>name</NAME>								// component name 
//<TYP>type</NAME>								// component type 
//...
//</CMP>
//<CMP>
//...
//</CMP>
//...


//	These tags are the component container tags

#define	DETAG_COMP				"CMP"
#define	DETAG_COMP_END			"/CMP"

//	Component Directory Entry Tag Defs

#define	DETAG_COMPNAME			"NAM"					// the component name
#define	DETAG_COMPTYPE			"TYP"					// a string identifying the component
#define	DETAG_UID				"UID"					// the UID
#define	DETAG_MSERVICE			"MSV"					// a string identifying a multicast service
#define	DETAG_ESERVICE			"ESV"					// a string identifying an E2E service
#define	DETAG_NOSERVICE			"NSV"					// a string identifying an empty service slot

//	E2E service code standard endpoint service names

#define	DE_E2ESERVICE_PARAMS	"Params"				// parameter deployment service
#define	DE_E2ESERVICE_SYNTROCFS	"SyntroCFS"				// SyntroCFS service

//	Service type codes

#define	SERVICETYPE_MULTICAST	0						// a multicast service
#define	SERVICETYPE_E2E			1						// an end to end service
#define	SERVICETYPE_NOSERVICE	2						// a code indicating no service

//-------------------------------------------------------------------------------------------
//	Syntro message types
//

//	HEARTBEAT
//	This message which is just the SYNTROMSG itself is sent regular by both parties
//	in a SyntroLink. It's used to ensure correct operation of the link and to allow
//	the link to be re-setup if necessary. The message itself is a Hello data structure -
//	the same as is sent on the Hello system.
//
//	The HELLO structure that forms the message may also be followed by a properly
//	formatted directory entry (DE) as described above. If there is nothing present,
//	this means that DE for the component hasn't changed. Otherwise, the DE is used by the
//	receiving SyntroControl as the new DE for the component.

#define	SYNTROMSG_HEARTBEAT		1

//	DE_UPDATE
//	This message is sent by a Component to the SyntroControl in order to transfer a DE.
//	Note that the message is sent as a null terminated string.

#define	SYNTROMSG_SERVICE_LOOKUP_REQUEST	2

//	SERVICE_LOOKUP_RESPONSE
//	This message is sent back to a component with the results of the lookup.
//	The relevant fields are filled in the SYNTRO_SERVICE_LOOKUP structure.

#define	SYNTROMSG_SERVICE_LOOKUP_RESPONSE	3

//	DIRECTORY_REQUEST
//	An appliation can request a copy of the directory using this message.
//	There are no parameters or data - the message is just a SYNTRO_MESSAGE

#define SYNTROMSG_DIRECTORY_REQUEST			4

//	DIRECTORY_RESPONSE
//	This message is sent to an application in response to a request.
//	The message consists of a SYNTRO_DIRECTORY_RESPONSE structure.

#define SYNTROMSG_DIRECTORY_RESPONSE		5

//	SERVICE_ACTIVATE
//	This message is sent by a SyntroControl to an Endpoint multicast service when the Endpoint
//	multicast should start generating data as someone has subscribed to its service.

#define	SYNTROMSG_SERVICE_ACTIVATE			6

//	MULTICAST_FRAME
//	Multicast frames are sent using this message. The data is the parameter

#define	SYNTROMSG_MULTICAST_MESSAGE	16

//	MULTICAST_ACK
//	This message is sent to acknowledge a multicast and request the next

#define	SYNTROMSG_MULTICAST_ACK		17

//	E2E - Endpoint to Endpoint message

#define	SYNTROMSG_E2E				18

#define	SYNTROMSG_MAX				18			// highest legal message value

//-------------------------------------------------------------------------------------------
//	SYNTRO_MESSAGE - the structure that defines the object transferred across
//	the SyntroLink - the component to component header. This structure must 
//	be the first entry in every message header.
//

//	The structure itself

typedef struct
{
	unsigned char	nSCmd;					// the type of message
	SYNTRO_UC4		nLen;					// message length (includes the SYNTRO_MESSAGE itself and everything that follows)
	unsigned char	nFlags;					// used to send priority
	unsigned char	nSpare;					// to put on 32 bit boundary
	unsigned char	nCksm;					// checksum = 256 - sum of previous bytes as chars
} SYNTRO_MESSAGE;

//	SYNTRO_EHEAD - Endpoint header
//	
//	This is used to send messages between specific services within components.
//	nSeq is used to control the acknowledgement window. It starts off at zero
//	and increments with each new message. Acknowledgements indicate the next acceptable send
//	seq and so open the window again.

#define	SYNTRO_MAX_WINDOW	4					// the maximum number of outstanding messages

typedef struct
{
	SYNTRO_MESSAGE	cSM;						// the SyntroLink header
	SYNTRO_UID		cSrc;						// source component of the endpoint message
	SYNTRO_UID		cDst;						// dest component of the message
	SYNTRO_UC2		nSPort;						// the source port number
	SYNTRO_UC2		nDPort;						// the destination port number
	unsigned char	nSeq;						// seq number of message
	unsigned char	nPar0;						// an application-specific parameter (for E2E use)				
	unsigned char	nPar1;
	unsigned char	nPar2;						// make a multiple of 32 bits
} SYNTRO_EHEAD;

//-------------------------------------------------------------------------------------------
//	The SYNTRO_SERVICE_LOOKUP structure

#define	SERVICE_LOOKUP_INTERVAL	(SYNTRO_CLOCKS_PER_SEC * 2)	 // while waiting
#define	SERVICE_REFRESH_INTERVAL (SYNTRO_CLOCKS_PER_SEC * 4) // when registered
#define	SERVICE_REFRESH_TIMEOUT	(SERVICE_REFRESH_INTERVAL * 3) // Refresh timeout period
#define	SERVICE_REMOVING_INTERVAL (SYNTRO_CLOCKS_PER_SEC * 4) // when closing
#define	SERVICE_REMOVING_MAX_RETRIES		2				// number of times an endpoint retries closing a remote service

#define	SERVICE_LOOKUP_FAIL		0							// not found
#define	SERVICE_LOOKUP_SUCCEED	1							// found and response fields filled in
#define	SERVICE_LOOKUP_REMOVE	2							// this is used to remove a multicast registration

typedef struct
{
	SYNTRO_MESSAGE		cSM;								// the SyntroLink header
	SYNTRO_UID			cUID;								// the returned UID of the service
	SYNTRO_UC4			nID;								// the returned ID for this entry (to detect restarts requiring re-regs)
	SYNTRO_SERVPATH		pSrvPath;							// the service path string to be looked up
	SYNTRO_UC2			nRPort;								// the returned port to use for the service - the remote index for the service
	SYNTRO_UC2			nCompIndex;							// the returned component index on SyntroControl (for fast refreshes)
	SYNTRO_UC2			nLPort;								// the port number of the requestor - the local index for the service
	unsigned char		nSrvType;							// the service type requested
	unsigned char		nResp;								// the response code
} SYNTRO_SERVICE_LOOKUP;

typedef struct
{
	SYNTRO_MESSAGE		cSM;								// the SyntroLink header
	SYNTRO_UC2			endpointPort;						// the endpoint service port to which this is directed
	SYNTRO_UC2			nCompIndex;							// the returned component index on SyntroControl (for fast refreshes)
	SYNTRO_UC2			syntroControlPort;					// the SyntroControl to send the messages to
	unsigned char		nResp;								// the response code
} SYNTRO_SERVICE_ACTIVATE;


//	SYNTROMESSAGE nFlags masks

#define	SYNTROLINK_PRI			0x03						// bits 0 and 1 are priority bits

#define	SYNTROLINK_PRIORITIES	4							// four priority levels

#define	SYNTROLINK_HIGHPRI		0							// highest priority - typically for real time control data
#define	SYNTROLINK_MEDHIGHPRI	1
#define	SYNTROLINK_MEDPRI		2
#define	SYNTROLINK_LOWPRI		3							// lowest priority - typically for multicast information

//-------------------------------------------------------------------------------------------
//	SYNTRO_DIRECTORY_RESPONSE - the directory response message structure
//

typedef struct
{
	SYNTRO_MESSAGE		cSM;								// the SyntroLink header
															// the directory string follows
} SYNTRO_DIRECTORY_RESPONSE;

//-------------------------------------------------------------------------------------------
//	SYNTRO_TIMESTAMP - data structure used to send timestamps
//
//	This is based on the Windows SYSTEMTIME but uses portable data types
//

typedef	struct
{
    SYNTRO_UC2 nYear;
    SYNTRO_UC2 nMonth;
    SYNTRO_UC2 nDayOfWeek;
    SYNTRO_UC2 nDay;
    SYNTRO_UC2 nHour;
    SYNTRO_UC2 nMinute;
    SYNTRO_UC2 nSecond;
    SYNTRO_UC2 nMilliseconds;
} SYNTRO_TIMESTAMP;

//-------------------------------------------------------------------------------------------
//	SyntroCFS Definitions
//

//	SYNTRO_CFSHEADER is used on every SyntroCFS E2E message
//	cfsType is used to hold the message type code.
//	cfsParam depends on the cfsType field. If it is a response, this is a response code.
//	cfsIndex is the index of the record referred to in the req/res. Not always used.
//	cfsLength is the total length of data that follows the header. The type of data depends on cfsType.

//	Note about stream handles and response codes
//
//	Since stream handles and response codes can share the same field in some cases,
//	the top bit (bit 15) of the field is used to indicate which it is. Error response codes
//	have the top bit set. So, if the top bit is clear, this is a success response and the remaining
//	15 bits may contain the stream handle (on an open response). If the top bit is set, it is an error 
//	response code and the remaining 15 bits indicate the type.

typedef struct
{
	SYNTRO_UC2		cfsType;					// the message type
	SYNTRO_UC2		cfsParam;					// a parameter value used for response codes for example
	SYNTRO_UC2		cfsStoreHandle;				// the handle used to identify an open stream at the SyntroCFS store
	SYNTRO_UC2		cfsClientHandle;			// the handle used to identify an open stream at the client
	SYNTRO_UC4		cfsIndex;					// record index
	SYNTRO_UC4		cfsLength;					// length of data that follows this structure (record, stream name etc)
} SYNTRO_CFSHEADER;

//	SyntroCFS message type codes
//
//	Note: cfsLength is alsways used and must be set to zero if the message is just the SYNTRO_CFSHEADER

//	SYNTROCFS_TYPE_DIR_REQ is sent to a SyntroCFS store to request a list of available streams.
//	cfsParam, cfsStoreHandle, cfsClientHandle, cfsIndex are not used. 

#define	SYNTROCFS_TYPE_DIR_REQ			0		// stream directory request

//	SYNTROCFS_TYPE_DIR_RES is returned from a SyntroCFS store in response to a request.
//	cfsParam contains a response code. If it indicates success, the stream names
//	follow the header as a sequence of null terminated strings. cfsLength indicates the total length.
//	cfsIndex cfsStoreHandle, cfsClientHandle is not used.

#define	SYNTROCFS_TYPE_DIR_RES			1		// stream directory response

//	SYNTROCFS_TYPE_OPEN_REQ is sent to a SyntroCFS store to open a stream.
//	cfsParam contains the response code
//	cfsClientHandle contains the handle to be used by the client for this stream.
//	cfsStoreHandle is unused.
//	cfsIndex is not used. 
//	The stream name is a null terminated stream
//	that follows the header. The total length of the stream name (including the null) is in 
//	cfsLength.

#define	SYNTROCFS_TYPE_OPEN_REQ			2		// stream open request

//	SYNTROCFS_TYPE_OPEN_RES is sent from the SyntroCFS store in response to a request
//	cfsParam indicates the response code.
//	cfsClientHandle contains the handle to be used by the client for this stream.
//	cfsStoreHandle contains the handle to be used by the store for this stream.
//	cfsIndex is not used.

#define	SYNTROCFS_TYPE_OPEN_RES			3		// stream open response

//	SYNTROCFS_TYPE_CLOSE_REQ is sent to the SyntroCFS store to close an open stream
//	cfsParam is unused. 
//	cfsClientHandle contains the handle to be used by the client for this stream.
//	cfsStoreHandle contains the handle to be used by the store for this stream.
//	cfsIndex is unused.

//	cfsIndex and cfsLength are not used.

#define	SYNTROCFS_TYPE_CLOSE_REQ		4		// stream close request

//	SYNTROCFS_TYPE_CLOSE_RES is send from the SyntroCFS store in response to a close request
//	cfsParam contains the response code. If successful, this is the file handle that was closed
//	and no longer valid. If unsuccessful, this is the error code.
//	cfsClientHandle contains the handle to be used by the client for this stream.
//	cfsStoreHandle contains the handle to be used by the store for this stream.
//	cfsIndex is unused.

#define	SYNTROCFS_TYPE_CLOSE_RES		5		// stream close response

//	SYNTROCFS_TYPE_KEEPALIVE_REQ is sent to the SyntroCFS store to keep an open stream alive
//	cfsParam contains the stream handle.
//	cfsClientHandle contains the handle to be used by the client for this stream.
//	cfsStoreHandle contains the handle to be used by the store for this stream.
//	cfsIndex is not used.

#define	SYNTROCFS_TYPE_KEEPALIVE_REQ	6		// keep alive heartbeat request

//	SYNTROCFS_TYPE_KEEPALIVE_RES is sent from the SyntroCFS store in response to a request
//	cfsParam contains the stream handle for an open stream or an error code.
//	cfsClientHandle contains the handle to be used by the client for this stream.
//	cfsStoreHandle contains the handle to be used by the store for this stream.
//	cfsIndex is not used.

#define	SYNTROCFS_TYPE_KEEPALIVE_RES	6		// keep alive heartbeat response

//	SYNTROCFS_TYPE_READ_INDEX_REQ is sent to the SyntroCFS store to request the record at the index specified
//	cfsParam is unused.
//	cfsClientHandle contains the handle to be used by the client for this stream.
//	cfsStoreHandle contains the handle to be used by the store for this stream.
//	cfsIndex contains the record index to be read.


#define	SYNTROCFS_TYPE_READ_INDEX_REQ	16		// requests a read of record at index n

//	SYNTROCFS_TYPE_READ_INDEX_RES is send from the SyntroCFS store in response to a request.
//	cfsParam contains the stream handle if successful, an error code otherwise.
//	cfsClientHandle contains the handle to be used by the client for this stream.
//	cfsStoreHandle contains the handle to be used by the store for this stream.
//	cfsIndex contains the record index.
//	cfsLength indicates the total length of the record that follows the header

#define	SYNTROCFS_TYPE_READ_INDEX_RES	17		// response to a read at index n - contains record or error code

//	SyntroCFS Size Defines

#define	SYNTROCFS_MAX_CLIENT_STREAMS			32				// max streams a client can have open at one time per EP

//	SyntroCFS Error Response codes

#define	SYNTROCFS_SUCCESS						0				// this is a success code as top bit is zero
#define	SYNTROCFS_ERROR_CODE					0x8000			// this is where error codes start

#define	SYNTROCFS_ERROR_SERVICE_UNAVAILABLE		(SYNTROCFS_ERROR_CODE + 0)	// service endpoint is not available
#define	SYNTROCFS_ERROR_REQUEST_ACTIVE			(SYNTROCFS_ERROR_CODE + 1)	// service request already active (usually directory)
#define	SYNTROCFS_ERROR_REQUEST_TIMEOUT 		(SYNTROCFS_ERROR_CODE + 2)	// service request timeout
#define	SYNTROCFS_ERROR_UNRECOGNIZED_COMMAND	(SYNTROCFS_ERROR_CODE + 3)	// cfsType wasn't recognized
#define	SYNTROCFS_ERROR_MAX_CLIENT_STREAMS		(SYNTROCFS_ERROR_CODE + 4)	// too many streams open at client
#define	SYNTROCFS_ERROR_MAX_STORE_STREAMS		(SYNTROCFS_ERROR_CODE + 5)	// too many streams open at store
#define	SYNTROCFS_ERROR_STREAM_NOT_FOUND		(SYNTROCFS_ERROR_CODE + 6)	// stream name wasn't in an open request
#define	SYNTROCFS_ERROR_STREAM_INVALID_FORMAT	(SYNTROCFS_ERROR_CODE + 7)	// stream isn't a structured type
#define	SYNTROCFS_ERROR_INVALID_HANDLE			(SYNTROCFS_ERROR_CODE + 8)	// stream handle not valid
#define	SYNTROCFS_ERROR_INVALID_RECORD_INDEX	(SYNTROCFS_ERROR_CODE + 9)	// record index beyond end of stream in read request

//	SyntroCFS Timer Values

#define	SYNTROCFS_DIRREQ_TIMEOUT				(SYNTRO_CLOCKS_PER_SEC * 5)	// how long to wait for a stream directory response
#define	SYNTROCFS_OPENREQ_TIMEOUT				(SYNTRO_CLOCKS_PER_SEC * 5)	// how long to wait for a stream open response
#define	SYNTROCFS_READREQ_TIMEOUT				(SYNTRO_CLOCKS_PER_SEC * 5)	// how long to wait for a stream read response
#define	SYNTROCFS_CLOSEREQ_TIMEOUT				(SYNTRO_CLOCKS_PER_SEC * 5)	// how long to wait for a stream close response
#define	SYNTROCFS_KEEPALIVE_INTERVAL			(SYNTRO_CLOCKS_PER_SEC * 2)	// interval between keep alives
#define	SYNTROCFS_KEEPALIVE_TIMEOUT				(SYNTROCFS_KEEPALIVE_INTERVAL * 3)	// at which point the stream is considered closed

//	SyntroCFS E2E Message Priority
//	Always use this priority for SyntroCFS messages. Random selection could lead to re-ordering

#define	SYNTROCFS_E2E_PRIORITY					(SYNTROLINK_MEDHIGHPRI)

//-------------------------------------------------------------------------------------------
//	Syntro Record Headers
//
//	Record headers must always have the record type as the first field.
//

typedef struct
{
	SYNTRO_UC2		nType;						// the record type code
	SYNTRO_UC2		nSubType;					// the sub type code
	SYNTRO_UC2		nHeaderLength;				// total length of specific record header
	SYNTRO_UC2		nParam;						// type specific parameter
	SYNTRO_TIMESTAMP	cTimestamp;				// timestamp for the sample
} SYNTRO_RECORD_HEADER;

//	Major type values

#define	SYNTRO_RECORD_TYPE_VIDEO	0			// a video stream
#define	SYNTRO_RECORD_TYPE_AUDIO	1			// an audio stream
#define	SYNTRO_RECORD_TYPE_NAV		2			// navigation data

#define	SYNTRO_RECORD_TYPE_USER		(0x8000)	// user defined codes start here

//	Video minor type code

#define	SYNTRO_RECORD_TYPE_VIDEO_MJPEG		0	// MJPEG compression

//	Audio minor type code

#define	SYNTRO_RECORD_TYPE_AUDIO_PCM		0	// PCM audio

//	Navigation minor type codes

#define	SYNTRO_RECORD_TYPE_NAV_IMU			0	// IMU data
#define	SYNTRO_RECORD_TYPE_NAV_GPS			1	// GPS data
#define	SYNTRO_RECORD_TYPE_NAV_ODOMETRY		2	// odometry data

//	SYNTRO_RECORD_VIDEO - used to send video frames
//
//	The structure follows the SYNTRO_EHEAD structure. Immediately following this structure
//	is the left (or single) image data followed by the right image data (if present).

typedef struct
{
	SYNTRO_RECORD_HEADER	cRecordHeader;		// the record type header
	SYNTRO_UC2		nWidth;						// width of each image
	SYNTRO_UC2		nHeight;					// height of each image
	SYNTRO_UC4		nSize;						// size of the left image
} SYNTRO_RECORD_VIDEO;

//----------------------------------------------------------
//
//	Syntro servo defs. These are used in many things, including SyntroRobot and SyntroAV

#define	SYNTRO_SERVO_CENTER			0x8000		// middle of servo range
#define	SYNTRO_SERVO_RANGE			0x7fff		// servo value range from center

#define	SYNTRO_SERVO_LEFT_END		(SYNTRO_SERVO_CENTER - SYNTRO_SERVO_RANGE)	// left end of servo range
#define	SYNTRO_SERVO_RIGHT_END		(SYNTRO_SERVO_CENTER + SYNTRO_SERVO_RANGE)	// right end of servo range

#endif	// _SYNTRODEFS_H

