byte motorPin1 = 8;	// Blue   - 28BYJ48 pin 1
byte motorPin2 = 9;	// Pink   - 28BYJ48 pin 2
byte motorPin3 = 10;	// Yellow - 28BYJ48 pin 3
byte motorPin4 = 11;	// Orange - 28BYJ48 pin 4
byte motorSpeed = 3;     //variable to set stepper speed
int obr = 512; // szacowane na obrót 512
int i;
//int zmm = 0;
byte pozAkt = 5;
byte pozDoc = 5;
byte pozmin = 2;
byte pozmax = 100;
long del = 150;
long licznik = 1;
boolean start1 = true;
boolean start2 = true;
boolean start3 = true;
#define styg 4
#define styd 5
#define przg 3
#define przd 2
#define ledPin 13
#define potp A2

#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 6
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
byte stemp = 50;
byte ntemp = 50;
byte to = 60;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(styg, INPUT_PULLUP);
  pinMode(styd, INPUT_PULLUP);
  pinMode(przg, INPUT_PULLUP);
  pinMode(przd, INPUT_PULLUP);
//  Serial.begin(9600);
  sensors.begin();
  //  attachInterrupt(0, pozX, LOW);
  //  attachInterrupt(1, pozX, LOW);
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  lcd.print("*main*");
}
void off() {
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  // delay(5000);
}
void counterclockwise() {
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay (motorSpeed);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin4, HIGH);
  delay (motorSpeed);
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin4, HIGH);
  delay(motorSpeed);
}
void clockwise() {
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay (motorSpeed);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, HIGH);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, LOW);
  delay(motorSpeed);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, HIGH);
  digitalWrite(motorPin1, HIGH);
  delay (motorSpeed);
  digitalWrite(motorPin4, LOW);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
  digitalWrite(motorPin4, HIGH);
  digitalWrite(motorPin3, LOW);
  digitalWrite(motorPin2, LOW);
  digitalWrite(motorPin1, HIGH);
  delay(motorSpeed);
}
void obrclockwise() {
  for (i = 1; i < obr; i++)
  {
    clockwise();
  }
  off();
  //  Serial.println("otw");
}
void obrcounterclockwise() {
  for (i = 1; i < obr; i++)
  {
    counterclockwise();
  }
  off();
  //  Serial.println("zamyk");
}

void mig() {
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
}

void start()
{
  if (start3 == true)
  {
    lcd.print("start3");
    if (digitalRead(styg) == 0)
    {
      obrcounterclockwise();
      obrcounterclockwise();
      obrcounterclockwise();
    }
    if (digitalRead(styd) == 0)
    {
      obrclockwise();
      obrclockwise();
      obrclockwise();
    }
    start3 = false;
  }

  if (start2 == true)
  {
    lcd.print("start2");
    if (digitalRead(styg) == 1)
    {
      obrclockwise();
      if (digitalRead(styg) == 0)
      {
        pozAkt = 0;
        pozmin = 3;
        start2 = false;
      }
    }
  }
  if (start1 == true)
  {
    lcd.print("start1");
    if (digitalRead(styd) == 1)
    {
      obrcounterclockwise();
      pozAkt++;
      if (digitalRead(styd) == 0)
      {
        pozmax = (pozAkt - 3);
        start1 = false;
      }
    }
  }

}
void serial()
{
  
}

void lcdfunc()
{
  lcd.clear();
  lcd.print("T:");
  lcd.print(ntemp);
  lcd.print("   ");
  lcd.print("P:");
  lcd.print(pozAkt);
  lcd.setCursor(1, 1);
  lcd.print("T opt:");
  lcd.print(to);
  lcd.print("   ");
  lcd.print("Pmax:");
  lcd.print(pozmax);
  //lcd.print();
  //lcd.print();
  //lcd.print();  
}

void pot()
{
to = analogRead(potp);
to = map(to, 0, 123, 40, 90);
}

