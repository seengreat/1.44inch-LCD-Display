# Seengreat 1.44 Inch LCD Display demo
# Author(s):Andy Li from Seengreat

import os
import sys
import spidev
import time
from gpiozero import *
import numpy as np

# define the key button pin in BCM number
RST_PIN  = 27
DC_PIN   = 25
BL_PIN   = 24
class LCD_1Inch44():
    def __init__(self):
        # gpio init
#         wpi.wiringPiSetup()
#         wpi.pinMode(DC_PIN, wpi.OUTPUT)  # D/C pin
        self.dc = DigitalOutputDevice( DC_PIN,active_high = True,initial_value =False)       
#         wpi.pinMode(RST_PIN, wpi.OUTPUT)  # reset pin
        self.rst = DigitalOutputDevice( RST_PIN,active_high = True,initial_value =False)
#         wpi.pinMode(BL_PIN, wpi.OUTPUT)  # back light control pin
        self.bl = PWMOutputDevice(BL_PIN,frequency = 1000)
        self.bl.value = 0.9
#         wpi.softPwmCreate(BL_PIN, 0, 100)
#         wpi.softPwmWrite(BL_PIN, 90)
        # spi init
        self.bus = 0
        self.dev = 0
        self.spi_speed = 8000000
        self.spi = spidev.SpiDev()
        self.spi.open(self.bus, self.dev)
        self.spi.max_speed_hz = self.spi_speed
        self.spi.mode = 0b00
        # self.spi.xfer([4000000, 10, 8])
        # define width and height of the 2 inch lcd
        self.w = 128
        self.h = 128 
        
    def write_cmd(self, cmd):
        """write command"""
#         wpi.digitalWrite(DC_PIN,wpi.LOW)
        self.dc.off()
        self.spi.writebytes([cmd])
        
    def write_data(self, value):
        """write data"""
#         wpi.digitalWrite(DC_PIN,wpi.HIGH)
        self.dc.on()
        self.spi.writebytes([value])
        
    def reset(self):
        """reset the lcd"""
#         wpi.digitalWrite(RST_PIN,wpi.HIGH)
        self.rst.on()
        time.sleep(0.01)
#         wpi.digitalWrite(RST_PIN,wpi.LOW)
        self.rst.off()
        time.sleep(0.01)
