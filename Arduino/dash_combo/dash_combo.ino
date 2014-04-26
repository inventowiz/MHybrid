#include <LiquidCrystal.h>

int in, n1, n2, n3;
String  input = "";
String output = "";

char data[17]; //array to store input data

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd1(47, 46, 45, 44, 43, 42);
LiquidCrystal lcd(53, 52, 51, 50, 49, 48);//bottom lcd //(47, 46, 45, 44, 43, 42);//upper lcd
int shiftD = 22;
int shiftU = 23;
int fuelGauge = A7;
int gear, grD, grU = 0;
int fuel;
String g = "N";
int topGear = 3;
int lowGear = -1;
int reset = 36;

float HV = 0,LV = 0;
int spd = 0,rpm = 0,torque = 0;

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  Serial2.begin(14400);    //open serial port for K-line communication
  
  lcd1.begin(16, 2); // set up the number of columns and rows on the lcd1 
  
  lcd.begin(16, 2); // set up the number of columns and rows on the LCD 
  lcd.setCursor(2, 0);
  lcd.print("FUEL");
  lcd.setCursor(9, 0);
  lcd.print("GEAR");
  
  pinMode(shiftD, INPUT);
  pinMode(shiftU, INPUT);
  pinMode(reset, INPUT);
}

void loop() {

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
       HV = -float(data[1] | (data[2] << 4) | (data[3] << 8) | (data[4] << 12));
       LV = float(data[6]);
       spd = int(data[11]);
       rpm = int(data[13] | (data[14] << 4));
       torque = int(data[16]);
       
       Serial.println("Start packet:");
       Serial.println(HV);
       Serial.println(LV);
       Serial.println(spd);
       Serial.println(rpm);
       Serial.println(torque);
       Serial.println("End packet");
      
    }
    //display params
   lcd1.setCursor(0,0);
   lcd1.print("HI ");
   lcd1.print(HV,1);
   lcd1.print(" LO ");
   lcd1.print(LV,1);
   lcd1.setCursor(0,1);
   lcd1.print("T: ");
   lcd1.print(torque);
   lcd1.print(" Nm");
  }
  //GEAR STUFF
  if (digitalRead(reset) == LOW)
  {
    grD = digitalRead(shiftD);  
    grU = digitalRead(shiftU);

    if (grD == HIGH && gear <= topGear && gear >= lowGear)
    {
      gear = gear - 1;
    }
    else if (grU == HIGH && gear <= topGear && gear >= lowGear)
    {
      gear = gear + 1;
    }
  }
  else if (digitalRead(reset) == HIGH) 
  {
    gear = 0;
  }

  lcd.setCursor(10,1);
  if (gear == 0)
  {
    lcd.print(g);
  }
  else if (gear = -1)
  {
    lcd.print(1);
  }
  else
  {
    gear = gear - 1;
    lcd.print(gear);
  }
  //Serial.print(gear);
  // FUEL STUFF
  lcd.setCursor(3,1);
  fuel = analogRead(fuelGauge);
  fuel = map(fuel, 2, 35, 0, 100);
  if (fuel <= 5){
      fuel = 0;
  }
  lcd.print(fuel); 
}


