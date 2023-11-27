
#define ByteSerial_h

#include "Arduino.h"

class ByteSerial {
  private:
  byte data[256] = {};
  byte skipped[255] = {};                 // There are 255 standared ascii code chars. if added to this array and then recived in the monitor then it will be prevent from written to the array buffer.
  int  skippedNum = 0;                    // The amount of values in this array accounts for the amout of chars skipped or to read from the array. FEX, if skipChar() has been called 5 times, then clearly the first 5 chars in that array should be skipped. rest will be 0.
  int currentLine = 0;
  int pullLine = 0;

  bool skipLineFeed = false;
  bool skipCarriageReturn = false;
  bool nonNull = false;
  bool skipCharSpace = false;

  void addbyte(byte);



  public:
  void read();
  int pull();
  void flush();
  void skipCarriage(bool);
  void skipNewLine(bool);
  void skipNull(bool);
  void skipSpace(bool);
  bool available();
  void skipByte(byte);

};