#define BLYNK_TEMPLATE_ID "TMPL3CT2XbHy-"
#define BLYNK_TEMPLATE_NAME "LedControl"
#define BLYNK_AUTH_TOKEN "n2Uy6XZzeTfeO3Y8tE0yZA26R-a2stgT"
void setup() {
  // put your setup code here, to run once:
pinMode(D0, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(D0,HIGH);
  delay(500);
  digitalWrite(D0,LOW);
  delay(500);


}
