#define BLYNK_TEMPLATE_ID "TMPLV5qz6z54"
#define BLYNK_DEVICE_NAME "Blynk API"
#define BLYNK_AUTH_TOKEN "c2_hpaqvpe6YpiZuTiH3j4SKVwOAgbM6"

#include <ESP8266WiFi.h> // include library
#include <BlynkSimpleEsp8266.h> // include library
#include <DHT.h> //Library untuk DHT
#define DHTPIN D3 //deklarasi pin D3 untuk output dari DHT11
#define DHTTYPE DHT11 //Tipe DHT11
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
char auth[] = BLYNK_AUTH_TOKEN ; //Auth Token

char ssid[] = "Suradi"; //nama hotspot yang digunakan
char pass[] = "Bangau12"; //password hotspot yang digunakan

// lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

//function untuk pengiriman sensor
void sendSensor()
{
float t = dht.readTemperature(); //pembacaan sensor
float h = dht.readHumidity();
int sensorReading = analogRead(A0);
int range = map(sensorReading, sensorMin, sensorMax, 0, 3);
Serial.print("% Temperature: ");
Serial.print(t);
Serial.println("C ");
Serial.print("% Kelembaban: ");
Serial.print(h);
Serial.println("% ");

switch (range) {
  case 0:    // A fire closer than 1.5 feet away.
    Blynk.virtualWrite(V4,"3");
    break;
  case 1:    // A fire between 1-3 feet away.
    Blynk.virtualWrite(V4,"2");
    break;
  case 2:    // No fire detected.
    Blynk.virtualWrite(V4,"1");
    break;
  }
  delay(1);  // delay between reads
Blynk.virtualWrite(V2, t); //mengirimkan data temperatur ke Virtual pin VO di Blynk Cloud
Blynk.virtualWrite(V3, h); //mengirimkan data kelemaban ke Virtual pin V1 di Blynk Cloud

}
void setup() {
  // initialize serial communication @ 9600 baud:
Serial.begin(115200); //serial monitor menggunakan bautrate 9600
Blynk.begin(auth, ssid, pass); //memulai Blynk
dht.begin(); //mengaktifkan DHT11
timer.setInterval(1000L, sendSensor); //Mengaktifkan timer untuk pengiriman data 1000ms
}

void loop() {
Blynk.run(); //menjalankan blynk
timer.run(); //menjalankan timer
}
