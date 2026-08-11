#include <Adafruit_VL53L0X.h>
#include <FastPID.h>

float Kp = 1.9, Ki = 0.001, Kd = 0.7, Hz = 45;
int output_bits = 9;
bool output_signed = true;

FastPID myPID(Kp, Ki, Kd, Hz, output_bits, output_signed);  // for staying in center
int output;

// addresses
#define LOX1_ADD 0x32  // left
#define LOX2_ADD 0x30  // front
#define LOX3_ADD 0x31  // right

// shut pins
#define SHUT1 10
#define SHUT2 11
#define SHUT3 12

Adafruit_VL53L0X lox1 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox2 = Adafruit_VL53L0X();
Adafruit_VL53L0X lox3 = Adafruit_VL53L0X();

// distances
int l_dist = 0;
int f_dist = 0;
int r_dist = 0;

// global constants
const int l_offset = 21;  // wheel width
const int r_offset = 21;  // wheel width
const int f_offset = 10;  // safety buffer
const int l_cal = 0;      // calibration values
const int r_cal = 0;
const int f_cal = 0;
const int turn_speed = 90;    // turn speed
const int speed_mid = 120;    // mid
const int track_width = 250;  // track_width

// global variables
int8_t turn = 0;
bool solve = 0;
bool stop = 1;


// motor
#define motorA1 2
#define motorA2 3
#define PWM_A 6
#define motorB1 7
#define motorB2 8
#define PWM_B 9

// UI
#define solve_button 15
#define green_led 14
#define stop_button 16
#define red_led 17
#define LED_1 18
#define LED_2 19
#define LED_3 20

// prototypes
void read_sensor();
void sensor_init();
void straight_without_pid();
void print_sensor();

void setup() {

  Serial.begin(115200);  // -----------------------------------------------------------------test-----------------------------------------------

  pinMode(solve_button, INPUT_PULLUP);
  pinMode(stop_button, INPUT_PULLUP);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  pinMode(PWM_A, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  pinMode(LED_1, OUTPUT);
  pinMode(LED_2, OUTPUT);
  pinMode(LED_3, OUTPUT);

  pinMode(SHUT1, OUTPUT);
  pinMode(SHUT2, OUTPUT);
  pinMode(SHUT3, OUTPUT);

  if (stop == 1) {
    digitalWrite(red_led, HIGH);
    digitalWrite(green_led, LOW);
  }
  sensor_init();                  // intiallizing three sensors
  myPID.setOutputRange(-50, 50);  // pid value limits
}

void loop() {

  read_sensor();
  print_sensor();

  if (digitalRead(solve_button) == LOW && solve != 1) {
    digitalWrite(green_led, HIGH);
    digitalWrite(red_led, LOW);
    delay(2000);
    solve = 1;
    stop = 0;
  }

  if (solve) {
    if (digitalRead(stop_button) == LOW) {
      solve = 0;
      stop = 1;
      while (stop) {
        digitalWrite(red_led, HIGH);
        digitalWrite(green_led, LOW);
        digitalWrite(PWM_B, 0);
        digitalWrite(PWM_A, 0);
        if (digitalRead(solve_button) == LOW && solve != 1) {
          digitalWrite(red_led, LOW);
          digitalWrite(green_led, HIGH);
          delay(2000);
          solve = 1;
          stop = 0;
        }
      }
    }
    straight_without_pid();
  }
}