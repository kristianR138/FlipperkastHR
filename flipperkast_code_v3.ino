#include <Servo.h>
#include <LiquidCrystal_I2C.h>
#include <math.h>

#define knopR 13
#define knopL 12

#define servoPinL 11
#define servoPinR 10

#define IRsensor 2


LiquidCrystal_I2C lcd(0x3F,20,4);

Servo servoL;
Servo servoR;

const int flipper_reach = 70; // flipperreach moet groter dan 0 en kleiner dan 100 anders gaan dingen kapot
int IRstate = HIGH;
int IRprestate = LOW;
unsigned int score = 0;
unsigned long gameStart;
int time;
float mult;
int CompleteScore = 0;
unsigned long DEATH_TIMEOUT = 5000;  // 5 seconds
unsigned long lastPress;

const int BTN_R = 0;
const int BTN_L = 1;
const int buttonPins[2] = {knopR, knopL};

//Een debouncer zodat de knopper niet onder lage stroom gaan ruisen
// een array van buttonstates omdat er twee knoppen zijn
int buttonState[2]            = {HIGH, HIGH};  //gedebouncde staat(hoog bij INPUT_PULLUP)
int lastButtonState[2]        = {HIGH, HIGH};  //een previous state die later verandered wordt
unsigned long lastDebounceTime[2] = {0, 0};
const unsigned long debounceDelay = 20;        //de cooldown tusser knopdrukken

// deze code runt 2 keer 1 keer per knop
void updateButtons() {
  for (int i = 0; i < 2; i++) {
    int reading = digitalRead(buttonPins[i]);

    // als de knop gedrukt(ruis of niet) dan wordt de tijd van de verandering genoteerd
    if (reading != lastButtonState[i]) {
      lastDebounceTime[i] = millis();
    }

    // als de knop langer dan de debounceDelay ingedrukt is is het input geaccepteerd
    if ((millis() - lastDebounceTime[i]) > debounceDelay) {
      if (reading != buttonState[i]) {
        buttonState[i] = reading;
      }
    }
    // zet de prestate
    lastButtonState[i] = reading;
  }
}
// deze code zorgt ervoor dat er alleen maar een flipper per keer actief is
// dit is gedaan door power issues, dit volgt nogsteeds de requirements

int activeButton = -1;        // -1 = geen button, 1 = BTN_R, 2 = BTN_L
bool rPressed = false;        // effective states, after the lockout
bool lPressed = false;

void updateLockout() {
  // the active button was released: free the lock
  if (activeButton != -1 && buttonState[activeButton] == HIGH) {
    activeButton = -1;
  }

  // nobody holds the lock: the first pressed button takes it
  if (activeButton == -1) {
    if (buttonState[BTN_R] == LOW) {
      activeButton = BTN_R;
    }
    else if (buttonState[BTN_L] == LOW) {
      activeButton = BTN_L;
    }
  }
  // Dit wordt gebruikt inplaatsvan digitalRead(KNOP)
  // deze variablen zijn gedebounced en elkaar uitsluitend
  rPressed = (activeButton == BTN_R);
  lPressed = (activeButton == BTN_L);
}

// displayt de score
void displayScore(int score) {
  lcd.setCursor(6,0);
  lcd.print(score);
}

// displayt de tijd en de multiplicator die de score vergroot
// multi vergroot met 0.5 elke 20 sec tot 10x

void displayTime() {
  // als de tijd minder dan 999s is vergroot de tijd
  if (time < 999){
    time = (millis() - gameStart) / 1000;
    lcd.setCursor(13,1);
    lcd.print(time);
    //Serial.print(time);
  }
  // multipliceert de score met het mult
  // dit vond ik leuk om toe te voegen
  mult = min(1 + (time / 20) * 0.5, 10);
  lcd.setCursor(12, 0);
  lcd.print(mult, 1); 
}

