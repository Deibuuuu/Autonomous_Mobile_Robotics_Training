#include "mecanumCar.h"
#include "IMUSensor.h"
#include "systemController.h"

mecanumCar robot;
IMUSensor imu; 
systemController controller(robot, imu);

void setup() {
    Serial.begin(115200);
    controller.begin();
}

void loop() {
    controller.update();
}