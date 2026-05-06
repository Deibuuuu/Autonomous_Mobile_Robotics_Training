#pragma once
#include <Arduino.h>

// --- System & Movement States ---
enum SystemState { IDLE, RUNNING, STOPPED /*, EVADE*/ }; // Phase 2: Added EVADE state (commented)
enum RobotDirection { RELEASE, FORWARD, BACKWARD, STRAFE_L, STRAFE_R, TURN_L, TURN_R };

// --- L298N Motor Pins (Verified) ---
const int FL_IN1 = 2;  const int FL_IN2 = 3;  const int FL_EN = 9;  // Originally CCW
const int FR_IN1 = 4;  const int FR_IN2 = 5;  const int FR_EN = 10; // Originally CCW
const int RL_IN1 = 6;  const int RL_IN2 = 7;  const int RL_EN = 11; // Swapped to CCW
const int RR_IN1 = 8; const int RR_IN2 = 12;  const int RR_EN = 13; // Swapped to CCW

// --- MPU6050 Addresses & Tuning ---
const int MPU_ADDR = 0x68;
const int PWR_MGMT_1 = 0x6B;
const int GYRO_Z_OUT = 0x47;
const float GYRO_KP = 1.0;   
const int BASE_SPEED = 200;  

// --- Button Pins ---
const int START_BTN = A1;
const int STOP_BTN = A0; 
const int RESET_BTN = A2;

/* // --- Phase 2: Environment Perception & Mapping ---
const int XSHUT_FRONT = 30; // Pins to assign unique I2C addresses
const int XSHUT_LEFT  = 31;
const int XSHUT_RIGHT = 32;

const int SD_CS_PIN = 53; // Hardware CS pin for MEGA SPI
const int OBSTACLE_THRESHOLD = 200; // Distance in mm
*/

/* // --- Phase 2: Pathfinding & Odometry ---
// Using dead reckoning (time-based) for odometry since no encoders are present
const unsigned long TIME_PER_CELL = 1000; // Time in ms to travel 1 grid cell
const int CELL_SIZE_MM = 300; // Each grid cell represents 300x300mm
*/