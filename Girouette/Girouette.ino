// Initialise la variable qui va recueillir la valeur du potentiomètre
int Pot; 

void setup() {
  Serial.begin(9600); //Initialise la communication entre le PC et Arduino
pinMode(A2, INPUT);
pinMode(A1,INPUT);
}
void loop() {
  // Lire la valeur du potentiomètre et la diviser par 1000 
  Pot = analogRead(A1)/10; 
  int BP = digitalRead(A2); 
/*
  //Affiche la valeur du potentiomètre sur le moniteur série
    Serial.print("Pot : ");  
    Serial.println(Pot);  
    Serial.print("Anemomètre : ");
    Serial.println(BP);
*/    

// Boucle permettant en foction de la valeur du potentiometre de renvoyer l'orientation de la Girouette
if (Pot == 50) {
  Serial.println("Nord Ouest");
}
else if (Pot == 53) { 
 Serial.println("Sud Ouest");
}
else if (Pot >= 54 && Pot <= 55) { 
 Serial.println("Nord Est");
}
else if (Pot == 56) { 
 Serial.println("Ouest");
}
else if (Pot == 58) { 
 Serial.println("Sud Est");
}
else if (Pot == 63) { 
 Serial.println("Sud");
}
else if (Pot == 59) { 
 Serial.println("Nord");
}
else if (Pot == 62) { 
 Serial.println("Est");
}
delay(1000);
}
