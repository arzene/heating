#pragma once

#include <I2CDevice.h>
#include <string>

class HTU21DF
{
public:
	HTU21DF(I2CDevice* i2cDevice);
	std::string GetTemperature();
private:
	I2CDevice* _i2cDevice;
	
private:
	void SleepMilliseconds(uint16_t ms);
//	Converter* _converter;
};
