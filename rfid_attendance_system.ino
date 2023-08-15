#include <SoftwareSerial.h> 
//#include <EEPROM.h>
SoftwareSerial myserial (D2,D3); //serial communication on d2 nd d3 pins where d2 acts as receiver nd d3 acts as transmitter
#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

int count=0;
String card_ID="";
String Name1="4C009624ED13";
String Name2="4C002BD5BE0C";
String Name3="4C0096695CEF";
//char* Name4="4C002CCFBC14";
int NumbCard[3];  //number of cards
int j=0;  
int statu[3];     //indicates the no.of times card is swiped if 0 that means card is swiped once, 1 indicates card is swiped for the second time 
int s=0;
int const Buzzer=8;

String Log;
String Name;//user name
String Number;//user number
int n ;//The number of card you want to detect (optional)  
int ID=1;

void setup() {
  lcd.begin(16, 2);
  myserial.begin(9600);
  Serial.begin(9600);
  Serial.println("CLEARSHEET");                 // clears starting at row 1
  Serial.println("LABEL,ID,Date,Name,Number,Card ID,Time IN,Time OUT");// make four columns (Date,Time,[Name:"user name"][Number:"user number"])

  
  pinMode(Buzzer,OUTPUT);
  
  lcd.setCursor(2,0);
  lcd.print("Welcome to VES");//Wlecome Message will appear in the beginning. 
  delay(200);
   }

void loop() {
  //look for new card
   if (myserial.available()) 
   {
    count=0;
    while(myserial.available() && count < 12)
    {
      card_ID[count]=myserial.read();
      count++;
      delay(5);
    }
      Serial.println(card_ID);
    }
   }
{    if(card_ID==Name1){
       Name="Rajat";//user name
       Number=1;//user number
       j=0;//incresd by one for every user you add
       s=0;//++1
      }
      else if(card_ID==Name2){
       Name="Varun";//user name
       Number=2;//user number
       j=1;//++1
       s=1;//++1
      }
      else if(card_ID==Name3){
       Name="Abhishek";//user name
       Number=3;//user number
       j=2;//++1
       s=2;//++1
      }
//      else if(card_ID==Name4){
//       Name="Pradeesh";//user name
//       Number=4;//user number
//       j=3;//++1
//       s=3;//++1
//      }

      else{
          digitalWrite(Buzzer,HIGH);
          goto cont;
     }
     {if(NumbCard[j] == 1 && statu[s] == 0){
      statu[s]=1;
      NumbCard[j] = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("Good Bye");
      lcd.setCursor(0,1);
      lcd.print(Name);
      Serial.print("DATA,");//send the Name to excel
      Serial.print(ID);
      Serial.print(",");
      Serial.print("DATE");
      Serial.print(",");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(Number); //send the user Number to excel
      Serial.print(",");
      Serial.print(card_ID); //send the card ID to excel
      Serial.print(",");
      Serial.print("");
      Serial.print(",");
      Serial.println("TIME Departed");
      ID=ID+1;
      }
      else if(NumbCard[j] == 0){
      NumbCard[j] = 1;
      statu[s]=0;
      n++;//(optional)
     lcd.clear();
     lcd.setCursor(4,0);
     lcd.print("Welcome ");
     lcd.setCursor(0,1);
     lcd.print(Name);
      Serial.print("DATA,");//send the Name to excel
      Serial.print(ID);
      Serial.print(",");
      Serial.print("DATE");
      Serial.print(",");
      Serial.print(Name);
      Serial.print(",");
      Serial.print(Number); //send the Number to excel
      Serial.print(",");
      Serial.print(card_ID); //send the card ID to excel
      Serial.print(",");
      Serial.print("TIME Arr");
      Serial.print(",");
      Serial.println("");
      ID=ID+1;
      }
      delay(1000);
cont:
delay(1000);
card_ID="";

//if(n==4)
//{
//    Serial.println("SAVEWORKBOOKAS,Names/WorkNames");
//    Serial.println("FORCEEXCELQUIT");
//    }
}
}

     

    

  
