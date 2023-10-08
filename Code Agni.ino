#define BUZZER_PIN      34
#define GAS_SENSOR_PIN  A0
#define TEMPERATURE_SENSOR_PIN D1
#define SOUND_SENSOR_PIN D2

unsigned long previousBuzzerMillis = 0;
unsigned long previousTempMillis = 0;
const unsigned long buzzerInterval = 3 * 60 * 1000;  // 3 minutes in milliseconds
const unsigned long tempCheckInterval = 60 * 1000;  // 1 minute in milliseconds
float previousTemperature = 0;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(GAS_SENSOR_PIN, INPUT);
  pinMode(TEMPERATURE_SENSOR_PIN, INPUT);
  pinMode(SOUND_SENSOR_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long currentMillis = millis();

  // Check and sound the buzzer every 3 minutes
  if (currentMillis - previousBuzzerMillis >= buzzerInterval) {
    previousBuzzerMillis = currentMillis;

    // Sound the buzzer
    digitalWrite(BUZZER_PIN, HIGH);
    tone(BUZZER_PIN, 100, 1000);
    delay(60000);  // Keep the buzzer on for 1 minute
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Check the temperature drop every minute
  if (currentMillis - previousTempMillis >= tempCheckInterval) {
    previousTempMillis = currentMillis;

    // Read temperature sensor value and convert to Celsius
    float temperatureValue = analogRead(TEMPERATURE_SENSOR_PIN) * 0.48828125; // Convert to Celsius

    // Check for a temperature drop of 5 degrees or more
    if (previousTemperature - temperatureValue >= 5) {
      int gasValue = analogRead(GAS_SENSOR_PIN);
      // Check if gas is detected (adjust threshold as needed)
      if (gasValue > 40) {
        // Gas detected: Handle it here
        digitalWrite(BUZZER_PIN, HIGH);
        tone(BUZZER_PIN, 100, 1000);  // Example tone
        delay(180000);  // Keep the buzzer on for 1 minute
        digitalWrite(BUZZER_PIN, LOW);
      }
    }
    previousTemperature = temperatureValue;
  }

  // Read sound sensor value
  int soundValue = analogRead(SOUND_SENSOR_PIN);
  // Check if a specific frequency sound is detected (adjust threshold as needed)
  if (soundValue == 100) {
    // Specific sound detected: Handle it here
    digitalWrite(BUZZER_PIN, HIGH);
    tone(BUZZER_PIN, 100, 1000);  // Example tone
    delay(180000);  // Keep the buzzer on for 1 minute
    digitalWrite(BUZZER_PIN, LOW);
  }

  // Other sensor readings and printing
  int gasValue = analogRead(GAS_SENSOR_PIN);
  Serial.print("Gas Value: ");
  Serial.println(gasValue);
  Serial.print("Temperature Value: ");
  Serial.println(previousTemperature);
  Serial.print("Sound Value: ");
  Serial.println(soundValue);

  delay(1000);  // Delay for 1 second between sensor readings
}
