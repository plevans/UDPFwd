/*		UDP Packet forwarder for internet connected HIL
 *
 * 		File:				main.c
 * 		Author(s): 			16 May 2018
 * 		Creation Date:		P L Evans
 *
 * 		Description:
 *		Program initialisation.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "udpfwd.h"

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>

#include "peprintf.h"


int UFD_initGUI( UdpFwdData *ud, GtkBuilder *bld ) {
	int i;

	UFD_initialiseOutputWindows( ud, bld );
	UFD_intialiseParameterWidgets( ud, bld );
	UFD_initialiseRemoteList( ud, bld );

	ud->runLocalThread = 0;
	ud->enableEmulation = 0;

	for( i = 0; i < 9; i++ ) {
		ud->recvParams[i].value = 0.;
		ud->sendParams[i].value = 0.;
		ud->recvParams[i].ID = -1;
		ud->sendParams[i].ID = -1;
	}

	ud->emulateFrequency = 0.5;

	ud->nrecvParams = 0;
	ud->nsendParams = 0;

	return 0;
}


int UFD_intialiseParameterWidgets( UdpFwdData *ud, GtkBuilder *bld ) {
	if(
			!(ud->widgets[WIDGET_LOCALPORT] = GTK_WIDGET( gtk_builder_get_object (bld, "EntryLocalPort") )) ||
			!(ud->widgets[WIDGET_HILIP] = GTK_WIDGET( gtk_builder_get_object (bld, "EntryHILIP") )) ||
			!(ud->widgets[WIDGET_HILPORT] = GTK_WIDGET( gtk_builder_get_object (bld, "EntryHILPort") )) ||

			!(ud->widgets[WIDGET_SENDNAME1] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry1") )) ||
			!(ud->widgets[WIDGET_SENDNAME2] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry2") )) ||
			!(ud->widgets[WIDGET_SENDNAME3] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry3") )) ||
			!(ud->widgets[WIDGET_SENDNAME4] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry4") )) ||
			!(ud->widgets[WIDGET_SENDNAME5] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry5") )) ||
			!(ud->widgets[WIDGET_SENDNAME6] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry6") )) ||
			!(ud->widgets[WIDGET_SENDNAME7] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry7") )) ||
			!(ud->widgets[WIDGET_SENDNAME8] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry8") )) ||
			!(ud->widgets[WIDGET_SENDNAME9] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry9") )) ||
			!(ud->widgets[WIDGET_RECVNAME1] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry10") )) ||
			!(ud->widgets[WIDGET_RECVNAME2] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry11") )) ||
			!(ud->widgets[WIDGET_RECVNAME3] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry12") )) ||
			!(ud->widgets[WIDGET_RECVNAME4] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry13") )) ||
			!(ud->widgets[WIDGET_RECVNAME5] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry14") )) ||
			!(ud->widgets[WIDGET_RECVNAME6] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry15") )) ||
			!(ud->widgets[WIDGET_RECVNAME7] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry16") )) ||
			!(ud->widgets[WIDGET_RECVNAME8] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry17") )) ||
			!(ud->widgets[WIDGET_RECVNAME9] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamNameEntry18") )) ||

			!(ud->widgets[WIDGET_SENDVALUE1] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry1") )) ||
			!(ud->widgets[WIDGET_SENDVALUE2] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry2") )) ||
			!(ud->widgets[WIDGET_SENDVALUE3] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry3") )) ||
			!(ud->widgets[WIDGET_SENDVALUE4] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry4") )) ||
			!(ud->widgets[WIDGET_SENDVALUE5] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry5") )) ||
			!(ud->widgets[WIDGET_SENDVALUE6] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry6") )) ||
			!(ud->widgets[WIDGET_SENDVALUE7] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry7") )) ||
			!(ud->widgets[WIDGET_SENDVALUE8] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry8") )) ||
			!(ud->widgets[WIDGET_SENDVALUE9] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry9") )) ||
			!(ud->widgets[WIDGET_RECVVALUE1] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry10") )) ||
			!(ud->widgets[WIDGET_RECVVALUE2] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry11") )) ||
			!(ud->widgets[WIDGET_RECVVALUE3] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry12") )) ||
			!(ud->widgets[WIDGET_RECVVALUE4] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry13") )) ||
			!(ud->widgets[WIDGET_RECVVALUE5] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry14") )) ||
			!(ud->widgets[WIDGET_RECVVALUE6] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry15") )) ||
			!(ud->widgets[WIDGET_RECVVALUE7] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry16") )) ||
			!(ud->widgets[WIDGET_RECVVALUE8] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry17") )) ||
			!(ud->widgets[WIDGET_RECVVALUE9] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamValueEntry18") )) ||

			!(ud->widgets[WIDGET_SENDTS1] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry1") )) ||
			!(ud->widgets[WIDGET_SENDTS2] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry2") )) ||
			!(ud->widgets[WIDGET_SENDTS3] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry3") )) ||
			!(ud->widgets[WIDGET_SENDTS4] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry4") )) ||
			!(ud->widgets[WIDGET_SENDTS5] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry5") )) ||
			!(ud->widgets[WIDGET_SENDTS6] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry6") )) ||
			!(ud->widgets[WIDGET_SENDTS7] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry7") )) ||
			!(ud->widgets[WIDGET_SENDTS8] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry8") )) ||
			!(ud->widgets[WIDGET_SENDTS9] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry9") )) ||
			!(ud->widgets[WIDGET_RECVTS1] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry10") )) ||
			!(ud->widgets[WIDGET_RECVTS2] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry11") )) ||
			!(ud->widgets[WIDGET_RECVTS3] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry12") )) ||
			!(ud->widgets[WIDGET_RECVTS4] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry13") )) ||
			!(ud->widgets[WIDGET_RECVTS5] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry14") )) ||
			!(ud->widgets[WIDGET_RECVTS6] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry15") )) ||
			!(ud->widgets[WIDGET_RECVTS7] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry16") )) ||
			!(ud->widgets[WIDGET_RECVTS8] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry17") )) ||
			!(ud->widgets[WIDGET_RECVTS9] = GTK_WIDGET( gtk_builder_get_object (bld, "ParamTimestampEntry18") )) ||

			!(ud->widgets[WIDGET_REMOTELIST] = GTK_WIDGET( gtk_builder_get_object (bld, "RemoteConnectionList") )) ||
			!(ud->widgets[WIDGET_REMOTESTORE] = GTK_WIDGET( gtk_builder_get_object (bld, "RemoteConnectionStore") )) ||
			!(ud->widgets[WIDGET_ADDREMOTE] = GTK_WIDGET( gtk_builder_get_object (bld, "ButtonAddRemote") )) ||
			!(ud->widgets[WIDGET_REMOVEREMOTE] = GTK_WIDGET( gtk_builder_get_object (bld, "ButtonRemoveRemote") )) ||

			!(ud->widgets[WIDGET_BROADCASTBUTTON] = GTK_WIDGET( gtk_builder_get_object (bld, "ButtonBroadcast") )) ||

			!(ud->widgets[WIDGET_BROADCASTTS] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastTimestampEntry") )) ||
			!(ud->widgets[WIDGET_BROADCASTID1] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastIDEntry1") )) ||
			!(ud->widgets[WIDGET_BROADCASTID2] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastIDEntry2") )) ||
			!(ud->widgets[WIDGET_BROADCASTID3] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastIDEntry3") )) ||
			!(ud->widgets[WIDGET_BROADCASTID4] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastIDEntry4") )) ||
			!(ud->widgets[WIDGET_BROADCASTID5] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastIDEntry5") )) ||
			!(ud->widgets[WIDGET_BROADCASTID6] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastIDEntry6") )) ||
			!(ud->widgets[WIDGET_BROADCASTID7] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastIDEntry7") )) ||
			!(ud->widgets[WIDGET_BROADCASTID8] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastIDEntry8") )) ||
			!(ud->widgets[WIDGET_BROADCASTID9] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastIDEntry9") )) ||
			!(ud->widgets[WIDGET_BROADCASTVALUE1] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastValueEntry1") )) ||
			!(ud->widgets[WIDGET_BROADCASTVALUE2] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastValueEntry2") )) ||
			!(ud->widgets[WIDGET_BROADCASTVALUE3] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastValueEntry3") )) ||
			!(ud->widgets[WIDGET_BROADCASTVALUE4] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastValueEntry4") )) ||
			!(ud->widgets[WIDGET_BROADCASTVALUE5] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastValueEntry5") )) ||
			!(ud->widgets[WIDGET_BROADCASTVALUE6] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastValueEntry6") )) ||
			!(ud->widgets[WIDGET_BROADCASTVALUE7] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastValueEntry7") )) ||
			!(ud->widgets[WIDGET_BROADCASTVALUE8] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastValueEntry8") )) ||
			!(ud->widgets[WIDGET_BROADCASTVALUE9] = GTK_WIDGET( gtk_builder_get_object (bld, "BroadcastValueEntry9") )) ||

			!(ud->widgets[WIDGET_MENULOCALSTART] = GTK_WIDGET( gtk_builder_get_object (bld, "MenuOpenPort") )) ||
			!(ud->widgets[WIDGET_MENULOCALSTOP] = GTK_WIDGET( gtk_builder_get_object (bld, "MenuClosePort") )) ||
			!(ud->widgets[WIDGET_MENUREMOTESTART] = GTK_WIDGET( gtk_builder_get_object (bld, "MenuEnableRemote") )) ||
			!(ud->widgets[WIDGET_MENUREMOTESTOP] = GTK_WIDGET( gtk_builder_get_object (bld, "MenuDisableRemote") ))
	) {
		printf( "Error loading parameter widgets\n" );
		exit(1);
	}
	return 0;
}

int UFD_initialiseRemoteList( UdpFwdData *ud, GtkBuilder *bld ) {

}

int main( int argc, char *argv[] ) {
    GtkBuilder      *builder;
    GtkWidget       *window;
    GError 			*err = NULL;
    WSADATA wsa;

    int i;

    UdpFwdData ud;

    memset( &ud, 0x00, sizeof(UdpFwdData) );

    /* Initialise gtk */
    gtk_init( &argc, &argv );

	/* Determine root document path to use */
