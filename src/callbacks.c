/*
 * callbacks.c
 *
 *  Created on: 15 May 2018
 *      Author: ezzpe
 *
 *      Callbacks referenced by UI file
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>

#include "udpfwd.h"
#include "peprintf.h"

G_MODULE_EXPORT void UFD_openPort( GtkWidget *button, gpointer userdata ) {
	UdpFwdData* ud = (UdpFwdData*) userdata;
	char *text;
	int port;

	/* Get IP Address / ports chosen by user */
	if( !(text = gtk_entry_get_text( GTK_ENTRY( ud->widgets[WIDGET_HILIP]) )) ) {
		peprintf( PEPSTR_ERROR, NULL, "Error retrieving specified HIL IP\n" );
		return;
	}

	strncpy( ud->localHILIP, text, 127 );

	if( !(text = gtk_entry_get_text( GTK_ENTRY( ud->widgets[WIDGET_HILPORT]) )) ) {
		peprintf( PEPSTR_ERROR, NULL, "Error retrieving specified HIL Port\n" );
		return;
	}

	strncpy( ud->localHILPort, text, 63 );

	if( !(text = gtk_entry_get_text( GTK_ENTRY( ud->widgets[WIDGET_LOCALPORT]) )) ) {
		peprintf( PEPSTR_ERROR, NULL, "Error retrieving specified local Port\n" );
		return;
	}

	strncpy( ud->localPort, text, 63 );

	port = atof( ud->localPort );
	if( port < 0 || port > 65536 ) {
		peprintf( PEPSTR_ERROR, NULL, "Invalid Local Port\n" );
		return;
	}
	port = atof( ud->localHILPort );
	if( port < 0 || port > 65536 ) {
		peprintf( PEPSTR_ERROR, NULL, "Invalid HIL Port\n" );
		return;
	}

	/* Start a thread to handle listening for data from local HIL */
	peprintf( PEPSTR_HILI, NULL, "Starting local comms listening thread...\n" );
	ud->runLocalThread = 1;
	if( !g_thread_new( "SimulationThread",(GThreadFunc) &UFD_localRecvThread, userdata ) ) {
		peprintf( PEPSTR_ERROR, NULL, "Failed to fork local comms thread\n" );
		ud->runLocalThread = 0;
	}


	/* Create a socket to handle sending data to local HIL */
	peprintf( PEPSTR_HILI, NULL, "Creating socket for sending data to local HIL (IP:%s, Port:%d)...\n", ud->localHILIP, port );
	ud->HILSockLen = sizeof(ud->HILSockAddr);


	//create socket
	if ( ( ud->localHILSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR ) {
		peprintf( PEPSTR_ERROR, NULL, "socket() failed with error code : %d" , WSAGetLastError());
		return;
	}

	//setup address structure
	memset((char *) &ud->HILSockAddr, 0, sizeof(ud->HILSockAddr));
	ud->HILSockAddr.sin_family = AF_INET;
	ud->HILSockAddr.sin_port = htons( port );
	ud->HILSockAddr.sin_addr.S_un.S_addr = inet_addr( ud->localHILIP );

	gtk_widget_set_sensitive( ud->widgets[WIDGET_MENULOCALSTOP], TRUE );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_MENULOCALSTART], FALSE );
	UFD_enableHILIP( ud, FALSE );
	UFD_enableBroadcast( ud, TRUE );
}


G_MODULE_EXPORT void UFD_closePort( GtkWidget *button, gpointer userdata ) {
	UdpFwdData* ud = (UdpFwdData*) userdata;

	peprintf( PEPSTR_HILI, NULL, "Attemping to close listening port for local HIL...\n" );

	ud->runLocalThread = 0;

	closesocket( ud->localHILSocket );
	ud->HILSockLen = 0;

	//while( ud->localThreadActive );

	gtk_widget_set_sensitive( ud->widgets[WIDGET_MENULOCALSTOP], FALSE );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_MENULOCALSTART], TRUE );
	UFD_enableHILIP( ud, TRUE );
	UFD_enableBroadcast( ud, FALSE );
}


G_MODULE_EXPORT void UFD_enableRemote( GtkWidget *button, gpointer userdata ) {
	UdpFwdData* ud = (UdpFwdData*) userdata;

	peprintf( PEPSTR_HILI, NULL, "Remote boradcast enabled\n" );
}

G_MODULE_EXPORT void UFD_disableRemote( GtkWidget *button, gpointer userdata ) {
	UdpFwdData* ud = (UdpFwdData*) userdata;

	peprintf( PEPSTR_HILI, NULL, "Remote broadcast disabled\n" );
}

G_MODULE_EXPORT void UFD_addRemote( GtkWidget *button, gpointer userdata ) {
	UdpFwdData* ud = (UdpFwdData*) userdata;

	peprintf( PEPSTR_HILI, NULL, "Remote address added\n" );
}

G_MODULE_EXPORT void UFD_removeRemote( GtkWidget *button, gpointer userdata ) {
	UdpFwdData* ud = (UdpFwdData*) userdata;

	peprintf( PEPSTR_HILI, NULL, "Remote address removed\n" );
}



G_MODULE_EXPORT void UFD_broadcastMessage( GtkWidget *button, gpointer userdata ) {
	UdpFwdData* ud = (UdpFwdData*) userdata;
	char *msg;

	if( (msg = gtk_entry_get_text( GTK_ENTRY( ud->widgets[WIDGET_BROADCASTMESSAGE] ) )) ) {
		peprintf( PEPSTR_INFO, NULL, "Sending packet to local HIL %s:%d\n", inet_ntoa(ud->HILSockAddr.sin_addr), ntohs(ud->HILSockAddr.sin_port) );
		peprintf( PEPSTR_INFO, NULL, "Data: %s\n", msg );
		if( sendto( ud->localHILSocket, msg, strlen(msg), 0, (struct sockaddr *) &ud->HILSockAddr, ud->HILSockLen ) == SOCKET_ERROR ) {
			peprintf( PEPSTR_ERROR, NULL, "sendto() failed with error code : %d" , WSAGetLastError() );
			return;
		}
		gtk_entry_set_text( GTK_ENTRY( ud->widgets[WIDGET_BROADCASTMESSAGE] ), "" );
	}
}


G_MODULE_EXPORT boolean UFD_broadcastKeypress( GtkWidget *widget, GdkEventKey *event, gpointer userdata) {
	UdpFwdData* ud = (UdpFwdData*) userdata;

    switch( event->keyval ) {
    	case GDK_KEY_Return:
    		UFD_broadcastMessage( NULL, userdata );
    	break;
    }

    return FALSE;
}
