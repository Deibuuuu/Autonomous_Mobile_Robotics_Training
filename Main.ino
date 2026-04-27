#include "mecanumCar.h"
#include "IMUSensor.h" // Ensure this line exists!

mecanumCar robot;
IMUSensor imu; 

void setup() {
    Serial.begin(115200);
    imu.init();
}

void loop() {
    imu.update();
    float yawVal = imu.getYaw();
    float correction = yawVal * GYRO_KP;

    // Fixed spelling and underscores
    robot.move(STRAFE_R, BASE_SPEED, correction);

    delay(10);
}