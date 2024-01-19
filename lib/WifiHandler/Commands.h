#pragma once

#include <cstdint>

enum Commands : uint8_t
{
    TIMESYNC                = 1,
    DUMMY                   = 2,
    ACCELEROMETER_READING   = 3,
    GYROSCOPE_READING       = 4
};