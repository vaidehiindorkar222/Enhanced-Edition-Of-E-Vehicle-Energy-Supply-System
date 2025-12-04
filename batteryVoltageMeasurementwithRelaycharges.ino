/*
  Dual Battery Solar Charging Controller (Accurate + Auto Relay Control)
  - For ACTIVE-LOW relay modules (e.g., HW-316)
  - Relay ON = digitalWrite(LOW)
  - Relay OFF = digitalWrite(HIGH)
*/

const int PIN_S_A = A0;
const int PIN_S_B = A1;
const int RELAY_A = 7;
const int RELAY_B = 8;
const int LED_PIN = 13;

const int SAMPLES = 30;
const float MIN_BAT_V = 0.5;
const float MAX_BAT_V = 16.8;

// ⚡ Thresholds
const float CHARGE_ON_VOLTAGE  = 3.0;   // Turn ON charging when battery below this
const float CHARGE_OFF_VOLTAGE = 3.5;   // Turn OFF charging when battery above this
const float LOW_VOLTAGE_ALERT  = 11.0;  // Optional LED alert

// Scale factors for voltage sensors
float SCALE_A = 5.50;
float SCALE_B = 5.50;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_A, OUTPUT);
  pinMode(RELAY_B, OUTPUT);
  pinMode(LED_PIN, OUTPUT);

  // Default all OFF (HIGH = OFF for active-LOW relay)
  digitalWrite(RELAY_A, HIGH);
  digitalWrite(RELAY_B, HIGH);
  digitalWrite(LED_PIN, LOW);

  delay(300);
  Serial.println(F("===================================="));
  Serial.println(F(" Dual Battery Solar Charge Controller (Active-LOW Relay)"));
  Serial.println(F("===================================="));
}

void loop() {
  float vcc = readVcc();
  float sA = readSensorVolts(PIN_S_A, vcc);
  float sB = readSensorVolts(PIN_S_B, vcc);

  float batA = sA * SCALE_A;
  float batB = sB * SCALE_B;

  if (batA < MIN_BAT_V || batA > MAX_BAT_V) batA = 0.0;
  if (batB < MIN_BAT_V || batB > MAX_BAT_V) batB = 0.0;

  // Display readings
  Serial.print("Battery A: ");
  if (batA <= 0.01) Serial.println("Not Connected");
  else { Serial.print(batA, 2); Serial.println(" V"); }

  Serial.print("Battery B: ");
  if (batB <= 0.01) Serial.println("Not Connected");
  else { Serial.print(batB, 2); Serial.println(" V"); }

  Serial.println("--------------------------------------");

  // Relay control logic (ACTIVE-LOW relays)
  static bool chargingA = false;
  static bool chargingB = false;

  // Battery A control
  if (batA > 0 && batA < CHARGE_ON_VOLTAGE && !chargingA) {
    chargingA = true;
    chargingB = false;
    digitalWrite(RELAY_A, LOW);   // ON (Active LOW)
    digitalWrite(RELAY_B, HIGH);  // OFF
    Serial.println("⚡ Charging Battery A");
  }

  if (chargingA && batA >= CHARGE_OFF_VOLTAGE) {
    chargingA = false;
    digitalWrite(RELAY_A, HIGH);  // OFF
    Serial.println("✅ Battery A Full - Stopping charge");
  }

  // Battery B control
  if (batB > 0 && batB < CHARGE_ON_VOLTAGE && !chargingB && !chargingA) {
    chargingB = true;
    chargingA = false;
    digitalWrite(RELAY_B, LOW);   // ON (Active LOW)
    digitalWrite(RELAY_A, HIGH);  // OFF
    Serial.println("⚡ Charging Battery B");
  }

  if (chargingB && batB >= CHARGE_OFF_VOLTAGE) {
    chargingB = false;
    digitalWrite(RELAY_B, HIGH);  // OFF
    Serial.println("✅ Battery B Full - Stopping charge");
  }

  // LED alert (optional)
  if ((batA > 0 && batA < LOW_VOLTAGE_ALERT) || (batB > 0 && batB < LOW_VOLTAGE_ALERT))
    digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);

  delay(2000);
}

// ---------------- Helper functions ----------------

float readSensorVolts(int pin, float measuredVcc) {
  long sum = 0;
  for (int i = 0; i < SAMPLES; i++) {
    sum += analogRead(pin);
    delay(3);
  }
  float raw = (float)sum / SAMPLES;
  if (raw < 6.0) return 0.0;
  float vS = (raw / 1023.0) * measuredVcc;
  return vS;
}

long readVccRaw() {
  ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  delay(2);
  ADCSRA |= _BV(ADSC);
  while (bit_is_set(ADCSRA, ADSC));
  long result = ADCL;
  result |= ADCH << 8;
  return result;
}

float readVcc() {
  long raw = readVccRaw();
  if (raw == 0) return 0.0;
  return (1.1 * 1023.0) / (float)raw;
}
