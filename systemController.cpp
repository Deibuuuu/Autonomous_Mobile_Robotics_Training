#include "systemController.h"

systemController::systemController(mecanumCar& car, IMUSensor& imu)
  : _robot(car), _imu(imu), _currentState(IDLE), _lastMoveTime(0), _moveState(0), _lastPrintedState(-1),
    _lastStartBtn(HIGH), _lastStopBtn(HIGH), _lastResetBtn(HIGH) /*, _lastScanTime(0), _pathLength(0), _currentWaypointIdx(0), _robotX(0), _robotY(0), _lastWaypointTime(0)*/ {}

void systemController::begin() {
  pinMode(START_BTN, INPUT_PULLUP);
  pinMode(STOP_BTN, INPUT_PULLUP);
  pinMode(RESET_BTN, INPUT_PULLUP);
  
  _lastStartBtn = digitalRead(START_BTN);
  _lastStopBtn = digitalRead(STOP_BTN);
  _lastResetBtn = digitalRead(RESET_BTN);

  _imu.init(); //iniatialization of IMU

  /* // --- Phase 2: Hardware Setup ---
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println(F("SD Card initialization failed!"));
  } else {
    Serial.println(F("SD Card initialized."));
    _logFile = SD.open("scan.csv", FILE_WRITE);
    if (_logFile) {
        _logFile.println("Front_mm,Left_mm,Right_mm");
        _logFile.close();
    }
    // Load pre-existing map if available
    if (_pathfinder.loadMapFromSD("map.txt")) {
        Serial.println(F("A* map loaded from SD."));
    } else {
        Serial.println(F("No map.txt found on SD. Using empty grid."));
    }
  }

  Wire.begin();
  
  pinMode(XSHUT_FRONT, OUTPUT);
  pinMode(XSHUT_LEFT, OUTPUT);
  pinMode(XSHUT_RIGHT, OUTPUT);
  
  // Reset all sensors
  digitalWrite(XSHUT_FRONT, LOW);
  digitalWrite(XSHUT_LEFT, LOW);
  digitalWrite(XSHUT_RIGHT, LOW);
  delay(10);
  
  // Initialize Front
  digitalWrite(XSHUT_FRONT, HIGH);
  delay(10);
  _distanceFront.begin();
  _distanceFront.setI2CAddress(0x30); // 7-bit address 0x30
  _distanceFront.setDistanceModeShort();
  
  // Initialize Left
  digitalWrite(XSHUT_LEFT, HIGH);
  delay(10);
  _distanceLeft.begin();
  _distanceLeft.setI2CAddress(0x32); // 7-bit address 0x32
  _distanceLeft.setDistanceModeShort();
  
  // Initialize Right
  digitalWrite(XSHUT_RIGHT, HIGH);
  delay(10);
  _distanceRight.begin();
  _distanceRight.setI2CAddress(0x34); // 7-bit address 0x34
  _distanceRight.setDistanceModeShort();
  */
}

void systemController::handleButtons() {
  bool currentStop = digitalRead(STOP_BTN);
  bool currentStart = digitalRead(START_BTN);
  bool currentReset = digitalRead(RESET_BTN);

  // 1. Check STOP button press (Falling edge: HIGH to LOW)
  if (currentStop == LOW && _lastStopBtn == HIGH) {
    if (_currentState != STOPPED) {
        Serial.println(F("\n[!] STOP BUTTON PRESSED - ENTERING E-STOP LATCH [!]"));
    }
    _currentState = STOPPED;
  }

  // 2. Check RESET button press (Falling edge)
  if (currentReset == LOW && _lastResetBtn == HIGH) {
    if (_currentState != IDLE) {
        Serial.println(F("\n[*] RESET BUTTON PRESSED - STATE RETURNED TO IDLE [*]"));
    }
    _currentState = IDLE;
    _imu.init(); 
    _robot.stop();
  } 

  // 3. Check START button press (Falling edge)
  if (currentStart == LOW && _lastStartBtn == HIGH) {
    // Only allow start if we are in IDLE state
    if (_currentState == IDLE) {
        Serial.println(F("\n[>] START BUTTON PRESSED - SYSTEM RUNNING [>]"));
        _currentState = RUNNING;
    }
  }

  _lastStopBtn = currentStop;
  _lastStartBtn = currentStart;
  _lastResetBtn = currentReset;

  // Enforce hardware stop immediately if in STOPPED state
  if (_currentState == STOPPED) {
      _robot.stop();
  }
}

