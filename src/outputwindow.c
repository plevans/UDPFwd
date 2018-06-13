/*		UDP Packet forwarder for internet connected HIL
 *
 * 		File:				outputwindow.c
 * 		Author(s): 			16 May 2018
 * 		Creation Date:		P L Evans
 *
 * 		Description:
 *		Display information in text output window
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>

#include "udpfwd.h"

#include "peprintf.h"


const static char* colours[] = { "gray_fg", "orange_fg", "red_fg", "blue_fg" };
static UdpFwdData *udptr = NULL;

typedef struct _outputTextUpdate {
	char *msg;
	unsigned int type;
} outputTextUpdate;



void UFD_updateGUISendParams( UdpFwdData *ud, UdpParameter *params, int nparams ) {
	int i;
	char buffer[1024];

	/* insert new paramaters at beginning of list */
	for( i = nparams; i < 9; i++ ) {
		ud->sendParams[i] = ud->sendParams[i-nparams];
	}

	for( i = 0; i < nparams; i++ ) {
		ud->sendParams[i] = params[i];
	}


	sprintf( buffer, "%d", ud->sendParams[0].timestamp );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDTS1]), buffer );
	sprintf( buffer, "%d", ud->sendParams[0].ID );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDNAME1]), buffer );
	sprintf( buffer, "%g", ud->sendParams[0].value );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDVALUE1]), buffer );

	sprintf( buffer, "%d", ud->sendParams[1].timestamp );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDTS2]), buffer );
	sprintf( buffer, "%d", ud->sendParams[1].ID );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDNAME2]), buffer );
	sprintf( buffer, "%g", ud->sendParams[1].value );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDVALUE2]), buffer );

	sprintf( buffer, "%d", ud->sendParams[2].timestamp );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDTS3]), buffer );
	sprintf( buffer, "%d", ud->sendParams[2].ID );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDNAME3]), buffer );
	sprintf( buffer, "%g", ud->sendParams[2].value );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDVALUE3]), buffer );

	sprintf( buffer, "%d", ud->sendParams[3].timestamp );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDTS4]), buffer );
	sprintf( buffer, "%d", ud->sendParams[3].ID );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDNAME4]), buffer );
	sprintf( buffer, "%g", ud->sendParams[3].value );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDVALUE4]), buffer );

	sprintf( buffer, "%d", ud->sendParams[4].timestamp );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDTS5]), buffer );
	sprintf( buffer, "%d", ud->sendParams[4].ID );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDNAME5]), buffer );
	sprintf( buffer, "%g", ud->sendParams[4].value );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDVALUE5]), buffer );

	sprintf( buffer, "%d", ud->sendParams[5].timestamp );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDTS6]), buffer );
	sprintf( buffer, "%d", ud->sendParams[5].ID );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDNAME6]), buffer );
	sprintf( buffer, "%g", ud->sendParams[5].value );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDVALUE6]), buffer );

	sprintf( buffer, "%d", ud->sendParams[6].timestamp );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDTS7]), buffer );
	sprintf( buffer, "%d", ud->sendParams[6].ID );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDNAME7]), buffer );
	sprintf( buffer, "%g", ud->sendParams[6].value );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDVALUE7]), buffer );

	sprintf( buffer, "%d", ud->sendParams[7].timestamp );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDTS8]), buffer );
	sprintf( buffer, "%d", ud->sendParams[7].ID );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDNAME8]), buffer );
	sprintf( buffer, "%g", ud->sendParams[7].value );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDVALUE8]), buffer );

	sprintf( buffer, "%d", ud->sendParams[8].timestamp );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDTS9]), buffer );
	sprintf( buffer, "%d", ud->sendParams[8].ID );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDNAME9]), buffer );
	sprintf( buffer, "%g", ud->sendParams[8].value );
	gtk_entry_set_text( GTK_ENTRY(ud->widgets[WIDGET_SENDVALUE9]), buffer );

}

gboolean UFD_updateGUISendParams_thread( gpointer userdata ) {
	UdpParameterList* pl = (UdpParameterList*) userdata;

	if( !udptr ) return G_SOURCE_REMOVE;

	UFD_updateGUISendParams( udptr, pl->params, pl->nparams );

	free( pl );

	return G_SOURCE_REMOVE;
}


