#include <Arduino.h>
#include <LCD.h>



LCD::LCD(uint8_t rs,uint8_t en,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3){
	LCD::_pins(true,rs,255,en,d0,d1,d2,d3,0,0,0,0);
}



LCD::LCD(uint8_t rs,uint8_t rw,uint8_t en,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3){
	LCD::_pins(true,rs,rw,en,d0,d1,d2,d3,0,0,0,0);
}



LCD::LCD(uint8_t rs,uint8_t en,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7){
	LCD::_pins(false,rs,255,en,d0,d1,d2,d3,d4,d5,d6,d7);
}



LCD::LCD(uint8_t rs,uint8_t rw,uint8_t en,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7){
	LCD::_pins(false,rs,rw,en,d0,d1,d2,d3,d4,d5,d6,d7);
}



void LCD::size(uint8_t w,uint8_t h){
	this->_sz[0]=w;
	this->_sz[1]=h;
}



void LCD::init(){
	pinMode(this->_rs_p,OUTPUT);
	if (this->_rw_p!=255){
		pinMode(this->_rw_p,OUTPUT);
	}
	pinMode(this->_en_p,OUTPUT);
	for (uint8_t i=0;i<(this->_b4==true?4:8);i++){
		pinMode(this->_d_pl[i],OUTPUT);
	}
	delayMicroseconds(50000);
	digitalWrite(this->_rs_p,LOW);
	digitalWrite(this->_en_p,LOW);
	if (this->_rw_p!=255){
		digitalWrite(this->_rw_p,LOW);
	}
	if (this->_b4==true){
		digitalWrite(this->_d_pl[0],0x01);
		digitalWrite(this->_d_pl[1],0x01);
		digitalWrite(this->_d_pl[2],0x00);
		digitalWrite(this->_d_pl[3],0x00);
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,HIGH);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(4601);
		digitalWrite(this->_en_p,HIGH);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(4601);
		digitalWrite(this->_en_p,HIGH);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(250);
		digitalWrite(this->_d_pl[0],0x00);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,HIGH);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(100);
	}
	else{
		this->_data(LOW,LCD_FUNCTIONSET|(this->_sz[1]>1?0x08:0x00)|(this->_b4==true?0x00:0x10));
		delayMicroseconds(4500);
		this->_data(LOW,LCD_FUNCTIONSET|(this->_sz[1]>1?0x08:0x00)|(this->_b4==true?0x00:0x10));
		delayMicroseconds(150);
		this->_data(LOW,LCD_FUNCTIONSET|(this->_sz[1]>1?0x08:0x00)|(this->_b4==true?0x00:0x10));
	}
	this->_data(LOW,LCD_FUNCTIONSET|(this->_sz[1]>1?0x08:0x00)|(this->_b4==true?0x00:0x10));
	this->_c_f=LCD_DISPLAYON|LCD_CURSOROFF|LCD_BLINKOFF;
	this->_data(LOW,LCD_DISPLAYCONTROL|this->_c_f);
	this->_data(LOW,LCD_CLEARDISPLAY);
	delayMicroseconds(2000);
	this->_d_f=LCD_ENTRYLEFT|LCD_ENTRYSHIFTDECREMENT;
	this->_data(LOW,LCD_ENTRYMODESET|this->_d_f);
}



void LCD::clear(){
	this->_data(LOW,LCD_CLEARDISPLAY);
	delayMicroseconds(2000);
}



void LCD::home(){
	this->_data(LOW,LCD_RETURNHOME);
	delayMicroseconds(2000);
}



void LCD::move(uint8_t x,uint8_t y){
	if (y>=this->_sz[1]){
		y=this->_sz[1]-1;
	}
	this->_data(LOW,LCD_SETDDRAMADDR|(x+(y==0?0x00:(y==1?0x40:(y==2?0x00+this->_sz[0]:0x40+this->_sz[0])))));
}



void LCD::write(uint8_t b){
	this->_data(HIGH,b);
}



void LCD::write(char c){
	this->_data(HIGH,c);
}



void LCD::write(short s){
	this->write(String(s));
}



void LCD::write(int i){
	this->write(String(i));
}



void LCD::write(unsigned int ui){
	this->write(String(ui));
}



void LCD::write(float f){
	this->write(String(f));
}



void LCD::write(long l){
	this->write(String(l));
}



void LCD::write(unsigned long ul){
	this->write(String(ul));
}



void LCD::write(double d){
	this->write(String(d));
}



void LCD::write(String s){
	for (size_t i=0;i<s.length();i++){
		this->_data(HIGH,s.charAt(i));
	}
}



void LCD::_pins(bool b4,uint8_t rs,uint8_t rw,uint8_t en,uint8_t d0,uint8_t d1,uint8_t d2,uint8_t d3,uint8_t d4,uint8_t d5,uint8_t d6,uint8_t d7){
	this->_b4=b4;
	this->_rs_p=rs;
	this->_rw_p=rw;
	this->_en_p=en;
	this->_d_pl=new uint8_t[8]{d0,d1,d2,d3,d4,d5,d6,d7};
	this->_sz=new uint8_t[2]{16,1};
}



void LCD::_data(uint8_t m,uint8_t v){
	digitalWrite(this->_rs_p,m);
	if (this->_rw_p!=255){
		digitalWrite(this->_rw_p,LOW);
	}
	if (this->_b4==true){
		for (int i=0;i<4;i++){
			digitalWrite(this->_d_pl[i],(v>>(i+4))&0x01);
		}
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,HIGH);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(100);
		for (int i=0;i<4;i++){
			digitalWrite(this->_d_pl[i],(v>>i)&0x01);
		}
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,HIGH);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(100);
	}
	else{
		for (uint8_t i=0;i<8;i++){
			digitalWrite(this->_d_pl[i],(v>>i)&0x01);
		}
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,HIGH);
		delayMicroseconds(1);
		digitalWrite(this->_en_p,LOW);
		delayMicroseconds(100);
	}
}
