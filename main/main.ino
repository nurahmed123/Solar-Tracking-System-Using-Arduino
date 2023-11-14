#include <Servo.h>

///TODO:: solar control
const int upper_ldr = A0;
const int lower_ldr = A1;
const int error = 10;

int upper_ldr_value;
int lower_ldr_value;

int upper_ldr_value_filter;
int lower_ldr_value_filter;

int servo_starting_point = 90;
int servo_pin = 5;
Servo solarServo;


void setup() {
  ///TODO: solar 
  solarServo.attach(servo_pin);

  pinMode(upper_ldr, INPUT);
  pinMode(lower_ldr, INPUT);

  solarServo.write(servo_starting_point);
}

void loop() {
  upper_ldr_value = analogRead(upper_ldr);
  lower_ldr_value = analogRead(lower_ldr);

  upper_ldr_value_filter = abs(upper_ldr_value - lower_ldr_value);
  lower_ldr_value_filter = abs(lower_ldr_value - upper_ldr_value);

  if((upper_ldr_value_filter <= error) || (lower_ldr_value_filter <= error)){
    return;
  }else{
    if(upper_ldr_value > lower_ldr_value){
      servo_starting_point -= 1;
    }
    
    if(upper_ldr_value < lower_ldr_value){
      servo_starting_point += 1;
    }
  }

  solarServo.write(servo_starting_point);

}