/* Updates display: triggered by thread but executed by main() */
static gboolean UFD_updateOutputText_thread( gpointer userdata ) {
	GtkTextBuffer *buffer;
	GtkTextIter end;
	GtkAdjustment *adj;
	const char *colour;
	char *msg;
	unsigned int type;
	
	msg = ((outputTextUpdate*) userdata)->msg;
	type = ((outputTextUpdate*) userdata)->type;
	
	if( !msg || !udptr ) return G_SOURCE_REMOVE;
	
	/* A message to display in console window */
	if( !(buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW(udptr->widgets[WIDGET_TEXTOUT]) )) ) {
		perror( "Unable to get text buffer for output results\n" );
		return G_SOURCE_REMOVE;
	}

	if( type & PEPSTR_HILI ) 		colour = colours[3];
	else if( type & PEPSTR_ERROR ) 	colour = colours[2];
	else if( type & PEPSTR_WARN )	colour = colours[1];
	else							colour = colours[0];

	gtk_text_buffer_get_end_iter( buffer, &end );
	gtk_text_buffer_insert_with_tags_by_name(buffer, &end, msg, -1, colour, NULL);
	gtk_text_view_scroll_to_iter( GTK_TEXT_VIEW(udptr->widgets[WIDGET_TEXTOUT]), &end, 0.0, FALSE, 0, 0 );
	if( (adj = gtk_viewport_get_vadjustment( GTK_VIEWPORT(udptr->widgets[WIDGET_TEXTOUTPORT]) )) ) {
		gtk_adjustment_set_value( adj, gtk_adjustment_get_upper( adj ) );
		gtk_viewport_set_vadjustment( GTK_VIEWPORT(udptr->widgets[WIDGET_TEXTOUTPORT]), adj );
	}
	
	free( msg );
	free( userdata );
	
	return G_SOURCE_REMOVE;
}

/* This function is registered as a callback with the PEPRINTF library
 * It allows simulation code to update messages in the output window and to update the progress bars */
void UFD_updateOutput( const char* msg, void* data, unsigned int type ) {
	outputTextUpdate *textdata;
	
	if( udptr ) {
		if( msg ) { /* There is some text to add to output window */
			/* Create copy of data to pass to main thread */
			textdata = malloc( sizeof(outputTextUpdate) );
			if( !textdata ) return;
			
			textdata->type = type;
			if( !(textdata->msg = malloc( (strlen(msg)+1)*sizeof(char ) )) ) {
				printf( "Error updating output window" );
				return;
			}
			
			strcpy( textdata->msg, msg );
			
			/* Request that main thread updates GUI as this function could have been called from another thread */
			gdk_threads_add_idle( UFD_updateOutputText_thread, textdata );
		}
	}
}

int UFD_initialiseOutputWindows( UdpFwdData *ud, GtkBuilder *bld ) {
	GtkTextBuffer *buffer;

	/* get handle on output window */
	if( !(ud->widgets[WIDGET_TEXTOUT] = GTK_WIDGET( gtk_builder_get_object (bld, "TextOutViewer") ))
			|| !(ud->widgets[WIDGET_TEXTOUTPORT] = GTK_WIDGET( gtk_builder_get_object (bld, "TextOutViewPort") ))) {
		printf( "Error loading text view\n" );
		return -1;
	}

	udptr = ud;

	if( !(buffer = gtk_text_view_get_buffer( GTK_TEXT_VIEW(udptr->widgets[WIDGET_TEXTOUT]) )) ) {
		printf( "Error initialising coloured output text\n" );
	} else {
		gtk_text_buffer_create_tag( buffer, "gray_fg", "foreground", "black", NULL );
		gtk_text_buffer_create_tag( buffer, "orange_fg", "foreground", "orange", NULL );
		gtk_text_buffer_create_tag( buffer, "red_fg", "foreground", "red", NULL );
		gtk_text_buffer_create_tag( buffer, "blue_fg", "foreground", "blue", NULL );
	}

	/* initialise redirect to output window handling function */
	pepinit();
	pepupdatecallback( (PEPCALLBACK) &UFD_updateOutput );

	return 0;
}




