/*
 Enc28J60NetworkClass.h
 UIPEthernet network driver for Microchip ENC28J60 Ethernet Interface.

 Copyright (c) 2013 Norbert Truchsess <norbert.truchsess@t-online.de>
 All rights reserved.

 inspired by enc28j60.c file from the AVRlib library by Pascal Stang.
 For AVRlib See http://www.procyonengineering.com/

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef Enc28J60Network_H_
#define Enc28J60Network_H_

#include "mempool.h"

#define UIP_RECEIVEBUFFERHANDLE 0xff

#define UIP_SENDBUFFER_PADDING 7
#define UIP_SENDBUFFER_OFFSET 1

#define TX_COLLISION_RETRY_COUNT 3

//#define ENC28J60DEBUG

/*
 * Empfangen von ip-header, arp etc...
 * wenn tcp/udp -> tcp/udp-callback -> assign new packet to connection
 */

class Enc28J60Network : public MemoryPool
{

private:
  static uint8_t csPin;
  static uint8_t mosiPin;
  static uint8_t misoPin;
  static uint8_t sckPin;
  static bool spiInitialized;

  static uint16_t nextPacketPtr;
  static uint8_t bank;

  static struct memblock receivePkt;

  static uint8_t readOp(uint8_t op, uint8_t address);
  static void writeOp(uint8_t op, uint8_t address, uint8_t data);
  static uint16_t setReadPtr(memhandle handle, memaddress position, uint16_t len);
  static void setERXRDPT();
  static void readBuffer(uint16_t len, uint8_t* data);
  static void writeBuffer(uint16_t len, uint8_t* data);
  static uint8_t readByte(uint16_t addr);
  static void writeByte(uint16_t addr, uint8_t data);
  static void setBank(uint8_t address);
  static uint8_t readReg(uint8_t address);
  static void writeReg(uint8_t address, uint8_t data);
  static void writeRegPair(uint8_t address, uint16_t data);
  static void phyWrite(uint8_t address, uint16_t data);
  static uint16_t phyRead(uint8_t address);
  static void clkout(uint8_t clk);

  friend void enc28J60_mempool_block_move_callback(memaddress,memaddress,memaddress);

public:

  static uint8_t getrev(void);
  static void powerOn();
  static void powerOff();
  static bool linkStatus();

  static void setSpiPins(uint8_t _mosi, uint8_t _miso, uint8_t _sck, uint8_t _cs) {csPin = _cs; mosiPin = _mosi; misoPin = _miso; sckPin = _sck;}
  static void setSpiPins(uint8_t _mosi, uint8_t _miso, uint8_t _sck) {mosiPin = _mosi; misoPin = _miso; sckPin = _sck;}
  static void setSpiPins(uint8_t _cs) {csPin = _cs;}
  static void initSPI();
  static bool init(uint8_t* macaddr);
  static memhandle receivePacket();
  static void freePacket();
  static memaddress blockSize(memhandle handle);
  static bool sendPacket(memhandle handle);
  static uint16_t readPacket(memhandle handle, memaddress position, uint8_t* buffer, uint16_t len);
  static uint16_t writePacket(memhandle handle, memaddress position, uint8_t* buffer, uint16_t len);
  static void copyPacket(memhandle dest, memaddress dest_pos, memhandle src, memaddress src_pos, uint16_t len);
  static uint16_t chksum(uint16_t sum, memhandle handle, memaddress pos, uint16_t len);
};

#endif /* Enc28J60NetworkClass_H_ */
