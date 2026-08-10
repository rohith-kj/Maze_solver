void sensor_init() {

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
    while (1)
      ;
  }
  digitalWrite(LED_1, HIGH);
  digitalWrite(SHUT2, HIGH);  // Bring Sensor 2 out of reset
  delay(10);
  if (!lox2.begin(LOX2_ADD)) {
    while (1)
      ;
  }
  digitalWrite(LED_2, HIGH);
  digitalWrite(SHUT3, HIGH);  // Bring Sensor 3 out of reset
  delay(10);
  if (!lox3.begin(LOX3_ADD)) {
    while (1)
      ;
  }
  digitalWrite(LED_3, HIGH);

  // measurement time budget
  lox1.setMeasurementTimingBudgetMicroSeconds(20000);
  lox2.setMeasurementTimingBudgetMicroSeconds(20000);
  lox3.setMeasurementTimingBudgetMicroSeconds(20000);

  lox1.startRangeContinuous();
  lox2.startRangeContinuous();
  lox3.startRangeContinuous();

  delay(1500);
  digitalWrite(LED_1, LOW);
  digitalWrite(LED_2, LOW);
  digitalWrite(LED_3, LOW);
}

void print_sensor() {
  
  Serial.print(l_dist);
  Serial.print(" ");
  Serial.print(f_dist);
  Serial.print(" ");
  Serial.print(r_dist);
  Serial.print(" ");
  Serial.println(turn);
}