#         wpi.digitalWrite(RST_PIN,wpi.HIGH)
        self.rst.on()
        time.sleep(0.01)
    def lcd_init(self):
        """lcd init..."""
        self.reset()
        
        self.write_cmd(0x01) #software reset
        time.sleep(0.02)
        
        self.write_cmd(0x11) #sleep out
        time.sleep(0.05)       
        # FRMCTR1:Frame Rate Control in normal mode
        self.write_cmd(0xB1)
        self.write_data(0x02)
        self.write_data(0x35)
        self.write_data(0x36)
        
        # FRMCTR2:Frame Rate Control in idle mode
        self.write_cmd(0xB2)
        self.write_data(0x02)
        self.write_data(0x35)
        self.write_data(0x36)
        
        # FRMCTR3:Frame Rate Control in Partial mode/full colors
        self.write_cmd(0xB3)
        self.write_data(0x02)
        self.write_data(0x35)
        self.write_data(0x36)
        self.write_data(0x02)
        self.write_data(0x35)
        self.write_data(0x36)
        
        # INVCTR:Displa INversion Control
        self.write_cmd(0xB4) 
        self.write_data(0x03)
        
        # PWCTR1:Power Control 1
        self.write_cmd(0xC0) 
        self.write_data(0xA2)
        self.write_data(0x02)
        self.write_data(0x84)
        
        self.write_cmd(0xC1) 
        self.write_data(0xC5)

        self.write_cmd(0xC2) 
        self.write_data(0x0D)
        self.write_data(0x00)

        self.write_cmd(0xC3) 
        self.write_data(0x8D)
        self.write_data(0x2A)
        
        self.write_cmd(0xC4) 
        self.write_data(0x8D)
        self.write_data(0xEE)

        self.write_cmd(0xC5) # VCOM
        self.write_data(0x0A)

        self.write_cmd(0x36) # MX,MY,RGB MODE
        self.write_data(0x68) #0xEC
        
        self.write_cmd(0xE0) 
        self.write_data(0x12)
        self.write_data(0x1C)
        self.write_data(0x10)
        self.write_data(0x18)
        self.write_data(0x33)
        self.write_data(0x2C)
        self.write_data(0x25)
        self.write_data(0x28)
        self.write_data(0x28)
        self.write_data(0x27)
        self.write_data(0x2F)
        self.write_data(0x3C)
        self.write_data(0x00)
        self.write_data(0x03)
        self.write_data(0x03)
        self.write_data(0x10)
        
        self.write_cmd(0xE1) 
        self.write_data(0x12)
        self.write_data(0x1C)
        self.write_data(0x10)
        self.write_data(0x18)
        self.write_data(0x2D)
        self.write_data(0x28)
        self.write_data(0x23)
        self.write_data(0x28)
        self.write_data(0x28)
        self.write_data(0x26)
        self.write_data(0x2F)
        self.write_data(0x3B)
        self.write_data(0x00)
        self.write_data(0x03)
        self.write_data(0x03)
        self.write_data(0x10)
        
        self.write_cmd(0xF0) 
        self.write_data(0x01)
        
        self.write_cmd(0xF6) 
        self.write_data(0x00)

        self.write_cmd(0x3A) 
        self.write_data(0x05)
        
        #self.write_cmd(0x11)
        #time.sleep(0.12)
        self.write_cmd(0x29)
        time.sleep(0.05)
        
    def set_windows(self, start_x, start_y, end_x, end_y):
        """display the windows of start point and end point"""
        # because register 36h = 0x68
        start_x += 1
        end_x += 1
        start_y += 2
        end_y += 2
        # set the start point and end point of x
        self.write_cmd(0x2A) 
        self.write_data(start_x >> 8)  # x address start
        self.write_data(start_x & 0xff)
        self.write_data(end_x >> 8)  # x address end
        self.write_data(end_x & 0xff)
        # set the start point and end point of y
        self.write_cmd(0x2B) 
        self.write_data(start_y >> 8)  # y address start
        self.write_data(start_y & 0xff)
        self.write_data(end_y >> 8)  # y address end
        self.write_data(end_y & 0xff)
        
        self.write_cmd(0x2C)
        
    def img_show(self, img):
        img_w, img_h = img.size
        
        image = np.asarray(img)
        pixel = np.zeros((self.w, self.h, 2), dtype = np.uint8)
        pixel[..., [0]] = np.add(np.bitwise_and(image[..., [0]], 0xf8), np.right_shift(image[..., [1]], 5))
        
        pixel[..., [1]] = np.add(np.bitwise_and(np.left_shift(image[..., [1]], 3), 0xe0), np.right_shift(image[..., [2]], 3))       
        
        pixel = pixel.flatten().tolist()
        
        self.set_windows(0, 0, 127, 127) # 36H=0XEC:2, 3, 129, 130; 36H=0X68:1, 2, 128, 129 
#         wpi.digitalWrite(DC_PIN,wpi.HIGH)
        self.dc.on()
        for i in range(0, len(pixel), 4096):
            self.spi.writebytes(pixel[i:i+4096])
                
    def clear(self):
        self.set_windows(0, 0, 127, 127) # 36H=0XEC:2, 3, 129, 130; 36H=0X68:1, 2, 128, 129 
#         wpi.digitalWrite(DC_PIN,wpi.HIGH)
        self.dc.on()
        buf = [0xFF]*(self.w*self.h*2)
        for i in range(0, len(buf), 4096):
            self.spi.writebytes(buf[i:i+4096])


    