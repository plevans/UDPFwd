/*		UDP Packet forwarder for internet connected HIL
 *
 * 		File:				remotelist.c
 * 		Author(s): 			16 May 2018
 * 		Creation Date:		P L Evans
 *
 * 		Description:
 *		Link GUI to list of remote HIL interfaces used to broadcast messages
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "udpfwd.h"

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>

#include "peprintf.h"




int UFD_broadcastParametersToRemoteList( UdpFwdData *ud ) {
	GtkTreeModel *m;
	GtkTreeSelection *s;

}
