// Smart Boot Sanitization System
// Low-Cost Automated Boot Washing and Sanitization
// Arduino Uno

// Pin Definitions
const int IR_SENSOR = 2;
const int BRUSH_MOTOR = 3;
const int WATER_PUMP = 4;
const int SOLENOID_VALVE = 5;
const int GREEN_LED = 6;
const int RED_LED = 7;

// Timing
const unsigned long WASH_TIME = 10000;       // 10 seconds
const unsigned long SANITIZE_TIME = 5000;    // 5 seconds

void setup() {
  pinMode(IR_SENSOR, INPUT);

  pinMode(BRUSH_MOTOR, OUTPUT);
  pinMode(WATER_PUMP, OUTPUT);
  pinMode(SOLENOID_VALVE, OUTPUT);

  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // Initial state
  digitalWrite(BRUSH_MOTOR, LOW);
  digitalWrite(WATER_PUMP, LOW);
  digitalWrite(SOLENOID_VALVE, LOW);

  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);

  Serial.begin(9600);
  Serial.println("Smart Boot Sanitization System Ready");
}

void loop() {

  int bootDetected = digitalRead(IR_SENSOR);

  if (bootDetected == LOW) {

    Serial.println("Boot Detected!");

    // System Busy
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);

    // -------------------------
    // Washing Process
    // -------------------------
    Serial.println("Washing Started");

    digitalWrite(WATER_PUMP, HIGH);
    digitalWrite(SOLENOID_VALVE, HIGH);
    digitalWrite(BRUSH_MOTOR, HIGH);

    delay(WASH_TIME);

    // Stop washing
    digitalWrite(BRUSH_MOTOR, LOW);
    digitalWrite(WATER_PUMP, LOW);
    digitalWrite(SOLENOID_VALVE, LOW);

    Serial.println("Washing Completed");

    delay(1000);

    // -------------------------
    // Sanitization Process
    // -------------------------
    Serial.println("Sanitization Started");

    digitalWrite(BRUSH_MOTOR, HIGH);

    delay(SANITIZE_TIME);

    // Stop sanitization
    digitalWrite(BRUSH_MOTOR, LOW);

    Serial.println("Sanitization Completed");

    // System Ready
    digitalWrite(RED_LED, LOW);
    digitalWrite(GREEN_LED, HIGH);

    Serial.println("Process Completed");
    Serial.println("System Ready");

    // Wait until boot is removed
    while (digitalRead(IR_SENSOR) == LOW) {
      delay(100);
    }

    delay(1000);
  }
}
