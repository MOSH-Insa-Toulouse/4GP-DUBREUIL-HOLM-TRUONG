#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C  // Adresse I2C de l'écran OLED



// Initialisation des différents composants
Adafruit_SSD1306 ecranOLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET); // Initialisation de l'écran OLED
Servo myservo; // Initialisation du servo-moteur
int pos = 90;
bool servoIsMoving = false; // État du mouvement du servo
unsigned long movestartTime = 0; // Temps de début du mouvement
const unsigned long moveDuration = 3000; // Durée du mouvement en millisecondes
int TargetPos = pos; // Position cible du servo
// Broches de connexion de l'encodeur
#define encoder0PinA  2  // CLK
#define encoder0PinB  4  // DT
#define ENCODER_SW    5  // bouton-poussoir

// Pin pour capteur graphène
#define GraphenePin A0 // Pin analogique pour le capteur de graphène

// Broches du MCP42100
const byte csPin           = 10;      // MCP42100 chip select pin
const int  maxPositions    = 256;     // Wiper can move from 0 to 255 = 256 positions
const long rAB             = 92500;   // 100k pot resistance between terminals A and B
const byte rWiper          = 125;     // 125 ohms pot wiper resistance
const byte pot0            = 0x11;    // Pot0 addr



// Liste des éléments du menu
String menuItems[] = { "Resistance R2", "Servo-moteur" };
int menuIndex = 0;            // Index du menu actuel

// Sous-menu pour le servo-moteur
String menuItemsServo[] = { "Pousser", "Tirer", "Retour" };
int menuIndexServo = 0; // Index du sous-menu servo
bool inSubMenuServo = false; // État du sous-menu servo

// Variables pour l'encodeur
int encoder0Pos = 0;          // Valeur de l'encodeur
bool adjustingResistance = false;  // État de l'ajustement de la résistance
bool buttonPressed = false;   // Variable pour vérifier l'état du bouton
 // État du sous-menu servo

// Ajout des différentes fonctions 

void showMenu() {

  /** 
   * @brief Affiche le menu principal sur l'écran OLED. Assure aussi l'affichage de la resistance lié à l'encordeur
   * @param None
   * @return Aucun
   **/
  ecranOLED.clearDisplay();  // Effacer l'écran avant de redessiner

  for (int i = 0; i < 2; i++) {
    if (i == menuIndex) {
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);  // Élément sélectionné (inverser les couleurs)
    } else {
      ecranOLED.setTextColor(SSD1306_WHITE);
    }

    ecranOLED.setCursor(10, 10 + (i * 20));
    ecranOLED.println(menuItems[i]);
  }

 // Afficher la valeur de la résistance si nous sommes en mode de réglage
  if (adjustingResistance) {
    ecranOLED.clearDisplay();
    ecranOLED.setCursor(10, 50);
    ecranOLED.print("R: ");
    long resistanceWB = ((rAB * encoder0Pos) / maxPositions) + rWiper;
    ecranOLED.print(resistanceWB);
    ecranOLED.println(" ohms");
  }

  ecranOLED.display();  // Afficher le contenu sur l'écran
}

void showServoMenu(){
  /**
   * @brief Affiche le sous-menu du servo-moteur sur l'écran OLED.
   * @param None
   * @return Aucun
   **/
ecranOLED.clearDisplay();
for(int i  = 0; i < 3; i++){
    if(i == menuIndexServo){
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }else{
      ecranOLED.setTextColor(SSD1306_WHITE);
    }
    ecranOLED.setCursor(10, 10 + (i * 20));
    ecranOLED.println(menuItemsServo[i]);
  }
  ecranOLED.display();

}
// Fonction pour ajuster la valeur du potentiomètre
void setPotWiper(int addr, int pos) {
  digitalWrite(csPin, LOW);
  SPI.transfer(addr); // Envoyer l'adresse du potentiomètre
  SPI.transfer(pos);   // Envoyer la valeur du balai
  digitalWrite(csPin, HIGH);
}


void navigateMenu(int &index, int maxIndex, void(*UpdateDisplay)()) {

/** 
 * @brief Gère la navigation dans le menu à l'aide de l'encodeur rotatif.
 * @param index : Référence à l'index du menu actuel
 * @param maxIndex : Nombre maximum d'éléments dans le menu
 * @param UpdateDisplay : Pointeur vers la fonction de mise à jour de l'affichage
 * @return Aucun
 **/
  // Vérifier la rotation de l'encodeur
  if (digitalRead(encoder0PinA) == LOW && digitalRead(encoder0PinB) == HIGH) {
    index = (index + 1) % maxIndex; // Passer à l'élément suivant du menu
    UpdateDisplay();   // Mettre à jour l'écran OLED
    delay(200);  
  }

  if (digitalRead(encoder0PinA) == HIGH && digitalRead(encoder0PinB) == LOW) {
    index = (index - 1 + maxIndex) % maxIndex; // Passer à l'élément précédent du menu
    UpdateDisplay();  // Mettre à jour l'écran OLED
    delay(200); 
  }

  if (digitalRead(encoder0PinA) == LOW && digitalRead(encoder0PinB) == HIGH) {
    index = (index + 1) % maxIndex; // Passer à l'élément suivant du menu
    UpdateDisplay();   // Mettre à jour l'écran OLED
    delay(200);  
  }

  if (digitalRead(encoder0PinA) == HIGH && digitalRead(encoder0PinB) == LOW) {
    index = (index - 1 + maxIndex) % maxIndex; // Passer à l'élément précédent du menu
    UpdateDisplay();  // Mettre à jour l'écran OLED
    delay(200); 
  }

}
void afficherAction(String action){
  /**
   * @brief Affiche une action en cours sur l'écran OLED.
   * @param action : Action à afficher
   * @return Aucun
   **/

  ecranOLED.clearDisplay();
  ecranOLED.setCursor(10, 10);
  ecranOLED.print("En cours");
  ecranOLED.display();
  delay(1000);
}

