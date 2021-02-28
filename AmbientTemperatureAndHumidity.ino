  
/*-------------------------------------------
Author : Anuj Mahendra Mutha
Website : https://www.anujmutha.com 
LinkedIn : https://www.linkedin.com/in/anujmutha/
Github : https://github.com/AnujMutha
Instagram : https://www.instagram.com/anuj.mutha/
Facebook : https://www.facebook.com/anuj.mutha.31
Twitter : https://twitter.com/anuj_mutha
--------------------------------------------*/
#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <DHT.h>

char auth[] = "<Blynk auth code recieved on your mail>"; //Enter the Auth code which was send by Blink

char ssid[] = "<your ssid here>";  //Enter your WIFI Name
char pass[] = "<your ssid's password here>";  //Enter your WIFI Password

#define DHTPIN 2          // Digital pin 4

#define DHTTYPE DHT11     // DHT 11

DHT dht(DHTPIN, DHTTYPE);
SimpleTimer timer;

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, h);  //V5 is for Humidity
  Blynk.virtualWrite(V6, t);  //V6 is for Temperature
}

void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
  Blynk.begin(auth, ssid, pass);

  dht.begin();

  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
}

void loop()
{
  Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer
}
