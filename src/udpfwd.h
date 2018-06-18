#ifndef UDPFWD_H
/*		UDP Packet forwarder for internet connected HIL
 *
 * 		File:				udpfwd.h
 * 		Author(s): 			16 May 2018
 * 		Creation Date:		P L Evans
 *
 * 		Description:
 *
 *
 */

#define UDPFWD_H

#include <stdint.h>
#include <gtk/gtk.h>
#include "packets.h"
#include "widgets.h"

#if defined (WIN32) || defined (WIN64)
	#include <windows.h>
	#include <shlobj.h>
	#define WINDOWS
#else
	#define MAX_PATH 2048
#endif




#define MAX_REMOTES 8

#define RECV_BUFFER_LENGTH 4096

#define MAX_PARAMS				36
#define MAX_DISPLAY_PARAMS		18

/** Structure containing information describing open socket for transmitting data to single remote.
 *
 */
typedef struct _UdpRemoteConnection {
	int remoteID;							/**< Which specific remote (in ud) does this refer to */
	SOCKET socket;							/**< Valid socket */
	struct sockaddr_in sockAddr;			/**< Remote address data */
	int sockLen;							/**< Length of remote address data */
	char	ipStr[128];						/**< IP Address as string for updating list */
	char	portStr[64];					/**< Port as string for updating list */
} UdpRemoteConnection;


/** Structure containing information describing the value of a single parameter at 1 instant in time.
 *
 */
typedef struct _UdpParameter {
	uint64_t		timestamp;		/**< Timestamp at which this parameter value was valid */
	uint8_t 		ID;				/**< Parameter ID (each shared parameter/signal needs a unique ID across distributed HIL system */
	double 			value;			/**< The value of this parameter/signal at t=timestamp */
} UdpParameter;


/** Structure containing a list of parameters
 *
 */
typedef struct _UdpParameterList {
	UdpParameter *params;			/**< Array of parameter structures */
	int nparams;					/**< Number of parameter structures in array */
} UdpParameterList;


/** Main structure for storing application's data.
 *
 */
typedef struct _UdpFwdData {
	GtkWidget *widgets[WIDGET_NUMBER];		/**< Pointers to GUI elements */
	
	char	docFolder[MAX_PATH];			/**< String containing path to documents folder */
	
	int		remotesActive;					/**< 0 If not actively forwarding to remotes, !=0 otherwise */
	
	UdpRemoteConnection *remotes;			/**< Array of outgoing remote connections */
	int nRemotes;							/**< Number of outgoing remote connections in array */

	int runLocalThread;						/**< Signifies thread to handle local (HIL) listening port should be running */
	int localThreadActive;					/**< Signifies thread to handle local (HIL) listening port is actually running */

	int runRemoteThread;					/**< Signifies thread to handle local (HIL) listening port should be running */
	int remoteThreadActive;					/**< Signifies thread to handle local (HIL) listening port is actually running */

	char localHILIP[128];					/**< String containing local HIL RTT IPv4 address */
	char localHILPort[64];					/**< String containing local HIL RTT Port */
	char localPort[64];						/**< String containing Port used for listening to HIL RTT */
	char remotePort[64];					/**< String containing Port used for listening to internet */

	SOCKET localHILSocket;					/**< Valid socket used to transmit to local HIL RTT */
	struct sockaddr_in HILSockAddr;			/**< Address data for local HIL RTT */
	int HILSockLen;							/**< Length of address data for local HIL RTT */

	SOCKET recvHILSocket;					/**< SOCKET used for receiving data, used when shutting down listening threads */
	SOCKET recvInternetSocket;				/**< SOCKET used for receiving data, used when shutting down listening threads */


	UdpParameter 	recvParams[9];			/**< Most recent parameter values received from remote (for display in GUI / retransmitting)*/
	UdpParameter	sendParams[9];			/**< Most recent paramter values recieved from HIL (for display in GUI / retransmitting)*/
	int nrecvParams, nsendParams;			/**< Number of parameters in 'recent' lists */
} UdpFwdData;


/* main.c */
int UFD_initGUI( UdpFwdData *ud, GtkBuilder *bld );
int UFD_intialiseParameterWidgets( UdpFwdData *ud, GtkBuilder *bld );
int UFD_initialiseRemoteList( UdpFwdData *ud, GtkBuilder *bld );

/* outputWindow.c */
void UFD_updateGUISendParams( UdpFwdData *ud, UdpParameter *params, int nparams );
void UFD_updateGUIRecvParams( UdpFwdData *ud, UdpParameter *params, int nparams );
static gboolean UFD_updateOutputText_thread( gpointer userdata );
void UFD_updateOutput( const char* msg, void* data, unsigned int type ) ;
int UFD_initialiseOutputWindows( UdpFwdData *ud, GtkBuilder *bld );
gboolean UFD_updateGUISendParams_thread( gpointer userdata );
gboolean UFD_updateGUIRecvParams_thread( gpointer userdata );

/* enableDisable.c */
void UFD_enableRemoteList( UdpFwdData *ud, gboolean enabled ) ;
void UFD_enableModelParams( UdpFwdData *ud, gboolean enabled );
void UFD_enableBroadcast( UdpFwdData *ud, gboolean enabled );
void UFD_enableHILIP( UdpFwdData *ud, gboolean enabled );

/* comms.c */
int UFD_localRecvThread( gpointer data );
int UFD_remoteRecvThread( gpointer data );
int UFD_broadcastPacketToRemotes( UdpFwdData *ud, void *buf, size_t buflen ) ;
int UFD_sendPacketToHIL( UdpFwdData *ud, void *buf, size_t buflen ) ;


/* packets.c */
void UFD_triphase_printBuffer( void* buffer, size_t nr_bytes ) ;
int UFD_triphase_decodeParams( void* buffer, size_t nr_bytes, UdpParameter *params, int maxParams );
int UFD_triphase_encodeBuffer( void* buffer, UdpParameter *params, int nparam, uint64_t timestamp );
int UFD_internet_decodeParams( void* buffer, size_t nr_bytes, UdpParameter *params, int maxParams );
int UFD_internet_encodeBuffer( void* buffer, UdpParameter *params, int nparam, uint64_t timestamp );

/* callbacks.c */
G_MODULE_EXPORT void UFD_openPort( GtkWidget *button, gpointer userdata ) ;
G_MODULE_EXPORT void UFD_closePort( GtkWidget *button, gpointer userdata ) ;
G_MODULE_EXPORT void UFD_enableRemote( GtkWidget *button, gpointer userdata );
G_MODULE_EXPORT void UFD_disableRemote( GtkWidget *button, gpointer userdata );
G_MODULE_EXPORT void UFD_addRemote( GtkWidget *button, gpointer userdata );
G_MODULE_EXPORT void UFD_removeRemote( GtkWidget *button, gpointer userdata ) ;
G_MODULE_EXPORT void UFD_broadcastMessage( GtkWidget *button, gpointer userdata ) ;

#endif
