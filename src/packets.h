/*
 * packets.h
 *
 *  Created on: 13 Jun 2018
 *      Author: ezzpe
 */

#ifndef SRC_PACKETS_H_
#define SRC_PACKETS_H_

/** Notes:
 *
 *
 * struct msghdr {
 * 	struct sockaddr_in* 	msg_name;								// connection data
 * 	int						msg_namelen 	= sizeof(msg_name);		// sizeof connection data
 * 	struct iovec* 			msg_iov;								// array of payload data structures (iovecs)
 * 	int						msg_iovlen;								// number of structures in msg_iov array
 * 	}
 *
 * 	struct iovec {
 * 		void* 				iov_base		= nrtdata (rt buffer);	// raw data (packet payload)
 * 		int					iov_len;								// number of bytes in payload
 * 	}
 *
 * 	structure of iov_base:
 * 		uint32_t 			iov_base[n_bytes_recvd];			// n_bytes_recvd should match total bytes in rt buffer (i.e. num vars * 4 if each variable is a 32bit value)
 * 																// just read off each byte and convert to parameters
 *
 */


double UFD_getParamValue( void* buffer, int varid );
void UFD_setParamValue( void* buffer, int varid, double value );
void UFD_printBuffer( void* buffer, size_t nr_bytes );

#endif /* SRC_PACKETS_H_ */
