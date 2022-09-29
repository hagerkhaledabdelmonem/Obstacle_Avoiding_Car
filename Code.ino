#include <Servo.h>
#define motor1_pin1  5
#define motor1_pin2  4
#define motor2_pin1  3
#define motor2_pin2  2
#define ENA  7
#define ENB  6

#define car_speed 100

#define trig  10
#define echo  11

Servo myservo;

void setup() {
  Serial.begin(9600);

  // motors pins

  pinMode(motor1_pin1, OUTPUT);
  pinMode(motor1_pin2, OUTPUT);
  pinMode(motor2_pin1, OUTPUT);
  pinMode(motor2_pin2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  // ultrasoinc pins

  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  myservo.attach(12);
  myservo.write(90);
}

void loop() {
  float duration , distance;
  digitalWrite (trig, LOW);
  delayMicroseconds(5);
  digitalWrite (trig, HIGH);
  delayMicroseconds(5);
  digitalWrite (trig, LOW);
  duration = pulseIn(echo, HIGH);
  distance = duration / 29 / 2;
  Serial.println(distance);
  
  if (distance > 5) {
    myservo.write(180);
    stright();
  }
  else {
    car_stop();
    delay(1000);
    checkRight();
    if (distance > 5) {
      myservo.write(180);
      car_right();
    }
    else {
      car_stop();
      delay(1000);
      checkLeft();
      if (distance > 5){
        myservo.write(180);
        car_left();
      }
      else{
        myservo.write(180);
        backforwd();
      }
        
    }

  }


}


void stright() {
  
  analogWrite(ENA , car_speed);
  analogWrite(ENB , car_speed);
  digitalWrite (motor1_pin1 , HIGH);
  digitalWrite (motor1_pin2 , LOW);
  digitalWrite (motor2_pin1 , HIGH);
  digitalWrite (motor2_pin2 , LOW);
}

void backforwd() {

  analogWrite(ENA , car_speed);
  analogWrite(ENB , car_speed);
  digitalWrite (motor1_pin1 , LOW);
  digitalWrite (motor1_pin2 , HIGH);
  digitalWrite (motor2_pin1 , LOW);
  digitalWrite (motor2_pin2 , HIGH);


  
}

void car_stop() {
  digitalWrite (motor1_pin1 , LOW);
  digitalWrite (motor1_pin2 , LOW);
  digitalWrite (motor2_pin1 , LOW);
  digitalWrite (motor2_pin2 , LOW);
}
void car_left() {
   
  analogWrite(ENA , car_speed);
  analogWrite(ENB , car_speed);
  digitalWrite (motor1_pin1 , HIGH);
  digitalWrite (motor1_pin2 , LOW);
  digitalWrite (motor2_pin1 , LOW);
  digitalWrite (motor2_pin2 , HIGH);
}
void car_right() {
  analogWrite(ENA , car_speed);
  analogWrite(ENB , car_speed);
  digitalWrite (motor1_pin1 , LOW);
  digitalWrite (motor1_pin2 , HIGH);
  digitalWrite (motor2_pin1 , HIGH);
  digitalWrite (motor2_pin2 , LOW);

  
}

void checkRight() {
  myservo.write(30);
  delay(100);
}
void checkLeft() {
  myservo.write(150);
  delay(100);
}
