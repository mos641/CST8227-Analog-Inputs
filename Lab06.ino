int redPin =  18;
int greenPin =  14;
int bluePin =  15;

int pot = 20;

int thermometer = 16;

int pshBttn = 19;

int demo = 1;

long int lastTime = millis();

void setup()   {
  Serial.begin(38400);

  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(pshBttn), buttonInterrupt, FALLING);

  Serial.println("===============================================");
  Serial.print("                     DEMO ");
  Serial.println(demo);
  Serial.println("===============================================");
}
int count = 0;
void loop()
{
  switch (demo) {
    case 1:
      if (checkTime(10))
      {
        count++;
        intensity();
      }
      if (count >= 220)
      {
        count = 0;
        printIntensity();
      }
      break;
    case 2:
      if (checkTime(1800))
      {
        temp();
      }
      break;
  }
}

void intensity()
{
  // read the pot position
  int redIntensity = analogRead(pot) / 4;

  // set all 3 pins to the desired intensity
  analogWrite(redPin, redIntensity);
  analogWrite(greenPin, 255 - redIntensity);
  analogWrite(bluePin, 0);
}

void printIntensity()
{
  // read the pot position
  int redIntensity = analogRead(pot) / 4;

  // set all 3 pins to the desired intensity
  float greenPercent = (redIntensity / 255.0) * 100;
  float redPercent = 100 - greenPercent;
  Serial.print(redPercent);
  Serial.println("% RED");
  Serial.print(greenPercent);
  Serial.println("% GREEN");
  Serial.println();
}

void temp()
{
  float celsius;
  float fahrenheit;
  int code = analogRead(thermometer);
  if (code <= 289) {
    celsius = 5 + (code - 289) / 9.82;
  }
  if (code > 289 && code <= 342) {
    celsius = 10 + (code - 342) / 10.60;
  }
  if (code > 342 && code <= 398) {
    celsius = 15 + (code - 398) / 11.12;
  }
  if (code > 398 && code <= 455) {
    celsius = 20 + (code - 455) / 11.36;
  }
  if (code > 455 && code <= 512) {
    celsius = 25 + (code - 512) / 11.32;
  }
  if (code > 512 && code <= 566) {
    celsius = 30 + (code - 566) / 11.00;
  }
  if (code > 566 && code <= 619) {
    celsius = 35 + (code - 619) / 10.44;
  }
  if (code > 619 && code <= 667) {
    celsius = 40 + (code - 667) / 9.73;
  }
  if (code > 667) {
    celsius = 45 + (code - 712) / 8.90;
  }
  fahrenheit = celsius * 1.8 + 32;
  Serial.print("temperature: ");
  Serial.print(celsius);
  Serial.print(" Celsius, ");
  Serial.print(fahrenheit);
  Serial.println(" Fahrenheit");
  Serial.println();
}

bool checkTime(int delay) {
  if (millis() - lastTime >= delay) {
    lastTime = millis();
    return true;
  }
  return false;
}

void buttonInterrupt() {
  if (demo == 1)
  {
    demo = 2;  
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  } else {
    demo = 1;
  }
  Serial.println("===============================================");
  Serial.print("                     DEMO ");
  Serial.println(demo);
  Serial.println("===============================================");
}
