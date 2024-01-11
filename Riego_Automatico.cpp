#include "DHT.h"
#include <LiquidCrystal.h>

#define DHTPIN 2     
#define DHTPIN_EXT 3 
#define DHTTYPE DHT11  

DHT dht(DHTPIN, DHTTYPE);
DHT dht_EXT(DHTPIN_EXT, DHTTYPE);

const int rs = 24; 
const int en = 25;
const int d4 = 26;
const int d5 = 27;
const int d6 = 28;
const int d7 = 29;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int pinP1 = 22;
const int pinP2 = 23;

const int cont = 1;
const int cont2 = 1;

// Bombas
const int bi1 = 30;
const int bi2 = 31;
const int be1 = 32;
const int be2 = 33;

const int valorBi1 = 0;
const int valorBi2 = 0;
const int valorBe1 = 0;
const int valorBe2 = 0;

void setup()
{
  lcd.begin(16, 2);
  lcd.print("¡Hola, mundo!");

  pinMode(pinP1, INPUT);
  pinMode(pinP2, INPUT);
  pinMode(bi1, OUTPUT);
  pinMode(bi2, OUTPUT);
  pinMode(be1, OUTPUT);
  pinMode(be2, OUTPUT);

  Serial.begin(9600);
  Serial.println(F("¡Prueba de DHTxx!"));
  Serial1.begin(9600);

  dht.begin();
  dht_EXT.begin();
  lcd.clear();

  digitalWrite(bi1, HIGH);
  digitalWrite(bi2, HIGH);
  digitalWrite(be1, LOW);
  digitalWrite(be2, LOW);
}

void loop()
{
  float humedad1 = map(analogRead(A2), 0, 1023, 100, 0);

  float humedad2 = map(analogRead(A1), 0, 1023, 100, 0);

  float humedad3 = map(analogRead(A0), 0, 1023, 100, 0);

  float humedad4 = map(analogRead(A3), 0, 1023, 100, 0);

  if (humedad1 < 18.0)
  {
    valorBi1 = 1;
    digitalWrite(bi1, HIGH);
  }
  else
  {
    valorBi1 = 0;
    digitalWrite(bi1, LOW);
  }

  if (humedad2 < 18.0)
  {
    valorBi2 = 1;
    digitalWrite(bi2, HIGH);
  }
  else
  {
    valorBi2 = 0;
    digitalWrite(bi2, LOW);
  }

  if (humedad3 < 18.0)
  {
    valorBe1 = 1;
    digitalWrite(be1, HIGH);
  }
  else
  {
    valorBe1 = 0;
    digitalWrite(be1, LOW);
  }

  if (humedad4 < 18.0)
  {
    valorBe2 = 1;
    digitalWrite(be2, HIGH);
  }
  else
  {
    valorBe2 = 0;
    digitalWrite(be2, LOW);
  }

  if (digitalRead(pinP1) == true)
  {
    cont++;
    delay(100);
  }

  if (digitalRead(pinP2) == true)
  {
    cont2++;
    delay(100);
  }

  if (cont == 5)
  {
    cont = 1;
  }
  if (cont2 == 3)
  {
    cont2 = 1;
  }

  if (cont == 1)
  {
    lcd.setCursor(0, 1);
    lcd.print("Humedad I1: ");
    lcd.print(humedad1);
  }
  if (cont == 2)
  {
    lcd.setCursor(0, 1);
    lcd.print("Humedad I2: ");
    lcd.print(humedad2);
  }
  if (cont == 3)
  {
    lcd.setCursor(0, 1);
    lcd.print("Humedad E1: ");
    lcd.print(humedad3);
  }
  if (cont == 4)
  {
    lcd.setCursor(0, 1);
    lcd.print("Humedad E2: ");
    lcd.print(humedad4);
  }

  delay(250);
  float t = dht.readTemperature();
  float t_ext = dht_EXT.readTemperature();

  if (cont2 == 1)
  {
    lcd.setCursor(0, 0);
    lcd.print("Temp Ext: ");
    lcd.print(t);
    lcd.print(" C");
  }

  if (cont2 == 2)
  {
    lcd.setCursor(0, 0);
    lcd.print("Temp Int: ");
    lcd.print(t_ext);
    lcd.print(" C");
  }

  Serial1.print(t * 10);
  Serial1.print(",");
  Serial1.print(t_ext * 10);
  Serial1.print("+");
  Serial1.print(humedad1 * 10);
  Serial1.print("-");
  Serial1.print(humedad2 * 10);
  Serial1.print("*");
  Serial1.print(humedad3 * 10);
  Serial1.print("[");
  Serial1.print(humedad4 * 10);
  Serial1.print("#");
  Serial1.print(valorBi1);
  Serial1.print("/");
  Serial1.print(valorBi2);
  Serial1.print("(");
  Serial1.print(valorBe1);
  Serial1.print(")");
  Serial1.println(valorBe2);
}
