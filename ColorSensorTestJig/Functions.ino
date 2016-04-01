#include <SoftwareSerial.h>
#define TxMode LOW    // Master transmit to G15
#define RxMode HIGH   // Master receive from G15
#define CTRL 2
#define HEADER 0xFF

//Instruction
#define READ 0x02
#define WRITE 0x03
#define RESET 0x06

//Address
#define Baud (byte) 0x04
#define Red (byte) 0x0A
#define Green (byte) 0x0B
#define Blue (byte) 0x0C
#define LED (byte) 0x09


//-1. Convert ADC value to key number
//1. Write Baud Rate
//2. Read Baud Rate
//3. Read Red Analog
//4. Read Green Analog
//5. Read Blue Analog
//6. Write LED
//7. Ping

//===============================================================================================================
//1.Write Baud Rate
//Input: ID
//Return: Baud Rate
//============================================================================================================
byte writeCsBd (byte ID)
{
  byte buf[8]; 

//Flush the RX buffer=================================  
  digitalWrite(CTRL,RxMode);
  while(mySerial.available()>0)
  {
    mySerial.read(); //Clear UART buffer
  }  
//Transmit to sensor===================================  
  digitalWrite(CTRL, TxMode);
  mySerial.write(HEADER);
  mySerial.write(HEADER);
  mySerial.write(ID);  //ID
  mySerial.write(0x04); //Length
  mySerial.write(WRITE); //Instruction
  mySerial.write(Baud); //Address
  mySerial.write(0x67); //Number of bytes
  byte checksum=0xFF-ID-0x04-WRITE-Baud-0x67;   
  mySerial.write(checksum); //Checksum

//Receive from sensor====================================
  digitalWrite(CTRL,RxMode);
  int nbyte= mySerial.readBytes(buf,6);

 if(nbyte==0)
   {
    errStatus=0xFF;
    return(0xFF);
  }
  else if (nbyte<6) //incomplete package recieved
  {
    errStatus=buf[4];
    return(0xFF);
  }
  else
  {
    errStatus=buf[4];
    return(0x00);
  }
}

//===============================================================================================================
//2.Read Baud Rate
//Input: ID
//Return: Baud Rate
//============================================================================================================
byte readCsBd (byte ID)
{
  byte buf[8]; 
//Flush the RX buffer=================================  
  digitalWrite(CTRL,RxMode);
  while(mySerial.available()>0)
  {
    mySerial.read(); //Clear UART buffer
  }
//Transmit to sensor===================================  
  digitalWrite(CTRL, TxMode);
  mySerial.write(HEADER);
  mySerial.write(HEADER);
  mySerial.write(ID); //ID
  mySerial.write(0x04); //Length
  mySerial.write(READ); //Instruction
  mySerial.write(Baud); //Address
  mySerial.write(0x01); //Number of bytes
  byte checksum=0xFF-ID-0x04-READ-Baud-0x01;
  mySerial.write(checksum); //checksum

 //Receive from sensor====================================
  digitalWrite(CTRL,RxMode);
  int nbyte= mySerial.readBytes (buf,7);

  if(nbyte==0)
  {
    errStatus=0xFF;
    return(0xFF);
  }
  else if (nbyte<7) //incomplete package recieved
  {
    errStatus=buf[4];
    return(0xFF);
  }
  else
  {
    errStatus=buf[4];
    if(buf[4]!=0) // if return status not zero (error occured)
    {
      return(0xFF); 
    }
    else
    {     
      return(buf[5]); //return BaudRate
    }
  }
}

//===============================================================================================================
//3.Read Red Analog
//Input: ID
//Return: Red Value
//============================================================================================================
byte readCsRed (byte ID)
{
  byte buf[8]; 
//Flush the RX buffer=================================  
  digitalWrite(CTRL,RxMode);
  while(mySerial.available()>0)
  {
    mySerial.read(); //Clear UART buffer
  }
//Transmit to sensor===================================  
  digitalWrite(CTRL, TxMode);
  mySerial.write(HEADER);
  mySerial.write(HEADER);
  mySerial.write(ID); //ID
  mySerial.write(0x04); //Length
  mySerial.write(READ); //Instruction
  mySerial.write(Red); //Address
  mySerial.write(0x01); //Number of bytes
  byte checksum=0xFF-ID-0x04-READ-Red-0x01;
  mySerial.write(checksum); //checksum

 //Receive from sensor====================================
  digitalWrite(CTRL,RxMode);
  int nbyte= mySerial.readBytes (buf,7);

  if(nbyte==0)
  {
    errStatus=0xFF;
    return(0xFF);
  }
  else if (nbyte<7) //incomplete package recieved
  {
    errStatus=buf[4];
    return(0xFF);
  }
  else
  {
    errStatus=buf[4];
    if(buf[4]!=0) // if return status not zero (error occured)
    {
      return(0xFF); 
    }
    else
    {     
      return(buf[5]); //return BaudRate
    }
  }
}

