// Import Library
#include <LiquidCrystal.h>
#include "WiFi.h"
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "broker.mqttdashboard.com";
int port = 1883;
// Create a random client ID
String clientId = String("CarSensor-1000") + String(random(0xffff), HEX);

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

// rs (LCD pin 4) to Arduino pin 5
// rw (LCD pin 5) to Arduino pin 6
// enable (LCD pin 6) to Arduino pin 7
// LCD pins d4, d5, d6, d7 to Arduino pins 8, 9, 10, 11
LiquidCrystal lcd(5, 19, 13, 12, 14, 27);
// LCD pin 15 to Arduino pin 4
// int bl = 4;

// Buzzer Positive to pin 1
// Switch Common to pin 2
// Ultrasonic SIG to pin 3
int buzzer = 2, switchBtn = 15;
int echoPin = 23, trigPin = 22;

// Show "Off" Text State
int showOffAlr = 0;
long oldDistance = 0;

// All distance
int stop = 70, should = 95, tclose = 150, closes = 200, gtclose = 300;

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  randomSeed(micros());

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");

    // Attempt to connect
    if (client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      String text = clientId + String(" Join");
      client.publish("swood", text.c_str());
      // ... and resubscribe
      // client.subscribe("swood");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(buzzer, OUTPUT);
  pinMode(switchBtn, INPUT);

  // pinMode(bl, OUTPUT);
  // digitalWrite(bl, HIGH); // turn backlight on
  lcd.begin(16, 2);       // use 16 col and 2 row
  lcd.clear();            // start with a blank screen
  lcd.display();          // Turn on the display:

  setup_wifi();
  client.setServer(mqtt_server, port);
}

void loop()
{
  if (!client.connected()) {
    reconnect();
  }

  int sw = digitalRead(switchBtn); // Read switch state

  if (sw == HIGH)
  {
    long cm = sonar();
    showText(cm);                                 // Display Distance num, text
    beepSound(cm);                                // Beep Beep Sound up to distance

    showOffAlr = 0; // just set value to 0 for off state
  }
  else
  {
    if (showOffAlr == 0) // clear display if already show some text
      lcd.clear();

    // Show this text if switch state is off
    lcd.setCursor(6, 0);
    lcd.print("Off.");
    lcd.setCursor(1, 1);
    lcd.print("turn on switch");
    showOffAlr = 1;
  }

  delay(100);
}

long sonar()
{
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);

  return pulseIn(echoPin, HIGH) / 29 / 2;;
}

void beepSound(long cm)
{
  int delayVal = beepDelay(cm); // get beep beep delay value
  digitalWrite(buzzer, HIGH);

  if (delayVal != 0) // if val is 0 then buzzer will not stop beepๆๆๆ
  {
    delay(delayVal);
    digitalWrite(buzzer, LOW); // stop beep
    delay(delayVal);
  }
}

void showText(int cm)
{
  if (oldDistance != cm) // if distance not change then dont need to update display
  {

    lcd.clear(); // clear all text
    lcd.setCursor(0, 0);
    if (cm < 336) // Should be in range
    {
      // Row 1: Show Distance num
      lcd.print("Distance: ");
      lcd.print(cm);
      lcd.print(" cm");
      Serial.println(cm);
      // Row 2: Show warning text
      lcd.setCursor(0, 1);
      if (cm <= stop)
      {
        lcd.print("STOP!");
        String text = clientId + String(" Crached");
        client.publish("swood", text.c_str());
      }
      else if (cm <= should)
        lcd.print("SHOULD STOP");
      else if (cm <= tclose)
        lcd.print("TOO CLOSE");
      else if (cm <= closes)
        lcd.print("CLOSE");
      else if (cm <= gtclose)
        lcd.print("GETTING CLOSE");
      else
        lcd.print("NOT CLOSE");
    }
    else
      lcd.print("OUT OF RANGE");
  }
  oldDistance = cm;
}

int beepDelay(long cm)
{
  // return beep beep delay
  int milisec = 1000;
  if (cm <= stop)
    milisec = 0;
  else if (cm <= should)
    milisec = 75;
  else if (cm <= tclose)
    milisec = 150;
  else if (cm <= closes)
    milisec = 300;
  else if (cm <= gtclose)
    milisec = 600;
  return milisec;
}