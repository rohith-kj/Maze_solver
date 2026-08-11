void read_sensor() {

  if (lox1.isRangeComplete()) {
    l_dist = lox1.readRange() + l_cal - l_offset;
  }
  if (lox3.isRangeComplete()) {
    r_dist = lox3.readRange() + r_cal - r_offset;
  }
  if (lox2.isRangeComplete()) {
    f_dist = lox2.readRange() + f_cal - f_offset;
  }
  if ((r_dist < 120 && l_dist < 120) && (f_dist > track_width + 50)) {  // 120 = (track_width - bot_width(including wheels))/2 + 60 (buffer for diagonal sections)
    turn = 0;                                                           // straight with feed back
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, LOW);
  } else if ((r_dist < 120 && l_dist < 120) && (f_dist < track_width + 50)) {  // 120 = (track_width - bot_width(including wheels))/2 + 60 (buffer for diagonal sections)
    turn = 2;                                                                  // straight without pid
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, HIGH);
    digitalWrite(LED_3, HIGH);
  } else if (l_dist > track_width && f_dist < track_width - 50) {
    turn = -1;  // left turn
    digitalWrite(LED_1, HIGH);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, LOW);
  } else if (r_dist > track_width && f_dist < track_width - 50) {
    turn = 1;  // right turn
    digitalWrite(LED_1, LOW);
    digitalWrite(LED_2, LOW);
    digitalWrite(LED_3, HIGH);
  }
}