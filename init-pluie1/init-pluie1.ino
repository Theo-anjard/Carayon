#include <Wire.h>
#ifdef ARDUINO_SAMD_VARIANT_COMPLIANCE
#define SERIAL SerialUSB
#else
#define SERIAL Serial
#endif
unsigned char low_data[8] = {0};
unsigned char high_data[12] = {0};
#define ATTINY1_HIGH_ADDR   0x78
#define ATTINY2_LOW_ADDR   0x77

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
   //Serial.println(low_data[i]);
  } 
  delay(10); }
void check()
{
  int sensorvalue_min = 150;
  int sensorvalue_max = 240;
    ValeursBasse8();
    ValeursHaute12();
    // Nombre de cellule à l'état haut. Un état haut indique qu'il y a de l'eau sur connecteur 
    int NValeursHaute = 0;
    int NValeursBasse= 0;
    int Sommes = 0;
   // Il pleut un peu
    int Entre1 = 0; 
    int Entre2 = 0;
    int SommesEntre = 0;
    // Stratigie de d'ouverture
   // int Compte1 = 0;
    //int Compte2 = 0;
   
for (int i = 0; i < 8; i++) {
  if (low_data[i] >= sensorvalue_min && low_data[i] < sensorvalue_max){
         //  Serial.println(low_data[i]);
      Entre1 = Entre1+1;    
  }
  
    if (low_data[i] >= sensorvalue_max){
    //  Serial.println(low_data[i]);
      NValeursBasse = NValeursBasse+1;
      }  
  delay(10); }

for (int i = 0; i < 12; i++) {
if (high_data[i] >= sensorvalue_min && high_data[i] < sensorvalue_max ){
      Entre2 = Entre2+1;

  }  
if (high_data[i] >= sensorvalue_max){
      NValeursHaute = NValeursHaute+1;
  } delay(10); 
  }

SommesEntre = Entre1 + Entre2;  
Sommes = NValeursHaute + NValeursBasse;


int j=0;

  if ( Sommes >= 4) {
    Serial.println("il pleut");
    Serial.print("Sommes : ");
    Serial.println(Sommes);
    
    }
  else if (SommesEntre >= 3) {
   Serial.println("il pleut un peu");
   Serial.print("j :");
   Serial.print(j);
   j=j+1;
   Serial.println("j : ");
   Serial.println(j);
   Serial.print("Sommes : ");
    Serial.println(Sommes);
      Serial.print("Sommes>150 : ");
   Serial.println(SommesEntre); 
    }
  
else {
  Serial.println("il ne pleut pas");
  // Serial.println(Sommes);
  }
Serial.println("*********************************************************");
    delay(1000); }

void setup() {
  Serial.begin(115200);
  Wire.begin();
int j=0;
}
void loop()
{
  check();
}
