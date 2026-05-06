#pragma once
#include <Arduino.h>
#include "mecanumCar.h"
#include "IMUSensor.h"

/* // --- Phase 2: Environment Perception & Pathfinding Includes ---
#include <SD.h>
#include <SPI.h>
#include <Wire.h>
#include <SparkFun_VL53L1X.h>
#include "AStar.h"
*/

class systemController {
public:
  systemController(mecanumCar& car, IMUSensor& imu);
  void begin();
  void update();

private:
  void handleButtons();
  void executeState();
  void sendTelemetry();
  void executeTurn(float targetAngleChange);

  /* // --- Phase 2: Methods ---
  void performScan();
  void logDataToSD(int distFront, int distLeft, int distRight);
  void calculatePath();
  void followPath();
  void updateOdometry();
  */

  mecanumCar& _robot;
  IMUSensor& _imu;
  SystemState _currentState;
  
  unsigned long _lastMoveTime;
  int _moveState;
  int _lastPrintedState;

  bool _lastStartBtn;
  bool _lastStopBtn;
  bool _lastResetBtn;

  /* // --- Phase 2: Variables ---
  SFEVL53L1X _distanceFront;
  SFEVL53L1X _distanceLeft;
  SFEVL53L1X _distanceRight;
  File _logFile;
  
  unsigned long _lastScanTime;

  AStar _pathfinder;
  Coordinate _currentPath[MAX_PATH_LENGTH];
  int _pathLength;
  int _currentWaypointIdx;

  int _robotX; // Dead reckoning X
  int _robotY; // Dead reckoning Y
  unsigned long _lastWaypointTime;
  */
};