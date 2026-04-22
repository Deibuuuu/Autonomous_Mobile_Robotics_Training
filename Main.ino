#include "mecanumCar.h"

mecanumCar robot;

void setup() {
  Serial.begin(115200);
  Serial.println("phase 1: straight drive test");
  delay(3000);
}

void loop() {
  Serial.println("moving forward...");
  robot.drive(TEST_SPEED, 0, 0);
  

  delay(2000);

  Serial.println("Stopping");
  robot.stop();

  while(true);
}
