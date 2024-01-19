#include <cstdint>
#include <EEPROM.h>

struct Parameters
{
    uint8_t  version           = 1;
    char     wifi_ssid[16]     = "";
    char     wifi_password[16] = "";
    uint32_t server_ip         = 0x4600A8C0; // 192.168.0.70, little-endian
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