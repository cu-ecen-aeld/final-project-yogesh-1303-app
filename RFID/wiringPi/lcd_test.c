
#include <wiringPi.h>
#include <lcd.h>
#include <stdio.h>

#define D4  (21) 
#define D5  (22)
#define D6  (23)
#define D7  (24)

#define EN  (7)
#define RS  (25)

int main()
{
	int lcd;
	wiringPiSetup();
	pinMode(D4, OUTPUT);
	pinMode(D5, OUTPUT);
	pinMode(D6, OUTPUT);
	pinMode(D7, OUTPUT);
	pinMode(EN, OUTPUT);
	pinMode(RS, OUTPUT);

	lcd = lcdInit(2, 16, 4, RS, EN, D4, D5, D6, D7, 0, 0, 0, 0);
	lcdClear(lcd);
	lcdPosition(lcd, 0, 0);
	lcdPuts(lcd, "Hello");
	return 0;
}
