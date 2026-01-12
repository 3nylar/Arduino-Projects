#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- CONFIG ----------
const uint8_t LCD_ADDR = 0x27; // Change if your LCD uses 0x3F
const uint8_t LCD_COLS = 16;
const uint8_t LCD_ROWS = 2;

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

// ---------- PINS ----------
const int trigPin = 9;
const int echoPin = 10;
const int ledRed = 5;
const int ledYellow = 6;
const int ledGreen = 7;
const int buzzer = 8;

// ---------- SETTINGS ----------
const int TANK_HEIGHT = 10; // cm, adjust to your tank height
const int NUM_READINGS = 5;  // for averaging
const int LOW_THRESHOLD = 25;    // % for low water warning
const int HIGH_THRESHOLD = 95;   // % for almost full

void setup() {
  Serial.begin(9600);
  
  // Initialize LCD
  lcd.init();
  lcd.backlight();
  
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(buzzer, OUTPUT);

  lcd.setCursor(0,0);
  lcd.print("Water Level Sys");
  delay(2000);
  lcd.clear();
}

long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000); // timeout 30ms
  long distance = duration * 0.034 / 2; // cm
  return distance;
}

long getAverageDistance() {
  long sum = 0;
  for(int i=0; i<NUM_READINGS; i++) {
    sum += measureDistance();
    delay(50);
  }
  return sum / NUM_READINGS;
}

void loop() {
  long distance = getAverageDistance(); // cm
  if(distance > TANK_HEIGHT) distance = TANK_HEIGHT; // limit max distance
  
  int waterLevelPercent = ((TANK_HEIGHT - distance) * 100) / TANK_HEIGHT;
  if(waterLevelPercent < 0) waterLevelPercent = 0;
  if(waterLevelPercent > 100) waterLevelPercent = 100;

  Serial.print("Distance: "); Serial.print(distance); Serial.print(" cm, ");
  Serial.print("Level: "); Serial.print(waterLevelPercent); Serial.println("%");

  // ---------- LED & Buzzer ----------
  if(waterLevelPercent >= HIGH_THRESHOLD){ // High water level
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, HIGH);
  } else if(waterLevelPercent >= LOW_THRESHOLD){ // Midlevel
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, LOW);
    digitalWrite(buzzer, LOW);
  } else { // low water
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);
    digitalWrite(buzzer, HIGH); // alert
  }

  // ---------- LCD ----------
  lcd.setCursor(0,0);
  lcd.print("Level: ");
  lcd.print(waterLevelPercent);
  lcd.print("%   ");

  lcd.setCursor(0,1);
  lcd.print("Dist: ");
  lcd.print(distance);
  lcd.print("cm   ");

  delay(1000);
}