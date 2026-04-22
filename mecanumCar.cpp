#include "mecanumCar.h"

mecanumCar::mecanumCar() {
    // Front Left
    pinMode(FL_ENA, OUTPUT); pinMode(FL_IN1, OUTPUT); pinMode(FL_IN2, OUTPUT);
    // Front Right
    pinMode(FR_ENB, OUTPUT); pinMode(FR_IN3, OUTPUT); pinMode(FR_IN4, OUTPUT);
    // Back Left
    pinMode(BL_ENA, OUTPUT); pinMode(BL_IN1, OUTPUT); pinMode(BL_IN2, OUTPUT);
    // Back Right
    pinMode(BR_ENB, OUTPUT); pinMode(BR_IN3, OUTPUT); pinMode(BR_IN4, OUTPUT);
}

  void mecanumCar::drive(float vX, float vY, float vTH) {
      // Mecanum Kinematics
      float fl = vX - vY - vTH;
      float fr = vX + vY + vTH;
      float bl = vX + vY - vTH;
      float br = vX - vY + vTH;

      // Normalization
      float maxVal = max(abs(fl), max(abs(fr), max(abs(bl), abs(br))));
      if (maxVal > 1.0) {
          fl /= maxVal; fr /= maxVal; bl /= maxVal; br /= maxVal;
      }

      setMotor(FL_ENA, FL_IN1, FL_IN2, fl);
      setMotor(FR_ENB, FR_IN3, FR_IN4, fr);
      setMotor(BL_ENA, BL_IN1, BL_IN2, bl);
      setMotor(BR_ENB, BR_IN3, BR_IN4, br);
  }

  void mecanumCar::setMotor(int ena, int in1, int in2, float power) {
      if (power > 0) { // Forward
          digitalWrite(in1, HIGH);
          digitalWrite(in2, LOW);
      } else if (power < 0) { // Backward
          digitalWrite(in1, LOW);
          digitalWrite(in2, HIGH);
      } else { // Stop
          digitalWrite(in1, LOW);
          digitalWrite(in2, LOW);
      }
      analogWrite(ena, (int)(abs(power) * 255));
  }

  void mecanumCar::stop() {
      drive(0, 0, 0);
  }