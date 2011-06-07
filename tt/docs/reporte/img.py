import sys
import serial
import time

if len(sys.argv) > 1:
	img_name=sys.argv[1]
else:
	print "Requiere una imagen como parametro..."
	exit()

ser = serial.Serial('/dev/ttyUSB0',115200*4)
ser.write("U")
ser.write("\x59\x03\x02")
ser.close()
time.sleep(3)
ser = serial.Serial('/dev/ttyUSB0',115200*4)
ser.write("U")

try:
	img=open(img_name,'r')
	try:
		h_type = img.read(2)
		h_size = ord(img.read(1)) | (ord(img.read(1)) << 8) | 
			(ord(img.read(1)) << 16) | (ord(img.read(1)) << 24)
		h_reserverd1 = ord(img.read(1)) | (ord(img.read(1)) << 8)
		h_reserverd2 = ord(img.read(1)) | (ord(img.read(1)) << 8)
		h_offset = ord(img.read(1)) | (ord(img.read(1)) << 8) | 
			(ord(img.read(1)) << 16) | (ord(img.read(1)) << 24)
		print "\tHeader\nType: " + h_type
		print "Size: %d" % h_size
		print "Reserverd 1: %d" % h_reserverd1
		print "Reserverd 2: %d" % h_reserverd2
		print "offset: %d" % h_offset
		hi_size = ord(img.read(1)) | (ord(img.read(1)) << 8) | 
			(ord(img.read(1)) << 16) | (ord(img.read(1)) << 24)
		hi_width = ord(img.read(1)) | (ord(img.read(1)) << 8) | 
			(ord(img.read(1)) << 16) | (ord(img.read(1)) << 24)
		hi_height = ord(img.read(1)) | (ord(img.read(1)) << 8) | 
			(ord(img.read(1)) << 16) | (ord(img.read(1)) << 24)
		hi_planes = ord(img.read(1)) | (ord(img.read(1)) << 8)
		hi_bits = ord(img.read(1)) | (ord(img.read(1)) << 8)
		hi_compression = ord(img.read(1)) | (ord(img.read(1)) << 8) | 
			(ord(img.read(1)) << 16) | (ord(img.read(1)) << 24)
		hi_imagesize = ord(img.read(1)) | (ord(img.read(1)) << 8) | 
			(ord(img.read(1)) << 16) | (ord(img.read(1)) << 24)
		hi_xresolution = ord(img.read(1)) | (ord(img.read(1)) << 8) | 
			(ord(img.read(1)) << 16) | (ord(img.read(1)) << 24)
		hi_yresolution = ord(img.read(1)) | (ord(img.read(1)) << 8) | 
			(ord(img.read(1)) << 16) | (ord(img.read(1)) << 24)
		hi_ncolours = ord(img.read(1)) | (ord(img.read(1)) << 8) | 
			(ord(img.read(1)) << 16) | (ord(img.read(1)) << 24)
		hi_importantcolours = ord(img.read(1)) | 
			(ord(img.read(1)) << 8) | (ord(img.read(1)) << 16) | 
			(ord(img.read(1)) << 24)
		print "\tInformation\nSize: %d" % hi_size
		print "Width: %d" % hi_width
		print "Height: %d" % hi_height
		print "Planes: %d" % hi_planes	
		print "Bits: %d" % hi_bits
		print "Compression: %d" % hi_compression
		print "Image Size: %d" % hi_imagesize	
		print "X Resolution: %d" % hi_xresolution
		print "Y Resolution: %d" % hi_yresolution
		print "N Colours: %d" % hi_ncolours	
		print "Important Colours: %d" % hi_importantcolours
	
		width_1 = (0xff00 & hi_width) >> 8
		width_2 = 0xff & hi_width
		height_1 = (0xff00 & hi_height) >> 8
		height_2 = 0xff & hi_height
		img_py = "I" + chr(0x00) + chr(0x00) + chr(0x00) + chr(0x00) + 
			chr(width_1) + chr(width_2) + chr(height_1) + 
			chr(height_2)
		img_py += "\x08"
		
		img.seek(h_offset)
		mem = []
		cnt = 0
		tmp = 4 - (hi_width % 4)
		for i  in range(hi_width * hi_height):
 			cnt += 1
			if cnt == hi_width:
				img.read(tmp)
				cnt = 0
                        mem.append(chr(ord(img.read(1))))
		mem.reverse()
		for i in mem:
			img_py += i
		ser.write(img_py)
	finally:
		img.close()
		ser.close()
except IOError:
	print ("IO Error");
	ser.close()
	exit()
