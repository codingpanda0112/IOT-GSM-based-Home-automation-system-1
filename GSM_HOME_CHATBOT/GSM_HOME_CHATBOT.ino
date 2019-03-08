#include <SoftwareSerial.h>
#include<LiquidCrystal.h>

SoftwareSerial mySerial(12, 13);//Setting the rx, tx respectively for arduino
LiquidCrystal lcd(6,7,8,9,10,11);// setting led values

#define Fan 3
#define Light 4
#define Tv 5

int temp=0,i=0;
int led=0;

char msg[50];


void setup() 
{
    mySerial.begin(9600);
    Serial.begin(9600);
    delay(100);

    lcd.begin(16,2);
    pinMode(Fan, OUTPUT);
    pinMode(Light,OUTPUT);
    pinMode(Tv,OUTPUT);

    lcd.setCursor(0,0);
    lcd.print("Iot PROJECT");
    delay(3000);
    lcd.clear();
    
    lcd.setCursor(0,0);
    lcd.print("GSM Home");
    lcd.setCursor(0,1);
    lcd.print("Automation Chabot");
    delay(2000);
    lcd.clear();
    
    Serial.println("AT+CNMI=2,2,0,0,0");
    delay(500);
    Serial.println("AT+CMGF=1");
    delay(1000);
    
    lcd.setCursor(0,0);
    lcd.print("SYSTEM READY!");

}

void loop() {
     digitalWrite(Tv, HIGH);
     digitalWrite(Light,HIGH);
     digitalWrite(Fan,HIGH);
    
      
}
