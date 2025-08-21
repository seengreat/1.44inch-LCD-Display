/********************************
 *  Seengreat 1.44 Inch LCD Display demo
 *  Author(s):Andy Li from Seengreat
 * ********************/
 
#include <string.h>
#include <stdlib.h>		
#include "sg_lgpio.h"
#include "lcd_gui.h"
#include "lcd_1inch44.h"
#include "key.h"

/*******************
#define K1_PIN      17
#define K2_PIN      18
#define K3_PIN      22
#define K4_PIN      23
#define R_PIN       20
#define L_PIN       21
#define UP_PIN      13
#define LEFT_PIN    5
#define DOWN_PIN    26
#define RIGHT_PIN   19
#define CENTER_PIN  6
**********/
	
void Key_Init(void)
{
    printf("Key Init\r\n");
    Lgpio_set_pinmode(K1_PIN,LGPIO_INPUT);
    Lgpio_set_pinmode(K2_PIN,LGPIO_INPUT);
    Lgpio_set_pinmode(K3_PIN,LGPIO_INPUT);
    Lgpio_set_pinmode(K4_PIN,LGPIO_INPUT);
    Lgpio_set_pinmode(L_PIN,LGPIO_INPUT);
    Lgpio_set_pinmode(R_PIN,LGPIO_INPUT);
    Lgpio_set_pinmode(UP_PIN,LGPIO_INPUT);
    Lgpio_set_pinmode(LEFT_PIN,LGPIO_INPUT);
    Lgpio_set_pinmode(DOWN_PIN,LGPIO_INPUT);
    Lgpio_set_pinmode(RIGHT_PIN,LGPIO_INPUT);
    Lgpio_set_pinmode(CENTER_PIN,LGPIO_INPUT);
}

