#pragma once
#include "constants.h"

class mecanumCar {
  public:
    mecanumCar();

    // the "set already" function
    void move(RobotDirection dir, int speed, float correction = 0);

    // low-level vector control
    void drive(int vX, int vY, float vTH);
    void stop();

  private: 
    void setMotor(int in1, int in2, int en, int speed);
};