#include <SoftwareSerial.h>
#include <Servo.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

"""
L'objectif de ce code est de programmer l'ensemble des fonctionnalité necessaire au fonctionnement du capteur. 
Pour cela le code se divise en 2 grandes parties :
  - La première est la déclaration est l'attribution des variables (La partie setup)
  - La seconde est le rôle de chaque composant connecté (la partie loop)

Les composants programmés ici sont : 
  - Le module Bluetooth (BT dans la suite du code)
  - L'encodeur rotatoire
  - L'écran OLED
  - Le servo-moteur 
Il faut encore ajouter les modules suivants :

  - L'amplificateur transimpédance pour le capteur graphène
  - Le flex-sensor
"""
#define EncA 2 // Pin CLK encodeur
#define EncB 4 // Pin DT encordeur
#define Switch 5 // Switch connexion
#define rxPin 8// Broche utilisée pour la lecture des données BT
#define txPin 7// Broche utilisée pour l'écriture des données BT

#define PixLength  128 // Taille de OLED en longueur
#define PixWidth  64 // Taille de OLED en Largeur
#define brocheResetOLED  -1 // Broche reset OLED
#define AdressI2COLED 0x3C // Adresse Protocole O2C OLED
#define baudrate 9600


"""BT Mod"""
SoftwareSerial mySerial(rxPin, txPin);

"""Encodeur Mod"""
volatile unsigned int Enc0Pos = 0;


"""OLED Screen Mod"""
Adafruit_SSD1306 OLED(PixLength, PixWidth, &Wire, brocheResetOLED);

"""Servo-moteur Mod"""
Servo myServo;
init pos = 0;






void setup() {
  // put your setup code here, to run once:


"""BT Mod"""
pinMode(rxPin, INPUT);
pinMode (txPin, OUTPUT);
mySerial.begin(baudrate);
Serial.begin(baudrate);
Serial.println("start")

"""Encodeur Mod"""

pinMode(EncA, INPUT);
digitalWrite(EncA, HIGH)
pinMode(EncB, INPUT);
digitalWrite(EncB, HIGH)
attachInterrupt(0, doEncoder, RISING);
"""OLED Screen Mod"""
if(!OLED.begin(SSD1306_SWITCHCAPVCC, AdressI2COLED))
while(1);

//****************************************************
// Affichage de 3 écrans successifs, x1, x2, x3
//****************************************************
for(byte tailleCaractere = 1; tailleCaractere <=3, tailleCaractere++){
  boolean bCouleurInverse = false;
  OLED.clearDisplay();
  OLED.setTextSize(tailleCaractere);
  OLED.setCursor(0,0);

//****************************************************
// Affichage de 8 lignes dans chaque ecran successif
//****************************************************
  for(byte nbLigne = 1; nbLigne<=8; nbLigne++){
    if(bCouleurInvese)
      OLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
      else
        OLED.setTextColor(SSD1306_WHITE);
      OLED.print("Ligne :");
      OLED.println(nbLigne);
      bCouleurInverse = !bCouleurInverse;
  }
  OLED.display();
  delay(2000);
}

"""Servo-moteur Mod"""
myServo.attach(12); // Pin connectée pour le servo-moteur
}







void loop() {
  // put your main code here, to run repeatedly:
"""BT Mod"""
int i = 0;
char someChar[32] = {0};
while(Serial.avaible()){
  do{
    someChar[i++] = Serial.read();
    delay(3);
  }while(Serial.avaible()>0)
  mySerial.println(someChar);
  Serial.println(someChar);
}while(mySerial.available()){
  Serial.print((char)mySerial.read());
}

"""Encodeur Mod"""
Serial.print("Position : ");
Serial.println(Enc0Pos, DEC)

"""Servo Mod"""
for(pos = 0; pos<180; pos+=1){
  myServo.write(pos);
  delay(15);
}
for(pos = 180;pos>=1; pos-= 1){
  myServo.write(pos);
  delay(15);
}
}



"""Position de l'encodeur rotatoire"""
void doEncoder(){
  if(digitalRead(EncB)==HIGH){
    Enc0Pos++;
  }else{
    Enc0Pos--;
  }
}
