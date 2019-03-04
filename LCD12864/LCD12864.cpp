#include "LCD12864.h"
//#include "LCDSprite.h"
#include <Arduino.h>

extern "C"
{
// #include <wiring.h>
#include <inttypes.h>
#include <stdio.h>  //not needed yet
#include <string.h> //needed for strlen()
#include <avr/pgmspace.h>
}

LCD12864::LCD12864()
{
    this->DEFAULTTIME = 1; // 80 ms default time
    this->delaytime = DEFAULTTIME;
    this->CS1 = 57;
    this->CS2 = 58;
    this->RS  = 56;
    this->RW  = 55;
    this->EN  = 54;
    this->D0  = 62;
    this->D1  = 63;
    this->D2  = 64;
    this->D3  = 65;
    this->D4  = 66;
    this->D5  = 67;
    this->D6  = 68;
    this->D7  = 69;
}

void LCD12864::setPins(uint8_t tRS, uint8_t tRW, uint8_t tD0, uint8_t tD1, uint8_t tD2, uint8_t tD3, uint8_t tD4, uint8_t tD5, uint8_t tD6, uint8_t tD7)
{
    digitalWrite(EN, 0);
    delayns();
    digitalWrite(this->RS, tRS);
    digitalWrite(this->RW, tRW);
    digitalWrite(this->D7, tD7);
    digitalWrite(this->D6, tD6);
    digitalWrite(this->D5, tD5);
    digitalWrite(this->D4, tD4);
    digitalWrite(this->D3, tD3);
    digitalWrite(this->D2, tD2);
    digitalWrite(this->D1, tD1);
    digitalWrite(this->D0, tD0);
    delayns();
    digitalWrite(EN, 1);
    delayns();
    digitalWrite(EN, 0);
}

void LCD12864::configPins(uint8_t tEN, uint8_t tRW, uint8_t tRS, uint8_t tCS1, uint8_t tCs2, uint8_t tD0, uint8_t tD1, uint8_t tD2, uint8_t tD3, uint8_t tD4, uint8_t tD5, uint8_t tD6, uint8_t tD7)
{

    this->EN  = tEN;
    this->RW  = tRW;
    this->RS  = tRS;
    this->CS1 = tCS1;
    this->CS2 = tCs2;
    this->D0  = tD0;
    this->D1  = tD1;
    this->D2  = tD2;
    this->D3  = tD3;
    this->D4  = tD4;
    this->D5  = tD5;
    this->D6  = tD6;
    this->D7  = tD7;
}

//*********************ÑÓÊ±º¯Êý************************//
void LCD12864::delayns(void)
{
    delayMicroseconds(delaytime);
}

void LCD12864::VectorConverter(int vector)
{
    int result = vector;
    for (int i = 0; i <= 7; i++)
    {
        this->temp[i] = (result >> i ) % 2;
    }

}

void LCD12864::selectCs(int tCS1, int tCS2)
{
    digitalWrite(this->CS2, tCS2);
    digitalWrite(this->CS1, tCS1);
}

void LCD12864::setPosition(int x, int y)
{
	unsigned char row = x % 256;
	unsigned char col = y % 245;
    if ( col >= 64 )
    {
        // 列地址大于等于64 右屏幕显示
        this->selectCs(0, 1);    // 右屏显示
        col = col - 64;
    }
    else
    {
        this->selectCs(1, 0);    // 左屏右屏
    }
    WriteCommand(0x40 | col);
    delayns();
    WriteCommand(0xb8 | row);
}

void LCD12864::WriteCommand(int CMD)
{
    delayns();
    VectorConverter(CMD); // lets get the binary from the dec
    setPins(0, 0, this->temp[0], this->temp[1], this->temp[2], this->temp[3], this->temp[4], this->temp[5], this->temp[6], this->temp[7]); //WriteCommand

}

void LCD12864::WriteData(int CMD)
{
    delayns();
    VectorConverter(CMD); // lets get the binary from the dec
    setPins(1, 0, this->temp[0], this->temp[1], this->temp[2], this->temp[3], this->temp[4], this->temp[5], this->temp[6], this->temp[7]); //WriteData
}

void LCD12864::Initialise(void)
{

    pinMode(this->CS1, OUTPUT);
    pinMode(this->CS2, OUTPUT);
    pinMode(this->RS, OUTPUT);
    pinMode(this->RW, OUTPUT);
    pinMode(this->EN, OUTPUT);
    pinMode(this->D0, OUTPUT);
    pinMode(this->D1, OUTPUT);
    pinMode(this->D2, OUTPUT);
    pinMode(this->D3, OUTPUT);
    pinMode(this->D4, OUTPUT);
    pinMode(this->D5, OUTPUT);
    pinMode(this->D6, OUTPUT);
    pinMode(this->D7, OUTPUT);
    delayns();

    WriteCommand(0x30);        // 30-H 基本操作
    WriteCommand(0x4c);        // 开显示，关光标，不闪烁
    WriteCommand(0x01);        // 清除显示
    WriteCommand(0x06);        // 光标移动方向-左，DDRAM的地址计数器(AC)加1
}

void LCD12864::CLEAR(void)
{
    WriteCommand(0x30);        // 30-H 基本操作
    WriteCommand(0x01);        // 清除显示
}

void LCD12864::Display(int X, int Y, unsigned char *ptr, int dat)
{
    int i;

    for (i = 0; i < dat; i++)
    {
        this->setPosition(X, dat*Y + i);
        this->WriteData(ptr[i]);
        this->setPosition(X+1, dat*Y + i);
        this->WriteData(ptr[i+dat]);
    }
}

LCD12864 LCDA = LCD12864();