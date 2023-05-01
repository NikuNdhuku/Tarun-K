#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DHTPIN 27    // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22

#define ONE_WIRE_BUS 25 // Digital pin connected to the 18B20 temperature sensor

#define PIR_PIN 15   // Digital pin connected to the PIR sensor
#define LED_PIN_1 12  // Digital pin connected to LED 1
#define LED_PIN_2 14  // Digital pin connected to LED 2
#define BUZZER_PIN 2 // Digital pin connected to the buzzer

DHT dht(DHTPIN, DHTTYPE);

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

bool motionDetected = false;

void setup() {
  Serial.begin(9600);
  
  dht.begin();
  tempSensor.begin();
  
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  // Read data from DHT22 sensor
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Read data from 18B20 temperature sensor
  tempSensor.requestTemperatures();
  float tempC = tempSensor.getTempCByIndex(0);
  Serial.print("Temperature 2: ");
  Serial.print(tempC);
  Serial.println(" *C");

  // Check if motion is detected by PIR sensor
  motionDetected = digitalRead(PIR_PIN);
  if (motionDetected == HIGH) {
    Serial.println("Motion Detected");
    digitalWrite(LED_PIN_1, HIGH);
    digitalWrite(LED_PIN_2, LOW);
    tone(BUZZER_PIN, 1000, 1000);
    delay(500);
  } else {
    Serial.println("No Motion Detected");
    digitalWrite(LED_PIN_1, LOW);
    digitalWrite(LED_PIN_2, HIGH);
    noTone(BUZZER_PIN);
  }

  delay(2000);
}
