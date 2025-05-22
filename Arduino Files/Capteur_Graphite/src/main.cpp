#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1
#define SCREEN_ADDRESS 0x3C  // Adresse I2C de l'écran OLED
#define MAX_MESURE 10

enum MenuState{MAIN_MENU, SERVO_MENU, ANGLE_MENU};
MenuState currentMenu = MAIN_MENU;
unsigned long lastEncoderUpdate = 0;
const int ENCODER_STEP_DELAY = 150; // Délai entre chaque pas de l'encodeur
int lastEncoderPos = 0;

struct mesure{
  int angle;
  int valBrute;
  float resistance;
};

mesure mesures[MAX_MESURE];
int currentMesure = 0;
bool finMesure = false;

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


//--------------------- Les Menus --------------------------------//

// Liste des éléments du menu principal
const char* menuItems[] = { "Resistance R2", "Servo-moteur" };
int menuIndex = 0;            // Index du menu actuel

// Sous-menu pour le servo-moteur
const char* menuItemsServo[] = { "Tirer", "Pousser", "Retour" };
int menuIndexServo = 0; // Index du sous-menu servo


const char* menuItemsAngle[] = { "Angle 30°", "Angle 45°", "Angle 60", "Angle 90", "Retour" };
int menuIndexAngle = 0; // Index du sous-menu angle

int SelectedDirection = 0; // Pousser ou Tirer


// Variables pour l'encodeur
int encoder0Pos = 0;          // Valeur de l'encodeur
bool adjustingResistance = false;  // État de l'ajustement de la résistance
bool buttonPressed = false;   // Variable pour vérifier l'état du bouton
 // État du sous-menu servo

// Ajout des différentes fonctions 

void showMenu() {
  static int lastIndex = -1;
  static bool lastAdjustState = false;
  
  if(menuIndex == lastIndex && adjustingResistance == lastAdjustState) return;

  ecranOLED.clearDisplay();

  if(adjustingResistance) {
    // Afficher seulement la résistance
    ecranOLED.setCursor(10, 10);
    ecranOLED.print("R: ");
    long resistanceWB = ((rAB * encoder0Pos) / maxPositions) + rWiper;
    ecranOLED.print(resistanceWB);
    ecranOLED.println(" ohms");
  }
  else {
    // Afficher le menu normal
    for (int i = 0; i < 2; i++) {
      ecranOLED.setTextColor(i == menuIndex ? SSD1306_BLACK : SSD1306_WHITE, 
                            i == menuIndex ? SSD1306_WHITE : SSD1306_BLACK);
      ecranOLED.setCursor(10, 10 + (i * 20));
      ecranOLED.println(menuItems[i]);
    }
  }

  ecranOLED.display();
  lastIndex = menuIndex;
  lastAdjustState = adjustingResistance;
}
// Affichage menu servo-moteur
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
// Affichage du menu pour choix de l'angle
void showAngleMenu(){
  /**
   * @brief Affiche le sous-menu de sélection de l'angle sur l'écran OLED
   * @param None
   * @return aucun
   **/
  ecranOLED.clearDisplay();
  for(int i = 0; i < 5; i++){
    if(i == menuIndexAngle){
      ecranOLED.setTextColor(SSD1306_BLACK, SSD1306_WHITE);
    }else{
      ecranOLED.setTextColor(SSD1306_WHITE);
    }
    ecranOLED.setCursor(10, 10+(i*12));
    ecranOLED.println(menuItemsAngle[i]);
  }
  ecranOLED.display();
}

void setPotWiper(int addr, int pos) {
  digitalWrite(csPin, LOW);
  SPI.transfer(addr); // Envoyer l'adresse du potentiomètre
  SPI.transfer(pos);   // Envoyer la valeur du balai
  digitalWrite(csPin, HIGH);
}



int selectedAngle = 30;

void executeServoAction(){
  int angles[] = {30, 45, 60, 90};
  int baseAngle = angles[menuIndexAngle];

  int targetAngle = (SelectedDirection==0) ? 90-baseAngle : 90+baseAngle;
  targetAngle = constrain(targetAngle, 0, 180);
  myservo.write(targetAngle);
 delay(1000);
  // Mesure 1 s

  unsigned long debutMesure = millis();
  int samples = 0;
  long sumRaw = 0;

  while(millis()-debutMesure<1000){
    int raw = analogRead(GraphenePin);
    sumRaw +=raw;
    samples++;
    delay(10);
  }

  // Sauvegarde résultats

  mesures[currentMesure].angle = baseAngle;
  mesures[currentMesure].valBrute = sumRaw/samples;
  mesures[currentMesure].resistance = ((5.0*rAB)/(1023.0/(sumRaw/samples)))-rAB;

  // Envoie des données au format csv
  Serial.print("Angle :");
  Serial.print(baseAngle);
  Serial.print(", Direction : ");
  Serial.print(SelectedDirection==0 ? "Tirer" : "Pousser");
  Serial.print(", Valeur brute :");
  Serial.print(mesures[currentMesure].valBrute);
  Serial.print(", Resistance :");
  Serial.println(mesures[currentMesure].resistance);

  currentMesure = (currentMesure+1)%MAX_MESURE;

  // Retour position initiale

  myservo.write(90);
  servoIsMoving = true;
  movestartTime = millis();
  delay(500);  
  if(menuIndexAngle>=4) return;
}


