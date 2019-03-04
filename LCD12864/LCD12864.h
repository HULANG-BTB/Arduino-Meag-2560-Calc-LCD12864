#ifndef LCD12864_h
#define LCD12864_h
#include <avr/pgmspace.h>
#include <inttypes.h>

class LCD12864
{

public:

    LCD12864();

    void Initialise(void);
    void setPins(uint8_t tRS, uint8_t tRW, uint8_t tD0, uint8_t tD1, uint8_t tD2, uint8_t tD3, uint8_t tD4, uint8_t tD5, uint8_t tD6, uint8_t tD7);
    void configPins(uint8_t tEN, uint8_t tRW, uint8_t tRS, uint8_t tCS1, uint8_t tCs2, uint8_t tD0, uint8_t tD1, uint8_t tD2, uint8_t tD3, uint8_t tD4, uint8_t tD5, uint8_t tD6, uint8_t tD7);
    void delayns(void);
    void VectorConverter(int vector);
    void selectCs(int CS1, int CS2);
    void setPosition(int x, int y);

    void WriteCommand(int CMD);
    void WriteData(int CMD);


    void CLEAR(void);
    void Display(int X, int Y, unsigned char *ptr, int dat);


    int ScreenBuffer[16][32];

    int delaytime;
    int DEFAULTTIME;

    int CS1;
    int CS2;
    int RS;
    int RW;
    int EN;
    int D0;
    int D1;
    int D2;
    int D3;
    int D4;
    int D5;
    int D6;
    int D7;

    int temp[8];

};
extern LCD12864 LCDA;
#endif
