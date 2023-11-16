#define EN_PIN    5
#define DIR_PIN   3
#define STEP_PIN  4

void setup() {
  Serial.begin(115200);
  pinMode(EN_PIN, OUTPUT);
  digitalWrite(EN_PIN, HIGH); // Deactivate driver (LOW active)
  pinMode(DIR_PIN, OUTPUT);
  digitalWrite(DIR_PIN, LOW);
  pinMode(STEP_PIN, OUTPUT);
  digitalWrite(STEP_PIN, LOW);

  digitalWrite(EN_PIN, LOW); // Activate driver
}

void moveStepper(int steps) {
  // Set the direction based on the sign of 'steps'
  digitalWrite(DIR_PIN, steps > 0 ? LOW : HIGH);

  // Pulse the STEP_PIN to generate steps
  for (int i = 0; i < abs(steps); i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(500); 
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(500);
  }
}

void loop() {
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    float angle = data.toFloat();

    if (!isnan(angle)) {
      int targetPosition = map(angle,0,180, 0,360); 
      int currentPosition = 0; 
      int stepsToMove = targetPosition - currentPosition;
      moveStepper(stepsToMove);
    }
  }
}
