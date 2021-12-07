CC = $(CROSS_COMPILE)gcc 
CFLAGS = -Wall
LDFLAGS = -lrt -pthread 
#-lgpiod
OBJFILES = client.o wiringPiSPI.o wiringPiI2C.o wiringSerial.o wiringPi.o softTone.o softPwm.o  
TARGET = client-gcc
#rpi_get_uid
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
