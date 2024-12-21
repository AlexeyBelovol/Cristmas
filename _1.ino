const int buttonPin = 11; // Пін кнопки
const int ledCount = 9;
int ledPins[ledCount] = {2, 3, 4, 5, 6, 7, 8, 9, 10};

int mode = 0;
const int modeCount = 3;

// Для відстеження стану кнопки
int lastButtonState = LOW;
int currentButtonState;
unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;

void setup() {
  // Налаштування LED пінів як виходів
  for (int i = 0; i < ledCount; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
  
  // Налаштування кнопки
  pinMode(buttonPin, INPUT_PULLUP); // Увімкнення вбудованого pull-up резистора
}

void loop() {
  // Читання стану кнопки (зверни увагу: активний LOW через pull-up)
  currentButtonState = digitalRead(buttonPin);

  // Захист від "дребезгу контакту"
  if (currentButtonState == LOW && lastButtonState == HIGH && (millis() - lastDebounceTime) > debounceDelay) {
    mode = (mode + 1) % modeCount; // Перемикання режимів
    lastDebounceTime = millis();
  }

  lastButtonState = currentButtonState;

  // Вибір режимів
  switch (mode) {
    case 0:
      modeSequential();
      break;
    case 1:
      modeAlternating();
      break;
    case 2:
      modeAllOnOff();
      break;
  }
}

void modeSequential() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }
  for (int i = ledCount - 1; i >= 0; i--) {
    digitalWrite(ledPins[i], HIGH);
    delay(200);
    digitalWrite(ledPins[i], LOW);
  }
}

void modeAlternating() {
  for (int i = 0; i < ledCount; i++) {
    if (i % 2 == 0) {
      digitalWrite(ledPins[i], HIGH);
    } else {
      digitalWrite(ledPins[i], LOW);
    }
  }
  delay(500);
  for (int i = 0; i < ledCount; i++) {
    if (i % 2 == 0) {
      digitalWrite(ledPins[i], LOW);
    } else {
      digitalWrite(ledPins[i], HIGH);
    }
  }
  delay(500);
}

void modeAllOnOff() {
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], HIGH);
  }
  delay(1000);
  for (int i = 0; i < ledCount; i++) {
    digitalWrite(ledPins[i], LOW);
  }
  delay(1000);
}
