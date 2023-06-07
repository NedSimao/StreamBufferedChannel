#include <StreamChannel.hpp>

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


}
