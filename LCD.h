#include <Arduino.h>
#include <string.h>



#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00



class LCD{
	public:
		LCD(uint8_t rs,uint8_t en,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3);
		LCD(uint8_t rs,uint8_t rw,uint8_t en,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3);
		LCD(uint8_t rs,uint8_t en,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7);
		LCD(uint8_t rs,uint8_t rw,uint8_t en,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7);
		void size(uint8_t w,uint8_t h);
		void init();
		void clear();
		void home();
		void move(uint8_t x,uint8_t y);
		void write(uint8_t b);
		void write(char c);
		void write(short s);
		void write(int i);
		void write(unsigned int i);
		void write(float f);
		void write(long l);
		void write(unsigned long l);
		void write(double d);
		void write(String s);
	private:
		bool _b4;
		uint8_t _rs_p;
		uint8_t _rw_p;
		uint8_t _en_p;
		uint8_t* _d_pl;
		uint8_t* _sz;
		uint8_t _c_f;
		uint8_t _d_f;
		void _pins(bool b4,uint8_t rs,uint8_t rw,uint8_t en,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7);
		void _data(uint8_t m,uint8_t v);
};
