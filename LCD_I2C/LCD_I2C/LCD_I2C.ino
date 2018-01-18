#include <LiquidCrystal_I2C.h>
/*
 * LCD_I2C.ino
 *
 * Created: 5/31/2017 7:15:51 PM
 * Author: OBED
 */ 
LiquidCrystal_I2C lcd(0x27, 16, 1);
void setup()
{
	
lcd.begin();
// Turn on the blacklight and print a message.
lcd.backlight();
lcd.print("JKUAT EEE");


}

void loop()
{

	  /* add main program code here, this code starts again each time it ends */

}
