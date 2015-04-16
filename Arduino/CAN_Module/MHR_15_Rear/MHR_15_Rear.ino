#include <mcp_can.h>
#include <SPI.h>
#include <Servo.h>

// Parameters
#define INTPIN    2
#define CSPIN    10

#define ETCTIMEOUT  1000
#define ETCMIN      1900
#define ETCMAX      1175

#define SHIFTHOME   1500
#define SHIFTDOWN   1100
#define SHIFTUP     2000
#define SHIFTHALF   1700
#define SHIFTDURMS   300

#define ETCPIN         9
#define SHIFTPIN       3

#define ETCID     0x40
#define SHIFTID   0x42

#define ETC_PACKET_LEN     1
#define SHIFT_PACKET_LEN   1
#define MAX_PACKET_LEN     8

Servo shift,etc;
MCP_CAN CAN0(CSPIN);

// Temporary storage for ISR
long unsigned int rxId;
unsigned char len = 0;
unsigned char rxBuf[MAX_PACKET_LEN];

// Current parameters
volatile long unsigned int timeOfLastPacket = 0;
volatile unsigned char ETCbuf[ETC_PACKET_LEN];
volatile unsigned char SHIFTbuf[SHIFT_PACKET_LEN];
volatile boolean changeWasMade = 0;

unsigned int ETC_pos = ETCMIN;
unsigned int SHIFT_pos = SHIFTHOME; //probably unnecessary

void setup()
{
  Serial.begin(115200); //debug
  
  CAN0.begin(CAN_500KBPS); //500kbaud
  attachInterrupt(0,CAN_ISR,FALLING); //int.0 is on pin 2 
  
  etc.attach(ETCPIN,800,2200); //800,2200
  etc.writeMicroseconds(ETCMIN);
  shift.attach(SHIFTPIN,600,2400); 
  shift.writeMicroseconds(SHIFTHOME);
  
  memset((void*)ETCbuf,0,ETC_PACKET_LEN);
  memset((void*)SHIFTbuf,0,SHIFT_PACKET_LEN);
  
  Serial.println("Rear CAN Module initalized.");
}

void loop()
{
  if(changeWasMade){
    updateData();
  }

  // Check for ETC timeout.
  noInterrupts();
  
  if(((millis() - timeOfLastPacket) >= ETCTIMEOUT) and etc.attached()){
    etc.writeMicroseconds(ETCMIN);
    delay(250);
    etc.detach();
    Serial.println("ETC detached");
  }
  
  interrupts();
  
  updateDevices();

  if(Serial.available() > 0){ //debugging interface
    char c = Serial.read();
    timeOfLastPacket = millis(); 
    
    switch(c){
       default:
        Serial.println("invalid input");
        break;
      case 'u': 
        // shift up
        shiftMe(true);
        break;
      case 'd':
        //shift down
        shiftMe(false);
        break;
      case 'h':
        // half shift
        shiftHalf();
        break;
      case 'n':
        shiftNeutral();
        break;
      case '+':
        Serial.print("\nETC moved to ");
        Serial.println(ETC_pos += 50);
        break;
      case '-':
        Serial.print("\nETC moved to ");
        Serial.println(ETC_pos -= 50);
        break;
      case 'e':
        Serial.print("Enter desired ETC position as integer percent (050%): ");
        char newpos[3];
        while(Serial.available() < 3);
        for(int i=0;i<3;i++)
          newpos[i] = (Serial.read() - 48); //to number
        int posfinal = 100*newpos[0] + 10*newpos[1] + newpos[2];
        if(posfinal > 100 or posfinal < 0){
          Serial.println("Invalid number");
          break;
        }
        posfinal = map(posfinal,0,100,ETCMIN,ETCMAX);
        Serial.print("\nETC moved to ");
        Serial.println(posfinal);
        ETC_pos = posfinal;
        break;

    }
    
  }

}

void CAN_ISR(){
  // Called whenever CAN0 detects a packet
  //  Spend as little time here as possible.
  CAN0.readMsgBuf(&len,rxBuf);
  rxId = CAN0.getCanId();
  
  changeWasMade = true;
  
  switch(rxId){
    case ETCID:
      timeOfLastPacket = millis();
      memcpy((void*)ETCbuf,(const void*)rxBuf,ETC_PACKET_LEN);
      changeWasMade = true;
      break;
    case SHIFTID:
      memcpy((void*)SHIFTbuf,(const void*)rxBuf,SHIFT_PACKET_LEN);
      changeWasMade = true;
      break; 
    default:
      break;
  }
}

void updateData(){
  // Parse CAN packets to get new data
  noInterrupts();
  
  // Shifting first
  if(SHIFTbuf[0] & 0x01){
    interrupts();
    // UPSHIFT 
    shiftMe(true);
    noInterrupts();
  }else if(SHIFTbuf[0] & 0x02){
    interrupts();
    // DOWNSHIFT 
    shiftMe(false);
    noInterrupts();
  }
  
  // Now ETC
  
  ETC_pos = map(ETCbuf[0],0,255,ETCMIN,ETCMAX);
  
  Serial.print("ETC");
  Serial.print(" - ");
  Serial.println(ETC_pos);
  changeWasMade = false;
  
  interrupts();
}

void updateDevices(){
  // Push saved data to devices
  //if(! (millis()%1000)) Serial.println(millis() - timeOfLastPacket);
  noInterrupts();
  if(!etc.attached() and ((millis() - timeOfLastPacket) < ETCTIMEOUT)){
    etc.attach(ETCPIN);
    Serial.println("ETC attached");
  }
  etc.writeMicroseconds(ETC_pos);
  interrupts();
}

void shiftMe(boolean up){
  // Executes a shift if called.
  Serial.print("Shifting ");
  Serial.println(up ? "UP" : "DOWN");
  if(up){
    etc.writeMicroseconds(ETCMIN); // lose engine
    shift.writeMicroseconds(SHIFTUP);
    delay(SHIFTDURMS);
    shift.writeMicroseconds(SHIFTHOME);
  }else{
    etc.writeMicroseconds(ETCMIN); // lose engine
    shift.writeMicroseconds(SHIFTDOWN);
    delay(SHIFTDURMS);
    shift.writeMicroseconds(SHIFTHOME);
  }
  
  //Shifting executed, clear buffer.
  memset((void*)SHIFTbuf,0,SHIFT_PACKET_LEN);
}

void shiftHalf(){
  Serial.println("Half shift");
  etc.writeMicroseconds(ETCMIN); // lose engine
  shift.writeMicroseconds(SHIFTHALF);
  delay(SHIFTDURMS);
  shift.writeMicroseconds(SHIFTHOME);
}

void shiftNeutral(){
  for(int i=0;i<6;i++){
    shiftMe(false);
    delay(SHIFTDURMS); 
  }
  shiftHalf();
}
