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

	for( i = 0; i < (nr_bytes>>2) ; i += 4 ) {
		peprintf( PEPSTR_INFO, NULL, "[%02d]: %08X %08X %08X %08X\n", i, buf[i], buf[i+1], buf[i+2], buf[i+3]);
	}
}
