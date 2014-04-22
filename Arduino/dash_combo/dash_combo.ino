#include <LiquidCrystal.h>

int lv = 0;   // low voltage
int in, n1, n2, n3;
String  input = "";
String output = "";

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

void setup() {
  Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
  lcd1.begin(16, 2); // set up the number of columns and rows on the lcd1 
  lcd1.setCursor(2, 0);
  lcd1.print("High");
  lcd1.setCursor(10, 0);
  lcd1.print("LOW");
  
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

  if (Serial.available() > 0) {
    in = Serial.read();
    if (in == 65 || in == 66 || input.length() != 0){ //ELIMINATES TRASH BETWEEN THE VALUES. DOES NOT RECORD ANY VAUES UNTIL "A" OR "B"
      input = input + String(in);
      // Serial.print("input: ");
      //Serial.print(input);
    }

    if (input.length() == 8) { //each digit is represented by 2 digit number    

      if (input.substring(0,2) == "65"){ //if starts with an 'A'

        n1 = input.substring(2,4).toInt();     
        n2 = input.substring(4,6).toInt();    
        n3 = input.substring(6).toInt();    

        n1 -= 48;
        n2 -= 48;
        n3 -= 48;

        output = String(n1)  + String(n2) + String(n3);

        Serial.print("HIGH: ");
        Serial.println(output);

        lcd1.setCursor(0, 1);
        lcd1.print(output);
      } 
      else if (input.substring(0,2) == "66") {
        n1 = input.substring(2,4).toInt();     
        n2 = input.substring(4,6).toInt();    
        n3 = input.substring(6).toInt();    

        n1 -= 48;
        n2 -= 48;
        n3 -= 48;

        output = String(n1)  + String(n2) + String(n3);

        Serial.print("LOW: ");
        Serial.println(output);

        lcd1.setCursor(6, 1);
        lcd1.print(output);
      }
      input = input.substring(8);
    }      
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
  Serial.print(gear);
  // FUEL STUFF
  lcd.setCursor(3,1);
  fuel = analogRead(fuelGauge);
  //fuel = map(fuel, 150, 1023, 0, 100);
  //if (fuel <= 5){
  //  fuel = 0;
 // }
  lcd.print(fuel); 
}