void TriggerServoMovement(int angle){
  /**
   * @brief Déclenche le mouvement du servo-moteur vers un angle cible.
   * @param angle : Angle cible pour le servo-moteur
   * @return Aucun
   */
  if(!servoIsMoving){
    TargetPos = angle; // Mettre à jour la position cible
    myservo.write(TargetPos); // Déplacer le servo vers la position cible
    movestartTime = millis(); // Enregistrer le temps de début du mouvement
    servoIsMoving = true; // Marquer que le servo est en mouvement
  }
}

void measure(){
  /**
   * @brief Mesure la résistance à l'aide du capteur de graphène.
   * @param Aucun
   * @return Aucun
   **/
  Serial.println("Mesure en cours...");
  int sensorValue = analogRead(GraphenePin); // Lire la valeur du capteur
  float voltage = sensorValue * (5.0 / 1023.0); // Convertir la valeur en tension
  float resistance = (voltage * rAB) / (5.0 - voltage); // Calculer la résistance
  Serial.print("Résistance mesurée: ");
  Serial.print(resistance);
  Serial.println(" ohms");
  delay(1000); // Attendre avant la prochaine mesure
}
void setup() {
  Serial.begin(9600);

  pinMode(csPin, OUTPUT);           // Configure chip select as output
  pinMode(encoder0PinA, INPUT_PULLUP);
  pinMode(encoder0PinB, INPUT_PULLUP);
  pinMode(ENCODER_SW, INPUT_PULLUP);
  //attachInterrupt(0,doEncoder, RISING); // Interruption sur le changement d'état de l'encodeur
  // Initialiser le SPI
  digitalWrite(csPin, HIGH);        // Chip select default to de-selected
  SPI.begin();

  //Initialiser l'écran OLED
  if (!ecranOLED.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("OLED not found"));
    while (1);
  }

  ecranOLED.clearDisplay();
  ecranOLED.setTextSize(1);
  ecranOLED.setTextColor(SSD1306_WHITE);
  showMenu(); // Afficher le menu initial

  myservo.attach(9); // Attacher le servo à la broche 9
}

void loop() {
  // Vérifier si le bouton est enfoncé
  if (digitalRead(ENCODER_SW) == LOW && !buttonPressed) {
    buttonPressed = true;  // Marquer que le bouton a été enfoncé
  
  if (inSubMenuServo){

    if(menuIndexServo==0){
      afficherAction("Pousser");
    TriggerServoMovement(180); // Déplacer le servo à 180 degrés
      delay(500);
      measure(); // Mesurer la résistance
      delay(500);
      showServoMenu(); // Afficher le sous-menu du servo-moteur
    }else if(menuIndexServo==1){
     afficherAction("Tirer");
     TriggerServoMovement(1); // Déplacer le servo à 0 degrés
     measure(); // Mesurer la résistance
     delay(500);
      showServoMenu(); // Afficher le sous-menu du servo-moteur
     // Afficher le sous-menu du servo-moteur
    }else if(menuIndexServo==2){
      inSubMenuServo = false; // Quitter le sous-menu
      showMenu(); // Afficher le menu principal
    }
  }else if (menuIndex == 0) {
    // Activer/désactiver le mode de réglage de la résistance
    adjustingResistance = !adjustingResistance;
    if (adjustingResistance) {
      Serial.println("Réglage de la résistance...");
    } else {
      Serial.println("Sortie du mode de réglage de la résistance...");
    }
    showMenu();  // Mettre à jour l'écran immédiatement après avoir appuyé sur le bouton
  } else if(menuIndex==1){
    inSubMenuServo = true; // Passer au sous-menu du servo-moteur
    menuIndexServo = 0;
    showServoMenu(); // Afficher le sous-menu du servo-moteur
  }
  delay(300);  // Anti-rebond pour le bouton
  }

   // Réinitialiser l'état du bouton lorsqu'il est relâché
  if (digitalRead(ENCODER_SW) == HIGH) {
    buttonPressed = false;
  }

  if(!adjustingResistance && !inSubMenuServo){
    navigateMenu(menuIndex, 2, showMenu); // Naviguer dans le menu principal
  }
  if(inSubMenuServo){
    navigateMenu(menuIndexServo, 3, showServoMenu); // Naviguer dans le sous-menu du servo-moteur
  }

// Ajustement de la résistance avec l’encodeur
if (adjustingResistance && !servoIsMoving) {
  if (digitalRead(encoder0PinA) == LOW && digitalRead(encoder0PinB) == HIGH) {
    encoder0Pos = constrain(encoder0Pos + 1, 0, 255);
    setPotWiper(pot0, encoder0Pos);
    showMenu();  // Afficher la nouvelle valeur sur l'écran
    delay(200);
  }

  if (digitalRead(encoder0PinA) == HIGH && digitalRead(encoder0PinB) == LOW) {
    encoder0Pos = constrain(encoder0Pos - 1, 0, 255);
    setPotWiper(pot0, encoder0Pos);
    showMenu();  // Afficher la nouvelle valeur sur l'écran
    delay(200);
  }
}
if(servoIsMoving){
  if(millis()-movestartTime >= moveDuration){
    myservo.write(pos); // Ramener le servo à la position initiale
    servoIsMoving = false; // Arrêter le mouvement du servo
   }
}

}


