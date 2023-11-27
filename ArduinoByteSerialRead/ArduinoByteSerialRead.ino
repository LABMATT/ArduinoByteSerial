// Demos reciving serial using byte system. This differs over using sreal prase as it doest wait for a timeout. 
// Ascii codes found here: https://www.ascii-code.com/

#include "ByteSerial.h"

// Creat a new instance of the libray.
ByteSerial byteSerial;

void setup() {
  // put your setup code here, to run once:

  // Start Serial connection.
  Serial.begin(9600);

  // Prmaiters we can change in the libray.
  byteSerial.skipNewLine(true);            // If the data recived ends with start new line then prevnt this byte(0x0A) from been put in the array.
  byteSerial.skipNull(false);              // If the data recived ends with 0x00 then prevent this byte from been put in an array.
  byteSerial.skipCarriage(false);          // If the data recived ends with a carrigeReturn (0x0D) then prevent this byte been put in array.
  byteSerial.skipSpace(true);              // If the data recived has a space in it (0x20) then prevent this byte from been written to the array.
  byteSerial.skipByte(0x6c);               // skipByte allows you to register ascii code's (Up to 255 of them) that if recived over serial will not be written to buffer. This example prevents the lowercase letter 'l' or (0x6c) from been added to the buffer. 
}

void loop() {
  // put your main code here, to run repeatedly:

  // Read any bytes that maybe in the hardwere buffer.
  byteSerial.read();

  // Print out the last byte in our array using a pull command. But only if the data in the array is there.
  if(byteSerial.available()) {
    Serial.println(byteSerial.pull()); // Pull the first bytes of the buffer.
  }
  

  // Clears any data from the libray buffer. then 
  //byteSerial.flush();

//delay(1000);
}

