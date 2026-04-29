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
    robot.move(FORWARD, BASE_SPEED, correction);
    delay(1000);

    robot.move(BACKWARD, BASE_SPEED, correction); //FORWARD, BACKWARD, STRAFE_L, STRAFE_R, TURN_L, TURN_R, RELEASE (stop)
    delay(1000);

    robot.move(STRAFE_L, BASE_SPEED, correction);
    delay(1000);

    robot.move(STRAFE_R, BASE_SPEED, correction);
    delay(1000);

    robot.move(TURN_L, BASE_SPEED, correction);
    delay(1000);

    robot.move(TURN_R, BASE_SPEED, correction);
    delay(1000);

    robot.move(RELEASE, BASE_SPEED, correction);
    delay(1000);
}