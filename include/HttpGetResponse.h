#pragma once
#include <string>
#include <HTU21DF.h>

class JsonTemperatureResponse
{
public:
	JsonTemperatureResponse(HTU21DF* htu21df);
	std::string Get();
private:
	HTU21DF* _htu21df;
};