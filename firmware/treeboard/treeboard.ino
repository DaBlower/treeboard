#define STARTUPcycles 3 // how many times does the startup loop?
#define idleTime 60000


// buttons from left to right, top to bottom
int BUT1 = D1;
int BUT2 = D9;
int BUT3 = D0;
int BUT4 = D10;
int buttons[4] = {BUT1, BUT2, BUT3, BUT4};

// Button layout (with LEDs at the top)
// 2 | 4
// 1 | 3

// LEDs from left to right, top to bottom
int LED1 = D4;
int LED2 = D5;
int LED3 = D3;
int LED4 = D6;
int leds[4] = {LED1, LED2, LED3, LED4};
int startupLeds[4] = {LED1, LED2, LED4, LED3};

// LED layout (with LEDs at the top)
// 2 | 4
// 1 | 3

int pattern[10];
int currentStep = 0;

void reaction();
void duel();
void memoryGame();
void binary();


void startup();
void ledsOff();
void idle();

// define startTime
unsigned long startTime;

// when the last input was received
unsigned long lastInput;

void setup() {
  pinMode(BUT1, INPUT);
  pinMode(BUT2, INPUT);
  pinMode(BUT3, INPUT);
  pinMode(BUT4, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  analogWriteResolution(8);
  lastInput = millis();
  startup();
}

void loop() {
  // reaction
  if (digitalRead(BUT1) == HIGH){
    lastInput = millis();
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
  // duel
  if (digitalRead(BUT2) == HIGH){
    lastInput = millis();
    unsigned long pressedTime = millis();
    int currentLed = 0;
    while (digitalRead(BUT2) == HIGH){
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
  // memory game
  if (digitalRead(BUT3) == HIGH){
    lastInput = millis();
    unsigned long pressedTime = millis();
    int currentLed = 0;
    while (digitalRead(BUT3) == HIGH){
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
  // binary
  if (digitalRead(BUT4) == HIGH){
    lastInput = millis();
    unsigned long pressedTime = millis();
    int currentLed = 0;
    while (digitalRead(BUT4) == HIGH){
      if (millis() - pressedTime >= 750){
        if (currentLed > 3){
          ledsOff();
          binary();
          break;
        }
        digitalWrite(leds[currentLed], HIGH);
        currentLed++;
        pressedTime = millis();
      }
    }
  }
  // idle animation
  if (millis()-lastInput > idleTime){
    idle();
  }
}

void startup(){
  for (int i=0;i<STARTUPcycles;i++){
    for (int j=0;j<4;j++){
      digitalWrite(startupLeds[j], HIGH);
      delay(300);
    }
    for (int j=0;j<4;j++){
      digitalWrite(startupLeds[j], LOW);
    }
  }
}

void idle(){
  for (int i=0;i<4;i++){
    for (int j=15;j<160;j++){
      analogWrite(leds[i], j);
      delay(10);
    }
    for (int j=160;j>15;j--){
      analogWrite(leds[i], j);
      delay(10);
    }
  }
}

void binary(){
  randomSeed(analogRead(A2));
  int randNumber = random(15);
  startTime = millis();

  // showing binary
  for (int i=0;i<4;i++){
    digitalWrite(leds[i], (randNumber >> i) & 1); // shifts the bits of the number right by i and extracts the last bit using & 1 (which returns 0 or 1)
    delay(150);
  }
  while(millis()-startTime < 5000);
  for (int i=0;i<4;i++){
    digitalWrite(leds[i], LOW);
  }

  int count = 0;
  // input phase
  while(true){
    // top left-add 1
    if (digitalRead(buttons[0])){
      count += 1;
      delay(20); // debounce
    }
    // top right-add 5
    if (digitalRead(buttons[1])){
      count += 5;
      delay(20); // debounce
    }
    // bottom left-subtract 1
    if (digitalRead(buttons[2])){
      count -= 1;
      delay(20); // debounce
    }
    // bottom right-submit
    if (digitalRead(buttons[3])){
      startTime = millis();
      bool heldLongEnough;
      while(millis()-startTime < 2000){
        heldLongEnough = true;
        if (!digitalRead(buttons[3])){
          heldLongEnough = false;
          break;
        }
      }
      if (heldLongEnough){
        delay(1000);
        compare(count, randNumber);
        break;
      }
    }
  }
  delay(2000);
  ledsOff();
}

void compare(int c, int expected){
  if (c == expected){
    winFeedback();
  }
  else{
    failFeedback();
  }
}

void ledsOff() {
  for (int i=0; i < 4; i++){
    digitalWrite(leds[i], LOW);
  }
}

void reaction() {
  randomSeed(analogRead(A2));
  int randPin;
  int randTime;
  int time;
  for (int i = 0; i < 5; i++){ // repeat 5 times
    randPin = random(4);
    startTime = millis(); // what time did the led turn on?
    randTime = random(500,5000);
    delay(randTime);
    while (millis()-startTime < 10000){
      for (int i=0;i<4;i++){
        if (digitalRead(buttons[i]) == HIGH){ // are one of the buttons pressed
          time = millis()-startTime;
          break; // exit the for loop
        }
      }
    }
    delay(randTime);
  }

  ledsOff();

  if (time < 230){
    blink(100);
  }
  else if (time < 350){
    blink(250);
  }
  else{
    blink(400);
  }
}

void blink(int time){
  for (int i=0;i<4;i++){
    for (int j=0;j<4;j++){
      digitalWrite(leds[j], HIGH);
    }
    delay(time);
    for (int j=0;j<4;j++){
      digitalWrite(leds[j], LOW);
    }
  }
}

void duel(){
  randomSeed(analogRead(A2));
  const int maxScore = 5;
  int p1Score = 0; // player 1 is on the left
  int p2Score = 0; // player 2 is on the right
  int leftLeds[2] = {LED1, LED3};
  int rightLeds[2] = {LED2, LED4};
  while (p2Score < maxScore && p1Score < maxScore){
    int randIndex = random(2);
    delay(random(1000,4000));

    digitalWrite(leftLeds[randIndex], HIGH);
    digitalWrite(rightLeds[randIndex], HIGH);

    int winner = waitForButton(randIndex);

    digitalWrite(leftLeds[randIndex], LOW);
    digitalWrite(rightLeds[randIndex], LOW);

    if (winner == 1) p1Score++;
    else if (winner == 2) p2Score++;

    delay(500);
  }
  if (p1Score == maxScore) flashLeds(leftLeds[0], leftLeds[1]);
  else flashLeds(rightLeds[0], rightLeds[1]);

}

void flashLeds(int L1, int L2){ // flash L1 and L2
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

        if (i == expected || i == expected + 1) { // if it is the expected led or the respective one on the other side
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