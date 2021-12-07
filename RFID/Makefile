CC = $(CROSS_COMPILE)gcc 
CFLAGS = -Wall
LDFLAGS = -lrt -pthread -lgpiod
OBJFILES = wiringPiSPI.o wiringPiI2C.o wiringSerial.o pn532.o pn532_rpi.o rpi_get_uid.o wiringPi.o softTone.o softPwm.o  
TARGET = rpi_get_uid
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
