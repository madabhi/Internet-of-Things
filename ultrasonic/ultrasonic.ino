#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define FIREBASE_HOST "https://iot-website-8315e-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "-----BEGIN PRIVATE KEY-----\nMIIEvQIBADANBgkqhkiG9w0BAQEFAASCBKcwggSjAgEAAoIBAQDFleOD3a19+NQP\nbIHkpH6UM80tTVNFNylg/af7a8CrQ+lsXu6DVq3WQq+N4SKcMgf4jKXdeOsUq89D\nzHRwGpLtSuxptlemYmfGvO/cDHUWLjueixd0i8//OClRPMwBW/x4ikMtBxLDzs6R\nzKTgUz30uPKFH6Hz1lP8uxDxUulfgZhtmr8GA0F7dPYrcIirIPU7x61ureKNNQr1\nhYseQoX8n0gPHwiwEWAhZFLbYcsI7HYHYNiknt5SxbA98WbIGL4zHsQm+Obdfqpa\nlPyBOw9EyHdZ58ZrCS0eHS+hTC2yyEDiVCQfslpiFgx6UsIgFbA8Qr0TiF4G/b63\ntlH0Ya2zAgMBAAECggEADW1n8whzR4+5YrLywNgoWNVnzURVIOubUNii8vH1YEB3\nhHlF8MlI6Uxckc/ApvFNLfEzPY02rI/OLgwxNF9jFeQHSqM/WHveXP1ulA2t0HU2\nKAE3PtfGF2MvYnuk7zdJGQf6FCHaWlHktZPPQJiMKeQ1aUaVDBmjfczGXWkqvlPV\nIWOHbHzlZHVMHX1CaMisgfhshXhBk+WBqtAD5JxFx5OsPvKB/GfRrpEvxDtNBWwy\nOFF+zT1127VLef3BxCwQgWl/jt2t596GsrtzvCRIBYCAnwNN7ohJWElgwH1HEJoU\nbaZ4fonvqqsWWiYWCTMPeUUpm65GdRFfAe6xTBJPAQKBgQDoOfxhe9JVEObRvbEM\nSP1UAwvXOg9v8pBonS2IUEsjPLuuzVCJRH3us9r+OaiwypriObo810qlJX+ukZgI\n5Gitf3mhgNAAAE7Xbi33dAn9VFUB2KNgTN6PvxnmNI+VDwy5GUHUSIIYt2Z6A5L4\n9tHMT6wM5/nVi55XI3xCp9pTEQKBgQDZ0A7ZK5wW+OK4Vlk1vvswJVWCorTFmLmZ\nMhSN76gXDHe14R1W83QnBsLoD4OwX2xEx5c4vwapHSERrWUbTHWHKEOHEg1/NlaZ\nPVeayTMyF2BA6fNyCKgG5496hTi2ld8b3qYX2KAZ2xLWz4GQtSAMu4NoDts0I42M\ncGz7br5sgwKBgFYZOZNC/yZ+z7UvqTau0Q2W24r+gb61pgjDTaBedJ0p5UPX52Yd\nOLuJf0YGRp7VXztEv+HSyGAWWRJ19HJHjO/WdVgFlBiMBK8msHAwW4vK+oFmupv3\npASTi5yoHBvdqo/t51Q3VdSoGpxeOt2HVR105IscbqpXy2rvQyDLbsyhAoGBAKV7\n7cwR1gWeEqL698xdzXpG4zDdbXqzDk/WPMeZzZu1XT5SSnhFf3onKO4m22alGR0o\nhzwV5nmWKAnGM4sKDEEj1ipJDPgZ0LGcaXKwarUkDX1EQjHhYcfdJqVvkicmttv1\nzTtQ2lLKnwWVolrPQgpqbOwiXWi/mkuZHzPob8UBAoGAY+ayI5YyXASgjnnKuVOk\nz7LQRadR5PaO7tJ6zJLz1sfGZtAZxV5FgoPZtqxuc5VW4laZrux8IakMt+8DEoEy\nAb6KnCtcOjcGSfA1a7O0quxiRV9ogYwlIchZ2iZ+ybT54gcbEvgbyIroyftA6Ezi\n8THwbzWzk6E+el6AO565szU=\n-----END PRIVATE KEY-----\n"
const char* ssid = "Arpit";
const char* password = "@@@@@@@@";

const int trigPin = D0;
const int echoPin = D1;

FirebaseData firebaseData;
FirebaseJson firebaseJson;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  long duration, distance;

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.println(distance);

  firebaseJson.clear();
  firebaseJson.add("distance", distance);

  if (Firebase.pushJSON(firebaseData, "/distance", firebaseJson)) {
    Serial.println("Data sent to Firebase");
  } else {
    Serial.println("Error sending data to Firebase");
    Serial.println(firebaseData.errorReason());
  }

  delay(5000);
}
