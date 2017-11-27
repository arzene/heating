#include <HTU21DF.h>
#include <unistd.h>
#include <cstdint>
#include <iostream>
#include <sstream>

using namespace std;

HTU21DF::HTU21DF(I2CDevice* i2cDevice/*, Converter* converter*/)
	: _i2cDevice(i2cDevice)
{
	uint8_t registryAddress = 0xFE;
	_i2cDevice->Write(&registryAddress, sizeof(registryAddress));
	SleepMilliseconds(15);
	registryAddress = 0xE7;
	
	_i2cDevice->Write(&registryAddress, sizeof(registryAddress));
	uint8_t buffer[1];
	_i2cDevice->Read(buffer, 1);
	
	if (buffer[0] != 0x02)
		cout << "HTU21DF::HTU21DF reset failed" << endl;

	SleepMilliseconds(500);
}

string HTU21DF::GetTemperature()
{
//	cout << "GetTemperature() WRITE" << endl;
	return "Temperature!";
	const uint8_t registryAddress = 0xE3;
	if (_i2cDevice->Write(&registryAddress, sizeof(registryAddress)))
	{
		SleepMilliseconds(50);
		uint8_t buffer[3];
		_i2cDevice->Read(buffer, 3);
		float temp = (((buffer[0] << 8) + buffer[1]) * 175.2 /65536) - 46.85 ;
		stringstream ss;
		ss << temp;
		return ss.str();
	}
	
	return "none";
}

void HTU21DF::SleepMilliseconds(uint16_t ms)
{
	usleep(ms * 1000);
}