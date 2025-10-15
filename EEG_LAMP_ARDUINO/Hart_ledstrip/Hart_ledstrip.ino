#include <FastLED.h>

// ====== LED CONFIGURATION ======
#define LED_PIN_MAIN 36     // Main data pin
#define LED_PIN_BACKUP 37   // Backup data pin (optional)
#define NUM_LEDS 30         // Change to match your strip length
#define LED_TYPE SK6812
#define COLOR_ORDER GRB     // SK6812s are usually GRB
#define BRIGHTNESS 100      // 0–255

// ====== STRIP SETUP ======
CRGB leds[NUM_LEDS];

// ====== SELECT DATA PIN ======
// Set to LED_PIN_MAIN or LED_PIN_BACKUP
#define ACTIVE_LED_PIN LED_PIN_MAIN

void setup() {
  delay(1000); // power-up safety delay

  FastLED.addLeds<LED_TYPE, ACTIVE_LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);

  // Optional: ensure data line starts low
  pinMode(ACTIVE_LED_PIN, OUTPUT);
  digitalWrite(ACTIVE_LED_PIN, LOW);
}

void loop() {
  // Simple test pattern: red, green, blue, white, rainbow
  testSolid(CRGB::Red);
  testSolid(CRGB::Green);
  testSolid(CRGB::Blue);
  testSolid(CRGB::White);
  rainbowCycle();
}

// ====== Helper functions ======

void testSolid(const CRGB& color) {
  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();
  delay(1000);
}

void rainbowCycle() {
  for (int j = 0; j < 256 * 3; j++) { // cycle through hues
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV((i * 256 / NUM_LEDS + j) & 255, 255, 255);
    }
    FastLED.show();
    delay(10);
  }
}
