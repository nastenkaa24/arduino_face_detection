
#include <Servo.h>
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
Servo servo1;
int servoPin=12;
int greenPin=9;
int redPin=2;
int buzzPin=4;


SoftwareSerial mp3Serial(10, 11);  
DFRobotDFPlayerMini myDFPlayer;
void setup(){
  Serial.begin(115200); 
  pinMode(redPin, OUTPUT);
 pinMode(greenPin, OUTPUT);
 pinMode(buzzPin,OUTPUT);
servo1.attach(servoPin);
servo1.write(180);

mp3Serial.begin(9600);    

if (!myDFPlayer.begin(mp3Serial)) {
     Serial.println("DFPlayer Mini NOT detected!");
     while (true); 
   }

   Serial.println("DFPlayer Mini READY!");

   myDFPlayer.volume(30); 
 }



void loop(){
  if(Serial.available()){
    String msg = Serial.readStringUntil('\n');
    msg.trim();

    Serial.print("PRIMIT: ");
    Serial.println(msg);

    if(msg == "FACE_OK"){
      digitalWrite(greenPin, HIGH);
      digitalWrite(redPin,LOW);
      servo1.write(0);
      Serial.println("Reda 0001.mp3");
      myDFPlayer.play(1); 
      delay(20000);
     
    }
    else if (msg== "No Match Found")
    {
      
      digitalWrite(redPin,HIGH);
      digitalWrite(greenPin, LOW);
      tone(4, 1000);
      servo1.write(180);
        delay(5000); 
         noTone(4); 

    }
    else
    {
        digitalWrite(redPin,LOW);
        digitalWrite(greenPin, LOW);
        servo1.write(180);
    }
  }
}
