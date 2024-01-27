#pragma once

#include <cstdint>

struct __attribute__((__packed__)) VectorPacket
{
    uint32_t time;
    float X;
    float Y;
    float Z;
};