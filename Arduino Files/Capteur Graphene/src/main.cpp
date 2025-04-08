#include "Arduino.h"
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <Servo.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C  // Adresse I2C de l'écran OLED
#define txPin 7 // Pin d'écriture du module BT
#define rxPin 8 // Pin de lecture du module BT


// Initialisation de l'écran OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
// Définition du software serial pour le BT
SoftwareSerial mySerial(rxPin, txPin);
// Initialisation du servo-moteur
Servo myServo;
int pos = 0;
// Broches de connexion de l'encodeur
#define encoder0PinA  2  // CLK
#define encoder0PinB  4  // DT
#define ENCODER_SW    5  // bouton-poussoir

// Broches du MCP42100
const byte csPin           = 10;      // MCP42100 chip select pin
const int  maxPositions    =256;     // Wiper can move from 0 to 255 = 256 positions
const long rAB             = 46000;   // 100k pot resistance between terminals A and B
const byte rWiper          = 125;     // 125 ohms pot wiper resistance
const byte pot0            = 0x11;    // Pot0 addr

// Variables pour l'encodeur
int encoder0Pos = 0;          // Valeur de l'encodeur
int menuIndex = 0;            // Index du menu actuel
bool adjustingResistance = false;  // État de l'ajustement de la résistance
bool buttonPressed = false;   // Variable pour vérifier l'état du bouton

// Liste des éléments du menu
String menuItems[] = { "Resistance R2", "Option 2", "Option 3" };

// Fonction pour afficher le menu sur l'écran OLED
void showMenu() {
  display.clearDisplay();  // Effacer l'écran avant de redessiner

  for (int i = 0; i < 3; i++) {
    if (i == menuIndex) {
      display.setTextColor(SSD1306_BLACK, SSD1306_WHITE);  // Élément sélectionné (inverser les couleurs)
    } else {
      display.setTextColor(SSD1306_WHITE);
    }

    display.setCursor(10, 10 + (i * 20));
    display.println(menuItems[i]);
  }

 // Afficher la valeur de la résistance si nous sommes en mode de réglage
  if (adjustingResistance) {
    display.clearDisplay();
    display.setCursor(10, 50);
    display.print("R: ");
    long resistanceWB = ((rAB * encoder0Pos) / maxPositions) + rWiper;
    display.print(resistanceWB);
    display.println(" ohms");
  }

  display.display();  // Afficher le contenu sur l'écran
}

// Fonction pour ajuster la valeur du potentiomètre
void setPotWiper(int addr, int pos) {
  digitalWrite(csPin, LOW);
  SPI.transfer(addr); // Envoyer l'adresse du potentiomètre
  SPI.transfer(pos);   // Envoyer la valeur du balai
  digitalWrite(csPin, HIGH);
}

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);
  pinMode(csPin, OUTPUT);           // Configure chip select as output
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  myServo.attach(12);
  digitalWrite(csPin, HIGH);        // Chip select default to de-selected
  SPI.begin();

  //Initialiser l'écran OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED not found"));
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  showMenu(); // Afficher le menu initial
}

void loop() {
  // Vérifier si le bouton est enfoncé
  if (digitalRead(ENCODER_SW) == LOW && !buttonPressed) {
    buttonPressed = true;  // Marquer que le bouton a été enfoncé
    if (menuIndex == 0) {
      // Activer/désactiver le mode de réglage de la résistance
      adjustingResistance = !adjustingResistance;
      if (adjustingResistance) {
        Serial.println("Réglage de la résistance...");
      } else {
        Serial.println("Sortie du mode de réglage de la résistance...");
      }
      showMenu();  // Mettre à jour l'écran immédiatement après avoir appuyé sur le bouton
    }
    delay(300);  
  }

   // Réinitialiser l'état du bouton lorsqu'il est relâché
  if (digitalRead(ENCODER_SW) == HIGH) {
    buttonPressed = false;
  }

  // Vérifier le changement de sélection dans le menu
  if (!adjustingResistance) {
    if (digitalRead(encoder0PinA) == LOW && digitalRead(encoder0PinB) == HIGH) {
      menuIndex = (menuIndex + 1) % 3; // Passer à l'élément suivant du menu
      showMenu();   // Mettre à jour l'écran OLED
      delay(200);  
    }

    if (digitalRead(encoder0PinA) == HIGH && digitalRead(encoder0PinB) == LOW) {
      menuIndex = (menuIndex - 1 + 3) % 3; // Passer à l'élément précédent du menu
      showMenu();  // Mettre à jour l'écran OLED
      delay(200); 
    }
  }

 // Mettre à jour la valeur de la résistance lorsque nous sommes en mode de réglage
  if (adjustingResistance) {
    if (digitalRead(encoder0PinA) == LOW && digitalRead(encoder0PinB) == HIGH) {
      encoder0Pos = constrain(encoder0Pos + 1, 0, 255);
      setPotWiper(pot0, encoder0Pos);  // Mettre à jour la valeur de la résistance
      showMenu();  
      delay(200);
    }

    if (digitalRead(encoder0PinA) == HIGH && digitalRead(encoder0PinB) == LOW) {
      encoder0Pos = constrain(encoder0Pos - 1, 0, 255);
      setPotWiper(pot0, encoder0Pos);  // Mettre à jour la valeur de la résistance
      showMenu();  
      delay(200);
    }
  }

  // Fonction du module BT
  int i = 0;
  char someChar[32]={0};
  // when characters arrive over the Serial port

  while(Serial.available()){
    do{
      someChar[i++] = Serial.read();
      delay(3);
    }while(Serial.available()>0);
    mySerial.println(someChar);
    Serial.println(someChar);
  }
  while(mySerial.available()){
    Serial.print((char)mySerial.read());
  }

  // Fonction pour le Servo-moteur

  for(pos = 0;pos<180; pos+=1){  // Fait varier la position du servo moteur de 0 à 180°
    myServo.write(pos);
    delay(15);
  }

  for(pos =180;pos>=1;pos  -=1){ // Fait varier la position du servo moteur de 180° à 1
    myServo.write(pos);
    delay(15);
  }
}