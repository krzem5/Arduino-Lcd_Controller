#include <LCD.h>



LCD lcd(12,11,5,4,3,2);



void setup(){
	lcd.size(16,2);
	lcd.init();
	lcd.write("Seconds:");
}



void loop(){
	lcd.move(0,1);
	lcd.write(millis()/1e3);
}
