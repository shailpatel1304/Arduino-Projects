#include <Servo.h>          //Servo motor library. This is standard library
#include <NewPing.h>        //Ultrasonic sensor function library. You must install this library

const int MotorForward = 7;
const int MotorBack = 8;
const int MotorRight = 9;
const int MotorLeft = 11;
#define maximum_distance 200
#define trig_pin A1 //analog input 1
#define echo_pin A2 //analog input 2


boolean MoveForward = false;
int distance = 100;

NewPing sonar(trig_pin, echo_pin, maximum_distance); //sensor function
Servo servo_motor; //our servo name


void setup(){

  pinMode(MotorForward, OUTPUT);
  pinMode(MotorRight, OUTPUT);
  pinMode(MotorBack, OUTPUT);
  pinMode(MotorLeft, OUTPUT);
  
  servo_motor.attach(13); //our servo pin

  servo_motor.write(90);
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){

  int RightDistance = 0;
  int LeftDistance = 0;
  delay(50);

  if (distance <= 20){
    Stop();
    delay(300);
    Backward();
    delay(400);
    Stop();
    delay(300);
    RightDistance = CheckRight();
    delay(300);
    LeftDistance = CheckLeft();
    delay(300);

    if (distance >= LeftDistance){
      Right();
      Stop();
    }
    else{
      Left();
      Stop();
    }
  }
  else{
    Forward(); 
  }
    distance = readPing();
}

int CheckRight(){  
  servo_motor.write(10);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
}

int CheckLeft(){
  servo_motor.write(170);
  delay(500);
  int distance = readPing();
  delay(100);
  servo_motor.write(90);
  return distance;
  delay(100);
}

int readPing(){
  delay(70);
  int cm = sonar.ping_cm();
  if (cm == 0){
    cm = 250;
  }
  return cm;
}

void Stop(){
  
  digitalWrite(MotorForward, LOW);
  digitalWrite(MotorBack, LOW);
  digitalWrite(MotorLeft, LOW);
  digitalWrite(MotorRight, LOW);
}

void Forward(){

  if(!MoveForward){

    MoveForward = true;
    digitalWrite(MotorBack, LOW);
    digitalWrite(MotorForward, HIGH);
  }
}

void Backward(){

  MoveForward = false;
  digitalWrite(MotorForward, LOW);
  digitalWrite(MotorBack, HIGH);
  
}

void Right(){

  digitalWrite(MotorLeft, LOW);
  digitalWrite(MotorRight, HIGH);
  delay(500);
  digitalWrite(MotorLeft, LOW);
  digitalWrite(MotorRight, HIGH);
}

void Left(){

  digitalWrite(MotorLeft, HIGH);
  digitalWrite(MotorRight, LOW);
  delay(500);
  digitalWrite(MotorLeft, HIGH);
  digitalWrite(MotorRight, LOW);
}