//===============================================================================================================
//4.Read Green Analog
//Input: ID
//Return: Green Value
//============================================================================================================
byte readCsGreen (byte ID)
{
  byte buf[8]; 
//Flush the RX buffer=================================  
  digitalWrite(CTRL,RxMode);
  while(mySerial.available()>0)
  {
    mySerial.read(); //Clear UART buffer
  }
//Transmit to sensor===================================  
  digitalWrite(CTRL, TxMode);
  mySerial.write(HEADER);
  mySerial.write(HEADER);
  mySerial.write(ID); //ID
  mySerial.write(0x04); //Length
  mySerial.write(READ); //Instruction
  mySerial.write(Green); //Address
  mySerial.write(0x01); //Number of bytes
  byte checksum=0xFF-ID-0x04-READ-Green-0x01;
  mySerial.write(checksum); //checksum

 //Receive from sensor====================================
  digitalWrite(CTRL,RxMode);
  int nbyte= mySerial.readBytes (buf,7);

  if(nbyte==0)
  {
    errStatus=0xFF;
    return(0xFF);
  }
  else if (nbyte<7) //incomplete package recieved
  {
    errStatus=buf[4];
    return(0xFF);
  }
  else
  {
    errStatus=buf[4];
    if(buf[4]!=0) // if return status not zero (error occured)
    {
      return(0xFF); 
    }
    else
    {     
      return(buf[5]); //return BaudRate
    }
  }
}

//===============================================================================================================
//5.Read Blue Analog
//Input: ID
//Return: Blue Value
//============================================================================================================
byte readCsBlue (byte ID)
{
  byte buf[8]; 
//Flush the RX buffer=================================  
  digitalWrite(CTRL,RxMode);
  while(mySerial.available()>0)
  {
    mySerial.read(); //Clear UART buffer
  }
//Transmit to sensor===================================  
  digitalWrite(CTRL, TxMode);
  mySerial.write(HEADER);
  mySerial.write(HEADER);
  mySerial.write(ID); //ID
  mySerial.write(0x04); //Length
  mySerial.write(READ); //Instruction
  mySerial.write(Blue); //Address
  mySerial.write(0x01); //Number of bytes
  byte checksum=0xFF-ID-0x04-READ-Blue-0x01;
  mySerial.write(checksum); //checksum

 //Receive from sensor====================================
  digitalWrite(CTRL,RxMode);
  int nbyte= mySerial.readBytes (buf,7);

  if(nbyte==0)
  {
    errStatus=0xFF;
    return(0xFF);
  }
  else if (nbyte<7) //incomplete package recieved
  {
    errStatus=buf[4];
    return(0xFF);
  }
  else
  {
    errStatus=buf[4];
    if(buf[4]!=0) // if return status not zero (error occured)
    {
      return(0xFF); 
    }
    else
    {     
      return(buf[5]); //return BaudRate
    }
  }
}
//===============================================================================================================
//6.Write LED
//Input: ID, LED Value
//-----LED Value-----
//0x00 = OFF
//0x01 = ON
//0x02 = AUTO COLOR
//0x03 = RED
//0x04 = GREEN
//0x05 = BLUE
//0x06 = ALL OFF
//Return: -
//============================================================================================================
byte writeCsLed (byte ID,byte ledVal)
{
  byte buf[8]; 

//Flush the RX buffer=================================  
  digitalWrite(CTRL,RxMode);
  while(mySerial.available()>0)
  {
    mySerial.read(); //Clear UART buffer
  }  
//Transmit to sensor===================================  
  digitalWrite(CTRL, TxMode);
  mySerial.write(HEADER);
  mySerial.write(HEADER);
  mySerial.write(ID);  //ID
  mySerial.write(0x04); //Length
  mySerial.write(WRITE); //Instruction
  mySerial.write(LED); //Address
  mySerial.write(ledVal); //Number of bytes
  byte checksum=0xFF-ID-0x04-WRITE-LED-ledVal;   
  mySerial.write(checksum); //Checksum

//Receive from sensor====================================
  digitalWrite(CTRL,RxMode);
  int nbyte= mySerial.readBytes(buf,6);

 if(nbyte==0)
   {
    errStatus=0xFF;
    return(0xFF);
  }
  else if (nbyte<6) //incomplete package recieved
  {
    errStatus=buf[4];
    return(0xFF);
  }
  else
  {
    errStatus=buf[4];
    return(0x00);
  }
}

//===============================================================================================================
//4.Ping
//Input: ID
//Return:
//============================================================================================================
byte pingCs (byte ID)
{
  byte buf[8]; 

//Flush the RX buffer=================================  
  digitalWrite(CTRL,RxMode);
  while(mySerial.available()>0)
  {
    mySerial.read(); //Clear UART buffer
  }  
//Transmit to sensor===================================  
  digitalWrite(CTRL, TxMode);
  mySerial.write(HEADER);
  mySerial.write(HEADER);
  mySerial.write(ID);  //ID
  mySerial.write(0x02); //Length
  mySerial.write(0x01); //Instruction
  byte checksum=0xFF-ID-0x02-0x01;  
  mySerial.write(checksum); //Checksum

//Receive from sensor====================================
  digitalWrite(CTRL,RxMode);
  int nbyte= mySerial.readBytes(buf,6);

 if(nbyte==0)
   {
    errStatus=0xFF;
    return(0xFF);
  }
  else if (nbyte<6) //incomplete package recieved
  {
    errStatus=buf[4];
    return(0xFF);
  }
  else
  {
    errStatus=buf[4];
    return(0x00);
  }
}


// Convert ADC value to key number
int get_key(unsigned int input)
{
  int k;
    
  for (k = 0; k < NUM_KEYS; k++)
  {
    if (input < adc_key_val[k])
    {
           
    return k;
        }
  }
    
    if (k >= NUM_KEYS)
        k = -1;     // No valid key pressed
    
    return k;
}
