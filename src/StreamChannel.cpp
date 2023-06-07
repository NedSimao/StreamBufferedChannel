#include "StreamChannel.h"



boolean StreamBuffer::isFull(){

  return (_currentIndex==_definedSize);
}


StreamBuffer::StreamBuffer(){
        _definedSize=0;
        _currentIndex=0;
}


void StreamBuffer::setMaxChannelNumber(uint8_t channelNo){
  _definedSize=channelNo;

  _buffer=new uint16_t[_definedSize];
  _lsbBuffer=new uint8_t[_definedSize];
  _msbBuffer=new uint8_t[_definedSize];

  for (uint8_t i=0; i<_definedSize; i++){
      _buffer[i]=0;
      _lsbBuffer[i]=0;
      _msbBuffer[i]=0;

  } 


}


void StreamBuffer::appendChannelData(uint16_t data){
  _currentIndex=_currentIndex%_definedSize; //set the _currentIndex to 0 when the buffer if full and this function is called to append a new data

  *(_buffer+_currentIndex)=data;
  _currentIndex++;


}  

void StreamBuffer::Flush(){
  _currentIndex=0;
  for (uint8_t i=0; i<_definedSize; i++) _buffer[i]=0;

}


void StreamBuffer::appendChannelArray(uint16_t *dataSet, uint8_t arraySize){
  //the buffer is reset
  Flush();

if((arraySize<=_definedSize)&&(arraySize>0)){
  //fill the buffer with this datSet
  for (uint8_t i=0; i<arraySize;i++){
    this->appendChannelData(dataSet[i]);
  }

}else if (arraySize>_definedSize){
  //drop other packets 
  for (uint8_t i=0; i<_definedSize;i++){
    this->appendChannelData(dataSet[i]);
  }


}else{
  //dont do anything if the array size if less thant 0

}


}


void StreamBuffer::transmitBufferAscii(Stream &stream, String sepCar){

for (uint8_t i=0; i<_currentIndex; i++){

  stream.print(_buffer[i]);
  stream.print(sepCar);
}
stream.println();


}


void StreamBuffer::transmitBufferBinaryRaw8(Stream &stream){
for(uint8_t i=0; i<_currentIndex; i++){
      _lsbBuffer[i]=(_buffer[i] & 0xFF);
      _msbBuffer[i]=(_buffer[i] >> 8) & 0xFF;
}

String header="#"+ String(String(_currentIndex).length())+String(_currentIndex*sizeof(uint8_t));
//Send MSB AS FIRST PACKET
stream.print(header);
stream.write((uint8_t *) _msbBuffer,_currentIndex*sizeof(uint8_t)); // Send the upper byte first
stream.println();

//Send LSB AS SECOND PACKET
stream.print(header);
stream.write((uint8_t *) _lsbBuffer ,_currentIndex*sizeof(uint8_t)); // Send the lower byte
stream.println();

}


void StreamBuffer::transmitBufferBinaryRaw16(Stream &stream){

String header="#"+ String(String(_currentIndex).length())+String(_currentIndex*sizeof(uint8_t));
stream.print(header);
stream.write((char *) _buffer, (_currentIndex)*sizeof(uint16_t));


}


void StreamBuffer::sendBufferAsciiTimeStamp(Stream &stream, unsigned long timeStamp, String sepCar){
stream.print(timeStamp);
stream.print(sepCar);
this->transmitBufferAscii(stream,sepCar);

}


void StreamBuffer::sendBufferBinaryTimeStamp(Stream &stream, unsigned long timeStamp){
String header="#"+ String(String(_currentIndex).length())+String(_currentIndex*sizeof(uint8_t)+sizeof(unsigned long));

stream.print(header);
stream.write((char *) timeStamp, sizeof(unsigned long));
stream.write((char *) _buffer, (_currentIndex)*sizeof(uint16_t));

}


StreamBuffer::~StreamBuffer(){
  delete[] _buffer;
  delete[] _lsbBuffer;
  delete[] _msbBuffer;
}
