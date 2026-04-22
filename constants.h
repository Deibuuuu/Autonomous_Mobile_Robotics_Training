#pragma once

#include <Arduino.h>

// --- Front Left Motor ---
const int FL_ENA = 5; 
const int FL_IN1 = 7;
const int FL_IN2 = 8;

// --- Front Right Motor ---
const int FR_ENB = 6; 
const int FR_IN3 = 11;
const int FR_IN4 = 24;

// --- Back Left Motor ---
const int BL_ENA = 9; 
const int BL_IN1 = 22;
const int BL_IN2 = 23;

// --- Back Right Motor ---
const int BR_ENB = 10;  
const int BR_IN3 = 30;  
const int BR_IN4 = 31;  

// --- Test Settings ---
const float TEST_SPEED = 0.5; // 50% Power