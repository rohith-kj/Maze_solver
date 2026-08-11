void straight_without_pid() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);

  analogWrite(PWM_A, 90);
  analogWrite(PWM_B, 92);  // accomodating small variations in motor speed
}