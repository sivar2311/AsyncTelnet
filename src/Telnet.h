#include <Arduino.h>
#include <AsyncTCP.h>
#include <Print.h>

#include <vector>

class TelnetClass : public Print {
  public:
    TelnetClass();
    ~TelnetClass();
    void begin(int port = 23);

    virtual size_t write(uint8_t data) override;
    virtual size_t write(const uint8_t* buffer, size_t size) override;

  protected:
    void onConnect(void* arg, AsyncClient* client);
    void onDisconnect(void* arg, AsyncClient* client);

  protected:
    AsyncServer*              _server;
    std::vector<AsyncClient*> _clients;
};

extern TelnetClass Telnet;
