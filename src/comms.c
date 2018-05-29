/*
 * comms.c
 *
 *  Created on: 16 May 2018
 *      Author: ezzpe
 */


#include <stdio.h>
#include <stdlib.h>

#include "udpfwd.h"

#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>

#include "peprintf.h"


/* Function to handle receiving data from local HIL and broadcasting to remotes
 * Quick implemention based on example at https://www.binarytides.com/udp-socket-programming-in-winsock/ */
int UFD_localRecvThread( gpointer data ) {
	UdpFwdData *ud = (UdpFwdData*) data;
	SOCKET s;
	struct sockaddr_in server, si_other;
	int slen , recv_len;
	char buf[RECV_BUFFER_LENGTH];
	WSADATA wsa;
	struct timeval tv;
	int portShort;

	ud->localThreadActive = 1;

	portShort = atof( ud->localPort );

	slen = sizeof(si_other) ;

	//create socket
	if ( (s=socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP) ) == SOCKET_ERROR) {
		peprintf( PEPSTR_ERROR, NULL, "socket() failed with error code : %d" , WSAGetLastError() );
		return 0;
	}

	// set socket timeout

	tv.tv_sec = 0;
	tv.tv_usec = 100000;
	if (setsockopt( s, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) < 0 ) {
		peprintf( PEPSTR_ERROR, NULL, "failed to set socket timeout with error code : %d" , WSAGetLastError() );
		return 0;
	}

	//Prepare the sockaddr_in structure
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons( portShort );

	//Bind
	if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR) {
		peprintf( PEPSTR_ERROR, NULL, "Bind failed with error code : %d" , WSAGetLastError() );
		return 0;
	}


	//start communication
	peprintf( PEPSTR_INFO, NULL, "Waiting for incoming data from HIL...\n" );
	while( ud->runLocalThread ) {
		memset( buf,'\0', RECV_BUFFER_LENGTH );

		//try to receive some data, this is a blocking call
		if( (recv_len = recvfrom(s, buf, RECV_BUFFER_LENGTH, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR ) {
			peprintf( PEPSTR_ERROR, NULL, "recvfrom() failed with error code : %d" , WSAGetLastError());
			break;
		}

		//print details of the client/peer and the data received
		peprintf( PEPSTR_INFO, NULL, "Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port) );
		peprintf( PEPSTR_INFO, NULL, "Data: %s\n" , buf);

		/*
		//now reply the client with some message?
		if( sendto(s, buf, recv_len, 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR ) {
			peprintf( PEPSTR_ERROR, NULL, "sendto() failed with error code : %d" , WSAGetLastError());
			break;
		}
		*/
	}

	closesocket(s);
	//WSACleanup();

	peprintf( PEPSTR_HILI, NULL, "Local comms thread exiting: %s\n" );

	ud->localThreadActive = 0;
	return 0;
}



/* Function to handle receiving data from remote and passing to local
 * 1 of these threads will need to exist for each remote */
int UFD_remoteRecvThread( gpointer data ) {
	/* To be implemented but data will be a pointer to a Udp_RemoteConnection structure */

	/* TBD ... */
}

