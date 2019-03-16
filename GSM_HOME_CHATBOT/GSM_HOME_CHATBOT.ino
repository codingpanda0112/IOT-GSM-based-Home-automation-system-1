#include <SoftwareSerial.h>
#include<LiquidCrystal.h>

SoftwareSerial mySerial(12, 13);//Setting the rx, tx respectively for arduino
LiquidCrystal lcd(6,7,8,9,10,11);// setting led values

#define Fan 3
#define Light 4
#define Tv 5
#define Temperature 2

int commandFound=0,i=0;
int led=0;

char str[50];
String messageread="";


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
    Serial.println("AT+CMGF=1");
    delay(1000);
    
    Serial.println("AT+CNMI=2,2,0,0,0");
    delay(500);
   
    lcd.setCursor(0,0);
    lcd.print("  SYSTEM READY!");
    delay(2000);
    lcd.setCursor(0,0);
    lcd.print("Fan   Light  TV ");
    lcd.setCursor(0,1);
    lcd.print("OFF    OFF   OFF ");

}

void loop() {
    // digitalWrite(Fan, HIGH);
     //digitalWrite(Light,HIGH);
     //digitalWrite(Tv,HIGH);
     
    lcd.setCursor(0,0);
    lcd.print("Fan   Light  TV");
    if(commandFound==0)
    {
       myserialEvent();
       delay(3000);
       
    }
    else
    {
      command();
      commandFound=0;
      delay(2000);
    }
      
}


void myserialEvent() 
{
  while(mySerial.available()) 
  {
      Serial.println("available");
     
      if(mySerial.find('#')!=0)  
      { 
          Serial.println("in loop");      
          while (mySerial.available()) 
          {
                Serial.println("available 2");
                char inChar=mySerial.read();
                messageread=messageread+inChar;
                str[i++]=inChar;
                if(inChar=='*')
                {
                    Serial.println("out of loop");
                    commandFound=1;
                    Serial.println(str);
                    
                    return;
                } 
          } 
      }
      
   }
   
 }

void command()

{
    Serial.println("command");
    if(!(strncmp(str,"tv on",5)))
    {
      digitalWrite(Tv, HIGH);
      lcd.setCursor(13,1); 
      lcd.print("ON    ");
      delay(5000);
      sendMessage(1);
      delay(5000);
    }
    else if (!(strncmp(str,"tv off",6)))
    {
      digitalWrite(Tv, HIGH);
      lcd.setCursor(13,1); 
      lcd.print("ON    ");
      delay(5000);
      sendMessage(2);
      delay(5000);
    } 
    else if (!(strncmp(str,"light on",8)))
    {
      digitalWrite(Light, HIGH);
      lcd.setCursor(7,1); 
      lcd.print("ON    ");
      delay(5000);
      sendMessage(3);
      delay(5000);
    }
    else if (!(strncmp(str,"light off",9)))
    {
      digitalWrite(Light, HIGH);
      lcd.setCursor(7,1); 
      lcd.print("ON    ");
      delay(5000);
      sendMessage(4);
      delay(5000);
    } 
    else if (!(strncmp(str,"fan on",6)))
    {
      digitalWrite(Tv, HIGH);
      lcd.setCursor(0,1); 
      lcd.print("ON    ");
      delay(5000);
      sendMessage(5);
      delay(5000);
    }   
  else if (!(strncmp(str,"fan off",7)))
    {
      digitalWrite(Tv, HIGH);
      lcd.setCursor(0,1); 
      lcd.print("ON    ");
      delay(5000);
      sendMessage(6);
      delay(5000);
    } 
    else if (!(strncmp(str,"all on",6)))
    {
      digitalWrite(Tv, HIGH);
      lcd.setCursor(13,1); 
      lcd.print("ON     ON    ON  ");
      delay(5000);
      sendMessage(7);
      delay(5000);
    }  
    else if (!(strncmp(str,"all off",7)))
    {
      digitalWrite(Tv, HIGH);
      lcd.setCursor(13,1); 
      lcd.print("Off  Off   Off ");
      delay(5000);
      sendMessage(8);
      delay(5000);
    }   
}
 
void sendMessage(int device)
  
{ Serial.println("sending message");
  String message;
  switch(device)
  {
    case 1: message="TV is switched on";
      break;
    case 2: message="TV is off";
      break;
    case 3: message="Light is switched on";
      break;
    case 4: message="Light is  switched off";
      break;
    case 5: message="Fan is switched on";
      break;
    case 6: message="Fan is off";
      break;
    case 7: message="All are  on !";
      break;
    case 8: message="All are off!";
      break;
      default: message="Error";
       
  }
  Serial.println(message);
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  mySerial.println("AT+CMGS=\"+919902759513\"\r"); // Replace x with mobile number
  delay(1000);
  mySerial.println(message);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("Message sent");
}

float check_temp()
{
  
}
