char n1 = 0;
String number1 = "";
int arr[10];
int i = 0;
int j = 0;
const int ledpin = 13;

void sleep(){
  delay(4000);
}
void dot(){
  digitalWrite(ledpin, HIGH);
  delay(1000);
  digitalWrite(ledpin, LOW);
  delay(1000);
}

void dash(){
  digitalWrite(ledpin, HIGH);
  delay(3000);
  digitalWrite(ledpin, LOW);
  delay(1000);
}
void One(){
  dot();dash();dash();dash();dash();
  sleep();
}
void Two(){
  dot();dot();dash();dash();dash();
  sleep();
}
void Three(){
  dot();dot();dot();dash();dash();
  sleep();
}
void Four(){
  dot();dot();dot();dot();dash();
  sleep();
}
void Five(){
  dot();dot();dot();dot();dot();
  sleep();
}
void Six(){
  dash();dot();dot();dot();dot();
  sleep();
}
void Seven(){
  dash();dash();dot();dot();dot();
  sleep();
}
void Eight(){
  dash();dash();dash();dot();dot();
  sleep();
}
void Nine(){
  dash();dash();dash();dash();dot();
  sleep();
}
void Zero(){
  dash();dash();dash();dash();dash();
  sleep();
}
void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin,OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter A String of Numbers : ");
}

void loop() {
  // put your main code here, to run repeatedly:
   if (Serial.available()) {
     n1 = Serial.read();
//       if (n1 != '\n') {
//        number1 += n1;
        arr[i] = n1;
        Serial.println(arr[i]);
        i++;
//       }
//       else {
//        Serial.print("Your String:");
//        Serial.println(number1);
 //      }
   }
//   delay(2000);
   if(arr[j] == '1'){
    One();
    j++;
   }
   if(arr[j] == '2'){
    Two();
    j++;
   }
   if(arr[j] == '3'){
    Three();
    j++;
   }
   if(arr[j] == '4'){
    Four();
    j++;
   }
   if(arr[j] == '5'){
    Five();
    j++;
   }
   if(arr[j] == '6'){
    Six();
    j++;
   }
   if(arr[j] == '7'){
    Seven();
    j++;
   }
   if(arr[j] == '8'){
    Eight();
    j++;
   }
   if(arr[j] == '9'){
    Nine();
    j++;
   }
   if(arr[j] == '0'){
    Zero();
    j++;
   }
}
