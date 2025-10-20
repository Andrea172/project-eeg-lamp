#include <FastLED.h>

#define LED_PIN     36
#define NUM_LEDS    150
#define LED_TYPE    SK6812
#define COLOR_ORDER GRB

#define BRIGHT_MIN  50
#define BRIGHT_MAX  50

#define FADE_DELAY  10  // ms

CRGB leds[NUM_LEDS];


//CRGB color_low  = CRGB(0, 255, 180);   // turqouise
//CRGB color_high = CRGB(255, 200, 0);   // yellow

// Define the colors that will be used
CRGB color_0 = CRGB(128, 0, 128);   // Purple
CRGB color_1 = CRGB(0, 255, 0);     // Green
CRGB color_2 = CRGB(255, 0, 0);     // Red
CRGB color_3 = CRGB(255, 200, 0);   // Yellow 

// Global variables
CRGB current_color = color_0;
int current_brightness = BRIGHT_MIN;
int target_brightness = BRIGHT_MIN;

// FIX #1: The data type for a color variable must be 'CRGB', not 'int'.
CRGB target_color_rgb = color_0;

unsigned long last_update = 0;


void setup() {
  Serial.begin(9600);
  delay(3000);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(current_brightness);

  Serial.println("Board is ready. Send any character to test connection.");
  fill_solid(leds, NUM_LEDS, color_0);
  FastLED.show();
}

void loop() {
  // Read from serial port
  if (Serial.available()) {
    char c = Serial.read();

    if (c == '0') {
      target_color_rgb = color_0;
      target_brightness = BRIGHT_MIN;
    } else if (c == '1') {
      target_color_rgb = color_1;
      target_brightness = BRIGHT_MAX;
    } else if (c == '2') {
      target_color_rgb = color_2;
      target_brightness = BRIGHT_MAX;
    } else if (c == '3') {
      target_color_rgb = color_3;
      target_brightness = BRIGHT_MAX;
    }
  }

  if (millis() - last_update >= FADE_DELAY) {
    last_update = millis();

    // Smoothly fade brightness
    // if (current_brightness < target_brightness) current_brightness++;
    // else if (current_brightness > target_brightness) current_brightness--;

    // Smoothly transition each RGB component
    if (current_color.r < target_color_rgb.r) current_color.r++;
    else if (current_color.r > target_color_rgb.r) current_color.r--;
    
    if (current_color.g < target_color_rgb.g) current_color.g++;
    else if (current_color.g > target_color_rgb.g) current_color.g--;
    
    if (current_color.b < target_color_rgb.b) current_color.b++;
    else if (current_color.b > target_color_rgb.b) current_color.b--;

    FastLED.setBrightness(current_brightness);
    fill_solid(leds, NUM_LEDS, current_color);
    FastLED.show();
  }
}
