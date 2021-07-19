#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_CS    8
#define OLED_DC    9
#define OLED_RESET 10
#define OLED_MOSI   11
#define OLED_CLK   12

int adc;
float voltage,current,adc_volt;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {

  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  analogReference(DEFAULT);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000);
  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0,0);
  
}

void loop() {

  adc = analogRead(A0);
  delay(50);
  voltage = (adc*5.0)/1024.0;
  voltage = (voltage * 20)/5;
  display.clearDisplay();
  display.setCursor(0,0);
  display.print("volt: ");
  display.println(voltage);
  display.print("adc: ");
  display.println(adc);
  delay(150);
  //reding A1 for geting current value
  adc = analogRead(A1);
  delay(50);
  adc_volt = (adc*5.0)/1024.0;
  current = adc_volt/4.7;
  display.print("AMP: ");
  display.println(current);
  display.print("adc: ");
  display.println(adc_volt);
  display.display();
  delay(5000);
  
}