//2017 by Peter Lauer Primsperle Brewing
const int co2=5;   //lowactive
const int bier=6;  // lowactive
const int fuellen=4; //fill, pulldown 10k
const int led=7;    //full
const int voll=8;   
const int led2=9;   //Blink-LED 


//Display I2C: A5=SCL  A4=SDA
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup()  
{
  
  pinMode (co2, OUTPUT);
  digitalWrite (co2, HIGH);

  pinMode (bier, OUTPUT);
  digitalWrite (bier, HIGH);

  pinMode (fuellen, INPUT);
  digitalWrite (fuellen, LOW);

  pinMode (voll, INPUT);
  digitalWrite (voll, HIGH);

  pinMode (led, OUTPUT);
  digitalWrite (led, LOW);

  pinMode (led2, OUTPUT);
  digitalWrite (led2, LOW);
  
//LCD Setup
  lcd.init(); 
  lcd.backlight();
  
  lcd.setCursor(3, 0);
  lcd.print("Fuellomator");

  lcd.setCursor(4, 1);
  lcd.print ("Vers_01");

 
delay (4000);
   
   
   lcd.clear();
}

void loop() 
{
  
  digitalWrite (co2, HIGH); 
  digitalWrite (bier, HIGH);
  digitalWrite (fuellen, LOW);
  digitalWrite (voll, HIGH);
  digitalWrite (led, LOW);    //ready

 lcd.setCursor(5,0);
 lcd.print("Bereit");  
 lcd.setCursor(1,1);
 lcd.print("Flasche einst.");

 if (digitalRead(fuellen) == HIGH)    //push to fill, preload Co2
   { 
    digitalWrite(co2,LOW);

     lcd.setCursor(0,0);
     lcd.print("CO2 vorspannen,");  //print preload
     lcd.setCursor(0,1);
     lcd.print("bitte warten..."); 
     delay (4000);                    //preload 4s
 
//fill beer
  digitalWrite(co2,HIGH);      
  digitalWrite(bier,LOW);     
  lcd.clear();
while (digitalRead(voll) ==HIGH && digitalRead(co2)==HIGH) 
  {
   digitalWrite(bier,LOW);
   
   lcd.setCursor(0,0);
   lcd.print("Fuellen...");
   lcd.setCursor(0,1);
   lcd.print("bitte warten..."); 
   
   digitalWrite (led2,HIGH);
  }
//filled up
if  (digitalRead(voll)== LOW)   //wenns dann doch Pegelmeldung gibt....      
 {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ende - Flasche");
    lcd.setCursor(0,1);
    lcd.print("entnehmen."); 
    digitalWrite(bier,HIGH);
    digitalWrite(co2,HIGH);
    digitalWrite(led2,LOW);
    digitalWrite(led,HIGH);           
    delay(6000);                    
 } 
 lcd.clear();
}
}


