#include <mcp_can.h>
#include <SPI.h>

// Parameters
#define INTPIN    2
#define CSPIN    10

#define BMSID           0x4D
#define MAX_PACKET_LEN     8

#define MAX_V_SIZE  0x80
#define MAX_T_SIZE  0x80
#define MAX_S_SIZE  0x12
#define MAX_P_SIZE  0x16

MCP_CAN CAN0(CSPIN);

// Temporary storage for ISR
long unsigned int rxId;
unsigned char len = 0;
volatile unsigned char rxBuf[MAX_PACKET_LEN];
volatile boolean newPacket = false;

// Current parameters
unsigned long Varray[MAX_V_SIZE];
unsigned long Tarray[MAX_T_SIZE];
unsigned long Sarray[MAX_S_SIZE];
unsigned long Parray[MAX_P_SIZE];

void setup()
{
  Serial.begin(115200); //debug
  
  CAN0.begin(CAN_500KBPS); //500kbaud
  attachInterrupt(0,CAN_ISR,FALLING); //int.0 is on pin 2 
  
  memset(Varray,0,MAX_V_SIZE);
  memset(Tarray,0,MAX_T_SIZE);
  memset(Sarray,0,MAX_S_SIZE);
  memset(Parray,0,MAX_P_SIZE);
  
  Serial.println("Test initialized");
  Serial.println("Call a param table from serial (v,t,s,%)");
}

void loop()
{
  if(newPacket){
    process();
    newPacket = 0;
  }
  
  if(Serial.available()){
    // Protocol: pii <- paramater index index
    char buf[2];
    buf[0] = Serial.read();
    buf[1] = '\0';
    
    unsigned long* paramArray = NULL;
    unsigned int len = 0;
    switch(buf[0]){
      case 'v':
        paramArray = Varray;
        len = MAX_V_SIZE;
        break;
      case 't':
        paramArray = Tarray;
        len = MAX_T_SIZE;
        break;
      case 's':
        paramArray = Sarray;
        len = MAX_S_SIZE;
        break;
      case '%':
        paramArray = Parray;
        len = MAX_P_SIZE;
        break;
      default:
       Serial.print("Param rejected: ");
       Serial.println(buf[0]);
    }
    Serial.print("Data requested: ");
    Serial.println(buf);
    Serial.println("Data found: ");
    for(int i=0;i<len;i++){
      Serial.print(i);
      Serial.print(":\t");
      Serial.println(paramArray[i],HEX);
    }
  }
}

void CAN_ISR(){
  // Called whenever CAN0 detects a packet
  //  Spend as little time here as possible.
  CAN0.readMsgBuf((byte*)&len,(byte*)rxBuf);
  rxId = CAN0.getCanId();
  
  if(rxId == BMSID){
    newPacket = 1;
  }else{
    Serial.print("Packet not accepted: 0x");
    Serial.println(rxId,HEX);
  }
}

void process(){
  // Storage for strings. Extra space at end for Null char.
  unsigned char index[3]; memcpy((void*)index,(void*)rxBuf,2);
  unsigned char value[6]; memcpy((void*)value,(void*)(rxBuf+3),5);
  index[2] = '\0'; value[5] = '\0';
  
  // Get the useful data
  unsigned char param = rxBuf[2];
  unsigned int indexNum = (unsigned int)strtoul((char*)index,NULL,16);
  unsigned long int valNum = strtoul((char*)value,NULL,16);
  
//  Serial.print("Value from string: ");
//  Serial.print((char*)value); Serial.print(" -> ");
//  Serial.println(valNum, HEX);
  
  unsigned long* paramArray = NULL;
  
  switch(param){
    case 'v':
      paramArray = Varray;
      break;
    case 't':
      paramArray = Tarray;
      break;
    case 's':
      paramArray = Sarray;
      break;
    case '%':
      paramArray = Parray;
      break;
    default:
     Serial.print("Param rejected: ");
     Serial.println(param);
     break; 
  }
  
  if(!paramArray){
    //param rejected
    return;
  }
  
  //Check out of bounds.
  if(indexNum >= 0x7F){
    Serial.print("Out of bounds error: ");
    Serial.print(indexNum);
    Serial.print(" > ");
    Serial.print(0x7F);
    Serial.print(" on param ");
    Serial.println(param);
    return;
  }
  
  // Perform overwrite.
  paramArray[indexNum] = valNum;
}
