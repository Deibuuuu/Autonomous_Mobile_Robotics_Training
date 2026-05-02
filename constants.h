#pragma once
#include <Arduino.h>

// --- System & Movement States ---
enum SystemState { IDLE, RUNNING, STOPPED };
enum RobotDirection { RELEASE, FORWARD, BACKWARD, STRAFE_L, STRAFE_R, TURN_L, TURN_R };

// --- Bluetooth & Wireless Upload ---
#define BT_SERIAL Serial   // Pins 0 and 1
const int BT_BAUD = 115200; // Must match Mega bootloader

// --- L298N Motor Pins (Verified) ---
const int FL_IN1 = 2;  const int FL_IN2 = 3;  const int FL_EN = 9;
const int FR_IN1 = 4;  const int FR_IN2 = 5;  const int FR_EN = 10;
const int RL_IN1 = 6;  const int RL_IN2 = 7;  const int RL_EN = 11;
const int RR_IN1 = 8;  const int RR_IN2 = 12; const int RR_EN = 13;

// --- MPU6050 Addresses & Tuning ---
const int MPU_ADDR = 0x68;
const int PWR_MGMT_1 = 0x6B;
const int GYRO_Z_OUT = 0x47;
const float GYRO_KP = 2.0;   
const int BASE_SPEED = 200;  

// --- Button Pins ---
const int START_BTN = A0;
const int STOP_BTN = A1; 
const int RESET_BTN = A2;