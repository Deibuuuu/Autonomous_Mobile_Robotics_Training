#pragma once
#include <Arduino.h>
#include "mecanumCar.h"
#include "IMUSensor.h"

class systemController {
public:
  systemController(mecanumCar& car, IMUSensor& imu);
  void begin();
  void update();

private:
  void handleButtons();
  void executeState();
  void sendTelemetry();

  mecanumCar& _robot;
  IMUSensor& _imu;
  SystemState _currentState;
};