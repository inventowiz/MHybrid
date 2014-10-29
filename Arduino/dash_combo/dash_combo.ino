#include <LiquidCrystal.h>

#define RESET_PIN 36
#define shiftU 22
#define shiftD 23
#define fuelG A7

int in, n1, n2, n3;
String  input = "";
String output = "";

char data[17]; //array to store input data

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd1(47, 46, 45, 44, 43, 42);  //top lcd
LiquidCrystal lcd(53, 52, 51, 50, 49, 48);  //bottom lcd

//globals for loop iterations
int gear = 2;
int fuel;

//data from dSpace
float HV = 0,LV = 0;
int spd = 0,torque = 0;
unsigned rpm = 0;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  Serial2.begin(14400);    //open serial port for K-line communication
  
  lcd1.begin(16, 2); // set up the number of columns and rows on the lcd1 
  
  lcd.begin(16, 2); // set up the number of columns and rows on the LCD 
  
  pinMode(shiftD, INPUT);
  pinMode(shiftU, INPUT);
}

void loop() {
  // zero out data frame
  for(int i=0;i<17;i++)
    data[i] = 0; 

  if (Serial2.available()) {
    while(Serial2.available() < 17); //wait for 17 bytes
    //read in the data for processing
 
    for(int i=0;i<17;i++)
      data[i] = Serial2.read();
    
    if(data[0] == 'H' &&
       data[5] == 'L' &&
       data[10] == 'S' &&
       data[12] == 'T' &&
       data[15] == 'R'){
         
       //The data is now confirmed valid, start processing.
       HV = float(data[1]);
       LV = float(data[6]);
       spd = int(data[11]);
       rpm = unsigned(data[13]);
       torque = int(data[16]);
       
       Serial.println("Start packet:");
       Serial.println(HV);
       Serial.println(LV);
       Serial.println(spd);
       Serial.println(rpm);
       Serial.println(torque);
       Serial.println("End packet");
      
     }
   
  //flush the buffer
  while(Serial2.available())
     char dummy = Serial2.read();
  }
 
  //GEAR STUFF
  
  //set up an edge trigger
  boolean up,down;
  boolean pup,pdown;
  
  up = digitalRead(shiftU);
  down = digitalRead(shiftD);
  
  if(up && !pup)
    gear++;
  if(down && !pdown)
    gear--;
    
  pup = up;
  pdown = down;
    
  if(gear > 5){
    gear = 5;
  }
  if(gear < 1)
    gear = 1;
  
  // FUEL STUFF
  lcd.setCursor(1,1);
  fuel = analogRead(fuelG);
  fuel = map(fuel, 2, 35, 0, 100);
  if (fuel <= 5){
      fuel = 0;
  } 
  
 //display params
 lcd1.setCursor(0,0);
 lcd1.print("H:");
 lcd1.print(HV,0);
 lcd1.print("V ");
 lcd1.setCursor(0,1);
 lcd1.print("T:");
 lcd1.print(torque);
 
 lcd.setCursor(1,0);
 lcd.print(rpm);
 lcd.setCursor(6,0);
 lcd.print("RPM");
 lcd.setCursor(1,1);
 lcd.print("L:");
 lcd.print(LV,0);
 lcd.print("V");
 
 
  lcd1.setCursor(10,0);
  lcd1.print("F:");
  lcd1.print(fuel);
  lcd1.print("%");
  
  lcd1.setCursor(11,1);
  lcd1.print(spd);
  lcd1.setCursor(13,1);
  lcd1.print("mph");
}


