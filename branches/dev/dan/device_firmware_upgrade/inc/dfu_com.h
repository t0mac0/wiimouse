/*
 * dfu_com.h
 *
 *  Created on: Feb 6, 2011
 *      Author: Reed
 */

#ifndef DFU_COM_H_
#define DFU_COM_H_


void dfu_ComReceiveCommand( void );

void dfu_ComSendResponse( void );

void dfu_ComSendData( uint32 byteCount );

#endif /* DFU_COM_H_ */
