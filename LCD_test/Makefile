CC = $(CROSS_COMPILE)gcc
CFLAGS = -Wall
LDFLAGS = -lrt -lgpiod -pthread
OBJFILES = wiringPi.o softTone.o softPwm.o lcd.o lcd_test.o
TARGET = lcd_test
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
