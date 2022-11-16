/********************************
 *  Seengreat 1.44 Inch LCD Display demo
 *  Author(s):Andy Li from Seengreat
 * ********************/
 
#include <string.h>
#include <stdlib.h>		
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <softPwm.h>

#include "lcd_1inch44.h"

void Lcd_Gpio_Init(void)
{
	printf("Init gpio for wiringpi\r\n");
    if(wiringPiSetup() < 0)//use wiringpi Pin number
    { 
        printf("wiringPi lib init failed! \r\n");
    } 
    pinMode(PIN_CS, OUTPUT);
    pinMode(PIN_RST, OUTPUT);
    pinMode(PIN_DC, OUTPUT);
    pinMode(PIN_BL, OUTPUT);
    wiringPiSPISetup(0,8000000);
    softPwmCreate(PIN_BL, 0, 100); //black light pwm
    softPwmWrite(PIN_BL, 80);
}

/*******************************************************************************
function:
	Hardware reset
*******************************************************************************/
static void Lcd_Reset(void)
{
	digitalWrite(PIN_CS, 1);
	delay(100);
	digitalWrite(PIN_RST, 0);
	delay(100);
	digitalWrite(PIN_RST, 1);
	delay(100);
}

/*******************************************************************************
function:
		Write data and commands
*******************************************************************************/
static void Spi_write_cmd(u_char data)	 
{	
	digitalWrite(PIN_CS, 0);
	digitalWrite(PIN_DC, 0);
	wiringPiSPIDataRW(0,&data,1);
}

static void Spi_write_data(u_char data) 
{	
	digitalWrite(PIN_CS, 0);
	digitalWrite(PIN_DC, 1);
	wiringPiSPIDataRW(0,&data,1); 
	digitalWrite(PIN_CS,1);
}  

void Spi_write_word(u_int16_t data)
{
	u_char temp = 0;
	digitalWrite(PIN_CS, 0);
	digitalWrite(PIN_DC, 1);
	temp = (data>>8) & 0xff;
	wiringPiSPIDataRW(0,&temp,1);
	temp = data & 0xff;
	wiringPiSPIDataRW(0,&temp,1); 
	digitalWrite(PIN_CS, 1);
}	  


/******************************************************************************
function:	
		Common register initialization
******************************************************************************/
void Lcd_Init(void)
{
	Lcd_Gpio_Init();
	Lcd_Reset();

	Spi_write_cmd(0x01);
	delay(20); 

	Spi_write_cmd(0x11); 
	delay(50); 

	Spi_write_cmd(0xB1);
	Spi_write_data(0x02);
	Spi_write_data(0x35);
	Spi_write_data(0x36);

	Spi_write_cmd(0xB2);
	Spi_write_data(0x02);
	Spi_write_data(0x35);
	Spi_write_data(0x36);

	Spi_write_cmd(0xB3);
	Spi_write_data(0x02);
	Spi_write_data(0x35);
	Spi_write_data(0x36);
	Spi_write_data(0x02);
	Spi_write_data(0x35);
	Spi_write_data(0x36);

	Spi_write_cmd(0xB4);
	Spi_write_data(0x03); 

	Spi_write_cmd(0xBB);
	Spi_write_data(0x1F);

	Spi_write_cmd(0xC0);
	Spi_write_data(0xA2);
	Spi_write_data(0x02);
	Spi_write_data(0x84);

	Spi_write_cmd(0xC1);
	Spi_write_data(0xC5);

	Spi_write_cmd(0xC2);
	Spi_write_data(0x0D);
	Spi_write_data(0x00);
	
	Spi_write_cmd(0xC3);
	Spi_write_data(0x8D);   
	Spi_write_data(0x2A);   

	Spi_write_cmd(0xC4);
	Spi_write_data(0x8D);
	Spi_write_data(0xEE);

	Spi_write_cmd(0xC5);
	Spi_write_data(0x0A); 

	Spi_write_cmd(0x36);
	Spi_write_data(0x68); 

	Spi_write_cmd(0xE0);
	Spi_write_data(0x12);
	Spi_write_data(0x1C);
	Spi_write_data(0x10);
	Spi_write_data(0x18);
	Spi_write_data(0x33);
	Spi_write_data(0x2C);
	Spi_write_data(0x25);
	Spi_write_data(0x28);
	Spi_write_data(0x28);
	Spi_write_data(0x27);
	Spi_write_data(0x2F);
	Spi_write_data(0x3C);
	Spi_write_data(0x00);
	Spi_write_data(0x03);
	Spi_write_data(0x03);
	Spi_write_data(0x10);

	Spi_write_cmd(0xE1);
	Spi_write_data(0x12);
	Spi_write_data(0x1C);
	Spi_write_data(0x10);
	Spi_write_data(0x18);
	Spi_write_data(0x2D);
	Spi_write_data(0x28);
	Spi_write_data(0x23);
	Spi_write_data(0x28);
	Spi_write_data(0x28);
	Spi_write_data(0x26);
	Spi_write_data(0x2F);
	Spi_write_data(0x3B);
	Spi_write_data(0x00);
	Spi_write_data(0x03);
	Spi_write_data(0x03);
	Spi_write_data(0x10);
	
	Spi_write_cmd(0xF0);
	Spi_write_data(0x01);

	Spi_write_cmd(0xF6);
	Spi_write_data(0x00);

	Spi_write_cmd(0x3A);
	Spi_write_data(0x05);
	

	Spi_write_cmd(0x29);
	delay(50);
}


