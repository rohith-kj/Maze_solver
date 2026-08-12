void straight_without_pid() {

  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  analogWrite(PWM_A, straight_speed + motorA_cal);
  analogWrite(PWM_B, straight_speed + motorB_cal);
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