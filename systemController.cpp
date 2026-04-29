#include "systemController.h"

systemController::systemController(mecanumCar& car, IMUSensor& imu)
  : _robot(car), _imu(imu), _currentState(IDLE) {}

void systemController::begin() {
  pinMode(START_BTN, INPUT_PULLUP);
  pinMode(STOP_BTN, INPUT_PULLUP);
  pinMode(RESET_BTN, INPUT_PULLUP);
  _imu.init(); //iniatialization of IMU
}

void systemController::handleButtons() {
  int pressedBtn = -1;
  //check which btn is pressed
  if (digitalRead(RESET_BTN) == LOW)      pressedBtn = RESET_BTN; 
  else if (digitalRead(STOP_BTN) == LOW)  pressedBtn = STOP_BTN;
  else if (digitalRead(START_BTN) == LOW) pressedBtn = START_BTN;

  // process the pressed button
  switch (pressedBtn) {
    case START_BTN:
    _currentState = RUNNING;
    break;

    case STOP_BTN :
      _currentState = STOPPED;
      _robot.stop();
      break;

    case RESET_BTN:
      _currentState = IDLE;
      _imu.init(); //re-run calibration and zero the yaw
      _robot.stop();
      break;

    default:
      //no button pressed
      break;
  }

  // debounce delay
  if(pressedBtn != -1) delay(200);
}

void systemController::executeState() {
  if (_currentState == RUNNING) {
    _imu.update();
    float yawVal = _imu.getYaw();
    float correction = yawVal * GYRO_KP;
    _robot.move(STRAFE_R, BASE_SPEED, correction);
  } else {
    _robot.stop();
  }
};

void systemController::update() {
  handleButtons();
  executeState();
};