void Key_Task(void)
{
	Gui_Clear(WHITE);
	Gui_draw_rectangle(90, 43, 110, 53, BLACK, 1, FULL); //K1
	Gui_draw_rectangle(80, 58, 90, 78, BLACK, 1, FULL); //K2
	Gui_draw_rectangle(110, 58, 120, 78, BLACK, 1, FULL);//K3
	Gui_draw_rectangle(90, 83, 110, 93, BLACK, 1, FULL);//K4
	Gui_draw_rectangle(25, 5, 45, 15, BLACK, 1, FULL);//L
	Gui_draw_rectangle(83, 5, 103, 15, BLACK, 1, FULL);//R
	Gui_draw_rectangle(20, 43, 40, 53, BLACK, 1, FULL); //UP
	Gui_draw_rectangle(5, 58, 15, 78, BLACK, 1, FULL); //LEFT
	Gui_draw_rectangle(45, 58, 55, 78, BLACK, 1, FULL);//RIGHT
	Gui_draw_rectangle(20, 83, 40, 93, BLACK, 1, FULL); //DOWN
	Gui_draw_rectangle(20, 58, 40, 78, BLACK, 1, FULL);// CENTER
	Display(Image.img);
	int k1_flag = 0;
	int k2_flag = 0;
	int k3_flag = 0;
	int k4_flag = 0;
	int l_flag = 0;
	int r_flag = 0;
	int center_flag = 0;
	int up_flag = 0;
	int left_flag = 0;
	int right_flag = 0;
	int down_flag = 0;
	printf("Key Task\r\n");
	for(;;)
	{
	    //K1 key
	    if(Lgpio_read_pin(K1_PIN) == LGPIO_LOW && k1_flag == 0)
	    {
	        delay(10);
		if(Lgpio_read_pin(K1_PIN) == LGPIO_LOW) // make sure the button has been pressed
		{
		     k1_flag = 1;
		     Gui_draw_rectangle(90, 43, 110, 53, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("K1 Press\r\n");
		}
	    }
	    else if(Lgpio_read_pin(K1_PIN) == LGPIO_HIGH && k1_flag == 1) // key has been released
	    {
		k1_flag = 0;
		Gui_draw_rectangle(90, 43, 110, 53, BLACK, 1, FULL);
		Display(Image.img);
	    }
	    
            //K2 key
	    if(Lgpio_read_pin(K2_PIN) == LGPIO_LOW && k2_flag == 0)
	    {
	        delay(10);
		if(Lgpio_read_pin(K2_PIN) == LGPIO_LOW) // make sure the button has been pressed
		{
		     k2_flag = 1;
		     Gui_draw_rectangle(80, 58, 90, 78, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("K2 Press\r\n");
		}
	    }
	    else if(Lgpio_read_pin(K2_PIN) == LGPIO_HIGH && k2_flag == 1) // key has been released
	    {
		k2_flag = 0;
		Gui_draw_rectangle(80, 58, 90, 78, BLACK, 1, FULL);
		Display(Image.img);
	    }
	    
	    //K3 key
	    if(Lgpio_read_pin(K3_PIN) == LGPIO_LOW && k3_flag == 0)
	    {
		delay(10);
		if(Lgpio_read_pin(K3_PIN) == LGPIO_LOW) // make sure the button has been pressed
		{
		     k3_flag = 1;
		     Gui_draw_rectangle(110, 58, 120, 78, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("K3 Press\r\n");
		}
	    }
	    else if(Lgpio_read_pin(K3_PIN) == LGPIO_HIGH && k3_flag == 1) // key has been released
	    {
		k3_flag = 0;
		Gui_draw_rectangle(110, 58, 120, 78, BLACK, 1, FULL);
		Display(Image.img);
	    }
	    
	    //K4 key
	    if(Lgpio_read_pin(K4_PIN) == LGPIO_LOW && k4_flag == 0)
	    {
		delay(10);
		if(Lgpio_read_pin(K4_PIN) == LGPIO_LOW) // make sure the button has been pressed
		{
		     k4_flag = 1;
		     Gui_draw_rectangle(90, 83, 110, 93, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("K4 Press\r\n");
		}
	   }
	   else if(Lgpio_read_pin(K4_PIN) == LGPIO_HIGH && k4_flag == 1) // key has been released
	   {
		k4_flag = 0;
		Gui_draw_rectangle(90, 83, 110, 93, BLACK, 1, FULL);
		Display(Image.img);
	   }
	   
	   //L key
	  if(Lgpio_read_pin(L_PIN) == LGPIO_LOW && l_flag == 0)
	  {
		delay(10);
		if(Lgpio_read_pin(L_PIN) == LGPIO_LOW) // make sure the button has been pressed
		{
		     l_flag = 1;
		     Gui_draw_rectangle(25, 5, 45, 15, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("L Press\r\n");
		}
	  }
	  else if(Lgpio_read_pin(L_PIN) == LGPIO_HIGH && l_flag == 1) // key has been released
	  {
	     l_flag = 0;
	     Gui_draw_rectangle(25, 5, 45, 15, BLACK, 1, FULL);
	     Display(Image.img);
	  }
	  
	  //R key
	  if(Lgpio_read_pin(R_PIN) == LGPIO_LOW && r_flag == 0)
	  {
	     delay(10);
	     if(Lgpio_read_pin(R_PIN) == LGPIO_LOW) // make sure the button has been pressed
	     {
		 r_flag = 1;
		 Gui_draw_rectangle(83, 5, 103, 15, GREEN, 1, FULL);
		 Display(Image.img);
		 printf("R Press\r\n");
	     }
         }
	 else if(Lgpio_read_pin(R_PIN) == LGPIO_HIGH && r_flag == 1) // key has been released
	 {
	    r_flag = 0;
	    Gui_draw_rectangle(83, 5, 103, 15, BLACK, 1, FULL);
	    Display(Image.img);
	 }
	 
	//UP key
	if(Lgpio_read_pin(UP_PIN) == LGPIO_LOW && up_flag == 0)
	{
	    delay(10);
	    if(Lgpio_read_pin(UP_PIN) == LGPIO_LOW) // make sure the button has been pressed
	    {
		up_flag = 1;
		Gui_draw_rectangle(20, 43, 40, 53, GREEN, 1, FULL);
		Display(Image.img);
		printf("UP Press\r\n");
	    }
	}
	else if(Lgpio_read_pin(UP_PIN) == LGPIO_HIGH && up_flag == 1) // key has been released
	{
	    up_flag = 0;
	    Gui_draw_rectangle(20, 43, 40, 53, BLACK, 1, FULL);
	    Display(Image.img);
	}

	//LEFT key
	if(Lgpio_read_pin(LEFT_PIN) == LGPIO_LOW && left_flag == 0)
	{
	    delay(10);
	    if(Lgpio_read_pin(LEFT_PIN) == LGPIO_LOW) // make sure the button has been pressed
	    {
		 left_flag = 1;
		 Gui_draw_rectangle(5, 58, 15, 78, GREEN, 1, FULL);
		 Display(Image.img);
		 printf("LEFT Press\r\n");
	    }
	}
	else if(Lgpio_read_pin(LEFT_PIN) == LGPIO_HIGH && left_flag == 1) // key has been released
	{
	    left_flag = 0;
	    Gui_draw_rectangle(5, 58, 15, 78, BLACK, 1, FULL);
	    Display(Image.img);
	}
	    
        //RIGHT key
	if(Lgpio_read_pin(RIGHT_PIN) == LGPIO_LOW && right_flag == 0)
	{
	    delay(10);
	    if(Lgpio_read_pin(RIGHT_PIN) == LGPIO_LOW) // make sure the button has been pressed
	    {
		     right_flag = 1;
		     Gui_draw_rectangle(45, 58, 55, 78, GREEN, 1, FULL);
		     Display(Image.img);
		     printf("RIGHT Press\r\n");
	    }
	}
	else if(Lgpio_read_pin(RIGHT_PIN) == LGPIO_HIGH && right_flag == 1) // key has been released
	{
	    right_flag = 0;
	    Gui_draw_rectangle(45, 58, 55, 78, BLACK, 1, FULL);
	    Display(Image.img);
	}

	//DOWN key
	if(Lgpio_read_pin(DOWN_PIN) == LGPIO_LOW && down_flag == 0)
	{
	    delay(10);
	    if(Lgpio_read_pin(DOWN_PIN) == LGPIO_LOW) // make sure the button has been pressed
	    {
		down_flag = 1;
		Gui_draw_rectangle(20, 83, 40, 93, GREEN, 1, FULL);
		Display(Image.img);
		printf("DOWN Press\r\n");
	    }
	}
	else if(Lgpio_read_pin(DOWN_PIN) == LGPIO_HIGH && down_flag == 1) // key has been released
	{
		down_flag = 0;
		Gui_draw_rectangle(20, 83, 40, 93, BLACK, 1, FULL);
		Display(Image.img);
	}
	
	//CENTER key
	if(Lgpio_read_pin(CENTER_PIN) == LGPIO_LOW && center_flag == 0)
	{
	    delay(10);
	    if(Lgpio_read_pin(CENTER_PIN) == LGPIO_LOW) // make sure the button has been pressed
	    {
		center_flag = 1;
		Gui_draw_rectangle(20, 58, 40, 78, GREEN, 1, FULL);
		Display(Image.img);
		printf("Center Press\r\n");
	    }
	}
	else if(Lgpio_read_pin(CENTER_PIN) == LGPIO_HIGH && center_flag == 1) // key has been released
	{
	    center_flag = 0;
	    Gui_draw_rectangle(20, 58, 40, 78, BLACK, 1, FULL);
	    Display(Image.img);
	}

    } 		
}
