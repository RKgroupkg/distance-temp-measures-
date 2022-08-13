
#include <LiquidCrystal.h>
#include <dht.h>

dht DHT;


const int rs = 3, en = 8, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#define trigPin A5 // define TrigPin
#define echoPin A4 // define EchoPin.
#define MAX_DISTANCE 250 
#define DHT11_PIN 11

int button_1 =9;
int button_2 =10;
int range = 0;
int mode =0;
float calculate ;
int buzzer = A3;


int button_4 =12;



float timeOut = MAX_DISTANCE * 60; 
int soundVelocity = 340;
float Distance_sonar;  



float getSonar() {
  unsigned long pingTime;
  float distance;
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pingTime = pulseIn(echoPin, HIGH, timeOut); 
  distance = (float)pingTime * soundVelocity / 2 / 10000;
  return distance; 
}

void intro(){
   lcd.clear();
   lcd.setCursor(1, 0);
   lcd.write("Distance/termo");
   lcd.setCursor(3, 1);
   lcd.write("Measurer");
   delay(1000);
   for (int j = 0;j!=10;j++){
    lcd.scrollDisplayRight();
    delay(500);
    }
     lcd.clear();
      lcd.setCursor(6, 0);
     lcd.write("By");
     lcd.setCursor(0, 1);
     lcd.write("Ravi Ketan Raj");
     delay(1000);
     for (int j = 0;j!=10;j++){
          lcd.scrollDisplayRight();
          delay(500);
    }
    lcd.clear();
    lcd.setCursor(2, 0);
    for(int j=0;j!=4;j++){
      lcd.clear();
       lcd.setCursor(2, 0);
      lcd.write("Loding...");
      delay(500);
      lcd.clear();
       lcd.setCursor(2, 0);
      lcd.write("Loding..");
      delay(500);
      lcd.clear();
       lcd.setCursor(2, 0);
      lcd.write("Loding.");
      delay(500);
    }
  
  
  }
  void temp_humid (){
    int chk = DHT.read11(DHT11_PIN);
       lcd.setCursor(0, 1);
       lcd.print("T:");
       lcd.setCursor(2, 1);
       if (DHT.temperature == -999&DHT.humidity == -999){
         lcd.setCursor(0, 1);
       lcd.print("Sensor not found");
        }else{
       lcd.print(DHT.temperature);
       lcd.setCursor(7, 1);
       lcd.print("C");
        lcd.setCursor(9, 1);
       lcd.print("H:");
       lcd.setCursor(11, 1);
       lcd.print(DHT.humidity);}

    }


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

 
  pinMode(trigPin,OUTPUT);
  pinMode(echoPin,INPUT);
  pinMode(button_1,INPUT);
  pinMode(button_2,INPUT);
  pinMode(buzzer,OUTPUT);
 
  pinMode(button_4,INPUT);
  Serial.begin(9600); 
  if (digitalRead(button_2)== HIGH||digitalRead(button_4)== HIGH){
    
    }else{
    intro();
    }
   while (digitalRead(button_4)== HIGH){
    lcd.clear();
      lcd.write("pls dont preess button");
      lcd.setCursor(0, 1);
      lcd.write("to go activate it:");
      delay(10);
    }
   
}

void loop() {
  delay(100);
 
    Distance_sonar = getSonar(); 
   
  if (digitalRead(button_2)== HIGH){
    range++;
    Serial.println("button 2 pressed");
    Serial.println(range);
 
    
    while(digitalRead(button_2)== HIGH){
      delay(5);
      lcd.clear();
      lcd.write("range:");
       lcd.setCursor(0, 1);
       lcd.print(range);
       lcd.print("cm");
      
   
      }
 
    if ( mode ==4){
        mode = 0;
      }
    }
  if (digitalRead(button_1)== HIGH){
    mode++;
    Serial.println("button 1 pressed");
    Serial.println(mode);
 
    
    while(digitalRead(button_1)== HIGH){
      delay(5);
      lcd.clear();
      lcd.write("changed unit");
      lcd.setCursor(0, 1);
      lcd.write("Distance");
   
      }
 
    if ( mode ==4){
        mode = 0;
      }
    }
    
  
  
lcd.clear();

  if ( mode == 0){
  
    lcd.write("Dist:");
    
    lcd.setCursor(5, 0);
    lcd.print(Distance_sonar);
    lcd.print("cm");
  }else if (mode == 1){
    
    lcd.write("Dist:");
    int sonar_value = Distance_sonar;
    calculate = sonar_value/2.54;
      lcd.setCursor(5, 0);
      lcd.print(calculate);
      lcd.print("in");
    }else if (mode == 2) {
       
       lcd.write("Dist:");
       int sonar_value = Distance_sonar;
       calculate = sonar_value/30.48;
        lcd.setCursor(5, 0);
        lcd.print(calculate);
        lcd.print("foot");
      }else if (mode == 3) {
       
       lcd.write("Dist:");
       int sonar_value = Distance_sonar;
       calculate = sonar_value*10;
        lcd.setCursor(5, 0);
        lcd.print(calculate);
        lcd.print("mm");
      }
  
      if (Distance_sonar<range & range > 2){
        digitalWrite(buzzer,HIGH);
        lcd.clear();
        lcd.print("found an object");
        delay(10);
       
        }else {
          
          digitalWrite(buzzer,LOW);
          temp_humid ();
          } 

     if (digitalRead(button_4) == HIGH){
      lcd.clear();
      lcd.print("Are you sure");
      lcd.setCursor(0,1);
      lcd.print("-press again- ");
      delay(2000);
      lcd.clear();
      lcd.print("If not want prees other button");
      delay(2000);
      
     
        if (digitalRead(button_4) == HIGH){
          manual();
          }
      }     
       
         
            
            

    
}


void manual(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("How to use :-");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("-this device is uesd");
  lcd.setCursor(0, 1);
  lcd.print("mesure distance and temprature");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("It can show many unit of");
  lcd.setCursor(0, 1);
  lcd.print("distance as your like.");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("to change the unit of distance");
  lcd.setCursor(0, 1);
  lcd.print("just press yellow button");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("you can also set range");
  lcd.setCursor(0, 1);
  lcd.print("just press red button");
  delay(3000);
   lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("if want to see button info keep");
  lcd.setCursor(0, 1);
  lcd.print(" -press that button-");
  delay(3000);
  lcd.setCursor(0, 0);
  lcd.print("Made by:-");
  lcd.setCursor(0, 1);
  lcd.print("Ravi ketan raj");
  delay(3000);
  }
