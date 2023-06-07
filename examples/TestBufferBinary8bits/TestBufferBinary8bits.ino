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

Channel.transmitBufferBinaryRaw8(Serial);

}
