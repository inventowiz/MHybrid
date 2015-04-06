#include <Servo.h>

Servo etc;
int pos = 1500;

// ETC is 900us   FULL THROTTLE
//        1900us  IDLE THROTTLE


void setup()
{
  // put your setup code here, to run once:
  etc.attach(3,600,2400);
  Serial.begin(115200);
  etc.writeMicroseconds(pos);
}

void loop()
{
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    char c = Serial.read();
    if(c == '+')
      etc.writeMicroseconds(pos+=100);
    if(c == '-')
      etc.writeMicroseconds(pos-=100);
    if(c == 'e')  
      etc.detach();
    if(c == 'a')
      etc.attach(3,800,2200);
    if(c == 'u'){
      etc.writeMicroseconds(2000);
      delay(300);
      etc.writeMicroseconds(1500);
    }
    if(c == 'd'){
      etc.writeMicroseconds(1100);
      delay(300);
      etc.writeMicroseconds(1500);
    }
    if(c == 'h'){
      etc.writeMicroseconds(1700);
      delay(300);
      etc.writeMicroseconds(1500);
    }
    Serial.println(etc.readMicroseconds());
  }
  /*
  for(int i=1900;i>=1500;i-=2){ // 1900: closed 900: open
    etc.writeMicroseconds(i);
    Serial.println(etc.readMicroseconds());
    delay(2);
  }
  delay(100);
  etc.writeMicroseconds(1900);
  Serial.println(etc.readMicroseconds());
  delay(2000);
  */
  
}
