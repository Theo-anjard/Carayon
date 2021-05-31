// DHT22 (temp Humi)
#include "DHT.h"
#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
DHT dht(DHTPIN, DHTTYPE);

// Pluie

#include <Wire.h>
unsigned char low_data[8] = {0};
unsigned char high_data[12] = {0};
#define ATTINY1_HIGH_ADDR   0x78
#define ATTINY2_LOW_ADDR   0x77

void setup() {
  Serial.begin(9600);
  dht.begin();
  Wire.begin();
}
void loop() {
  delay(2000);
  tempHumi(); 
  check();
  }

void tempHumi(){
   // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print("%  Temperature: ");
  Serial.print(t);
  Serial.print("°C ");
  Serial.print(hic);
  Serial.println("°C "); 
}

void ValeursHaute12(void)
{
  memset(high_data, 0, sizeof(high_data));
  Wire.requestFrom(ATTINY1_HIGH_ADDR, 12);
  while (12 != Wire.available());
  for (int i = 0; i < 12; i++) {
    high_data[i] = Wire.read();
     delay(10);
}}

void ValeursBasse8(void)
{
  memset(low_data, 0, sizeof(low_data));
Wire.requestFrom(ATTINY2_LOW_ADDR, 8);
  while (8 != Wire.available());
 
  for (int i = 0; i < 8 ; i++) {
    low_data[i] = Wire.read(); // receive a byte as character
  } delay(10); }

void check()
{
  int sensorvalue_min = 250;
  int sensorvalue_max = 255;
    ValeursBasse8();
    ValeursHaute12();
    // Nombre de cellule à l'état haut. Un état haut indique qu'il y a de l'eau sur connecteur 
    int NValeursHaute = 0;
    int NValeursBasse= 0;
    int Sommes = 0;
    
for (int i = 0; i < 8; i++) {
    if (low_data[i] >= 251){
      NValeursBasse = NValeursBasse+1;
     // Serial.println(NValeursBasse);
    Serial.println(low_data[i]);
      }  
  delay(10); }

for (int i = 0; i < 12; i++) {
    if (high_data[i] >= 251){
      NValeursHaute = NValeursHaute+1;
     // Serial.println(NValeursHaute);
  } delay(10); 
  }
Sommes = NValeursHaute + NValeursBasse;

if ( Sommes >= 5){
   Serial.println("il pleut");
  // Serial.println(Sommes);
  }
else {
  Serial.println("il ne pleut pas");
  // Serial.println(Sommes);
  }
Serial.println("*********************************************************");
    delay(1000); }
