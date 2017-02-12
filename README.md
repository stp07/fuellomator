# fuellomator
Halbautomatischer Gegendruckabfüller für Bier mit Arduino Uno

Test Steuerung: https://youtu.be/0JZCbqLwJvY

Basis: Gegendruckabfüller aus Heizung/Sanitärteilen mit z.B. 1/4" Anschlüssen für CO2 und Bier, erhältlich in Hobbybrauershops oder Selbstbau nach bekannten Anleitungen

Funktionsweise:

-Tastendruck zum Start des Abfüllvorgangs, Magnetventil "CO2" öffnet für 4 Sekunden,

-Vorspannen einer Flasche mit Co2 für 4 Sekunden

-CO2-Ventil schließt, Bierventil öffnet

-Füllvorgang mit Bier gestoppt durch Füllstandssensor (Digitaleingang Arduino mit Pullup)

-Co2 und Bierleitung gesteuert durch Magnetventile über Relaisplatine an Digitalausgängen Arduino

-Füllgeschwindigkeit geregelt über CO2-Ablassventil

-Anzeigeausgabe über 16x2 LCD, jeweiliger Status wird angezeigt, zusätzlich Anzeige über 2 LEDs

Teile: (s. auch parts.md)

-Arduino UNO Rev3 oder Clone

-I2C 16x2 LCD mit Backpack

-China Relaisplatine (2-Kanal) 

-2 Magnetventile 12V, z.B. 1/4" mit IQS schnellverbindern

-Taster

-2 LED (z.B. grün für Meldung "Flasche voll" und rot (Auch  Blink-LED) für "Füllvorgang"

-10k Pullup bzw. Pulldown Widerstände 


Aufbau: s. Schema
