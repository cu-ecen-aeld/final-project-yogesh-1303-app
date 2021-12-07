#include <stdio.h>
#include <errno.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include <stdint.h>

#define REG_DATA_X_LOW  0x32
#define REG_DATA_Y_LOW  0x34
#define REG_DATA_Z_LOW  0x36

int main()
{
   int fd, result;

   // Initialize the interface by giving it an external device ID.
   // The MCP4725 defaults to address 0x60.   
   //
   // It returns a standard file descriptor.
   // 
   fd = wiringPiI2CSetup(0x24);
	
   if (fd == -1)
	printf("I2C error\n");
   //printf("Init result: %d",fd);
/*
   for(int i = 0; i < 0x0000ffff; i++)
   {
      // I tried using the "fast write" command, but couldn't get it to work.  
      // It's not entirely obvious what's happening behind the scenes as
      // regards to endianness or length of data sent.  I think it's only 
      // sending one byte, when we really need two.
      //
      // So instead I'm doing a 16 bit register access.  It appears to 
      // properly handle the endianness, and the length is specified by the 
      // call.  The only question was the register address, which is the 
      // concatenation of the command (010x = write DAC output) 
      // and power down (x00x = power up) bits.
      result = wiringPiI2CWriteReg16(fd, 0x40, (i & 0xfff) );

      if(result == -1)
      {
         printf("Error.  Errno is: %d",errno);
      }
   }
*/
   while(1)
   {
      /*
	   int dataX = wiringPiI2CReadReg16(fd, REG_DATA_X_LOW);
      dataX = -(~(int16_t)dataX + 1);
      
      int dataY = wiringPiI2CReadReg16(fd, REG_DATA_Y_LOW);
        dataY = -(~(int16_t)dataY + 1);
      
      int dataZ = wiringPiI2CReadReg16(fd, REG_DATA_Z_LOW);
       dataZ = -(~(int16_t)dataZ + 1);
        
      printf("%x %x %x \n", dataX, dataY, dataZ);
   */
	int data = wiringPiI2CRead(fd);  
	 printf("%x", data);

      usleep(100);
   }
   return 0;
}
