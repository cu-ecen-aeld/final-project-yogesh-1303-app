ifeq ($(CC),)
	CC = $(CROSS_COMPILE)gcc
endif
ifeq ($CFLAGS),)
	CFLAGS = -g -Wall -Werror
endif

ifeq ($(INCLUDES),)
	INCLUDES = -I/
endif

all: lcd_test 


lcd_test.o: lcd_test.c
	$(CC) $(CFLAGS) -c lcd_test.c

lcd_test: lcd_test.o
	$(CC) $(CFLAGS) lcd.o -o lcd_test -lgpiod


#lcd1: lcd1.o wiringPi.o
#	$(CC) $(CFLAGS) -c -o lcd1.o wiringPi.o -lgpiod


clean:
	rm -f *.o
	rm -f lcd_test
