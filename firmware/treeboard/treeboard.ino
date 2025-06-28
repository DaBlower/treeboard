int BUT1 = D0;
int BUT2 = D1;
int BUT3 = D10;
int BUT4 = D9;
int buttons[4] = {BUT1, BUT2, BUT3, BUT4};

int LED1 = D3;
int LED2 = D4;
int LED3 = D6;
int LED4 = D5;
int leds[4] = {LED1, LED2, LED3, LED4};

int pattern[10];
int currentStep = 0;

void reaction();
void duel();
void memoryGame();
void ledsOff();

void setup() {
  pinMode(BUT1, INPUT);
  pinMode(BUT2, INPUT);
  pinMode(BUT3, INPUT);
  pinMode(BUT4, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  if (digitalRead(BUT1) == HIGH){
    unsigned long pressedTime = millis();
    int currentLed = 0;
    while (digitalRead(BUT1) == HIGH){
      if (millis() - pressedTime >= 750){
        if (currentLed > 3){
          ledsOff();
          reaction();
          break;
        }
        digitalWrite(leds[currentLed], HIGH);
        currentLed++;
        pressedTime = millis();
      }
    }
  }
  if (digitalRead(BUT2) == HIGH){
    unsigned long pressedTime = millis();
    int currentLed = 0;
    while (digitalRead(BUT2) == HIGH){
      if (millis() - pressedTime >= 750){
        if (currentLed > 3){
          ledsOff();
          memoryGame();
          break;
        }
        digitalWrite(leds[currentLed], HIGH);
        currentLed++;
        pressedTime = millis();
      }
    }
  }
  if (digitalRead(BUT3) == HIGH){
    unsigned long pressedTime = millis();
    int currentLed = 0;
    while (digitalRead(BUT3) == HIGH){
      if (millis() - pressedTime >= 750){
        if (currentLed > 3){
          ledsOff();
          duel();
          break;
        }
        digitalWrite(leds[currentLed], HIGH);
        currentLed++;
        pressedTime = millis();
      }
    }
  }

}

void ledsOff() {
  for (int i=0; i < 4; i++){
    digitalWrite(leds[i], LOW);
  }
}

void reaction() {
  randomSeed(analogRead(A2));
  int randPin = random(4);
  int randTime = random(500,5000);
  delay(randTime);
  digitalWrite(leds[randPin], HIGH);
  long startTime = millis(); // what time did the led turn on?
  bool pressed = false;
  while (abs(millis()-startTime) > 10000)){
    for (int i=0;i<4;i++){
      if (digitalRead(buttons[i]) == HIGH){ // are one of the buttons pressed
        break; // exit the for loop
      }
    }
  }
  digitalWrite(leds[randPin], LOW);
}

void duel(){
  randomSeed(analogRead(A2));
  const int maxScore = 5;
  int p1Score = 0;
  int p2Score = 0;
  int rightLeds[2] = {LED1, LED2};
  int leftLeds[2] = {LED3, LED4};
  while (p2Score < maxScore && p1Score < maxScore){
    int randIndex = random(2);
    delay(random(1000,4000));

    digitalWrite(rightLeds[randIndex], HIGH);
    digitalWrite(leftLeds[randIndex], HIGH);

    int winner = waitForButton(randIndex);

    digitalWrite(rightLeds[randIndex], LOW);
    digitalWrite(leftLeds[randIndex], LOW);

    if (winner == 1) p1Score++;
    else if (winner == 2) p2Score++;

    delay(500);
  }
  if (p1Score == maxScore) flashLeds(LED1, LED2);
  else flashLeds(LED3, LED4);

}

int flashLeds(L1, L2){
  for (int i = 0; i < 6; i++) {
    digitalWrite(L1, HIGH);
    digitalWrite(L2, HIGH);
    delay(200);
    digitalWrite(L1, LOW);
    digitalWrite(L2, LOW);
    delay(200);
  }
}


int waitForButton(int expected){
  while (true) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttons[i]) == HIGH) {
        while (digitalRead(buttons[i]) == HIGH);  // wait for release
        delay(20);  // debounce

        if (i == expected || i == expected + 2) {
          return (i < 2) ? 1 : 2;  // buttons 0–1 → P1, 2–3 → P2
        } 
      }
    }
  }
}

void memoryGame(){
  currentStep = 1;
  while (true){
    generatePattern(); // create the pattern
    showPattern(); // show the pattern
    if (!getPlayerInput()){ // check if player failed
      failFeedback();
      break;
    }
    winFeedback();
    currentStep++; // increase difficulty
    delay(1000);
  }
}

void generatePattern(){
  randomSeed(analogRead(A2));
  for (int i = 0; i < currentStep; i++){
    pattern[i] = random(4);
  }
}

void showPattern(){
  for (int i = 0; i < currentStep; i++){
    int led = pattern[i];
    digitalWrite(leds[led], HIGH);
    delay(500);
    digitalWrite(leds[led], LOW);
    delay(250);
  }
}

bool getPlayerInput(){
  for (int i = 0; i < currentStep; i++){
    int expected = pattern[i];
    int pressed = waitForButtonPress();
    if (pressed != expected){
      return false;
    }
  }
  return true;
}

int waitForButtonPress(){
  while (true){
    for (int i = 0; i < 4; i++){
      if (digitalRead(buttons[i]) == HIGH){
        while (digitalRead(buttons[i]) == HIGH); // wait until button is released
        delay(50);
        return i;
      }
    }
  }
}

void failFeedback(){
  for (int i = 0; i < 2; i++){
    for (int j = 0; j < 4; j++){
      digitalWrite(leds[j], HIGH);
    }
    delay(150);
    for (int j = 0; j < 4; j++){
      digitalWrite(leds[j], LOW);
    }
    delay(150);
  }
}

void winFeedback(){
  for (int i = 0; i < 4; i++){
    digitalWrite(leds[i], HIGH);
    delay(150);
    digitalWrite(leds[i], LOW);
  }
}