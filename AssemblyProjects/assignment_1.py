import sys
import math
import PIL.Image as pl

# print(sys.version)

def ASCII2Dec(ascii):
    return ord(ascii)

def dec2ASCII(dec):
    return chr(dec)

print("A in decimal: " + str(ASCII2Dec('A')))
print("B in decimal: " + str(ASCII2Dec('B')))
print("C in decimal: " + str(ASCII2Dec('C')))
print("65 in ASCII: " + str(dec2ASCII(65)))
print("66 in ASCII: " + str(dec2ASCII(66)))
print("67 in ASCII: " + str(dec2ASCII(67)))

def dec2Binary(dec):
    if(dec >= 1):
        return dec
    lar = int(math.log(dec, 2))
    result = ""
    while(dec > 0):
        if((dec - pow(2, lar)) >= 0):
            result += "1"
            dec -= (pow(2, lar))
        else:
            result += "0"
        lar -= 1
    return int(result)

def dec2Octal(dec):
    if(dec < 8):
        return dec
    q = int(dec / 8)
    r = dec % 8
    result = str(r)
    dec = q
    while(dec > 0):
        q = int(dec / 8)
        r = dec % 8
        result = str(r) + result
        dec = q
    return int(result)


print("197 in binary is: " + str(dec2Binary(197)))
print("197 in octal is: " + str(dec2Octal(197)))

def imagePixelsColor(path, numPixels):
    with pl.open(path) as img:
        pixels = []
        for x in range(numPixels):
            pixels.append(img.getpixel((x, 0)))
    return pixels

image_path = "C:/Users/bitto/Downloads/sad-tired-ant-sunset-orange.jpg"  
img = pl.open(image_path)
import webbrowser
webbrowser.open(image_path)
pixel_colors = imagePixelsColor(image_path, 10)
print(pixel_colors)
        

