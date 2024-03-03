#include <cstdint>
#include <EEPROM.h>

struct Parameters
{
    uint8_t  version                 = 1;
    uint8_t  node_id                 = 0;
    char     wifi_ssid[16]           = "meilnav";
    char     wifi_password[16]       = ""; // 4 ITLIMS rooms...
    uint32_t multicast_group_address = 0x640000E0; // 224.0.0.100, little-endian
    uint16_t udp_listener            = 50000;
    uint16_t server_port             = 1234;
    uint8_t  multicast_ttl           = 3;
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