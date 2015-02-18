#include <mcp_can.h>
#include <SPI.h>
#include <Servo.h>
#include <AccelStepper.h>

// Parameters
#define INTPIN    2
#define CSPIN    10

#define ETCTIMEOUT   500
#define ETCMIN         0
#define ETCMAX      1600
#define ETCSPEED     100
#define ETCACCEL      50

#define SHIFTHOME     90
#define SHIFTDOWN      0
#define SHIFTUP      180

#define ETCSTEP     8
#define ETCDIR      9
#define SHIFTPIN   11

#define ETCID     0x40
#define SHIFTID   0x44

#define ETC_PACKET_LEN     2
#define SHIFT_PACKET_LEN   1
#define MAX_PACKET_LEN     8

Servo shift;
AccelStepper etc(AccelStepper::DRIVER,ETCSTEP,ETCDIR);
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
  
  etc.setMaxSpeed(ETCSPEED);
  etc.setAcceleration(ETCACCEL);
  shift.attach(SHIFTPIN); shift.write(SHIFTHOME);
  
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
  if((timeOfLastPacket - millis()) >= ETCTIMEOUT){
    ETC_pos = ETCMIN;
  }
  interrupts();
  
  updateDevices();

}

void CAN_ISR(){
  // Called whenever CAN0 detects a packet
  //  Spend as little time here as possible.
  CAN0.readMsgBuf(&len,rxBuf);
  rxId = CAN0.getCanId();
  
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
      Serial.print("Packet not accepted: 0x");
      Serial.println(rxId,HEX);
      break;
  }
}

void updateData(){
  // Parse CAN packets to get new data
  noInterrupts();
  
  // Shifting first
  if(SHIFTbuf[0] & 0x01){
    interrupts()
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
  ETC_pos = ETCbuf[0] & (ETCbuf[1] << 8);
  
  interrupts();
}

void updateDevices(){
  // Push saved data to devices
  etc.runToNewPosition(ETC_pos);
}

void shiftMe(boolean up){
  // Executes a shift if called.
  Serial.print("Shifting ");
  Serial.println(up ? "UP" : "DOWN");
  if(up){
    shift.write(SHIFTUP);
  }else{
    shift.write(SHIFTDOWN);
  }
  shift.write(SHIFTHOME);
  
  //Shifting executed, clear buffer.
  memset((void*)SHIFTbuf,0,SHIFT_PACKET_LEN);
}
