/*
 * NetworkXBee.h
 *                      The BSD License
 *
 *           Copyright (c) 2015, tomoaki@tomy-tech.com
 *                    All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef NETWORLXBEE_H_
#define NETWORLXBEE_H_

#ifdef ARDUINO
    #include <MqttsnClientApp.h>
 	#include <Timer.h>
#else
    #include "MqttsnClientApp.h"
	#include "Timer.h"
    #include <sys/time.h>
    #include <iostream>
#endif

#ifdef NETWORK_XBEE

using namespace std;

#if defined(ARDUINO)
    #if ARDUINO >= 100
        #include "Arduino.h"
        #include <inttypes.h>
    #else
        #if ARDUINO < 100
            #include "WProgram.h"
            #include <inttypes.h>
        #endif
    #endif

	#define XB_CTS_PIN   3   // XBee CTS
	#define XB_RTS_PIN   3   // XBee RTS
	#define XB_SLEEP_PIN 4   // XBee Pinhybernate
#endif


#define START_BYTE 0x7e
#define ESCAPE     0x7d
#define XON        0x11
#define XOFF       0x13


#define XB_API_REQUEST               0x10
#define XB_API_RESPONSE              0x90
#define XB_API_MODEMSTATUS           0x8A
#define XB_API_XMITSTATUS            0x8B

#define XB_PACKET_ACKNOWLEGED        0x01
#define XB_BROADCAST_PACKET          0x02
#define XB_BROADCAST_RADIUS_MAX_HOPS 0

#define PACKET_TIMEOUT_CHECK         1000   // 1 sec

/*====  STATUS ======
#define NO_ERROR               0
#define CHECKSUM_ERROR         1
#define PACKET_OVERFLOW        2
#define UNEXPECTED_START_BYTE  3
*/
namespace tomyAsyncClient {

/*===========================================
                Serial Port
 ============================================*/

#ifdef ARDUINO
#include <Stream.h>
class SerialPort{
public:
    SerialPort( );
    int  open(NETWORK_CONFIG config);
    bool send(unsigned char b);
    bool recv(unsigned char* b);
    bool checkRecvBuf(void);
    void flush(void);
	void rtsOn(void);
	void rtsOff(void);
private:
    Stream* _serialDev;
};
#endif /* ARDUINO */

#ifdef LINUX
/*-------------------------
    For Linux
 --------------------------*/
#include <termios.h>
class SerialPort{
public:
    SerialPort();
    ~SerialPort();
    int  open(NETWORK_CONFIG  config);
    bool send(unsigned char b);
    bool recv(unsigned char* b);
    bool checkRecvBuf();
    void flush();
	void rtsOn(void);
	void rtsOff(void);
private:
    int _fd;  // file descriptor
    struct termios _tio;
};
#endif /* LINUX */


/*===========================================
               Class  Network
 ============================================*/
class Network {
public:
    Network();
    ~Network();

    int      broadcast(const uint8_t* payload, uint16_t payloadLen);
    int      unicast(const uint8_t* payload, uint16_t payloadLen);
    void     setGwAddress();
    void     resetGwAddress(void);
    int      initialize(NETWORK_CONFIG  config);
    uint8_t* getMessage(int* len);

private:
    void setSleep();
	void setSerialPort(SerialPort *serialPort);
    uint8_t send(const uint8_t* payload, uint8_t payloadLen, uint8_t type);
	uint8_t readApiFrame(uint16_t timeoutMillsec);
    uint8_t readApiFrame(void);
    void sendByte(uint8_t);
    int  recvByte(uint8_t*);

    uint8_t     _responseData[MQTTSN_MAX_PACKET_SIZE + 1];
    uint8_t     _packetLen;
    Timer       _tm;

    SerialPort* _serialPort;
    uint8_t     _gwAddr64[8];
    uint8_t     _gwAddr16[2];

    uint8_t     _byteData;
    uint8_t     _checksum;

    int  _returnCode;
    bool _sleepflg;
    uint8_t _frameId;
};

}
#endif  /* NETWORK_XBEE */
#endif  /* NETWORLXBEE_H_ */
