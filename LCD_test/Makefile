ifeq ($(CC),)
	CC = $(CROSS_COMPILE)gcc
endif
ifeq ($CFLAGS),)
	CFLAGS = -g -Wall -Werror
endif

ifeq ($(INCLUDES),)
	INCLUDES = -I/
endif

DEPS = lcd.h softTone.h softPwm.h wiringPi.h

all: lcd_test 


lcd_test.o: lcd_test.c $(DEPS)
	$(CC) $(CFLAGS) -c lcd_test.c -lwiringPi -lwiringPiDev

lcd_test: lcd_test.o
	$(CC) $(CFLAGS) lcd_test.o -o lcd_test -lwiringPi -lwiringPiDev
#-lgpiod


#lcd1: lcd1.o wiringPi.o
#	$(CC) $(CFLAGS) -c -o lcd1.o wiringPi.o -lgpiod


clean:
	rm -f *.o
	rm -f lcd_test
