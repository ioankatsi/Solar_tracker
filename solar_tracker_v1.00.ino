/**
 * @author      Ioannis Katsikavelas <>
                Dimitrios Tsoukantanas <d.tsoukantanas@yahoo.com 
 * @copyright   2015 - Ioannis Katsikavelas - Dimitrios Tsoukantanas
 * @license     {@link http://choosealicense.com/licenses/mit/ | MIT License}
 */
#include <Servo.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo Servo1 ;// x axis
Servo Servo2 ;//y axis

/*the cable colours also helped us on hardware installation 
  that's why we followed the pattern here too*/
  
const int GSensorPin = A0 ;//green left
const int BSensorPin = A1 ;//blue right
const int bSensorPin = A2 ;//brown bottom
const int OSensorPin = A3 ;//orange up

int blueSensor=0;
int greenSensor=0;
int brownSensor=0;
int orangeSensor=0;

//correction factor after reading ldrs due to their construction inaccuracy
int correctionBlue=1;
int correctionGreen=1;
int correctionOrange=1;
int correctionBrown=1;

const int dif=50;//difference for LDRs

int angle1 = 0 ;// x angle to write on servo
int angle2 = 0 ;//y angle to write on servo

int x = 0 ;


void setup()
  {
  lcd.begin(16,2);
  Servo1.attach(9) ;
  Servo2.attach(10) ;
  Serial.begin(9600);
  lcd.print("MADE BY : ") ;
  delay(3000);
  lcd.setCursor(0, 1);
  lcd.print("MWRAITIS .S");
  delay(3000);
  lcd.clear();
  lcd.print("MWRAITIS .N");
  delay(3000);
  lcd.clear();
  lcd.print("TSOUKANTANAS .D");
  delay(3000);
  lcd.clear();
  lcd.print("KATSIKAVELAS .I");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
}

void loop() 
{
  
   blueSensor=analogRead(BSensorPin)*correctionBlue;
   greenSensor=analogRead(GSensorPin)*correctionGreen;
   brownSensor=analogRead(bSensorPin)*correctionBrown;
   orangeSensor=analogRead(OSensorPin)*correctionOrange;
   
     if ( (abs(greenSensor - blueSensor) > dif) && ((greenSensor - blueSensor)>0) )  
     {
        angle1=angle1+5;
        if (angle1 >165)
        { 
          angle1=165;
        }
         Servo1.write(angle1);
        delay(45);
        }        
     else  if ( (abs(greenSensor - blueSensor) > dif) && ((greenSensor - blueSensor)<0) )
     {
       angle1=angle1-5;
       if (angle1 < 0)
       {
         angle1=0;
       }
        Servo1.write(angle1);
        delay (45);
     } 
     else
     {
       //do nothing
     }
    if ( (abs(brownSensor - orangeSensor)> dif) && ((brownSensor - orangeSensor)>0) )       
    {
        angle2=angle2+5;
        if (angle2 >179)
        { 
          angle2=179;
        }
         Servo2.write(angle2);
        delay(45);
        }        
     else if ( abs(brownSensor - orangeSensor) > dif && brownSensor - orangeSensor<0 ) 
     {
       angle2=angle2-5;
       if (angle2 < 0)
       {
         angle2=0;
       }
        Servo2.write(angle2);
        delay (45);
     }
     else
     {
        //do nothing
     }    
     
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Angle 1 : ");
     lcd.print(angle1);
     delay(100);
   
     lcd.setCursor(1,1);
     lcd.print("Angle 2 : ");
     lcd.print(angle2);
     delay(100);
     Serial.print(" ANGLE 1\t");
     Serial.print(angle1);
     Serial.print(" \t green  ");
     Serial.print(greenSensor);
     Serial.print(" \t blue  ");
     Serial.print(blueSensor);
     Serial.print(" difference ");
     Serial.print(greenSensor - blueSensor);
     
     Serial.print(" ANGLE 2\t");
     Serial.print(angle2);
     Serial.print(" \t brown ");
     Serial.print(brownSensor);
     Serial.print(" \t orange  ");
     Serial.print(orangeSensor);
     Serial.print(" difference ");
     Serial.println(brownSensor - orangeSensor);
     
     delay(1000);
     
}

