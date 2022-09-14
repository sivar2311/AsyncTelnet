#include "Telnet.h"

TelnetClass::TelnetClass()
    : _server(nullptr) {
}

TelnetClass::~TelnetClass() {
    if (_server) delete _server;
}

void TelnetClass::begin(int port) {
    if (_server) delete _server;
    _server = new AsyncServer(port);
    _server->onClient(std::bind(&TelnetClass::onConnect, this, std::placeholders::_1, std::placeholders::_2), nullptr);
    _server->begin();
}

size_t TelnetClass::write(uint8_t data) {
    for (auto client : _clients) {
        client->write((const char*) &data, 1);
    }
    return 1;
}

size_t TelnetClass::write(const char* data, size_t size) {
    for (auto client : _clients) {
        client->write(data, size);
    }
    return size;
}

void TelnetClass::onConnect(void* arg, AsyncClient* client) {
	_clients.push_back(client);
    client->onDisconnect(std::bind(&TelnetClass::onDisconnect, this, std::placeholders::_1, std::placeholders::_2));
    Serial.printf("[TelnetClass]: %d client(s) connected\r\n", _clients.size());
}

void TelnetClass::onDisconnect(void* arg, AsyncClient* client) {
    _clients.erase(std::remove(_clients.begin(), _clients.end(), client), _clients.end());
    Serial.printf("[TelnetClass]: %d client(s) connected\r\n", _clients.size());
}

TelnetClass Telnet;