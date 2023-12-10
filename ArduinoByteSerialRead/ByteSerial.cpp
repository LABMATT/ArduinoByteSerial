#include "Arduino.h"
#include "ByteSerial.h"


// Read the serial data into a buffer. Pull byte then set to array location.
void ByteSerial::read() {

  while(Serial.available() > 0 && currentLine != 256)
  {
    byte byteIN = Serial.read();

    switch(byteIN) {

      // If "skipNull" value is enabled and the byte is null then break free from switch.
      case 0x00:
      if(nonNull)
      {
        break;
      }

      // If "skipNewLine" value is enabled and the byte is equal to line feed then break free from switch.
      case 0x0A:
      if(skipLineFeed)
      {
        break;
      }

      
      // If "skipCarriage" value is enabled and the byte is equal to line feed then break free from switch.
      case 0x0D:
      if(skipCarriageReturn)
      {
        break;
      }


      // If "skipSpace" value is enabled and the byte is equal to space then break free from switch.
      case 0x20:
      if(skipCharSpace)
      {
        break;
      }

      // If no special chars were decteded then add byte to the buffer.
      default:
      addbyte(byteIN);
      break;
    }
  }
}


// Adds a byte to the array based on current line.
void ByteSerial::addbyte(byte byteIN) {

  bool flagged = false;

  // Compair the byte in to the list of skipped bytes/chars
  for(int check = 0; check != skippedNum; check++) {

    if(byteIN == skipped[check])
    {

      flagged = true;
    }
  }


  // If flagged is true caused by a skipped char then dont do anything. else add to array as normal.
  if(flagged == false) {
    
    data[currentLine] = byteIN;
    currentLine++;
  }
}


// Pull byte reads the stack FIFO (first in first out) then after that shifts the stack array up one to make up for the byte that got read. Sets last byte to 0 in place. 
// Futher takes ONE from the currentLine value so the next byte will be written to the next free space in the array.
int ByteSerial::pull() {

  // by defualt set to hex for end of trasnmission.
  int pull = 0;

  pull = data[0];

  // Bitshfit the data in the array. 
  for(int bitshift = 0; bitshift != 99; bitshift ++) {
    data[bitshift] = data[bitshift + 1];
  }

  // Sets the last value in array to 0;
  data[100] = 0;

  // If the current line is not 0 then take away one element as we have read one. This means the next line thats read will go into this postion in the array.
  if(currentLine != 0) {
    currentLine--;
  }
  
  return pull;
}

// erases the current data in the buffer. Sets all values to 0. Then sets CurrentLine to 0 in order to write new bytes to the start of the array.
void ByteSerial::flush() {

  for(int fl = 0;fl < 256; fl++)
  {
    data[fl] = 0;
  }

  currentLine = 0;
}


// If a carrage return is dected skip over it and do not write the ascii byte to the array.
void ByteSerial::skipCarriage(bool skip) {
  
  skipCarriageReturn = skip;
}


// If a newline is dected skip over it and do not write the ascii byte to the array.
void ByteSerial::skipNewLine(bool skip) {
  
  skipLineFeed = skip;
}


// If a null byte is dected skip over it and do not write the ascii byte to the array.
void ByteSerial::skipNull(bool skip) {

  nonNull = skip;
}


// If a space byte is dected skip over it and do not write the ascii byte to the array.
void ByteSerial::skipSpace(bool skip) {

  skipCharSpace = skip;
}


// Returns if there is bytes in the array or not based on the current line indicator.
bool ByteSerial::available() {

  if(currentLine != 0) {

    return true;
  }

  return false;
}


// If a hex byte that is inputted into this function is dectedted in a "read()" function then it will skip over adding it to the array.
// The permaniter of this funciton is a byte that we wish to obmit. 
void ByteSerial::skipByte(byte skipByte) {

  skipped[skippedNum] = skipByte;
  skippedNum++;
}

// Checks if the int is currently availble. 
bool ByteSerial::intAvailable() {

}


// IntOP profomrs operations on intergers. Take bool (scoutmMode) that enables it to remove values from the stack, else it just returns if an int is avaiable. Returns an array with first item been if an int is avaible and second been the int. 
int[2] ByteSerial::intOP(bool scoutMode) {

  // A normal signed 8 bit int has 6 digits, first digit is a sign bit dictating if number is postive or negative. the last element in this array must be a space, carrige return or new line for this to be considered an int. 
  int sudoINTdata[] = {data[0], data[1], data[2], data[3], data[4], data[5], data[6]};
  const int bitArray[] = {10000, 1000, 100, 10, 1};
  int sudoINT[6] = {};
  int placeValue = 0;
  int result = 0;


  for(int val = 0; val != 6; val++)
  {
    // First stage adds one to the ints place value, then sets the sudo int as the value. 
    switch(data[val])
    {
      case 0x30:          // HEX FOR "0"
      placeValue++; 
      sudoINT[val] = 0;
      break;

      case 0x31:          // HEX FOR "1"
      placeValue++; 
      sudoINT[val] = 0;
      break;

      case 0x32:          // HEX FOR "2"
      placeValue++; 
      sudoINT[val] = 0;
      break;

      case 0x33:          // HEX FOR "3"
      placeValue++; 
      sudoINT[val] = 0;
      break;

      case 0x34:          // HEX FOR "4"
      placeValue++; 
      sudoINT[val] = 0;
      break;

      case 0x35:          // HEX FOR "5"
      placeValue++; 
      sudoINT[val] = 0;
      break;

      case 0x36:          // HEX FOR "6"
      placeValue++; 
      sudoINT[val] = 0;
      break;

      case 0x37:          // HEX FOR "7"
      placeValue++; 
      sudoINT[val] = 0;
      break;

      case 0x38:          // HEX FOR "8"
      placeValue++; 
      sudoINT[val] = 0;
      break;

      case 0x39:          // HEX FOR "9"
      placeValue++; 
      sudoINT[val] = 0;
      break;

      // Second bank of switch checks to see if the last charter is a termination char. If so then let us return int Else if val is not 6 then this is not an int as the number is elsewhere in the string.

      case 0x0D: // Carrige reutnr
      val = 6;
      break; 

      case 0x0A: // New Line
      val = 6;
      break; 

      case 0x20: // Space
      val = 6;
      break; 

      default:
      return false;
    }


    // Gets the place value and take a mutiple of 10 to 
    for(int sum = 0; placeValue != 0; sum++)) {
      result = (sudoINT[sum] * bitArray[5-placeValue]);
      placeValue--;
    }

    result;

    return result;

  }


}


int ByteSerial::pullInt() {

}