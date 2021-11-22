CC = gcc 
CFLAGS = -Wall
LDFLAGS = -lrt -pthread -lwiringPi -lwiringPiDev
OBJFILES = wiringPi.o lcd_test.o
TARGET = lcd_test
all: $(TARGET)
$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
clean:
	rm -f $(OBJFILES) $(TARGET) *~
