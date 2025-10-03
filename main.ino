#include <vector>

using namespace std;

vector<int> ledPins = {2, 3, 4, 5};
vector<int> buttonPins = {6, 7, 8, 9};
int buzzerPin = 10;

float nC4 = 261.63;
float nD4 = 293.66;
float nE4 = 329.63;
float nF4 = 349.23;
float nG4 = 392.00;
float nA4 = 440.00;
float nB4 = 493.88;
float nC5 = 523.25;

vector<float> melody = {nC4, nE4, nG4, nC5};

int levelToBeat = 5;

void flashSequence(vector<int> guessVector, int level) {
  for (int i = 0; i < level; i++) {
    int j = guessVector[i];
    digitalWrite(ledPins[j], HIGH);
    tone(buzzerPin, melody[j], 500);
    delay(500);  
    digitalWrite(ledPins[j], LOW);
    delay(500); 
  }
}

bool checkButtonSequence(int level, vector<int> guessVector) {
  int presses = 0;
  while (presses < level) {
    for (int i = 0; i < 4; i++) {
      if (digitalRead(buttonPins[i]) == LOW) {
        delay(50);
        if (digitalRead(buttonPins[i]) == LOW) {
          digitalWrite(ledPins[i], HIGH);
          tone(buzzerPin, melody[i], 300);
          delay(300);
          digitalWrite(ledPins[i], LOW);
          while (digitalRead(buttonPins[i]) == LOW) {
            delay(10);
          }
          if (i != guessVector[presses]) {
            return false;
          }
          presses++;
          break;
        }
      }
    }
  }
  return true;
}

void loseSong() {
  tone(buzzerPin, nC5, 500);
  delay(500);
  tone(buzzerPin, nG4, 500);
  delay(500);
  tone(buzzerPin, nE4, 500);
  delay(500);
  tone(buzzerPin, nC4, 500);
  delay(500);
}

void startSong() {
  tone(buzzerPin, nC4, 500);
  delay(500);
  tone(buzzerPin, nE4, 500);
  delay(500);
  tone(buzzerPin, nG4, 500);
  delay(500);
  tone(buzzerPin, nB4, 500);
  delay(500);
  tone(buzzerPin, nC5, 500);
  delay(500);
  tone(buzzerPin, nB4, 500);
  delay(500);
  tone(buzzerPin, nG4, 500);
  delay(500);
  tone(buzzerPin, nE4, 500);
  delay(500);
  tone(buzzerPin, nC4, 500);
  delay(1500);
}

void winSong() {
  tone(buzzerPin, nE4, 500);
  for (int pin : ledPins) {
    digitalWrite(pin, HIGH);
  }
  delay(500);

  tone(buzzerPin, nE4, 500);
  for (int pin : ledPins) {
    digitalWrite(pin, LOW);
  }
  delay(500);

  tone(buzzerPin, nF4, 500);
  for (int pin : ledPins) {
    digitalWrite(pin, HIGH);
  }
  delay(500);

  tone(buzzerPin, nG4, 500);
  for (int pin : ledPins) {
    digitalWrite(pin, LOW);
  }
  delay(500);

  tone(buzzerPin, nG4, 500);
  for (int pin : ledPins) {
    digitalWrite(pin, HIGH);
  }
  delay(500);

  tone(buzzerPin, nF4, 500);
  for (int pin : ledPins) {
    digitalWrite(pin, LOW);
  }
  delay(500);

  tone(buzzerPin, nE4, 500);
  for (int pin : ledPins) {
    digitalWrite(pin, HIGH);
  }
  delay(500);

  tone(buzzerPin, nD4, 500);
  for (int pin : ledPins) {
    digitalWrite(pin, LOW);
  }
  delay(500);

  tone(buzzerPin, nC4, 500);
  for (int pin : ledPins) {
    digitalWrite(pin, HIGH);
  }
  delay(500);

  for (int pin : ledPins) {
    digitalWrite(pin, LOW);
  }
  delay(500);
}

void setup() {
  for (int pin : ledPins) {
    pinMode(pin, OUTPUT);
  }
  for (int pin : buttonPins) {
    pinMode(pin, INPUT_PULLUP);
  }
  pinMode(buzzerPin, OUTPUT);

  //startSong();
}

void loop() {
  randomSeed(analogRead(A0));
  int level = 1;

  vector<int> guessVector = {};
  for (int i = 0; i < levelToBeat; i++) {
    guessVector.push_back(random(0, 4));
  }

  bool win = false;
  while (level <= levelToBeat) {
    win = false;
    // Led flashes the sequence (1 to 15 flashes)
    flashSequence(guessVector, level);
    // Get button sequence from user, 
    bool correct = checkButtonSequence(level, guessVector);
    if (correct) {
      // If correct loop
      win = true;
      delay(500);
      level++;
      continue;
    }
    else {
      // If wrong reset
      win = false;
      delay(500);
      loseSong();
      delay(500);
      break;
    }
  }
  if (win) {
    winSong();
    delay(500);
  }
}