void styki()
{
  if (digitalRead(styg) != 1)
  {
    pozAkt = 2;
  }
  if (digitalRead(styd) != 1)
  {
    pozAkt = 38;
  }
}
void ogrpoz()
{
  if (pozDoc > 38) {
    pozDoc = 38;
  }
  if (pozDoc < 2) {
    pozDoc = 2;
  }
}
void delays()
{
  if (ntemp < 40)
  {
    del = 200;
  }
  else if ((ntemp >= 40 && ntemp <= 62) || (ntemp >= 68 && ntemp <= 76))
  {
    del = 20;
  }
  else if (ntemp >= 62 && ntemp <= 68)
  {
    del = 60;
  }
  else if (ntemp > 76)
  {
    del = 1;
  }
  else
  {
    del = 100;
  }
}
void petla()
{
  for (i = 1; i < del; i++);
}
void pozycjonuj()
{
  if (pozAkt > pozDoc/*&& pozAkt <= 38*/)
  {
    obrclockwise();
    pozAkt--;
  }
  else if (pozAkt < pozDoc/* && pozAkt >= 2 */)
  {
    obrcounterclockwise();
    pozAkt++;
  }
  else
  {
    mig;
  }
}
void tempy()
{ sensors.requestTemperatures();
  stemp = ntemp;
  ntemp = (sensors.getTempCByIndex(0));
}
void sprTempNowaPoz()
{
  if (ntemp < (to - 25))
  { pozDoc--;
    if (pozDoc > 17)
    {
      pozDoc = 17;
    }
  }
  else if (ntemp >= (to - 25) && ntemp < (to - 12))
  { if (ntemp > stemp)
    {
      mig;
    }
    else if (ntemp < stemp)
    {
      pozDoc--;
    }
    else if (ntemp == stemp)
    {
      pozDoc--;
    }
    if (pozDoc > 20)
    {
      pozDoc = 20;
    }
  }
  else if ((ntemp >= (to - 12)) && (ntemp < (to - 7)))
  { if (ntemp > stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp < stemp)
    { pozDoc--;
      pozDoc--;
    }
    else if (ntemp == stemp)
    { pozDoc--;
      pozDoc--;
    }
    if (pozDoc > 24)
    {
      pozDoc = 24;
    }
    if (pozDoc < 12)
    {
      pozDoc = 12;
    }
  }
  else if ((ntemp >= (to - 7)) && (ntemp <= (to - 3)))
  { if (ntemp > stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp < stemp)
    { pozDoc--;
      pozDoc--;
    }
    else if (ntemp == stemp)
    {
      pozDoc--;
    }
    if (pozDoc > 32)
    {
      pozDoc = 32;
    }
    if (pozDoc < 16)
    {
      pozDoc = 16;
    }
  }
  else if ((ntemp > (to - 3)) && (ntemp < (to + 3)))
  { if (ntemp > stemp)
    {
      pozDoc++;
    }
    else if (ntemp < stemp)
    {
      pozDoc--;
    }
    else if (ntemp == stemp)
    {
      mig();
    }
    if (pozDoc > 36)
    {
      pozDoc = 36;
    }
    if (pozDoc < 20)
    {
      pozDoc = 20;
    }
  }
  else if ((ntemp >= (to + 3)) && (ntemp <= (to + 5)))
  { if (ntemp > stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp == stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp < stemp)
    { pozDoc--;
      pozDoc--;
    }
    if (pozDoc < 24)
    {
      pozDoc = 24;
    }
  }
  else if ((ntemp > (to + 5)) && (ntemp <= (to + 5)))
  { if (ntemp > stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp == stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp < stemp)
    { pozDoc--;
      pozDoc--;
    }
    if (pozDoc < 24)
    {
      pozDoc = 24;
    }
  }
  else if ((ntemp > (to + 5)) && (ntemp < (to + 7)))
  { if (ntemp > stemp)
    { pozDoc++;
      pozDoc++;
    }
    else if (ntemp == stemp)
    {
      pozDoc++;
    }
    else if (ntemp < stemp)
    {
      mig;
    }
    if (pozDoc < 28)
    {
      pozDoc = 28;
    }
  }
  else if (ntemp >= (to + 7))
  { pozDoc++;
    if (pozDoc < 32)
    {
      pozDoc = 32;
    }
  }
}

void loop() {

  tempy();
  lcdfunc();
  start();
  delays();
  sprTempNowaPoz();
  styki();
  ogrpoz();
  petla();
  pozycjonuj();
  //serial();
  lcdfunc();
}


