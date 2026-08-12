void straight_without_pid(bool dir, int spid) {  //  dir = 0 -- reverse, dir = 1 -- forward

  digitalWrite(motorA1, !dir);
  digitalWrite(motorA2, dir);
  digitalWrite(motorB1, dir);
  digitalWrite(motorB2, !dir);
  analogWrite(PWM_A, spid + motorA_cal);
  analogWrite(PWM_B, spid + motorB_cal);
}

void straight() {

  diff = l_dist - r_dist;  // taking difference
  output = myPID.step(0, diff);
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);

  if (diff > 0) {
    analogWrite(PWM_A, speed + motorA_cal + output);
    analogWrite(PWM_B, speed + motorB_cal - output);
  } else {
    analogWrite(PWM_A, speed + motorA_cal + output);
    analogWrite(PWM_B, speed + motorB_cal - output);
  }
}

void bend(int dir) {  // dir = -1 -- left, dir = 1 -- right
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  if (dir == -1) {  // turn left
    analogWrite(PWM_A, turn_speed - 60);
    analogWrite(PWM_B, turn_speed);
  } else if (dir == 1) {  // turn right
    analogWrite(PWM_A, turn_speed);
    analogWrite(PWM_B, turn_speed - 60);
  }
}