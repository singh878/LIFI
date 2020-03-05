#include <LiquidCrystal.h>

LiquidCrystal lcd(3, 4, 6, 7, 8, 9); //RS,EN,D4,D5,D6,D7

int pin = 2;
volatile unsigned int pulse;
char ch;
int i = 0;
int j = 0;
int bin[7];
double asc = 0;

void setup()
{
  //Serial.begin(9600);
  pinMode(pin, INPUT);
  attachInterrupt(0, count_pulse, RISING); // pulse is int storing the amount of rising LED flashes from the transmitter

  lcd.begin(16, 2);//initializing LCD
  for (i = 0; i < 5; i++) {
    lcd.setCursor(0, 0);
    lcd.print("WELCOME TO BTKIT(college name)");
    lcd.setCursor(0, 1);
    lcd.print("  LIFI PROJECT");
    lcd.noDisplay();
    delay(250);
    lcd.display();
    delay(300);
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" TYPE YOUR TEXT");
  lcd.setCursor(0, 1);

}

void loop()
{

  if (pulse != 0)
  {
    interrupts();
    delay(60);
    i = 0;
    if (pulse < 3) {
      bin[i] = 0;
      i++;
    }
    else if (pulse > 3) {
      bin[i] = 1;
      i++;
    }

    if (i > 7) {
      for (j = 0; j < 7; j++) {
        asc = asc + (bin[j] * pow(2, 7 - j));
      }
      i = 0;
    }

    Serial.println(char(asc));
    if (char(asc) == "-") {
      Serial.print(" CLEAR LCD");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(" TYPE YOUR TEXT");
      lcd.setCursor(0, 1);
    }
    lcd.print(char(asc));
  }
}

void count_pulse()
{
  pulse++;
}
