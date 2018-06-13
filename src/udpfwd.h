

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

#include "gtk/gtk.h"

#include "packets.h"

#if defined(WIN32) || defined (WIN64)
	#include <windows.h>
	#include <shlobj.h>
	#define WINDOWS
#else
	#define MAX_PATH 2048
#endif

#include "widgets.h"


#define MAX_REMOTES 8

#define RECV_BUFFER_LENGTH 1024

#define MAX_PARAMS				36
#define MAX_DISPLAY_PARAMS		18


typedef struct _UdpRemoteConnection {
	struct _UdpFwdData *ud;
	int remoteID;		/* Which specific remote (in ud) does this refer to */
	SOCKET socket;

	/* TBD... */
} UdpRemoteConnection;


typedef struct _UdpParameter {
	uint64_t		timestamp;
	uint64_t 		ID;
	double 			value;
} UdpParameter;


typedef struct _UdpParameterList {
	UdpParameter *params;
	int nparams;
} UdpParameterList;


typedef struct _UdpFwdData {
	GtkWidget *widgets[WIDGET_NUMBER];		/**< Pointers to GUI elements */
	
	char	docFolder[MAX_PATH];			/**< String containing path to documents folder */
	
	int		remotesActive;					/**< 0 If not actively forwading to remotes, !=0 otherwise */
	
	UdpRemoteConnection remotes[MAX_REMOTES];
	int nActiveRemotes;

	int runLocalThread, localThreadActive, enableEmulation;
	char localHILIP[128];
	char localHILPort[64];
	char localPort[64];

	SOCKET localHILSocket;
	struct sockaddr_in HILSockAddr;
	int HILSockLen;


	UdpParameter 	recvParams[9];					/**< Most recent parameter values received from remote (for display in GUI / retransmitting)*/
	UdpParameter	sendParams[9];					/**< Most recent paramter values recieved from HIL (for display in GUI / retransmitting)*/
	int nrecvParams, nsendParams;

	double emulateFrequency;
} UdpFwdData;


/* main.c */
int UFD_initGUI( UdpFwdData *ud, GtkBuilder *bld );
int UFD_intialiseParameterWidgets( UdpFwdData *ud, GtkBuilder *bld );
int UFD_initialiseRemoteList( UdpFwdData *ud, GtkBuilder *bld );

/* outputWindow.c */
static gboolean UFD_updateOutputText_thread( gpointer userdata );
void UFD_updateOutput( const char* msg, void* data, unsigned int type ) ;
int UFD_initialiseOutputWindows( UdpFwdData *ud, GtkBuilder *bld );
gboolean UFD_updateGUISendParams_thread( gpointer userdata );

/* enableDisable.c */
void UFD_enableRemoteList( UdpFwdData *ud, gboolean enabled ) ;
void UFD_enableModelParams( UdpFwdData *ud, gboolean enabled );
void UFD_enableBroadcast( UdpFwdData *ud, gboolean enabled );
void UFD_enableHILIP( UdpFwdData *ud, gboolean enabled );

/* comms.c */
int UFD_localRecvThread( gpointer data );
int UFD_emulationThread( gpointer data );

/* packets.c */
int UFD_decodeParams( void* buffer, size_t nr_bytes, UdpParameter *params, int maxParams );
int UFD_encodeBuffer( void* buffer, UdpParameter *params, int nparam, uint64_t timestamp );

/* callbacks.c */
void UFD_updateGUISendParams( UdpFwdData *ud, UdpParameter *params, int nparams );

#endif
