#include "Adafruit_VL53L0X.h"
#include <FastPID.h>

float Kp = 1.2, Ki = 0.001, Kd = 0.05, Hz = 25;
int output_bits = 9;
bool output_signed = true;

FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);
int output;

// addresses
#define LOX1_ADD 0x32
#define LOX2_ADD 0x30
#define LOX3_ADD 0x31

// shut pins
#define SHUT1 10
#define SHUT2 11
#define SHUT3 12

// distances
int l_dist = 0;
int f_dist = 0;
int r_dist = 0;

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// motor
#define motorA1 2
#define motorA2 3
#define PWM_A 6
#define motorB1 7
#define motorB2 8
#define PWM_B 9

void read_dist();

void setup() {

  Serial.begin(115200);
  delay(1500);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  pinMode(SHUT1, OUTPUT);
  pinMode(SHUT2, OUTPUT);
  pinMode(SHUT3, OUTPUT);

  digitalWrite(SHUT1, LOW);
  digitalWrite(SHUT2, LOW);
  digitalWrite(SHUT3, LOW);
  delay(10);
  digitalWrite(SHUT1, HIGH);
  digitalWrite(SHUT2, HIGH);
  digitalWrite(SHUT3, HIGH);
  delay(10);

  digitalWrite(SHUT2, LOW);
  digitalWrite(SHUT3, LOW);
  digitalWrite(SHUT1, HIGH);  // Bring Sensor 1 out of reset
  delay(10);
  if (!lox1.begin(LOX1_ADD)) {
    Serial.println(F("Failed to boot first VL53L0X1"));
    while (1)
      ;
  }

  digitalWrite(SHUT2, HIGH);  // Bring Sensor 2 out of reset
  delay(10);
  if (!lox2.begin(LOX2_ADD)) {
    Serial.println(F("Failed to boot second VL53L0X1"));
    while (1)
      ;
  }

  digitalWrite(SHUT3, HIGH);  // Bring Sensor 3 out of reset
  delay(10);
  if (!lox3.begin(LOX3_ADD)) {
    Serial.println(F("Failed to boot third VL53L0X3"));
    while (1)
      ;
  }

  lox1.setMeasurementTimingBudgetMicroSeconds(20000);
  lox2.setMeasurementTimingBudgetMicroSeconds(20000);
  lox3.setMeasurementTimingBudgetMicroSeconds(20000);

  lox1.startRangeContinuous();
  lox2.startRangeContinuous();
  lox3.startRangeContinuous();

  myPID.setOutputRange(-50, 50);  // pid value limits
}

void loop() {

  read_dist();
  Serial.print(l_dist);
  Serial.print(" ");
  Serial.print(f_dist);
  Serial.print(" ");
  Serial.println(r_dist);

  if (f_dist > 120) {
    output = myPID.step(0, l_dist - r_dist);
    if (output > 0) {
      digitalWrite(motorA1, HIGH);
      digitalWrite(motorA2, LOW);
      analogWrite(PWM_A, 90 + output);
      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, LOW);
      analogWrite(PWM_B, 90 - output);
    }
    if (output < 0) {
      digitalWrite(motorA1, HIGH);
      digitalWrite(motorA2, LOW);
      analogWrite(PWM_A, 90 - (-output));
      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, LOW);
      analogWrite(PWM_B, 90 + (-output));
    }
  } else {
    if (l_dist > 370) {
      digitalWrite(motorA1, HIGH);
      digitalWrite(motorA2, LOW);
      analogWrite(PWM_A, 110);
      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, LOW);
      analogWrite(PWM_B, 0);
  
    }
    else if(r_dist > 370){
      digitalWrite(motorA1, HIGH);
      digitalWrite(motorA2, LOW);
      analogWrite(PWM_A, 0);
      digitalWrite(motorB1, HIGH);
      digitalWrite(motorB2, LOW);
      analogWrite(PWM_B, 110);
    }
  }
}

void read_dist() {

  if (lox1.isRangeComplete()) {
    l_dist = lox1.readRange();
  }
  if (lox2.isRangeComplete()) {
    f_dist = lox2.readRange();
  }
  if (lox3.isRangeComplete()) {
    r_dist = lox3.readRange();
  }
}