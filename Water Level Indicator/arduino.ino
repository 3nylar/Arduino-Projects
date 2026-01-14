#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- CONFIG ----------
const uint8_t LCD_ADDR = 0x27; // Change if your LCD uses 0x3F
const uint8_t LCD_COLS = 16;
const uint8_t LCD_ROWS = 2;

LiquidCrystal_I2C lcd(LCD_ADDR, LCD_COLS, LCD_ROWS);

// ---------- PINS ----------
const uint8_t trigPin = 9;
const uint8_t echoPin = 10;
const uint8_t ledRed = 5;
const uint8_t ledYellow = 6;
const uint8_t ledGreen = 7;
const uint8_t buzzer = 8;

// ---------- SETTINGS ----------
const float DIST_EMPTY = 12.0; // cm, adjust to your tank height
const float DIST_FULL = 2.0;  // cm, adjust to your tank height
const uint8_t NUM_READINGS = 5;  // for averaging

const uint8_t LOW_THRESHOLD = 25;    // % for low water warning
const uint8_t HIGH_THRESHOLD = 95;   // % for almost full

// ---------- TIMING ----------
unsigned long lastBeepTime = 0;

void buzzerGreen() {
  if (millis() - lastBeepTime >= 3000) {
    tone(buzzer, 2000, 100); // short high beep
    lastBeepTime = millis();
  }
}

void buzzerYellow() {
  if (millis() - lastBeepTime >= 1000) {
    tone(buzzer, 1500, 150); // medium beep
    lastBeepTime = millis();
  }
}

void buzzerRed() {
  if (millis() - lastBeepTime >= 500) {
    tone(buzzer, 800, 200);  // urgent low beep
    lastBeepTime = millis();
  }
}


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
  if(distance > DIST_EMPTY) distance = DIST_EMPTY; // limit
  if (distance < DIST_FULL)  distance = DIST_FULL; // limit
  
  int waterLevelPercent = ((DIST_EMPTY - distance) * 100) / (DIST_EMPTY - DIST_FULL); // % calculation 

  waterLevelPercent = constrain(waterLevelPercent, 0, 100); // constrain to 0-100%

  Serial.print("Distance: "); 
  Serial.print(distance); 
  Serial.print(" cm | Level: ");
  Serial.print(waterLevelPercent); 
  Serial.println("%");

  // ---------- LED & Buzzer ----------
  if(waterLevelPercent >= HIGH_THRESHOLD){ // High water level
    digitalWrite(ledGreen, HIGH);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, LOW);
    buzzerGreen();
  } else if(waterLevelPercent >= LOW_THRESHOLD){ // Midlevel
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, HIGH);
    digitalWrite(ledRed, LOW);
    buzzerYellow();
  } else { // low water
    digitalWrite(ledGreen, LOW);
    digitalWrite(ledYellow, LOW);
    digitalWrite(ledRed, HIGH);
    buzzerRed(); // alert
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

  delay(500);
}