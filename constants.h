#pragma once
#include <Arduino.h>

// --- Movement States ---
enum RobotDirection {
  RELEASE, //stop
  FORWARD,
  BACKWARD,
  STRAFE_L,
  STRAFE_R,
  TURN_L,
  TURN_R
};

// --- L298N Motor Pins (Verified) ---
const int FL_IN1 = 2;  const int FL_IN2 = 3;  const int FL_EN = 9;
const int FR_IN1 = 4;  const int FR_IN2 = 5;  const int FR_EN = 10;
const int RL_IN1 = 6;  const int RL_IN2 = 7;  const int RL_EN = 11;
const int RR_IN1 = 8;  const int RR_IN2 = 12; const int RR_EN = 13;

// --- MPU6050 Raw Addresses ---
const int MPU_ADDR = 0x68;
const int PWR_MGMT_1 = 0x6B;
const int GYRO_Z_OUT = 0x47; // Specifically for Z-Axis

// --- Stabilization Config ---
const float GYRO_KP = 2.0;    
const int BASE_SPEED = 200;