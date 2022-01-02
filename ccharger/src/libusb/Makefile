

CC := gcc
CPPFLAGS 	:= -I./
LDFLAGS  	:= -L/usr/local/lib/
LIBS 		:= -libusb-1.0


setup.o: setup.c usb_device_handle.c usb_device_enum.c
	   $(CC) $(CPPFLAGS)  -g `pkg-config --libs --cflags libusb-1.0 --enable-debug-log ` -c -o $@ $<
usb_device_handle.o:  usb_device_handle.c usb_device_handle.h
	   $(CC) $(CPPFLAGS) -g `pkg-config --libs --cflags libusb-1.0` -c -o $@ $<

usb_device_enum.o: usb_device_enum.c usb_device_enum.h
	   $(CC) $(CPPFLAGS) -g `pkg-config --libs --cflags libusb-1.0` -c -o $@ $<
