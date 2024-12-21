#define CROW_STATIC_DIRECTORY "../"
#define CROW_STATIC_ENDPOINT "/<path>"
#include <iostream>
using namespace std;
#include "crow_all.h"
#include "PoDefinition.h"
#include "PoUtilities.h"
#include "PoMath.h"

void Root(crow::request &req, crow::response &res)
{
    res.code = 302;
    res.set_header("Location", "index.html");
    res.end();
    return;
}

void HelloWorld(crow::request& req, crow::response& res)
{
	res.set_header("Content-Type", "text/plain");
	res.write("Hello, World!\n");
	res.end();
	return;
}

void Root_api_authenticate(crow::request& req, crow::response& res)
{
    std::string credentialsencoded = req.url_params.get("credentials");
    std::string credentialsdecoded = crow::utility::base64decode(credentialsencoded, credentialsencoded.size());
    size_t index = credentialsdecoded.find(':');
    std::string phone = credentialsdecoded.substr(0, index);
    std::string password = credentialsdecoded.substr(index + 1);

	res.set_header("Access-Control-Allow-Origin", "*");
	res.set_header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
	res.set_header("Content-Type", "application/octet-stream");
	struct ResponseData
	{
		uint32 state;
		char name[60];
	}responsedata;
	ZeroMemory(&responsedata, sizeof(ResponseData));

	if (phone == "9920466103" && password == "224466")
	{
		responsedata.state = 1;
		strcpy_s(responsedata.name, sizeof(responsedata.name), "Abhimanyu Singh");
	}
	else
	{
		responsedata.state = 0;
	}
	std::string responsestring(reinterpret_cast<char*>(&responsedata), sizeof(responsedata));
	res.write(responsestring);
	res.end();
	return;
}

int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")(Root);

	CROW_ROUTE(app, "/helloworld")(HelloWorld);

    CROW_ROUTE(app, "/api/authenticate")(Root_api_authenticate);

    app.port(80).multithreaded().run();
}