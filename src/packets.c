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

typedef union _duint32 {
	double d;
	uint32_t u1;
	uint32_t u2;
} duint32;


double UFD_getParamValue( void* buffer, int varid ) {
	uint32_t* buf = (uint32_t*) buffer;
	double value;

	if( sizeof(double) != sizeof(uint32_t) ) {
		peprintf( PEPSTR_WARN, NULL, "Possible variable size problem, sizeof(double) = %d, sizeof(uint32_t) = %d\n", sizeof(double), sizeof(uint32_t) );
	}

	memcpy( &value, buf+varid, sizeof(double) );

	return value;
}

void UFD_setParamValue( void* buffer, int varid, double value ) {
	uint32_t* buf = (uint32_t*) buffer;

	if( sizeof(double) != sizeof(uint32_t) ) {
		peprintf( PEPSTR_WARN, NULL, "Possible variable size problem, sizeof(double) = %d, sizeof(uint32_t) = %d\n", sizeof(double), sizeof(uint32_t) );
	}

	memcpy( buf+varid, &value, sizeof(double) );
}


void UFD_printBuffer( void* buffer, size_t nr_bytes ) {
	uint32_t* buf = (uint32_t*) buffer;
	int i;
	int nvar = nr_bytes / sizeof(double);
	duint32 du;
	double d;
	uint32_t *u1, *u2;

	u1 = &d;
	u2 = u1+1;

	peprintf( PEPSTR_INFO, NULL, "%d bytes, %d variables (sizeof(uint32_t) = %d)\n", nr_bytes, nvar, sizeof(uint32_t) );

	for( i = 0; i < nvar; i++ ) {
		du.u1 = buf[i*2];
		du.u2 = buf[i*2+1];

		*u1 = buf[i*2];
		*u2 = buf[i*2+1];

		peprintf( PEPSTR_INFO, NULL, "0x%08x (%f, %f)\t", (du.u2)|(du.u1<<32), du.d, d );
	}

	peprintf( PEPSTR_INFO, NULL, "\n" );

}


void UFD_decodeParams( void* buffer, size_t nr_bytes, double *params ) {
	uint32_t* buf = (uint32_t*) buffer;
	int i;
	int nvar = nr_bytes / sizeof(double);
	double d;
	uint32_t *u1, *u2;

	u1 = &d;
	u2 = u1+1;

	for( i = 0; i < nvar && i < MAX_PARAMS; i++ ) {
		*u1 = buf[i*2];
		*u2 = buf[i*2+1];

		params[i] = d;
	}

}


int UFD_encodeBuffer( void* buffer, double *params, int nparam ) {
	uint32_t* buf = (uint32_t*) buffer;
	int i;
	double d;
	uint32_t *u1, *u2;

	u1 = &d;
	u2 = u1+1;

	for( i = 0; i < MAX_PARAMS && i < nparam; i++ ) {
		d = params[i];

		buf[i*2] = *u1;
		buf[i*2+1] = *u2;
	}

	return 8*nparam;
}
