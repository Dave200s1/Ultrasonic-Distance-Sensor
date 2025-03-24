#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// OLED display settings for Wokwi
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDR 0x3C  // I2C address for Wokwi's OLED

//Sensor settings
#define TRIGER_PIN 13
#define ECHO_PIN 12

float duration;
float distanceCM;


// Display initialisieren
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);

void setup() {
  pinMode(TRIGER_PIN,OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Wire.begin();  // Initialize I2C
  
  // OLED initialisieren
  if(!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while(1); // anhalten falls initialisierung fehlschaegt
  }

}

void loop() {
 //sauberes Signal senden
 digitalWrite(TRIGER_PIN, LOW);
 delayMicroseconds(2);

 //trigger signal senden
 digitalWrite(TRIGER_PIN, HIGH);
 delayMicroseconds(10);
 digitalWrite(TRIGER_PIN, LOW);

 duration = pulseIn(ECHO_PIN,HIGH);

 distanceCM = (duration * 0.034) / 2;

 // Texteinstellungeng
 display.setTextSize(1);        // 2x text size
 display.setTextColor(WHITE);   // White text
 display.setCursor(10, 25);     // Centered position
 
 // Nachricht 
 display.print("Distance: ");
 display.print(distanceCM);
 display.print(" cm");

 //buffer
 display.display();
 // Display erneuern
 display.clearDisplay();
 delay(100);
}

