#include <SoftwareSerial.h>
#include<string.h>
#include<LiquidCrystal.h>

SoftwareSerial mySerial(12, 13);//Setting the rx, tx respectively for arduino
LiquidCrystal lcd(6,7,8,9,10,11);// setting led values

#define Fan 4
#define Light 3
#define Tv 5
#define tempPin 0


int commandFound=0,tempflag=0;
int lightflag=0,fanflag=0,tvflag=0;
int led=0;
//int i=0;
float temprs,tempr;

char str[70];
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
    
    if(tempflag!=1){
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
        lcd.setCursor(0,0);
        lcd.print("  SYSTEM READY!");
        delay(2000);
        lcd.setCursor(0,0);
        lcd.print("Fan   Light  TV ");
        lcd.setCursor(0,1);
        lcd.print("OFF    OFF   OFF ");
    }
   
    Serial.println("AT+CMGF=1");
    delay(1000);
    
    Serial.println("AT+CNMI=2,2,0,0,0");
    delay(500);
   
   
    digitalWrite(Fan, HIGH);
    digitalWrite(Light,HIGH);
    digitalWrite(Tv,HIGH);
    delay(2000);
    digitalWrite(Fan, LOW);
    digitalWrite(Light,LOW);
    digitalWrite(Tv,LOW);

}

void loop() {
    //digitalWrite(Fan, HIGH);
    //digitalWrite(Light,HIGH);
    //digitalWrite(Tv,HIGH);
    
    if( tempflag!=1)
    {
        lcd.setCursor(0,0);
        lcd.print("Fan   Light  TV");
        if (fanflag==1)
        {
            lcd.setCursor(0,1); 
            lcd.print("ON    "); 
        }
        else
        {
          lcd.setCursor(0,1); 
          lcd.print("OFF   "); 
        }
        if(tvflag==1)
        {
          lcd.setCursor(13,1); 
          lcd.print("ON  ");
        }
        else
        {
          lcd.setCursor(13,1); 
          lcd.print("OFF "); 
        }
        if(lightflag==1)
        {
            lcd.setCursor(7,1); 
            lcd.print("ON    "); 
        }
        else
        {
             lcd.setCursor(7,1); 
            lcd.print("OFF   "); 
        }
      
    }
    else
    {
      lcd.setCursor(0,0); 
      lcd.print("Temperature: ");    
      
      lcd.setCursor(0,1);
      lcd.print(String(temprs));
      tempflag=0;
      
    }
    
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
  {   int i=0;
      //Serial.println("available");
     
      if(mySerial.find('#')!=0)  
      {  
          //Serial.println("in loop");      
          while (mySerial.available()) 
          {
                //Serial.println("available 2");
                char inChar=mySerial.read();
                messageread=messageread+inChar;
                //Serial.println(inChar);
                str[i++]=inChar;
                if(inChar=='*')
                {
                    Serial.println("message found!");
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
      tvflag=1;
      digitalWrite(Tv, HIGH);
      lcd.setCursor(13,1); 
      lcd.print("ON    ");
      delay(1000);
      sendMessage(1);
      delay(5000);
    }
    else if (!(strncmp(str,"tv off",6)))
    {
      tvflag=0;
      digitalWrite(Tv, LOW);
      lcd.setCursor(13,1); 
      lcd.print("Off   ");
      delay(1000);
      sendMessage(2);
      delay(5000);
    } 
    else if (!(strncmp(str,"light on",8)))
    {
      lightflag=1;
      digitalWrite(Light, HIGH);
      lcd.setCursor(7,1); 
      lcd.print("ON    ");
      delay(1000);
      sendMessage(3);
      delay(5000);
    }
    else if (!(strncmp(str,"light off",9)))
    {
      lightflag=0;
      digitalWrite(Light, LOW);
      lcd.setCursor(7,1); 
      lcd.print("ON    ");
      delay(1000);
      sendMessage(4);
      delay(5000);
    } 
    else if (!(strncmp(str,"fan on",6)))
    {
     fanflag=1;
      digitalWrite(Fan, HIGH);
      lcd.setCursor(0,1); 
      lcd.print("ON    ");
      delay(1000);
      sendMessage(5);
      delay(5000);
    }   
  else if (!(strncmp(str,"fan off",7)))
    {
      fanflag=0;
      digitalWrite(Fan, LOW);
      lcd.setCursor(0,1); 
      lcd.print("ON    ");
      delay(1000);
      sendMessage(6);
      delay(5000);
    } 
    else if (!(strncmp(str,"all on",6)))
    {
      digitalWrite(Tv, HIGH);
      digitalWrite(Fan, HIGH);
      digitalWrite(Light, HIGH);
      lcd.setCursor(0,1); 
      lcd.print("ON     ON    ON  ");
      delay(1000);
      sendMessage(7);
      delay(5000);
    }  
    else if (!(strncmp(str,"all off",7)))
    {
      digitalWrite(Tv, LOW);
      digitalWrite(Fan, LOW);
      digitalWrite(Light, LOW);
      
      lcd.setCursor(0,1); 
      lcd.print("Off  Off   Off ");
      delay(1000);
      sendMessage(8);
      delay(5000);
    }   
    else if (!(strncmp(str,"currtemp",8)))
    {
      tempflag=1;
      float tep=check_temp();
      String msg="current temperature:"+String(temprs)+"C";
      delay(1000);
      delay(1000);
      Serial.println(msg);
      sendMessage(9);
      //Donot change this delay needed for short term display
      delay(5000);
    } 
    if(!(strncmp(str,"slb ",3)))
    {
      String Str(str);
      //Serial.println(Str.substring(4,5));
      int bright=Str.substring(4,5).toInt();
      int brightfloat=51*bright;
      lightflag=1;
      setBrightness(Light,brightfloat);
      delay(1000);
      lcd.setCursor(7,1); 
      lcd.print("ON    ");
      delay(1000);
      sendMessage(10);
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
    case 9: message="Current room Temperature:"+String(tempr);
      break;
    case 10: message="Bightness of the light set!";
      break;
      default: message="Error";
       
  }
  Serial.println(message);
  mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);  // Delay of 1000 milli seconds or 1 second
  //mySerial.println("AT+CMGS=\"+919902759513\"\r"); 
  // Replace x with mobile number
  mySerial.println("AT+CMGS=\"+919008791799\"\r");
  delay(1000);
  mySerial.println(message);// The SMS text you want to send
  delay(100);
   mySerial.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  Serial.println("Message sent");
}

float check_temp()
{ 
  Serial.println("temp loop");
  temprs;
  temprs = analogRead(tempPin);
  Serial.println(temprs);
   // read analog volt from sensor and save to variable temp
   tempr = temprs * 0.48828125;
   // convert the analog volt to its temperature equivalent
   delay(5000); 
  // Serial.print("TEMPERATURE = ");
   //Serial.print(tempr); // display temperature value
   //Serial.print("*C");
   //rial.println();
   
   return tempr;
  
}

void setBrightness(int led, int brightness) {
  // set the brightness of pin 9:
  Serial.println("seeting brightness");
  analogWrite(led, brightness);
  // change the brightness for next time through the loop:
  delay(3000);
}
