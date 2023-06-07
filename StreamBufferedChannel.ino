#include "src/StreamChannel.h"

#define SIZE 3
uint16_t DATA[SIZE]={200, 128,150};


StreamBuffer Channel;

void setup() {
// put your setup code here, to run once:
Serial.begin(9600);
Channel.setMaxChannelNumber((uint8_t) SIZE);
}

void loop() {
// put your main code here, to run repeatedly:
Channel.appendChannelArray(DATA,SIZE);



//Channel.transmitBufferAscii(Serial, "\t");
//Channel.transmitBufferBinaryRaw8(Serial);
//Channel.transmitBufferBinaryRaw16(Serial);
//Channel.sendBufferAsciiTimeStamp(Serial, 12,"\t");
//Channel.sendBufferBinaryTimeStamp(Serial, 12);

delay(100);

}
