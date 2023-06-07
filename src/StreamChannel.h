#ifndef _STREAMCHANNEL_H_
#define _STREAMCHANNEL_H_

#include <Arduino.h>
#include <stdlib.h>

class StreamBuffer{

private:
        //Declaring variables being used betwween the functions
        uint16_t *_buffer;
        uint8_t *_lsbBuffer;
        uint8_t *_msbBuffer;
        uint8_t _definedSize;
        uint8_t _currentIndex;

private:
        boolean isFull();

public:
      //Declaring API to be implemented and used afterword
      StreamBuffer();
      void setMaxChannelNumber(uint8_t channelNo=3);           //Allocate a buffer of 8 bit long
      void appendChannelData(uint16_t);            //insert the value from one channel to the BufferChannelQueue
      void appendChannelArray(uint16_t *, uint8_t); //add an array with values from each channels
      void transmitBufferAscii(Stream &stream, String sepCar=";");
      void transmitBufferBinaryRaw8(Stream &stream);
      void transmitBufferBinaryRaw16(Stream &stream);
      void sendBufferAsciiTimeStamp(Stream &stream, unsigned long, String sepCar=";");
      void sendBufferBinaryTimeStamp(Stream &stream, unsigned long);
      void Flush();
      ~StreamBuffer();

};

extern StreamBuffer StreamChannel;

#endif /*STREAMCHANNEL_H*/