void setup(){

  //cheatmode voor inf leven
  //DEATH_TIMEOUT = 99999999999999999; 
  
  //general setup

  pinMode(knopR, INPUT_PULLUP);
  pinMode(knopL, INPUT_PULLUP);
  Serial.begin(9600);
  servoL.attach(servoPinL);
  servoR.attach(servoPinR);
  
  //lcd setup 

  lcd.init();
  lcd.begin(16, 2);
  lcd.backlight();

  //startup dialoog

  lcd.setCursor(0,0);
  lcd.print("Welkom in de");
  lcd.setCursor(0,1);
  lcd.print("Flipper Casino!");
  delay(5000);
  lcd.clear();
  //deze is wat langer doordat er 17 characters per lijn zijn
  lcd.setCursor(0,0);
  lcd.print("Blijf de flippers");
  delay(750);
  lcd.setCursor(0,0);
  lcd.print("lijf de flippers");
  delay(750);
  lcd.setCursor(0,1);
  lcd.print("drukken of anders");
  delay(750);
  lcd.setCursor(0,1);
  lcd.print("rukken of anders");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("verlies je");
  lcd.setCursor(0,1);
  lcd.print("en ga je dood!");
  delay(5000);
  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("Score:"); // lcdsetCursor 6 om de score te printen op de goeie plek
  lcd.print(0);
  lcd.setCursor(0,1);
  lcd.print("Time elapsed:"); // lcdsetCursor 13 om de score te printen op de goeie plek
  lcd.setCursor(11, 0);
  lcd.print("X");


  servoL.write(0);                 //naar startplek
  servoR.write(flipper_reach);     //naar startplek(mirrored)
  
  //timer setup
  //de gametimer is na het inladen begonnen

  gameStart = millis();
  lastPress = millis();
}

void loop() {
  //de game loop
  while (1){
    //Update de knopvalues
    updateButtons();
    updateLockout();

    // death timer
    // deze manier van death detectie is ervoor gekozen omdat ik er geen zin in had/geen tijd had
    if (rPressed || lPressed) {
      lastPress = millis();
    }
    if (millis() - lastPress >= DEATH_TIMEOUT) {
      break;
      //YOU DIED
    }
    //doet de flipper bewegen als de knoppen gedrukt zijn
    //en terug naar zijn originele plek als ze niet gedrukt zijn
    switch (rPressed) {
      case 0:
        servoR.write(flipper_reach);
        //delay(100 * flipper_reach / 60); optionele delay
        //Serial.print("ButtonR: ");
        //Serial.print(buttonState[BTN_R]);
        break;
      case 1:
        servoR.write(0);
        //Serial.print("ButtonR: ");
        //Serial.print(buttonState[BTN_R]);
        break;
    }
    // deze is anderso, omdat de flipper ook andersom zit
    switch (lPressed) {
      case 1:
        servoL.write(flipper_reach);
        //delay(100 * flipper_reach / 60); optioneel
        //Serial.print("ButtonL: ");
        //Serial.println(buttonState[BTN_L]);
        break;
      case 0:
        servoL.write(0);
        //Serial.print("ButtonL: ");
        //Serial.println(buttonState[BTN_L]);
        break;
    }
    // de IR sensor code (met previous states) met score berekening
    IRstate = digitalRead(IRsensor);

    if (IRstate == 0 && IRstate != IRprestate) {
      //Serial.println("adding 1 to score");
      score++;
      delay(100);
      CompleteScore += score * 10 * mult;
      displayScore(CompleteScore);
    }
    IRprestate = IRstate;
    // elke run doet de code time displayen
    //Serial.print(" score: ");
    //Serial.println(score);
    displayTime();
  }
  // deze code runt als je doodgaat
  servoL.write(0);                 // terug naar startplek
  servoR.write(flipper_reach);     // terug naar startplek(mirrored)
  // eindedialoog
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Je bent dood!");
  lcd.setCursor(0, 1);
  lcd.print("Score:");
  lcd.print(CompleteScore);
  //sturen naar de server
  //naam
  Serial.print("Kristian");
  Serial.print(",");
  //score
  Serial.print(CompleteScore);
  Serial.print(",");
  //machine_id
  Serial.println("TIklas1C");
  delay(5000);

  lcd.setCursor(0,0);
  lcd.print("Druk een knop");
  lcd.setCursor(0,1);
  // als er iemand weggaat en iemand later pas komt staat het spel klaar
  if (CompleteScore == 0) {
    lcd.print("om te beginnen!");
  } else {
    lcd.print("Volgende speler!");
  }
  while (digitalRead(knopR) == HIGH && digitalRead(knopL) == HIGH) {}  // wachten tot een knopdruk(met ruis)
  asm volatile ("jmp 0");          // software reset
}