#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define auth ""
char ssid[] = "";  // Your WiFi network name
char pass[] = "";  // Your WiFi password

int ledPin = D6;  // The pin number of your LED
int motionPin = D5;  // The pin number of your motion detector sensor
int motionStatus = LOW;  // The current status of the motion detector sensor

void setup() {
  Serial.begin(9600);

  pinMode(ledPin, OUTPUT);
  pinMode(motionPin, INPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop() {

  motionStatus = digitalRead(motionPin);  // Read the motion detector sensor

  if (digitalRead(motionPin) == HIGH) {  // If motion is detected, turn on the LED
    digitalWrite(ledPin, HIGH);
    Blynk.virtualWrite(V1, 1);  // Update the button widget in the app
    Blynk.run();

    while(digitalRead(motionPin) == HIGH){
    Serial.println("Detected");
    if(ledPin==LOW)
    {
    Blynk.virtualWrite(V1, 0);

    }
    Blynk.run();
    delay(1500);
    }
    
  } if (digitalRead(motionPin) == LOW){  // If no motion is detected, turn off the LED
    delay(1500);

    Serial.println("NOT Detected");

    digitalWrite(ledPin, LOW);
    Blynk.virtualWrite(V1, 0);
    Blynk.run();
      // Update the button widget in the app
  }
}