void systemController::executeState() {
  if (_currentState == RUNNING) {
    _imu.update();
    float yawVal = _imu.getYaw();
    
    // Phase 1: PID-Style Correction
    // This calculates a proportional correction based on how far the yaw has drifted
    float correction = yawVal * GYRO_KP;

    unsigned long currentMillis = millis();
    // Change movement state every 2 seconds
    if (currentMillis - _lastMoveTime > 2000) {
        _lastMoveTime = currentMillis;
        _moveState++;
        if (_moveState > 3) { // 4 states for testing (0, 1, 2, 3)
            _moveState = 0;
        }

        /* // Exact Turn Tests (Commented out for now)
        // Execute block turns when entering the state
        if (_moveState == 1) {
            Serial.println(F("\nTesting: EXACT TURN LEFT 90"));
            executeTurn(85.0); // 85 deg to account for motor momentum/overshoot
            _lastMoveTime = millis(); // Reset timer so we pause for 2s after turn
        } else if (_moveState == 3) {
            Serial.println(F("\nTesting: EXACT TURN RIGHT 90"));
            executeTurn(-85.0); // -85 deg for right turn
            _lastMoveTime = millis();
        }
        */
    }
    
    if (_lastPrintedState != _moveState) {
        switch (_moveState) {
            case 0: Serial.println(F("Testing: FORWARD")); break;
            case 1: Serial.println(F("Testing: RELEASE (Pause)")); break;
            // case 2: Serial.println(F("Testing: BACKWARD")); break;
            // case 3: Serial.println(F("Testing: RELEASE (Pause)")); break;
            
            /* // --- Other Movements ---
            case 4: Serial.println(F("Testing: STRAFE LEFT")); break;
            case 5: Serial.println(F("Testing: STRAFE RIGHT")); break;
            case 6: Serial.println(F("Testing: TURN LEFT (Continuous)")); break;
            case 7: Serial.println(F("Testing: TURN RIGHT (Continuous)")); break;
            */
        }
        _lastPrintedState = _moveState;
    }

    switch (_moveState) {
        // ACTIVE TEST: Forward & Backward
        case 0: _robot.move(FORWARD, BASE_SPEED, correction); break;
        case 1: _robot.move(RELEASE, 0, 0); break;
        // case 2: _robot.move(BACKWARD, BASE_SPEED, correction); break;
        // case 3: _robot.move(RELEASE, 0, 0); break;
        
        /* // --- All Other Movements (Commented out) ---
        // To test these, change the "if (_moveState > 3)" above to "if (_moveState > 7)"
        // And remove the RELEASE states if you want continuous transitions
        case 4: _robot.move(STRAFE_L, BASE_SPEED, correction); break;
        case 5: _robot.move(STRAFE_R, BASE_SPEED, correction); break;
        case 6: _robot.move(TURN_L, BASE_SPEED, 0); break;
        case 7: _robot.move(TURN_R, BASE_SPEED, 0); break;
        */
    }

    /* // --- Phase 2: Environment Perception ---
    performScan();
    */
  } else /* if (_currentState == EVADE) {
    _robot.stop();
    if (_lastPrintedState != -2) {
        Serial.println(F("\n[!] OBSTACLE DETECTED - EVADING [!]"));
        _lastPrintedState = -2;
    }
  } else */ {
    _robot.stop();
    _lastPrintedState = -1; // Reset printed state when not running
  }

  sendTelemetry();
};

void systemController::sendTelemetry() {
  static unsigned long lastMsg = 0;
  if (millis() - lastMsg > 250) {
    Serial.print(F("Yaw: ")); Serial.print(_imu.getYaw());
    Serial.print(F(" | State: ")); Serial.println(_currentState);
    lastMsg = millis();
  }
}

void systemController::executeTurn(float targetAngleChange) {
    _robot.stop();
    delay(200); // Pause before turning
    
    _imu.update();
    float startYaw = _imu.getYaw();
    float targetYaw = startYaw + targetAngleChange;
    
    int turnSpeed = 150; // Slower speed for turn accuracy
    RobotDirection dir = (targetAngleChange > 0) ? TURN_L : TURN_R;
    
    _robot.move(dir, turnSpeed, 0);
    
    while(true) {
        _imu.update();
        float currentYaw = _imu.getYaw();
        
        if (targetAngleChange > 0) { // Turning Left
            if (currentYaw >= targetYaw) break;
        } else { // Turning Right
            if (currentYaw <= targetYaw) break;
        }
        delay(5);
    }
    
    _robot.stop();
    delay(200); // Pause after turning
}

