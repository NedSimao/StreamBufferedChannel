#include <StreamChannel.hpp>

#define SIZE 3
uint16_t DATA[SIZE]={200, 128,150};


StreamBuffer Channel;

void setup() {
Serial.begin(9600);
Channel.setMaxChannelNumber((uint8_t) SIZE);
}

void loop() {
  Channel.appendChannelArray(DATA,SIZE);

  /* Updates frequently */
  previousTime = millis();
  
  Channel.appendChannelArray(DATA,SIZE);
  
  unsigned long currentTime = millis();

  Channel.sendBufferBinaryTimeStamp(Serial, (currentTime - previousTime));


   /* Update the timing for the next time around */
   previousTime = currentTime;
  
}
