#include<Adafruit_SSD1306.h> // Download Link in Description Box
#define RESET LED_BUILTIN
Adafruit_SSD1306 oled(RESET);
void setup()
{
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  oled.setTextSize(2);
  oled.setTextColor(WHITE);
  oled.display();
  delay(1000);
  oled.clearDisplay();
}
void loop()
{
 oled.clearDisplay();
 oled.setCursor(1,2);
 oled.print("Abhinav\Singh");
 oled.display();
 delay(1000);
}