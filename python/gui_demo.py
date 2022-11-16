import lcd_1inch44
from PIL import ImageDraw, Image, ImageFont
import time

if __name__ == '__main__':
    lcd = lcd_1inch44.LCD_1Inch44()
    lcd.lcd_init()
    lcd.clear()
    img0 = Image.new("RGB", (lcd.w, lcd.h), "WHITE")
    lcd_draw = ImageDraw.Draw(img0)
    Font = ImageFont.truetype("MiSans-Light.ttf",18) # read chinese font file
    text= u"深桂科技"
    img1 = Image.open('fruits.jpg') # open jpg file
    while True:
        lcd_draw.line([(5, 5),(30, 30)], fill = "RED",width = 1)
    
        lcd_draw.rectangle([(35,10),(55,30)],fill = "WHITE",outline="BLUE")
        lcd_draw.rectangle([(60,10),(80,30)],fill = "BLUE")
        lcd_draw.rectangle([(50,45),(120,55)],fill = "GREEN")    
        lcd_draw.arc((90,10,120,40), 0, 360, fill =(0,255,255))
        lcd_draw.ellipse((10,35,40,65), fill = (255,255,0))
    
        lcd_draw.text((2, 65), 'SEENGREAT', fill = "BLUE",font=Font)
        lcd_draw.text((2, 85), 'ABcd321', fill = "RED",font=Font)
    
        lcd_draw.text((2, 105),text, fill = "BLUE",font=Font)
    
        lcd.img_show(img0)
      
        time.sleep(3)
        lcd.img_show(img1) # show image
        time.sleep(3)