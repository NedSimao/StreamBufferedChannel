#include <StreamChannel.hpp>

#define SIZE 3
uint16_t DATA[SIZE]={200, 128,150};

unsigned long previousTime = 0;

StreamBuffer Channel;

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
Channel.setMaxChannelNumber((uint8_t) SIZE);
}

void loop() {
  /* Updates frequently */
  previousTime = millis();
  
  Channel.appendChannelArray(DATA,SIZE);
  
  unsigned long currentTime = millis();

  Channel.sendBufferAsciiTimeStamp(Serial, (currentTime - previousTime),"\t");

   /* Update the timing for the next time around */
   previousTime = currentTime;
  
  

}


