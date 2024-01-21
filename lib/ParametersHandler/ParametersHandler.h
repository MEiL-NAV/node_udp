#include <cstdint>
#include <EEPROM.h>

struct Parameters
{
    uint8_t  version           = 3;
    uint8_t  node_id           = 0;
    char     wifi_ssid[16]     = "";
    char     wifi_password[16] = "";
    uint16_t udp_listener      = 50000;
    uint32_t server_ip         = 0x8000A8C0; // 192.168.0.128, little-endian
    uint16_t server_port       = 1234;
};

class ParametersHandler
{
public:
    Parameters parameters;

    ~ParametersHandler();

    void init();
    void save();

private:
    EEPROMClass eeprom;
    void restore_defaults();
};