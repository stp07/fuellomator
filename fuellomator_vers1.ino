//Steuerung für einen Gegendruck-Abfüller für Bier mit Arduino Uno Rev3, 2 Magnetventile, China-Relaisplatine (2er)
//2017 by Peter Lauer Primsperle Brewing



//Pinbelegung Ein- und Ausgänge:
const int co2=5;   // Magnetschalter CO2 über Relais (Schaltlogik umgedreht,lowactive)
const int bier=6;  // Magnetschalter Bier über Relais (Schaltlogik umgedreht,lowactive)
const int fuellen=4; //Starttaster Füllvorgang, Pulldown-Widerstand 10k
const int led=7;    //LED als Anzeige für fertigen Füllvorgang, (grün), Widerstand 150Ohm
const int voll=8;   //Sensor bzw. Kontakt "volle Flasche"  mit Pullup-Widerstand, damit 5V anliegen zur permanenten Messung
const int led2=9;   //Blink-LED während Füllvorgang (rot), Widerstand 150 Ohm


//Display an A4: SCL und A5: SDA

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

Serial.begin(9600);
  
//LCD Setup ------------------------------------
  lcd.init(); 
  lcd.backlight();
  
  lcd.setCursor(3, 0);
  lcd.print("Fuellomator");

  lcd.setCursor(4, 1);
  lcd.print ("Vers_01");
 
delay (4000);
   
   
   lcd.clear();

   

}
// Ende Setup ------------------------------------

void loop() 
{
  
  digitalWrite (co2, HIGH); 
  digitalWrite (bier, HIGH);
  digitalWrite (fuellen, LOW);
  digitalWrite (voll, LOW);
  digitalWrite (led, LOW);    //Startzustand im Loop

 lcd.setCursor(5,0);
 lcd.print("Bereit");  //Startzustand mit Meldung "Bereit"
 lcd.setCursor(1,1);
 lcd.print("Flasche einst.");




 //-------------------------wenn Tastendruck ab hier weiter, sonst Verbleib im obigen Teil vom Loop--------------------------------------
 if (digitalRead(fuellen) == HIGH)    //wenn Taster "fuellen" gedrückt wird, dann CO2-Magnetventil öffnen und für 4 Sekunden vorspannen
   { 
    digitalWrite(co2,LOW);

     lcd.setCursor(0,0);
     lcd.print("CO2 vorspannen,");  //Anzeige: Vorspannen
     lcd.setCursor(0,1);
     lcd.print("bitte warten..."); 
     delay (4000);                    //Vorspanndauer: 4 Sekunden, eventuell anpassen



   
//-------------Bier einfüllen----------------------------------------
  digitalWrite(co2,HIGH);      //CO2-Ventil wieder schließen
  digitalWrite(bier,LOW);    //Bierventil öffnen    
  lcd.clear();
while (digitalRead(voll) ==HIGH && digitalRead(co2)==HIGH) // während des Füllvorgangs, wenn die Pegelmeldung noch nicht erreicht ist....
  {
   digitalWrite(bier,LOW);//--> Bierventil offen lassen
   
   lcd.setCursor(0,0);
   lcd.print("Fuellen...");
   lcd.setCursor(0,1);
   lcd.print("bitte warten...");  //Meldung "bitte warten"
   
   digitalWrite (led2,HIGH);
  }

//--------------Füllvorgang beendet, Meldung----------------------------  
if  (digitalRead(voll)== LOW)   //wenns dann doch Pegelmeldung gibt....      
 {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Ende - Flasche");
    lcd.setCursor(0,1);
    lcd.print("entnehmen."); 
    digitalWrite(bier,HIGH);       //Magnetventil Bier schließen
    digitalWrite(led2,LOW);
    digitalWrite(led,HIGH);            //Led grün leuchtet (Led 1)
    delay(6000);                       //5 Sekunden halten
 } 

 lcd.clear();



 
}//------------------Füll-Loop Ende-----------------------------------
}//zurück zum Start


