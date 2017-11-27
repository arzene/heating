#include <I2CDevice.h>
#include <iostream>
#include <unistd.h>
#include <linux/i2c-dev.h>

using namespace std;

I2CDevice::I2CDevice(int busFileDescriptor, int address)
	: _busFileDescriptor(busFileDescriptor)
{
	if (ioctl(_busFileDescriptor, I2C_SLAVE, address) < 0)
	{
		cout << "I2CDevice::I2CDevice Failed to open the i2c bus" << endl;
	}
	else
		cout << "I2CDevice::I2CDevice bus opened successfull" << endl;
		
}
bool I2CDevice::Write(const uint8_t* data, uint16_t dataSize)
{
//	cout << "I2CDevice::Write data size: " << dataSize << " _busFileDescriptor: " << _busFileDescriptor << endl;
	return write(_busFileDescriptor, data, dataSize) == dataSize;
}

bool I2CDevice::Read(uint8_t* data, uint16_t dataSize)
{
	size_t bytesRead = 0;
	int errorCount = 0;
	while (bytesRead < dataSize && errorCount < 20)
	{
		int temp = read(_busFileDescriptor, data + bytesRead, dataSize - bytesRead); 
		
		if (temp > 0)
			bytesRead += temp; 
		else
		{
			cout << "I2CDevice::Read error: " << temp << endl;
			usleep(10000);
			errorCount++;
		}

	}
//	cout << "I2CDevice::Read read: " << bytesRead << " bytes" << endl;
	return true;
}
