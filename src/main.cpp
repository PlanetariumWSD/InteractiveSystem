#include <Arduino.h>
#include <Ethernet.h>
#include <ArduinoHttpClient.h>
#include <ArduinoJson.h>
#include <CapacitiveSensor.h>

// Server info
const char SERVER_ADDRESS[] = "192.168.1.1";
const int SERVER_PORT = 3000;
const int MAX_SETTING_SIZE = 175;

// Client info
const String SEAT_NUM = "3"; // TODO: using `String` is wasteful, figure out an alternative method
IPAddress ip(192, 168, 1, 177);
byte mac[] = {0xAD, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};

// Networking
EthernetClient httpEthernet;
EthernetClient wsEthernet;
HttpClient http = HttpClient(httpEthernet, SERVER_ADDRESS, SERVER_PORT);
WebSocketClient ws = WebSocketClient(wsEthernet, SERVER_ADDRESS, SERVER_PORT);
StaticJsonDocument<MAX_SETTING_SIZE> setting;

// Hardware
byte previousButtonChoice = -1;
class Button
{
public:
  CapacitiveSensor sensor;
  long sensorThreshold = 200;

  Button(uint8_t sensorPin, byte ledPin_) : sensor(2, sensorPin), ledPin(ledPin_)
  {
    sensor.set_CS_Timeout_Millis(50);
  }

  void setLed(byte brightness)
  {
    analogWrite(ledPin, brightness);
  }

private:
  byte ledPin;
};

Button buttons[5] = {
    Button(A0, 3),
    Button(A1, 5),
    Button(A2, 6),
    Button(A3, 9),
    Button(A4, 10)};

void setup()
{
  Serial.begin(9600);
  while (!Serial)
    continue;
  Serial.println("Ready: " + SEAT_NUM);
  Ethernet.begin(mac, ip);
  ws.begin("/settings/" + SEAT_NUM);
}

void checkWS()
{
  if (ws.parseMessage() > 0)
  {
    Serial.println(ws.readString());
    deserializeJson(setting, ws.readString());
    for (byte i = 0; i < 4; i++)
    {
      buttons[i].setLed(setting[i]["brightness"]);
    }
  }
}

void checkButtons()
{
  for (byte newConsideration = 0; newConsideration < 4; newConsideration++)
  {
    if (
        previousButtonChoice != newConsideration &&
        setting[newConsideration]["live"] &&
        buttons[newConsideration].sensor.capacitiveSensor(30) > buttons[newConsideration].sensorThreshold)
    {
      http.post("/states/" + SEAT_NUM, "application/json", "{ \"latestPress\": " + String(newConsideration) + " }"); // TODO: create `intToString()` to replace `String()`
      buttons[newConsideration].setLed(setting[newConsideration]["brightness"]);
      for (byte i = 0; i < 4; i++)
        if (i != newConsideration)
          buttons[i].setLed(0);
      previousButtonChoice = newConsideration;
    }
  }
}

void loop()
{
  checkWS();
  checkButtons();
}
