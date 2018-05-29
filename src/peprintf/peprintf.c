/*		Virtual Prototyping for Power Electronics
 *
 * 		File:				peprintf.c
 * 		Author(s): 			4 Aug 2014
 * 		Creation Date:		P L Evans
 *
 * 		Description:
 *		printf replacement that can redirect to various other functions
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

#include "peprintf.h"

static PEPDATA pepdata;

#define PEP_DEBUG

int peprintf( unsigned int strtype, void *optr, const char *str, ... ) {
	va_list args;
	char *finalstr = NULL;
	int i;

	if( pepdata.init != PEP_ISINIT ) pepinit();

	va_start( args, str );

	/* print to standard streams if required */
	if( (strtype & (PEPSTR_INFO|PEPSTR_WARN)) && pepdata.usestdout ) {
		vprintf( str, args );
	} else if( (strtype == PEPSTR_ERROR) && pepdata.usestderr ) {
		if( !(finalstr = malloc( PEPSTR_MAXSIZE * sizeof(char) )) ) {
			perror( "ERROR: peprintf could not allocate memory for formatted string\n" );
			return -1;
		}
		vsprintf( finalstr, str, args );

		i = strlen(finalstr)-1;
		while( (finalstr[i] == '\n' || finalstr[i] == '\r') && i > 0 ) finalstr[i--] = '\0';

		perror( finalstr );
	}

	/* Do any other required actions */
	if( !finalstr && !(finalstr = malloc( PEPSTR_MAXSIZE * sizeof(char) )) ) {
		perror( "ERROR: peprintf could not allocate memory for formatted string\n" );
		return -1;
	}
	vsprintf( finalstr, str, args );

	if( (strtype & PEPSTR_ERROR) ){
		i = strlen(finalstr)-1;

		while( (finalstr[i] == '\n' || finalstr[i] == '\r') && i > 0 ) finalstr[i--] = '\0';

#ifdef PEP_ADD_ERRNO
		strncat( finalstr, " (errno =  ", PEPSTR_MAXSIZE-strlen(finalstr)-1 );
		errorstr = strerror( errno );
		strcat( finalstr, errorstr );
		i = strlen(finalstr);
		finalstr[i] = ')';
#endif

		finalstr[i+1] = '\n';
		finalstr[i+2] = '\0';

		if( pepdata.file )	vfprintf( pepdata.file, finalstr, args );
		if( pepdata.callback ) pepdata.callback( finalstr, optr, strtype );
	} else if (strtype & (PEPSTR_INFO|PEPSTR_WARN) ) {
		if( pepdata.file )	vfprintf( pepdata.file, finalstr, args );

		if( pepdata.callback ) {
			pepdata.callback( finalstr, optr, strtype );
		}
	} else if( pepdata.callback ) {
		pepdata.callback( finalstr, optr, strtype );
	}

	va_end( args );

	if( finalstr ) free( finalstr );

#ifdef PEP_DEBUG
	fflush( stdout );
	fflush( stderr );
#endif

	return 0;
}

int pepinit() {
	pepdata.callback = NULL;
	pepdata.file = NULL;
	pepdata.init = PEP_ISINIT;
	pepdata.usestdout = pepdata.usestderr = 1;
	return 0;
}

int pepupdatefile( const char *file ) {
	if( pepdata.file ) fclose( pepdata.file );
	if( file && !(pepdata.file = fopen( file, "a" )) ) {
		perror( "ERROR: pepupdatefile could not open logfile\n" );
		return -1;
	} else pepdata.file = NULL;
	return 0;
}

int pepupdatecallback( PEPCALLBACK callback ) {
	pepdata.callback = callback;
	return 0;
}

int pepusestdout( int use ) {
	pepdata.usestdout = use;
	return 0;
}

int pepusestderr( int use ) {
	pepdata.usestderr = use;
	return 0;
}



