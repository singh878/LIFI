
int ledPin = 13;
char ch;
int asc;
int i = 0;
int j = 0;
int bin[7];
// bin[0]=x[7] or MSB and bin[7]=x[0] or LSB

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  for (i = 0; i < 7; i++)
    bin[i] = 0;
}

void loop()
{
  if (Serial.available() > 0) {

    ch = Serial.read();
    asc = int(ch);
    Serial.println(asc);

    for (i = 0; i < 7; i++) {
      bin[i] = asc % 2;
      asc = asc / 2;
      Serial.println(bin[i]);
    }

    for (i = 0; i < 7; i++) {
      if (bin[i] == 0) {
        for (j = 0; j < 2; j++) {
          digitalWrite(ledPin, HIGH);
          delay(5);
          digitalWrite(ledPin, LOW);
          delay(5);
        }
        delay(40);
      }
      else if (bin[i] == 1) {
        for (j = 0; j < 5; j++) {
          digitalWrite(ledPin, HIGH);
          delay(5);
          digitalWrite(ledPin, LOW);
          delay(5);
        }
        delay(10);
      }
    }
  }
}
