#include "mecanumCar.h"

mecanumCar::mecanumCar() {
    const int pins[] = {FL_IN1, FL_IN2, FL_EN, FR_IN1, FR_IN2, FR_EN, 
                        RL_IN1, RL_IN2, RL_EN, RR_IN1, RR_IN2, RR_EN};
    for(int i=0; i<12; i++) pinMode(pins[i], OUTPUT);
}

void mecanumCar::move(RobotDirection dir, int speed, float correction) {
    switch(dir) {
        case FORWARD:   drive(speed, 0, correction);  break;
        case BACKWARD:  drive(-speed, 0, correction); break;
        case STRAFE_L:  drive(0, -speed, correction); break;
        case STRAFE_R:  drive(0, speed, correction);  break;
        case TURN_L:    drive(0, 0, -speed);          break;
        case TURN_R:    drive(0, 0, speed);           break;
        case RELEASE:   stop();                       break;
    }
}

void mecanumCar::drive(int vX, int vY, float vTH) {
    // Corrected wheel kinematics logic
    int fl = vX + vY + vTH; // Front Left
    int fr = vX - vY - vTH; // Front Right
    int rl = vX - vY + vTH; // Rear Left
    int rr = vX + vY - vTH; // Rear Right

    setMotor(FL_IN1, FL_IN2, FL_EN, fl);
    setMotor(FR_IN1, FR_IN2, FR_EN, fr);
    setMotor(RL_IN1, RL_IN2, RL_EN, rl);
    setMotor(RR_IN1, RR_IN2, RR_EN, rr);
}

void mecanumCar::setMotor(int in1, int in2, int en, int speed) {
    if (speed > 0) {
        digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
    } else if (speed < 0) {
        digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
    } else {
        digitalWrite(in1, LOW); digitalWrite(in2, LOW);
    }
    analogWrite(en, constrain(abs(speed), 0, 255));
}

void mecanumCar::stop() { drive(0, 0, 0); }