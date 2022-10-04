#include <DHTesp.h>
#include "WiFi.h"
#include "HTTPClient.h"

const char* ssid = "Wokwi-GUEST";
const char* password = "";
const String url = "https://api.thingspeak.com/update?api_key=412O19M7SUR0112U&";

HTTPClient http;
DHTesp dhtSensor;

void setup() {

  Serial.begin(115200);
  Serial.println("Iniciando Setup");
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println("Connecting to WiFi...");
  }
  dhtSensor.setup(13,DHTesp::DHT22);
  Serial.println("Finalizando Setup");
  pinMode(14, OUTPUT);

}

void loop() {

  float temperatura = dhtSensor.getTemperature();
  float umidade = dhtSensor.getHumidity();

  String path = url + "field1=" + String(temperatura) + "&field2=" + String(umidade);

  http.begin(path);
  int httpCode = http.GET();
  String payload = http.getString();

  Serial.println("HttpCode:" + String(httpCode));
  Serial.println("Payload:" + payload);

  Serial.println("Temperatura :" + String(temperatura) + "°C");
  Serial.println("Umidade :" + String(umidade) + "%");
  Serial.println("==============================");

  delay(3000);

  digitalWrite(14, HIGH);
  delay(1000);

  digitalWrite(14, LOW);

}
