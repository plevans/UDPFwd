

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

#include "gtk/gtk.h"

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


typedef struct _UdpRemoteConnection {
	struct _UdpFwdData *ud;
	int remoteID;		/* Which specific remote (in ud) does this refer to */
	SOCKET socket;

	/* TBD... */
} UdpRemoteConnection;


typedef struct _UdpFwdData {
	GtkWidget *widgets[WIDGET_NUMBER];		/**< Pointers to GUI elements */
	
	char	docFolder[MAX_PATH];			/**< String containing path to documents folder */
	
	int		remotesActive;					/**< 0 If not actively forwading to remotes, !=0 otherwise */
	
	UdpRemoteConnection remotes[MAX_REMOTES];
	int nActiveRemotes;

	int runLocalThread, localThreadActive;
	char localHILIP[128];
	char localHILPort[64];
	char localPort[64];

	SOCKET localHILSocket;
	struct sockaddr_in HILSockAddr;
	int HILSockLen;

} UdpFwdData;


/* main.c */
int UFD_initGUI( UdpFwdData *ud, GtkBuilder *bld );
int UFD_intialiseParameterWidgets( UdpFwdData *ud, GtkBuilder *bld );
int UFD_initialiseRemoteList( UdpFwdData *ud, GtkBuilder *bld );

/* outputWindow.c */
static gboolean UFD_updateOutputText_thread( gpointer userdata );
void UFD_updateOutput( const char* msg, void* data, unsigned int type ) ;
int UFD_initialiseOutputWindows( UdpFwdData *ud, GtkBuilder *bld );

/* enableDisable.c */
void UFD_enableRemoteList( UdpFwdData *ud, gboolean enabled ) ;
void UFD_enableModelParams( UdpFwdData *ud, gboolean enabled );
void UFD_enableBroadcast( UdpFwdData *ud, gboolean enabled );
void UFD_enableHILIP( UdpFwdData *ud, gboolean enabled );
void UFD_enableEmulation( UdpFwdData *ud, gboolean enabled );

/* comms.c */
int UFD_localRecvThread( gpointer data );

#endif
