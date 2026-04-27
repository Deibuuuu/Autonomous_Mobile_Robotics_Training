#include "IMUSensor.h"

IMUSensor::IMUSensor() : yaw(0), lastTime(0), gyroZ_offset(0) {}

void IMUSensor::init() {
    Wire.begin();
    
    // Wake up MPU6050
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(PWR_MGMT_1);
    Wire.write(0x00);
    Wire.endTransmission(true);
    delay(100);

    // Calibrate: Average 500 readings to find the rest-state noise
    long sumZ = 0;
    for (int i = 0; i < 500; i++) {
        readRawGyro();
        sumZ += gyroZ;
        delay(3);
    }
    gyroZ_offset = sumZ / 500.0;
    lastTime = millis();
}

void IMUSensor::readRawGyro() {
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(GYRO_Z_OUT);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 2, true);
    gyroZ = (Wire.read() << 8) | Wire.read();
}

void IMUSensor::update() {
    readRawGyro();
    unsigned long now = millis();
    float dt = (now - lastTime) / 1000.0;
    lastTime = now;

    // Logic: Integrate change in rotation over time
    // 131.0 is the default sensitivity for +/- 250 deg/s
    yaw += ((gyroZ - gyroZ_offset) / 131.0) * dt;
}

float IMUSensor::getYaw() { return yaw; }