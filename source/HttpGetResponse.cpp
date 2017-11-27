#include <HttpGetResponse.h>
#include <jsoncpp/json/json.h>
#include <sstream>

using namespace std;

JsonTemperatureResponse::JsonTemperatureResponse(HTU21DF* htu21df)
	: _htu21df(htu21df)
{}

std::string JsonTemperatureResponse::Get()
{
	Json::Value jsonResult;
	jsonResult["temperature"] = _htu21df->GetTemperature();
	stringstream ss;
	ss << jsonResult;
	return ss.str();
}