void systemController::update() {
  handleButtons();
  executeState();
}

/* // --- Phase 2: Environment Perception & Pathfinding Methods ---
void systemController::performScan() {
  unsigned long currentMillis = millis();
  
  if (currentMillis - _lastScanTime >= 50) { // Scan every 50ms
    _lastScanTime = currentMillis;
    
    _distanceFront.startRanging();
    _distanceLeft.startRanging();
    _distanceRight.startRanging();

    // Wait for data
    while (!_distanceFront.checkForDataReady() || 
           !_distanceLeft.checkForDataReady() || 
           !_distanceRight.checkForDataReady()) {
      delay(1); 
    }
    
    int dFront = _distanceFront.getDistance();
    int dLeft = _distanceLeft.getDistance();
    int dRight = _distanceRight.getDistance();
    
    _distanceFront.clearInterrupt();
    _distanceFront.stopRanging();
    _distanceLeft.clearInterrupt();
    _distanceLeft.stopRanging();
    _distanceRight.clearInterrupt();
    _distanceRight.stopRanging();

    // Check for obstacle
    if ((dFront > 0 && dFront < OBSTACLE_THRESHOLD) ||
        (dLeft > 0 && dLeft < OBSTACLE_THRESHOLD) ||
        (dRight > 0 && dRight < OBSTACLE_THRESHOLD)) {
      _currentState = EVADE; // Or STOPPED
    }

    // Log data
    logDataToSD(dFront, dLeft, dRight);
  }
}

void systemController::logDataToSD(int distFront, int distLeft, int distRight) {
  _logFile = SD.open("scan.csv", FILE_WRITE);
  if (_logFile) {
    _logFile.print(distFront);
    _logFile.print(",");
    _logFile.print(distLeft);
    _logFile.print(",");
    _logFile.println(distRight);
    _logFile.close();
  }
}

void systemController::calculatePath() {
    // Example: Path from current pos to (10,10)
    int goalX = 10;
    int goalY = 10;
    
    Serial.println(F("Calculating A* Path..."));
    _pathLength = _pathfinder.findPath(_robotX, _robotY, goalX, goalY, _currentPath);
    
    if (_pathLength > 0) {
        Serial.print(F("Path found! Length: "));
        Serial.println(_pathLength);
        _currentWaypointIdx = 0;
        // _currentState = NAVIGATING;
    } else {
        Serial.println(F("No path found!"));
        _currentState = STOPPED;
    }
}

void systemController::updateOdometry() {
    // Dead reckoning: update (X, Y) based on time elapsed while moving.
    // Extremely inaccurate without wheel encoders!
    unsigned long currentMillis = millis();
    if (currentMillis - _lastWaypointTime >= TIME_PER_CELL) {
        _lastWaypointTime = currentMillis;
        // Assume we reached the next cell in our path
        if (_currentWaypointIdx < _pathLength) {
            _robotX = _currentPath[_currentWaypointIdx].x;
            _robotY = _currentPath[_currentWaypointIdx].y;
            _currentWaypointIdx++;
        }
    }
}

void systemController::followPath() {
    if (_currentWaypointIdx >= _pathLength) {
        Serial.println(F("Goal Reached!"));
        _robot.stop();
        _currentState = IDLE;
        return;
    }

    updateOdometry();

    // Determine direction to the current waypoint
    int targetX = _currentPath[_currentWaypointIdx].x;
    int targetY = _currentPath[_currentWaypointIdx].y;
    
    int dx = targetX - _robotX;
    int dy = targetY - _robotY;

    // Use Mecanum drive to strafe/move toward target cell
    if (dy > 0) _robot.move(FORWARD, BASE_SPEED, 0);
    else if (dy < 0) _robot.move(BACKWARD, BASE_SPEED, 0);
    else if (dx > 0) _robot.move(STRAFE_R, BASE_SPEED, 0);
    else if (dx < 0) _robot.move(STRAFE_L, BASE_SPEED, 0);
}
*/