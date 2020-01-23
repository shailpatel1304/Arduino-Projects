#include <Servo.h>    //including servo libaries 
#define SERVO1 8      
#define PHOTORESIS A0 
#define BUTTON 11
#define LED 12

Servo s1;   //name of servo
int pos = 0;    //position variable for servo
int i = 0;    //variable for loops
int valueArray[20];   //Array to hold photoresistor values
int maxdegree = 18;   //maxdegree that servo can reach
int stepdegree = 10;    //servo will rotate in 10 degree increments
int maxValue = 0;   //global variable for max value of photoresistor
int locaofmaxValue = 0;   //location of the max value, At which degree was this
int counter = 0;

void setup() {
  s1.attach(SERVO1);    //assign pin to servo
  s1.write(pos);    //rotate server to 0
  delay(1000);
  Serial.begin(9600);
  Serial.println("Program will Start");
  pinMode(BUTTON, INPUT_PULLUP);    //assign pin to INPUT, PULLUP is used as a virtual resistor for the switch
  pinMode(LED, OUTPUT);   //assign pin to OUTPUT
}

void scan(){    //scan function will rotate servo from 0 to 180 tracking the values of the photoresistor
  digitalWrite(LED, HIGH);    //LED will turn on when scan is inilizied 
  for(pos = 0; pos<= maxdegree; pos++){   //loop to go from 0 to 180 in 10 degree increments
    Serial.print("Going to " );Serial.print(pos*stepdegree);Serial.println(" Degrees");
    s1.write(pos*stepdegree);
    valueArray[pos] = analogRead(PHOTORESIS);   //at each spot of the array, record the value observed by the photoresistor
    Serial.print("Array at spot " );Serial.print(pos);Serial.print(" has value ");Serial.println(valueArray[pos]);
    delay(40);
  }
  delay(2000);
  s1.write(0);    //go back to 0
}

void maxvalueFinder(){    //this function will find the max value recorded by the photoresistor and at which degree that max value was found at
  maxValue = valueArray[i];
  locaofmaxValue = i;
  for(i = 0; i <= maxdegree; i++){    //standard algorthim to find max value
    if(valueArray[i] > maxValue){
      maxValue = valueArray[i];
      locaofmaxValue = i;
    }
  }
  Serial.print("Max Value is ");Serial.print(maxValue);Serial.print(" at Array Spot ");Serial.println(locaofmaxValue);
}

void movServo(){    //function to move the servo to the correct position with the greated value recorded by the photoresistor
  s1.write(locaofmaxValue*stepdegree);
  delay(200);
  counter = 1;
  digitalWrite(LED, LOW);
}
void loop() {
  if(counter == 0){   //main functions to find at which degree has the greatest amount of light reaching the photoresistor
    scan();
    maxvalueFinder();
    movServo();
  }
  if(counter == 1){   //once a max value is found and the servo is pointing to it
    int currentValue = analogRead(PHOTORESIS);    //keep reading the values from the photoresistor
    if(currentValue < maxValue-100 || digitalRead(BUTTON) == LOW){    //when the photoresistor value decreses or a button is pressed
      counter = 0;    //rerun main functions to find the new degree
      delay(1000);
    }
  }
}
