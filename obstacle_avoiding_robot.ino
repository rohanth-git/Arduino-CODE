
#include <AFMotor.h>
#include <NewPing.h>
#include <Servo.h> 

#define TRIG_PIN A1 
#define ECHO_PIN A0 
#define MAX_DISTANCE 200 
#define MAX_SPEED 190 // sets speed of DC  motors
#define MAX_SPEED_OFFSET 20
#define left_led A3
#define right_led A4


NewPing sonar(TRIG_PIN, ECHO_PIN, MAX_DISTANCE); 

AF_DCMotor motor1(1, MOTOR12_64KHZ); 
AF_DCMotor motor2(4, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR12_64KHZ);
AF_DCMotor motor4(2, MOTOR12_64KHZ);
Servo myservo;   

boolean goesForward=false;
int distance = 100;
int speedSet = 0;

void setup() {
  
  myservo.attach(9);  
  myservo.write(105); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  pinMode (left_led,OUTPUT);
  pinMode (right_led,OUTPUT);
}

void loop() {
 int distanceR = 0;
 int distanceL =  0;
 delay(40);
 digitalWrite(left_led,LOW);
 digitalWrite(right_led,LOW);
 
 if(distance<=15)
 {
  moveStop();
  delay(100);
  digitalWrite(left_led,HIGH);
  digitalWrite(right_led,HIGH);
  moveBackward();
  delay(400);
  digitalWrite(left_led,LOW);
  digitalWrite(right_led,LOW);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL)
  {
    
    
    turnRight();
    moveStop();
  }else
  {
    
    turnLeft();
    moveStop();
  }
 }else
 {
  moveForward();
 }
 distance = readPing();
 
}
void blinking(){
  digitalWrite(left_led,LOW);
  digitalWrite(right_led,LOW);
  delay(30);
  digitalWrite(left_led,HIGH);
  digitalWrite(right_led,HIGH);
  delay(3);
  digitalWrite(left_led,LOW);
  digitalWrite(right_led,LOW);
  delay(30);
  digitalWrite(left_led,HIGH);
  digitalWrite(right_led,HIGH);  
}
int lookRight()
{
    myservo.write(30); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(105); 
    return distance;
}

int lookLeft()
{
    myservo.write(180); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(105); 
    return distance;
    delay(100);
}

int readPing() { 
  delay(70);
  int cm = sonar.ping_cm();
  if(cm==0)
  {
    cm = 250;
  }
  return cm;
}

void moveStop() {
  motor1.run(RELEASE); 
  motor2.run(RELEASE);
  motor3.run(RELEASE); 
  motor4.run(RELEASE);
 
  } 
  
void moveForward() {

 if(!goesForward)
  {
    goesForward=true;
    motor1.run(FORWARD);      
    motor2.run(FORWARD);
    motor3.run(FORWARD);      
    motor4.run(FORWARD);      
   for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2) 
   {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
   }
  }
}

void moveBackward() {
    goesForward=false;
    motor1.run(BACKWARD);      
    motor2.run(BACKWARD);
    motor3.run(BACKWARD);      
    motor4.run(BACKWARD); 
    
  for (speedSet = 0; speedSet < MAX_SPEED; speedSet +=2)
  {
    motor1.setSpeed(speedSet);
    motor2.setSpeed(speedSet+MAX_SPEED_OFFSET);
    delay(5);
  }
}  

void turnRight() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
  motor3.run(BACKWARD);
  motor4.run(FORWARD);
  digitalWrite(right_led,HIGH);     
  delay(2000);
  motor1.run(FORWARD);      
  motor2.run(FORWARD);
  motor3.run(FORWARD);      
  motor4.run(FORWARD);      
} 
 
void turnLeft() {
  motor1.run(FORWARD);     
  motor2.run(BACKWARD);
  motor3.run(FORWARD);     
  motor4.run(BACKWARD);
  digitalWrite(left_led,HIGH);
  delay(2000);
  motor1.run(FORWARD);     
  motor2.run(FORWARD);
  motor3.run(FORWARD);     
  motor4.run(FORWARD);
}  


