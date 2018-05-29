/*		Virtual Prototyping for Power Electronics
 *
 * 		File:				peprintf.h
 * 		Author(s): 			4 Aug 2014
 * 		Creation Date:		P L Evans
 *
 * 		Description:
 *		printf replacement that can redirect to various other functions
 *
 */
#ifndef PEPRINTF_H_
#define PEPRINTF_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

/* String types that will be procesed as per printf */
#define PEPSTR_INFO			0x0001
#define PEPSTR_WARN			0x0002
#define PEPSTR_ERROR		0x0004
#define PEPSTR_HILI			0x0008
/* Other payloads that use peprint to pass data to linked callback */
#define	PEPSTR_DATA0		0x0010
#define	PEPSTR_DATA1		0x0020
#define	PEPSTR_DATA2		0x0040
#define	PEPSTR_DATA3		0x0080
#define	PEPSTR_DATA4		0x0100
#define	PEPSTR_DATA5		0x0200

#define PEPERR_OK		0
#define PEPERR_FIO		1

#define PEP_ISINIT 0xDEADBEEF

#define PEPSTR_MAXSIZE 1024

typedef void (*PEPCALLBACK) ( const char *str, void*, unsigned int );

typedef struct _PEPDATA {
	PEPCALLBACK callback;
	FILE *file;
	unsigned int init;
	int usestdout, usestderr;
} PEPDATA;

int peprintf( unsigned int strtype, void *optr, const char *str, ... );

int pepinit();

int pepupdatefile( const char *file );

int pepupdatecallback( PEPCALLBACK callback );

int pepusestdout( int use );
int pepusestderr( int use );

#endif /* PEPRINTF_H_ */
