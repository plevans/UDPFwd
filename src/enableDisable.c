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
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE10], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE11], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE12], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE13], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE14], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE15], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE16], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE17], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE18], enabled );

	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE9], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE10], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE11], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE12], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE13], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE14], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE15], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE16], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE17], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_SENDVALUE18], enabled );
}


void UFD_enableBroadcast( UdpFwdData *ud, gboolean enabled ) {
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTBUTTON], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTMESSAGE], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_EMULATEREMOTE], enabled );
}


void UFD_enableHILIP( UdpFwdData *ud, gboolean enabled ) {
	gtk_widget_set_sensitive( ud->widgets[WIDGET_LOCALPORT], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_HILPORT], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_HILIP], enabled );
}

void UFD_enableEmulation( UdpFwdData *ud, gboolean enabled ) {

	gtk_widget_set_sensitive( ud->widgets[WIDGET_EMULATEFREQUENCY], enabled );

	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE9], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE10], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE11], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE12], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE13], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE14], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE15], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE16], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE17], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_RECVVALUE18], enabled );
}
