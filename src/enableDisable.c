/*
 * enableDisable.c
 *
 *  Created on: 29 May 2018
 *      Author: ezzpe
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
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME9], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME10], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME11], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME12], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME13], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME14], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME15], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME16], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME17], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMNAME18], enabled );

	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE1], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE2], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE3], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE4], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE5], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE6], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE7], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE8], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE9], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE10], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE11], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE12], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE13], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE14], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE15], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE16], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE17], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_PARAMVALUE18], enabled );
}


void UFD_enableBroadcast( UdpFwdData *ud, gboolean enabled ) {
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTBUTTON], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_BROADCASTMESSAGE], enabled );
}


void UFD_enableHILIP( UdpFwdData *ud, gboolean enabled ) {
	gtk_widget_set_sensitive( ud->widgets[WIDGET_LOCALPORT], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_HILPORT], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_HILIP], enabled );
}

void UFD_enableEmulation( UdpFwdData *ud, gboolean enabled ) {
	gtk_widget_set_sensitive( ud->widgets[WIDGET_EMULATEREMOTE], enabled );
	gtk_widget_set_sensitive( ud->widgets[WIDGET_EMULATEFREQUENCY], enabled );
}
