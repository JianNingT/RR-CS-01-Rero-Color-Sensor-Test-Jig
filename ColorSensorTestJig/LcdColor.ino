#include <SoftwareSerial.h>
#include <LCD4Bit_mod.h>
#include <Servo.h>
Servo myServo;
#define TxMode LOW    // Master transmit to G15
#define RxMode HIGH   // Master receive from G15
#define CTRL 2

SoftwareSerial mySerial(0, 1);
LCD4Bit_mod lcd = LCD4Bit_mod(2); 
byte errStatus =0;
byte result = 0;
byte redval = 0;
byte greenval = 0;
byte blueval = 0;
byte clrtest = 0; // 0=? 1=black 2=red 3=green 4=blue
byte test1 = 0;
byte test2 = 0;
byte test3 = 0;
byte test4 = 0;

//LCD
int  adc_key_val[5] ={30, 150, 360, 535, 760 };
int NUM_KEYS = 5;
int adc_key_in;
int key=-1;
int oldkey=-1;



void setup() {

  pinMode(2, OUTPUT);
  pinMode(13,OUTPUT);

  myServo.attach(11,544,2700);
  myServo.write(544);

   lcd.init();
   lcd.clear();
   lcd.cursorTo(1,0);
   lcd.printIn("CYTRON TECH.");
   lcd.cursorTo(2, 0);
   lcd.printIn("Colour Test Jig");  
   digitalWrite(13,HIGH);
   delay(1000);
   digitalWrite(13,LOW);

}

