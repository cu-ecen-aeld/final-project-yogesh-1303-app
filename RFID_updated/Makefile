CC = $(CROSS_COMPILE)gcc 
CFLAGS = -Wall
LDFLAGS = -lrt -pthread -lgpiod	
#-lgpiod
OBJFILES = server.o wiringPiSPI.o wiringPiI2C.o wiringSerial.o pn532.o pn532_rpi.o wiringPi.o softTone.o softPwm.o  
TARGET = server-gcc
#rpi_get_uid
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
