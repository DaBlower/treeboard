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
int steps = 0;

void reaction();
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
  while (true){
    for (int i=0;i<4;i++){
      if (digitalRead(buttons[i]) == HIGH || abs(startTime-millis() > 10000)){ // are one of the buttons pressed or has it been more than 10 seconds?
        break; // exit the while loop
      }
    }
  }
  digitalWrite(leds[randPin], LOW);
}

void memoryGame(){
  steps = 1;
  while (true){
    generatePattern(); // create the pattern
    showPattern(); // show the pattern
    if (!getPlayerInput()){ // check if player failed
      failFeedback();
      break;
    }
    winFeedback();
    currentStep++; // increase difficulty
    delay(1000)
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