#include <SoftwareSerial.h>
#define MotorBack 11   //not yet implemented
#define MotorForward 9   //not yet implemented
#define MotorLeft 8   //not yet implemented
#define MotorRight 7   //not yet implemented

SoftwareSerial mySerial(0, 1); // RX | TX
int val;
void setup() {
   Serial.begin(9600);
   mySerial.begin(9600);
   Serial.println("You're connected via Bluetooth");
   pinMode(MotorRight,OUTPUT);   //left motors forward
   pinMode(MotorLeft,OUTPUT);   //left motors reverse
   pinMode(MotorForward,OUTPUT);   //right motors forward
   pinMode(MotorBack,OUTPUT);   //right motors reverse

}

void loop() {
   if (mySerial.available())
   {
    val=(mySerial.read());
    if (val == '1')
    {
      Serial.println("Forward");
     // Serial.println(Serial.read(val));
      Forward();
      /*digitalWrite(7,HIGH);
      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);*/           
    
    }
    
        else if (val =='2')
    {
      Serial.println("Reverse");
     // Serial.println(Serial.read(val));
      Backward();
      /*digitalWrite(7,LOW);
      digitalWrite(8,HIGH);
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);*/
    }
    
        else if (val =='3')
    {
      Serial.println("Left");
    //  Serial.println(Serial.read(val));
      Left();
      /*digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
      digitalWrite(10,LOW);*/
    }

        else if (val =='4')
    {
      Serial.println("Right");
      //Serial.println(Serial.read(val));
      Right();
      /*digitalWrite(5,HIGH);
      digitalWrite(6,LOW);
      digitalWrite(7,LOW);
      digitalWrite(8,LOW);*/
    }

        else if (val == ' ')
    {
      Serial.println("Stop");
      Stop();
      /*digitalWrite(7,LOW);
      digitalWrite(8,LOW);
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);*/
    }
   delay(30);
  }
}

void Forward(){
  digitalWrite(MotorBack, LOW);
  Serial.println("Going Forward");
  digitalWrite(MotorForward, HIGH);
}

void Backward(){
  digitalWrite(MotorForward, LOW);
  Serial.println("Going Backwark");
  digitalWrite(MotorBack, HIGH);
}

void Left(){ 
  digitalWrite(MotorRight, LOW);
  Serial.println("Turning Left");
  digitalWrite(MotorLeft, HIGH);
}

void Right(){
  digitalWrite(MotorLeft, LOW);
  Serial.println("Turning Right");
  digitalWrite(MotorRight, HIGH);
}

void Stop(){
  digitalWrite(MotorForward, LOW);
  digitalWrite(MotorBack, LOW);
  digitalWrite(MotorLeft, LOW);
  digitalWrite(MotorRight, LOW);
}