void handleEncoderRotation() {
  if (millis() - lastEncoderUpdate < ENCODER_STEP_DELAY) return;

  int encoderDelta = 0;
  int currentStateA = digitalRead(encoder0PinA);
  int currentStateB = digitalRead(encoder0PinB);
  
  static int previousStateA = HIGH;
  if (previousStateA != currentStateA && currentStateA == LOW) {
    encoderDelta = (currentStateB == LOW) ? -1 : 1;
  }
  previousStateA = currentStateA;

  if (encoderDelta != 0) {
    lastEncoderUpdate = millis();
    
    if (adjustingResistance) {
      encoder0Pos = constrain(encoder0Pos + encoderDelta, 0, 255);
      setPotWiper(pot0, encoder0Pos);
      showMenu();
    } else {
      switch(currentMenu) {
        case MAIN_MENU:
          menuIndex = constrain(menuIndex + encoderDelta, 0, 1);
          showMenu();
          break;
          
        case SERVO_MENU:
          menuIndexServo = constrain(menuIndexServo + encoderDelta, 0, 2);
          showServoMenu();
          break;
          
        case ANGLE_MENU:
          menuIndexAngle = constrain(menuIndexAngle + encoderDelta, 0, 4);
          showAngleMenu();
          break;
      }
    }
  }
}


void handleMenuSelection() {
  switch (currentMenu) {
    case MAIN_MENU:
      if (menuIndex == 0) {
        adjustingResistance = !adjustingResistance;
        if (!adjustingResistance) showMenu(); // Rafraîchir seulement si on sort du mode réglage
      } else {
        currentMenu = SERVO_MENU;
        menuIndexServo = 0; // Réinitialiser la sélection servo
        showServoMenu();
      }
      break;

  case SERVO_MENU:
    if(menuIndexServo==2){
      currentMenu =MAIN_MENU;
      showMenu();
    }else{
      SelectedDirection = menuIndexServo;
      currentMenu = ANGLE_MENU;
      showAngleMenu();
    }
      break;
    case ANGLE_MENU:
    if(menuIndexAngle==4){
      currentMenu = SERVO_MENU;
      showServoMenu();
    }else{
      executeServoAction();
      currentMenu = ANGLE_MENU;
      showAngleMenu();
    }
    break;

    
  
  default:
    break;
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
  delay(300);
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
  delay(300); // Attendre avant la prochaine mesure
}

void testCapteurGraphite() {
  // 1. Lire la valeur analogique brute
  int valeurBrute = analogRead(GraphenePin);
  
  // 2. Calculer la tension (pour info)
  float tension = valeurBrute * (5.0 / 1023.0);
  
  // 3. Afficher les résultats
  Serial.print("Valeur brute: ");
  Serial.print(valeurBrute);
  Serial.print(" | Tension: ");
  Serial.print(tension);
  Serial.println("V");
  
  // Petit délai pour lisibilité
  delay(500);
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
    buttonPressed = true;
    handleMenuSelection();
    delay(150);
    }  // Marquer que le bouton a été enfoncé
   
   // Réinitialiser l'état du bouton lorsqu'il est relâché
  if (digitalRead(ENCODER_SW) == HIGH) {
    buttonPressed = false;
  }
  //---------- Navigation dans les menus
 handleEncoderRotation();
 
// Ajustement de la résistance avec l’encodeur
if (adjustingResistance && !servoIsMoving) {
  if (digitalRead(encoder0PinA) == LOW && digitalRead(encoder0PinB) == HIGH) {
    encoder0Pos = constrain(encoder0Pos + 1, 0, 255);
    setPotWiper(pot0, encoder0Pos);
    showMenu();  // Afficher la nouvelle valeur sur l'écran
  }

  if (digitalRead(encoder0PinA) == HIGH && digitalRead(encoder0PinB) == LOW) {
    encoder0Pos = constrain(encoder0Pos - 1, 0, 255);
    setPotWiper(pot0, encoder0Pos);
    showMenu();  // Afficher la nouvelle valeur sur l'écran
  }
}
}


