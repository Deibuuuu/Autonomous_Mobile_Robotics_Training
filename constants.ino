#pragma once

#include <Arduino.h>

// --- Front Left Motor ---
const int FL_ENA = 2; 
const int FL_IN1 = 22;
const int FL_IN2 = 23;

// --- Front Right Motor ---
const int FR_ENB = 3; 
const int FR_IN3 = 24;
const int FR_IN4 = 25;

// --- Back Left Motor ---
const int BL_ENA = 4; 
const int BL_IN1 = 26;
const int BL_IN2 = 27;

// --- Back Right Motor ---
const int BR_ENB = 5; 
const int BR_IN3 = 28;
const int BR_IN4 = 29;

// --- Test Settings ---
const float TEST_SPEED = 0.5; // 50% Power