/*		UDP Packet forwarder for internet connected HIL
 *
 * 		File:				enableDisable.c
 * 		Author(s): 			29 May 2018
 * 		Creation Date:		P L Evans
 *
 * 		Description:
 *		Enable/disable GUI components
 */

#include <stdio.h>
#include <stdlib.h>

#include "udpfwd.h"

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>

#include "peprintf.h"


void UFD_enableRemoteList( UdpFwdData *ud, gboolean enabled ) {
	gtk_widget_set_sensitive( ud->widgets[WIDGET_REMOTELIST], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_REMOTESTORE], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_ADDREMOTE], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_REMOVEREMOTE], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_REMOTEIP], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_REMOTEPORT], enabled );
}


void UFD_enableModelParams( UdpFwdData *ud, gboolean enabled ) {
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE9], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVNAME1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVNAME2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVNAME3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVNAME4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVNAME5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVNAME6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVNAME7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVNAME8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVNAME9], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVTS1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVTS2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVTS3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVTS4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVTS5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVTS6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVTS7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVTS8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVTS9], enabled );

	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE9], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDNAME1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDNAME2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDNAME3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDNAME4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDNAME5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDNAME6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDNAME7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDNAME8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDNAME9], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDTS1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDTS2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDTS3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDTS4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDTS5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDTS6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDTS7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDTS8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDTS9], enabled );
}


void UFD_enableBroadcast( UdpFwdData *ud, gboolean enabled ) {
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTTS], enabled );

	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTVALUE1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTVALUE2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTVALUE3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTVALUE4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTVALUE5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTVALUE6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTVALUE7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTVALUE8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTVALUE9], enabled );

	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTID1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTID2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTID3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTID4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTID5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTID6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTID7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTID8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTID9], enabled );

	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTBUTTON], enabled );
}


void UFD_enableHILIP( UdpFwdData *ud, gboolean enabled ) {
	gtk_widget_set_sensitive( ud->widgets[WIDGET_LOCALPORT], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_HILPORT], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_HILIP], enabled );
}

