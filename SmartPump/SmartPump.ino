#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

// Define Ultrasonic Sensor Pins and Constants
#define TRIG_PIN 5      // Trigger pin for ultrasonic sensor
#define ECHO_PIN 6      // Echo pin for ultrasonic sensor
#define MAX_DISTANCE 22 // Maximum distance to measure (in cm)

// Define Relay Pin
#define RELAY_PIN 7     // Relay control pin

// Initialize LCD with I2C address 0x27 and dimensions 20x4
LiquidCrystal_I2C lcd(0x27, 20, 4);

// Initialize Ultrasonic Sensor
NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE);

// Define Container Dimensions
#define CONTAINER_HEIGHT 22 // Height of the container in cm

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  // Display "Computer Engineering ND 2 - Automatic pump with Water Container monitoring and Display" for 2 seconds
  lcd.setCursor(0, 0);
  lcd.print("Computer Engineering");
  lcd.setCursor(0, 1);
  lcd.print("ND2 - Smart pump");
  lcd.setCursor(0, 2);
  lcd.print("with Water Container");
  lcd.setCursor(0, 3);
  lcd.print("monitoring & Display");
  delay(2000);
  
  // Clear the LCD after 2 seconds
  lcd.clear();

  // Initialize Relay Pin
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW); // Ensure pump is initially off

  // Display Initial Message
  lcd.setCursor(0, 0);
  lcd.print("Computer Engineering");
  lcd.setCursor(0, 1);
  lcd.print("ND2 - Smart pump");
  lcd.setCursor(0, 2);
  lcd.print("with Water Container");
  lcd.setCursor(0, 3);
  lcd.print("monitoring & Display");
  delay(2000);
  lcd.clear();
}

void loop() {
  // Measure Distance
  float distance = sonar.ping_cm();

  // Calculate Water Level as Percentage
  float waterLevel = CONTAINER_HEIGHT - distance;
  if (waterLevel < 0) waterLevel = 0;
  float waterLevelPercentage = (waterLevel / CONTAINER_HEIGHT) * 100;

  // Determine Pump State
  bool pumpOn = waterLevel < 10.0; // Example threshold of 2cm

  // Control Pump
  digitalWrite(RELAY_PIN, pumpOn ? HIGH : LOW);

  // Display Water Level and Pump State on LCD
  lcd.setCursor(0, 0);
  lcd.print("Computer Engineering");
  lcd.setCursor(0, 1);
  lcd.print("ND2 - Smart pump");
  lcd.setCursor(0, 2);
  lcd.print("Water Level: ");
  lcd.print(waterLevelPercentage, 1); // Display percentage with one decimal place
  lcd.print("%   ");

  lcd.setCursor(0, 3);
  lcd.print("Pump State: ");
  lcd.print(pumpOn ? "ON " : "OFF");

  // Debugging Output to Serial Monitor
  Serial.print("Water Level: ");
  Serial.print(waterLevelPercentage, 1);
  Serial.print("%, Pump State: ");
  Serial.println(pumpOn ? "ON" : "OFF");

  // Small delay to avoid flooding the serial monitor
  delay(1000);
}
