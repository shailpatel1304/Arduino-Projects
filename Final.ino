#include <Servo.h>    //including servo libaries 
#include <SoftwareSerial.h>
#define SERVO1 13
#define Photoresistor A5
#define MotorBack 7   
#define MotorForward 8   
#define MotorLeft 9   
#define MotorRight 11   
#define trig 2
#define echo 3
#define FrontLights 12

SoftwareSerial mySerial(0, 1); // RX | TX
int val;    //variable to hold Serial.reads value
int ultrasounddelay = 2000;
int sensityofdistance = 20;
int sensitofPhotoresistor = 500;
long duration;    //how long it took ultrasonic sensor to recieve sound wave
long distance;    //the calculated distance to an object
int distanceArray[3];   //array to hold values of distance at each 
Servo s1;   //name of servo
int pos = 90;    //position variable for servo
int i = 0;    //variable for loops
int maxdegree = 2;   //maxdegree that servo can reach
int stepdegree = 90;    //servo will rotate in 10 degree increments
int maxValue = 0;   //global variable for max value of photoresistor
int locaofmaxValue = 0;   //location of the max value, At which degree was this

void setup(){
  //defining pins and pinmodes
  pinMode(MotorBack, OUTPUT);
  pinMode(MotorLeft, INPUT);
  pinMode(MotorRight, INPUT);
  pinMode(MotorForward, OUTPUT);
  pinMode(FrontLights, OUTPUT);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  //setting all functions to LOW
  digitalWrite(MotorBack, LOW);
  digitalWrite(MotorForward, LOW);
  digitalWrite(MotorLeft, LOW);
  digitalWrite(MotorRight, LOW);
  digitalWrite(FrontLights, LOW);
  s1.attach(SERVO1);    //assign pin to servo
  s1.write(pos);    //rotate server to 90
  Serial.begin(9600);
  mySerial.begin(9600);   //starting bluetooth controller
  Serial.println("Starting Code in 5 Seconds");
  delay(5000); 
}

void ultrasonic(){    //function to run ultrasonic sensor
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);   //emmit a soundwave
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  duration = pulseIn(echo, HIGH);   //read the emitted soundwave
  distance = duration * 0.034 / 2;    //calculate the distance to object
}

void distancesensor(){    //function to check which direction has a least objects in its path
  for(pos = 0; pos <= maxdegree; pos++) { //loop to go from 0 to 180 in 90 degree increments
    Serial.print("Going to " ); Serial.print(pos * stepdegree); Serial.println(" Degrees");
    s1.write(pos * stepdegree);
    delay(ultrasounddelay);
    ultrasonic();
    distanceArray[pos] = distance;
    Serial.print("Array at spot " ); Serial.print(pos); Serial.print(" has value "); Serial.println(distanceArray[pos]);
  }
  s1.write(90);    //go back to 90
  delay(40);    //delay to wait for server to move to 90
  maxValue = distanceArray[i];
  locaofmaxValue = i;
  for(i = 0; i <= maxdegree; i++) {  //standard algorthim to find max value
    if(distanceArray[i] > maxValue) {
      maxValue = distanceArray[i];
      locaofmaxValue = i;
    }
  }
  distance = distanceArray[locaofmaxValue];
  Serial.print("Max Value is "); Serial.print(maxValue); Serial.print(" at Array Spot "); Serial.println(locaofmaxValue);
}

void scanning(){    //function to prevent the car from driving into an object
  while(distance > sensityofdistance) {
    ultrasonic();
  }
  Stop();
}

void Forward(){   //control motors to go forward
  digitalWrite(MotorBack, LOW);
  Serial.println("Going Forward");
  digitalWrite(MotorForward, HIGH);
}

void Backward(){    //control motors to go backwards
  digitalWrite(MotorForward, LOW);
  Serial.println("Going Backwark");
  digitalWrite(MotorBack, HIGH);
}

void Left(){    //control motors to go left
  digitalWrite(MotorRight, LOW);
  Serial.println("Turning Left");
  digitalWrite(MotorLeft, HIGH);
}

void Right(){   //control motors to go right
  digitalWrite(MotorLeft, LOW);
  Serial.println("Turning Right");
  digitalWrite(MotorRight, HIGH);
}

void Stop(){    //stop all motors
  digitalWrite(MotorForward, LOW);
  digitalWrite(MotorBack, LOW);
  digitalWrite(MotorLeft, LOW);
  digitalWrite(MotorRight, LOW);
}

void NoTurn(){    //reset the left and right motors to go striaght
  digitalWrite(MotorLeft, LOW);
  digitalWrite(MotorRight, LOW);
}

void Mode1(){   //ultrasonic mode
  if(distance <= sensityofdistance){   //once the car is really close to an object
      Backward();   //first go backward for 2 seconds then find which direction has the longest distance to an object
      delay(2000);
      Stop();
      distancesensor();
  }
  if(locaofmaxValue == 0 && distance > sensityofdistance){    //if the longest distance to an object is at 0 degrees
    Right();    //go right and forward and keep scanning the distance
    Forward();
    scanning();
  }
  if(locaofmaxValue == 1 && distance > sensityofdistance){    //if the longest distance to an object is at 90 degrees
    Forward();    //keep going forward and keep scanning the distance
    scanning();
  }
  if(locaofmaxValue == 2 && distance > sensityofdistance){    //if the longest distance to an obkect is at 180 degrees
    Left();   //go left and forward and keep scanning the distance
    Forward();
    scanning();
  }
}

void loop(){
  if(mySerial.available()){   //if bluetooth connection is available
    val = mySerial.read();    //read the values being recieved by Bluetooth controller
    //code for automatic headlights
    if(analogRead(Photoresistor)< sensitofPhotoresistor){
      digitalWrite(FrontLights, HIGH);
    }
    if(analogRead(Photoresistor) >= sensitofPhotoresistor){
      digitalWrite(FrontLights, LOW);
    }
    //code to check which button was pressed by the user on the smartphone app
    if(val == 'F'){
      Forward();
    }
    if(val == 'B'){
      Backward();
    }
    if(val == 'L'){
      Left();
    }
    if(val == 'R'){
      Right();
    }
    if(val == 'W'){
      NoTurn();
    }
    if(val == 'U'){
      Stop();
    }
    //if V is pressed then switch to Mode1 which is Ultrasonic mode/Autonomious Mode
    if(val == 'V'){
      Mode1();
    }
  }
}