void loop(){

//Waiting for Sensor

  lcd.clear();
  lcd.cursorTo(1,0);
  lcd.printIn("Connect Sensor");
  lcd.cursorTo(2,0);
  lcd.printIn("Press 'Select'");
  result = 0;

  while(result == 0){

  adc_key_in = analogRead(0);    // read the value from the sensor  
  key = get_key(adc_key_in);            // convert into key press
  
  if (key != oldkey)            // if keypress is detected
  {
    delay(50);    // wait for debounce time
    adc_key_in = analogRead(0);    // read the value from the sensor  
    key = get_key(adc_key_in);            // convert into key press
    if (key != oldkey)        
    {     
      oldkey = key;
      if (key >=0){
        result = 1;
        if (key == 4){
            mySerial.begin(19200);
        }
        else{

            //Select not pressed. Reseting Baud Rate from 
            
            lcd.clear();
            lcd.cursorTo(1,0);
            lcd.printIn("Reseting");
            lcd.cursorTo(2,0);
            lcd.printIn("Baud Rate");
            mySerial.begin(115200);
            result = writeCsBd(0x69);
            delay(1000);
            lcd.clear();
              if(result == 0){
                lcd.cursorTo(1,0);
                lcd.printIn("BaudRate Reset");
                lcd.cursorTo(2,0);
                lcd.printIn("Successful");
                
                }
                else{
                  lcd.cursorTo(1,0);
                  lcd.printIn("Unknown Error");
              }
              digitalWrite(13,HIGH);
              delay(1000);
              digitalWrite(13,LOW);
              while(1){}
  
          }
      }
    }
  
  }
  }

  result = 0;
  
//Check if Baud Rate is default (19200).
  lcd.clear();

  lcd.cursorTo(1,0);
  lcd.printIn("CheckingBaudRate");

  byte baudRateCheck = readCsBd(0x69);

  delay(1000);

  lcd.clear();
 
  if(errStatus == 0){
  lcd.cursorTo(1,0);
  lcd.printIn("Baud Rate");
  lcd.cursorTo(2,0);
  lcd.printIn("Check Complete");
  }
  else{
    lcd.cursorTo(1,0);
    lcd.printIn("Can't Connect");
    lcd.cursorTo(2,0);
    lcd.printIn("To Sensor");
    digitalWrite(13,HIGH);
    delay(1000);
    digitalWrite(13,LOW);
    while(1){}
  }

//Begin Sensor Testing

  lcd.clear();
  lcd.cursorTo(1,0);
  lcd.printIn("Begin Sensor");
  lcd.cursorTo(2,0);
  lcd.printIn("Testing");
  myServo.write(2200);
  delay(1500);
  
//Test Black
  lcd.clear();
  lcd.cursorTo(1,0);
  lcd.printIn("Testing Black");
  lcd.cursorTo(2,0);
  lcd.printIn("Detected: ");
      redval = readCsRed(0x69);
      greenval = readCsGreen(0x69);
      blueval = readCsBlue(0x69);
      if( redval >= greenval + blueval){
        lcd.printIn("Red");
        clrtest = 2;
      }
      else if ( greenval >= redval + blueval){
        lcd.printIn("Green");
        clrtest = 3;
      }
      else if ( blueval >= redval + greenval){
        lcd.printIn("Blue");
        clrtest = 4;
      }
      else if ( 15 >= blueval + redval + greenval){
        lcd.printIn("Black");
        clrtest = 1;
      }
      else{
        lcd.printIn("???");
        clrtest = 0;
      }
      delay(1000);

      test1 = clrtest;
      clrtest = 0;

//Test Red
  lcd.clear();
  lcd.cursorTo(1,0);
  lcd.printIn("Testing Red");
  myServo.write(1600);
  lcd.cursorTo(2,0);
  lcd.printIn("Detected: ");
  delay(1000);
      redval = readCsRed(0x69);
      greenval = readCsGreen(0x69);
      blueval = readCsBlue(0x69);
      if( redval >= greenval + blueval){
        lcd.printIn("Red");
        clrtest = 2;
      }
      else if ( greenval >= redval + blueval){
        lcd.printIn("Green");
        clrtest = 3;
      }
      else if ( blueval >= redval + greenval){
        lcd.printIn("Blue");
        clrtest = 4;
      }
      else if ( 15 >= blueval + redval + greenval){
        lcd.printIn("Black");
        clrtest = 1;
      }
      else{
        lcd.printIn("???");
        clrtest = 0;
      }
      delay(1000);

      test2 = clrtest;
      clrtest = 0;
      
//Test Green
  lcd.clear();
  lcd.cursorTo(1,0);
  lcd.printIn("Testing Green");
  myServo.write(1100);
  lcd.cursorTo(2,0);
  lcd.printIn("Detected: ");
  delay(1000);
      redval = readCsRed(0x69);
      greenval = readCsGreen(0x69);
      blueval = readCsBlue(0x69);
      if( redval >= greenval + blueval){
        lcd.printIn("Red");
        clrtest = 2;
      }
      else if ( greenval >= redval + blueval){
        lcd.printIn("Green");
        clrtest = 3;
      }
      else if ( blueval >= redval + greenval){
        lcd.printIn("Blue");
        clrtest = 4;
      }
      else if ( 15 >= blueval + redval + greenval){
        lcd.printIn("Black");
        clrtest = 1;
      }
      else{
        lcd.printIn("???");
        clrtest = 0;
      }
      delay(1000);

      test3 = clrtest;
      clrtest = 0;
      
//Test Green
  lcd.clear();
  lcd.cursorTo(1,0);
  lcd.printIn("Testing Blue");
  myServo.write(544);
  lcd.cursorTo(2,0);
  lcd.printIn("Detected: ");
  delay(1000);
      redval = readCsRed(0x69);
      greenval = readCsGreen(0x69);
      blueval = readCsBlue(0x69);
      if( redval >= greenval + blueval){
        lcd.printIn("Red");
        clrtest = 2;
      }
      else if ( greenval >= redval + blueval){
        lcd.printIn("Green");
        clrtest = 3;
      }
      else if ( blueval >= redval + greenval){
        lcd.printIn("Blue");
        clrtest = 4;
      }
      else if ( 15 >= blueval + redval + greenval){
        lcd.printIn("Black");
        clrtest = 1;
      }
      else{
        lcd.printIn("???");
        clrtest = 0;
      }
      delay(1000);

      test4 = clrtest;
      clrtest = 0;
      
//Test Results
result = 0;
if(test1 == 1){
  }
  else{
    digitalWrite(13,HIGH);
    delay(250);
    digitalWrite(13,LOW);
    delay(250);
    digitalWrite(13,HIGH);
    delay(250);
    digitalWrite(13,LOW);
    delay(250);
    digitalWrite(13,HIGH);
    delay(250);
    digitalWrite(13,LOW);
    delay(250);
   result = 1;
   lcd.clear();
   lcd.cursorTo(1,0);
   lcd.printIn("Black: Failed");
   lcd.cursorTo(2,0);
   lcd.printIn("Sensed: ");
   if( test1 == 1){
    lcd.printIn("Black");
   }
   else if ( test1 == 2){
    lcd.printIn("Red");
   }
   else if ( test1 == 3){
    lcd.printIn("Green");
   }
   else if ( test1 == 4){
    lcd.printIn("Blue");
   }
   else{
    lcd.printIn("non RGB");
   }
   digitalWrite(13,HIGH);
   delay(250);
   digitalWrite(13,LOW);
   delay(2000);
   }

if(test2 == 2){
  }
  else{
   result = 1;
   lcd.clear();
   lcd.cursorTo(1,0);
   lcd.printIn("Red: Failed");
   lcd.cursorTo(2,0);
   lcd.printIn("Sensed: ");
   if( test2 == 1){
    lcd.printIn("Black");
   }
   else if ( test2 == 2){
    lcd.printIn("Red");
   }
   else if ( test2 == 3){
    lcd.printIn("Green");
   }
   else if ( test2 == 4){
    lcd.printIn("Blue");
   }
   else{
    lcd.printIn("non RGB");
   }
   digitalWrite(13,HIGH);
   delay(250);
   digitalWrite(13,LOW);
   delay(2000);
   }

if(test3 == 3){
  }
  else{
   result = 1;
   lcd.clear();
   lcd.cursorTo(1,0);
   lcd.printIn("Green: Failed");
   lcd.cursorTo(2,0);
   lcd.printIn("Sensed: ");
   if( test3 == 1){
    lcd.printIn("Black");
   }
   else if ( test3 == 2){
    lcd.printIn("Red");
   }
   else if ( test3 == 3){
    lcd.printIn("Green");
   }
   else if ( test3 == 4){
    lcd.printIn("Blue");
   }
   else{
    lcd.printIn("non RGB");
   }
   digitalWrite(13,HIGH);
   delay(250);
   digitalWrite(13,LOW);
   delay(2000);
   }

if(test4 == 4){
  }
  else{
   result = 1;
   lcd.clear();
   lcd.cursorTo(1,0);
   lcd.printIn("Blue: Failed");
   lcd.cursorTo(2,0);
   lcd.printIn("Sensed: ");
   if( test4 == 1){
    lcd.printIn("Black");
   }
   else if ( test4 == 2){
    lcd.printIn("Red");
   }
   else if ( test4 == 3){
    lcd.printIn("Red");
   }
   else if ( test4 == 4){
    lcd.printIn("Red");
   }
   else{
    lcd.printIn("non RGB");
   }
   digitalWrite(13,HIGH);
   delay(250);
   digitalWrite(13,LOW);
   delay(2000);
   lcd.clear();
   lcd.cursorTo(1,0);
   lcd.printIn("Test: Fail");
   digitalWrite(13,HIGH);
   delay(250);
   digitalWrite(13,LOW);
   }

if( result == 0){
   lcd.clear();
   lcd.cursorTo(1,0);
   lcd.printIn("Test: Pass");
   digitalWrite(13,HIGH);
   delay(1000);
   digitalWrite(13,LOW);
   delay(1000);
}
else{}

  while (pingCs(0x69) == 0){
  }


}