#ifdef WINDOWS
	if( SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, 0, ud.docFolder ) != S_OK ) {
		printf( "Could not find my documents folder, using C:\\.\n" );
		strcpy( ud.docFolder, "c:" );
	} 
	
	strcat( ud.docFolder, "\\UdpFwd\\" );
#else
	strcpy( ud.docFolder, "~/UdpFwd/" );
#endif

	/* Load and initialise GUI */
    builder = gtk_builder_new ();
    if( !gtk_builder_add_from_file( builder, "share/udpfwd/UDPForwarder.glade", &err ) ) {
        printf( "GUI Definitions load failed\n" );
    	fprintf( stderr, "Unable to read file: %s\n", err->message );
    	g_error_free( err );
		exit(1);
    }

    if( !(window = GTK_WIDGET( gtk_builder_get_object (builder, "MainWindow") )) ) {
    	printf( "Unable to load main window description, UI definition corrupt\n" );
    	exit(1);
    }
    gtk_container_set_reallocate_redraws( GTK_CONTAINER (window), TRUE );
	
    gtk_widget_set_events( window, GDK_EXPOSURE_MASK );
    g_signal_connect_swapped( window, "destroy", G_CALLBACK(gtk_main_quit), NULL );

    ud.widgets[WIDGET_MAINWINDOW] = window;
    UFD_initGUI( &ud, builder );

    gtk_widget_realize( window );
    gtk_widget_show_all( window );
    //gtk_window_maximize( GTK_WINDOW(window) );
	
    gtk_builder_connect_signals( builder, &ud );
    g_object_unref( G_OBJECT( builder ) );

    /* Disable all GUI elements except for local IP parameters */
    UFD_enableRemoteList( &ud, FALSE ) ;
    UFD_enableModelParams( &ud, FALSE );
    UFD_enableBroadcast( &ud, FALSE );
    UFD_enableHILIP( &ud, TRUE );

    //Initialise winsock
    peprintf( PEPSTR_HILI, NULL, "GUI initialised.\nInitialising Winsock...");
	if( WSAStartup( MAKEWORD(2,2), &wsa ) != 0 ) {
		peprintf( PEPSTR_ERROR, NULL,  "Winsock startup failed. Error Code : %d", WSAGetLastError() );
		return 0;
	}

    /* Disable local stop menu item as not running */
    gtk_widget_set_sensitive( ud.widgets[WIDGET_MENULOCALSTOP], FALSE );

    /* Disable the remote menu options as this feature isnt yet implemented */
    gtk_widget_set_sensitive( ud.widgets[WIDGET_MENUREMOTESTART], FALSE );
    gtk_widget_set_sensitive( ud.widgets[WIDGET_MENUREMOTESTOP], FALSE );

    peprintf( PEPSTR_HILI, NULL, "complete\n" );
	
    gtk_main ();

    WSACleanup();

    return 0;
}
