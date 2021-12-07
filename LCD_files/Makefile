CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall
LDFLAGS = -lrt -pthread -lgpiod
OBJFILES = client.o wiringPi.o softTone.o softPwm.o lcd.o
TARGET = client
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
