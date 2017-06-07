#pragma once

#include <LiquidCrystal_I2C.h>

#if LCD
LiquidCrystal_I2C lcd(0x27,20,4); // set the LCD address to 0x27 for a 16 chars and 2 line display
#endif

void lcdSetup() {
#if LCD
	lcd.init();
	lcd.backlight();
#endif
}

void displayWheels(String direction) {
#if LCD
	lcd.setCursor(0,0);
	lcd.print(direction + "          ");
#endif
}
