#include "config.h"
#include "FastLED.h"

AdafruitIO_Feed *counter = io.feed("lights");
#define NUM_LEDS 36
#define DATA_PIN 5
CRGB leds[NUM_LEDS];

void setup()
{
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while (!Serial)
    ;

  Serial.print("Connecting to Adafruit IO");

  // connect to io.adafruit.com
  io.connect();

  // set up a message handler for the count feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  counter->onMessage(handleMessage);

  // wait for a connection
  while (io.status() < AIO_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void loop()
{
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
}

// this function is called whenever a 'counter' message
// is received from Adafruit IO. it was attached to
// the counter feed in the setup() function above.
void handleMessage(AdafruitIO_Data *data)
{
  String s = data->value();
  Serial.print("received <- ");
  Serial.println(s);
  
  CRGB colour = CRGB::Black;
  
  if (s == "off")
  {
    colour = CRGB::Black;
  }
  if (s == "full")
  {
    colour = CRGB::White;
  }
  if (s == "chill")
  {
    colour = CRGB::Purple;
  }
  if (s == "warm")
  {
    colour = CRGB::DarkOrange;
  }
  if (s == "dim")
  {
    colour = CRGB::DarkSeaGreen;
  }

  fill_solid( leds, NUM_LEDS, colour);

}
