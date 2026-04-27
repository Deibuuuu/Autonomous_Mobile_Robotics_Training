#pragma once
#include <Wire.h>
#include "Constants.h"

class IMUSensor {
public:
    IMUSensor();
    void init();
    void update();
    float getYaw();

private:
    void readRawGyro();
    int16_t gyroZ;
    float gyroZ_offset;
    float yaw;
    unsigned long lastTime;
};