/*
 * packets.c
 *
 *  Created on: 13 Jun 2018
 *      Author: ezzpe
 *
 *      Functions to encode / decode UDP packet
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "udpfwd.h"

#include "peprintf.h"


void UFD_printBuffer( void* buffer, size_t nr_bytes ) {
	uint32_t* buf = (uint32_t*) buffer;
	int i;
	int nvar = nr_bytes / sizeof(double);
	double d;
	uint32_t *u1, *u2;

	u1 = &d;
	u2 = u1+1;

	peprintf( PEPSTR_INFO, NULL, "%d bytes, %d variables (sizeof(uint32_t) = %d)\n", nr_bytes, nvar, sizeof(uint32_t) );

	for( i = 0; i < nvar; i++ ) {

		*u1 = buf[i*2];
		*u2 = buf[i*2+1];

		peprintf( PEPSTR_INFO, NULL, "0x%08x (%f)\t", (uint64_t) (*u2)|(*u1<<32), d );
	}

	peprintf( PEPSTR_INFO, NULL, "\n" );

}


int UFD_decodeParams( void* buffer, size_t nr_bytes, UdpParameter *params, int maxParams ) {
	uint32_t* buf = (uint32_t*) buffer;
	int i;
	int nvar = nr_bytes / sizeof(double);
	double d;
	uint32_t *u1, *u2;
	uint64_t timestamp;

	u1 = &timestamp;
	u2 = u1+1;

	/* First parameter in list assumed to be timestamp (integer)
	 * All parameters in packet are assumed to have same time-stamp
	 * */
	*u1 = buf[0];
	*u2 = buf[1];


	/* Now read remaining double precision values */
	u1 = &d;
	u2 = u1+1;

	for( i = 1; i < nvar && i < maxParams; i++ ) {
		*u1 = buf[i*2];
		*u2 = buf[i*2+1];

		params[i-1].ID = i-1;				// just assuming first parameter in packet has ID 0, 2nd ID 1, etc - really the IDs should be encoded in the packet
		params[i-1].value = d;
		params[i-1].timestamp = timestamp;
	}

	return i-1;
}

int UFD_encodeBuffer( void* buffer, UdpParameter *params, int nparam, uint64_t timestamp ) {
	uint32_t* buf = (uint32_t*) buffer;
	int i;
	double d;
	uint32_t *u1, *u2;

	/* Add time-stamp as first parameter */
	u1 = &timestamp;
	u2 = u1+1;
	buf[0] = *u1;
	buf[1] = *u2;

	u1 = &d;
	u2 = u1+1;

	for( i = 1; i < nparam+1; i++ ) {
		d = params[i-1].value;

		buf[i*2] = *u1;
		buf[i*2+1] = *u2;
	}

	return 8*(nparam+1);
}
