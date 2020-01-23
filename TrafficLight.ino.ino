const int ledpin = 13;
  int n1 = 0; 
String number1 = "";
int n2 = 0;
String number2 = "";
int x = 0;
int i = 0; 
int y =0;
int redlight=0;
int greenlight=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledpin, OUTPUT);
  Serial.begin(9600);
  Serial.println("Enter Values:");
  delay(2000);
}
void Red(int x){
  Serial.print("Hello");
  digitalWrite(ledpin, HIGH);
 delay(x*1000);
  digitalWrite(ledpin, LOW);
}
void Green(int x){
  int d = x;
  while(d != 0){
    Serial.print("Bye");
    Serial.println(d);
    digitalWrite(ledpin, HIGH);
    delay(500);
    digitalWrite(ledpin, LOW);
    delay(500);
    d--;
    Serial.println(d);
  }
}
void loop() {
  // put your main code here, to run repeatedly:
  if(n1 == 0 || n2 == 0){
  if(Serial.available()){
    if(i == 0){
    n1 = Serial.read();
    number1 = n1;
    i++; 
    
    }
    else{
    if(y==0){
    n2 = Serial.read();
    number2 = n2; 
    y++;
//    Green(n2);
    }
//    Serial.end();
    }
  }
  }
  delay(2000);
  Serial.println("Values:");
  Serial.print("num1:");
  Serial.println(number1);
  Serial.print("num2:");
  Serial.println(number2);
   Serial.print("n1:");
  Serial.println(n1);
   Serial.print("n2:");
  Serial.println(n2);
  if(n1 != 0 && n2 !=0){
//    number1 = number1 - 48;
//    number2 = number2 - 48;
  Red(n1-48);
  Green(n2-48);
  }
}
