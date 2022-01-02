#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "usb_device_handle.h"








ssize_t open_device(struct libusb_device_handle *dhp, struct libusb_device_descriptor *ddp) 
{
	ssize_t ret = 0;
	uint32_t if_num, rc;
	struct libusb_device_handle *dh =NULL;
	// Fill vendor id and product id
	// Bus 001 Device 006: ID 1a86:7523 QinHeng Electronics HL-340 USB-Serial adapter
	#define VENDOR_ID      0x1a86   
	#define PRODUCT_ID     0x7523
	ddp->idVendor 	= (uint16_t ) 0x1a86;  //	uint16_t
	ddp->idProduct	= 0x7523;

	printf("vendor :%hu product :%hu\n", VENDOR_ID, PRODUCT_ID); 
	dh = libusb_open_device_with_vid_pid(NULL, VENDOR_ID, PRODUCT_ID);
	if (!dhp) {
		perror("error finding device");
		exit(-1);
	}


	for (if_num = 0; if_num < 35; if_num++) {
		if (libusb_kernel_driver_active(dh, if_num)) {
			libusb_detach_kernel_driver(dh, if_num);
			fprintf(stdout,"detach kernrl driver\n");
			fprintf(stdout, "interface number is %d\n",if_num);
		}
		if (rc = libusb_claim_interface(dh, if_num) < 0) {
			fprintf(stderr, "Error claiming interface: %s\n",
			libusb_error_name(rc));
			exit(-1);
		}
	}

}





void get_usb_speed(struct libusb_device *p)
{
	enum libusb_speed els;

	uint32_t speed = libusb_get_device_speed(p);

	switch (speed) {
		case LIBUSB_SPEED_UNKNOWN:
			printf("unknown speed\n");
			break;
			
		case LIBUSB_SPEED_LOW:
			printf("low speed\n");
			break;
		case LIBUSB_SPEED_FULL:
			printf("full speed\n");
			break;
	}
			

	printf("speed number : %d\n", speed);
}



ssize_t setup_packet(struct libusb_control_setup *p)
{

	p->bmRequestType 	= LIBUSB_RECIPIENT_DEVICE; // uint8_t
	p->bRequest 		= LIBUSB_REQUEST_TYPE_STANDARD;
	p->wValue		= 0; // uint16_t
	p->wIndex		= 0;
	p->wLength		= 0;
	return 0;
}
