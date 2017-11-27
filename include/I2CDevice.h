#pragma once

#include <sys/ioctl.h>
#include <cstdint>

class I2CDevice 
{
public:
	I2CDevice(int busFileDescriptor, int address);
	bool Write(const uint8_t* data, uint16_t dataSize);
	bool Read(uint8_t* data, uint16_t dataSize);
private:
	int _busFileDescriptor;
};