//select the srceen area(from point(start_x,start_y) to point(end_x,end_y))
void Set_Window(u_int16_t start_x, u_int16_t start_y, u_int16_t end_x, u_int16_t  end_y)
{ 
	start_x += 1;
	end_x += 1;
	start_y += 2;
	end_y += 2;
	Spi_write_cmd(0x2a);
	Spi_write_data(start_x >>8);
	Spi_write_data(start_x & 0xff);
	Spi_write_data(end_x >> 8);
	Spi_write_data(end_x & 0xff);

	Spi_write_cmd(0x2b);
	Spi_write_data(start_y >>8);
	Spi_write_data(start_y & 0xff);
	Spi_write_data(end_y >> 8);
	Spi_write_data(end_y & 0xff);

	Spi_write_cmd(0x2C);
}


//set cursor to the point(x, y)
void Set_Cursor(u_int16_t x, u_int16_t y)
{ 
	x += 1;
	y += 2;
	Spi_write_cmd(0x2a);
	Spi_write_data(x >> 8);
	Spi_write_data(x);
	Spi_write_data(x >> 8);
	Spi_write_data(x);

	Spi_write_cmd(0x2b);
	Spi_write_data(y >> 8);
	Spi_write_data(y);
	Spi_write_data(y >> 8);
	Spi_write_data(y);

	Spi_write_cmd(0x2C);
}

//refresh the entire screen to color
void Lcd_Clear(u_int16_t color)
{
	u_int16_t i;
	u_int16_t image[LCD_W];
	for(i=0;i<LCD_W;i++)
	{
		image[i] = color>>8 | (color&0xff)<<8;
	}
	u_char *p = (u_char *)(image);
	Set_Window(0, 0, LCD_W-1, LCD_H-1);
	digitalWrite(PIN_DC, 1);
	for(i = 0; i < LCD_H; i++)
	{
		wiringPiSPIDataRW(0, (unsigned char *)p, LCD_W*2);
	}
}


//display the image to whole screen 
void Display(u_int16_t *image)
{
	u_int16_t i;
	u_int16_t p[LCD_SIZE];
    memcpy(p,image,LCD_SIZE);
	Set_Window(0, 0, LCD_W-1, LCD_H-1);
	digitalWrite(PIN_DC, 1);
	for(i = 0; i < LCD_H; i++)
	{
		wiringPiSPIDataRW(0, (unsigned char *)p+LCD_W*2*i, LCD_W*2);
	}
}

//set the point(x,y) to color
void Draw_Point(u_int16_t x, u_int16_t y, u_int16_t Color)
{
	Set_Cursor(x, y);
	Spi_write_word(Color); 	    
}

