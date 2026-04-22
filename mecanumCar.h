#pragma once

#include "constants.h"

class mecanumCar {
  public:
      mecanumCar();
      
      // vX: Forward/Backward, vY: Strafe, vTH: Rotation
      void drive(float vX, float vY, float vTH);
      void stop();

  private:
      // L298N specific motor control
      void setMotor(int ena, int in1, int in2, float power);
};