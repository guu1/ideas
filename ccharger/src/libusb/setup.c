#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
 #include <unistd.h>


#include <libusb-1.0/libusb.h>


#include "usb_device_handle.h"
#include "usb_device_enum.h"







void print_device();





void main(void)
{
	//
	// device descriptor
	struct libusb_device_descriptor *sldd = malloc(sizeof(struct libusb_device_descriptor));
	//
	// config descriptor
	struct libusb_config_descriptor	*slcd  = malloc(sizeof(struct libusb_config_descriptor)); //
	//
	struct libusb_control_setup	*slcs = malloc(sizeof(struct libusb_control_setup)); // control setup
	//
	// endpoint descriptor
	struct libusb_endpoint_descriptor *sled= malloc(sizeof(struct libusb_control_setup));
	//
	// interface descriptor
    	struct libusb_interface_descriptor *slid;
	//
	//
	// the device handle
	struct libusb_device_handle	*sldh = NULL;	
	// the device 
	struct libusb_device		*dev  = NULL;



	ssize_t ret;

	//
	//
	// Initialize the lib
	if ((ret = libusb_init(NULL)) < 0) {
		fprintf(stderr, "failed to init lib %s", libusb_error_name(ret));
		exit(-1);
	}

	//
	// 
	// max level debug
#define DEBUG
	    #ifdef DEBUG
    //LIBUSB_DEBUG
    putenv( "LIBUSB_DEBUG=4" );
    #endif
	libusb_set_option(NULL, 4);



	//
	//
	// get our device 
	get_device(&dev);
	if (dev == NULL) {
		puts("no dev");
		goto cleanup;
	}


	//
	//
	// get the device descriptor
	if ((ret = libusb_get_device_descriptor(dev, sldd)) < 0) {
		fprintf(stderr, "failed to get device descriptor %s", libusb_error_name(ret));
		goto cleanup;
	}

	printf("Device descriptor\n");
	printf("bLenght : %hhu\n", sldd->bLength);
	printf("bDescriptorType : %hhu\n", sldd->bDescriptorType);
	printf("bcdUSB : %hhu\n", sldd->bcdUSB);
	printf("bDeviceClass : %hhu\n", sldd->bDeviceClass);
	printf("bDeviceSubClass : %hhu\n", sldd->bDeviceSubClass);
	printf("bDeviceProtocol : %hhu\n", sldd->bDeviceProtocol);
	printf("bMaxPacketSize0 : %hhu\n", sldd->bMaxPacketSize0);
	printf("Vendorid and Productid : %x, %x\n", sldd->idVendor, sldd->idProduct);



	//
	//
	// get the config descriptor
	//libusb_get_config_descriptor (libusb_device *dev, uint8_t config_index, struct libusb_config_descriptor **config)
	if ((ret = libusb_get_config_descriptor(dev, 0 , &slcd)) < 0) {
	//if (ret = libusb_get_active_config_descriptor(dev, &slcd) < 0) {
		fprintf(stderr, "failed to get config descriptor");
		libusb_error_name(ret);
		goto cleanup;
	}
	uint8_t index = slcd->iConfiguration;

	printf("Config descriptor\n");
	printf("bLenght : %hhu\n", slcd->bLength);
	printf("bDescriptorType : %hhu\n", slcd->bDescriptorType);
	printf("wTotaLength : %hu\n", slcd->bNumInterfaces);
	printf("bConfigurationValue : %hhu\n", slcd->bConfigurationValue);
	printf("iConfiguration : %hhu\n", slcd->iConfiguration);
	printf("bmAttributes : %hhu\n", slcd->bmAttributes);
	printf("MaxPower : %hhu\n", slcd->MaxPower);



	//libusb_get_ss_endpoint_companion_descriptor(NULL, 
	
	sled = active_config(dev, sldh);

	print_device(dev, sldd);


	//
	//
	// open the device 
	if ((ret = libusb_open(dev, &sldh)) < 0) {
		fprintf(stderr ,"failed to open %s\n", libusb_error_name(ret));
		goto cleanup;
	}

	//libusb_get_device(sldh);
	//slcd->bConfigurationValue = 1230;
	// libusb_get_config_descriptor_by_value (libusb_device *dev, uint8_t bConfigurationValue, struct libusb_config_descriptor **config)
	//if (ret = libusb_get_config_descriptor_by_value(dev, slcd->bConfigurationValue, &slcd) < 0) {	
	////if (ret = libusb_get_configuration(sldh, ((int *)&slcd->bConfigurationValue)) < 0) {
	//	fprintf(stderr ,"failed to get configuration %s\n", libusb_error_name(ret));
	//	goto cleanup;
	//}



	printf("\nconfig value %hu\n", slcd->bConfigurationValue); 


		

//	if (slcd->bConfigurationValue == 0);
//		perror("




	uint32_t if_num,rc;



	//for (if_num = 0; if_num < 30; if_num++) {
	//	puts("loop");
	//	if (libusb_kernel_driver_active(sldh, if_num)) {
	//		puts("found driver active");
	//		ret = libusb_detach_kernel_driver(sldh, if_num);
	//		//ret = libusb_set_auto_detach_kernel_driver(sldh, 1);
	//		fprintf(stdout,"detach kernrl driver %s\n", libusb_error_name(ret));
	//		fprintf(stdout, "interface number is %d\n",if_num);
	//		//if ((ret = libusb_set_configuration(sldh, slcd->bConfigurationValue)) < 0) {
	//		//	fprintf(stderr, "failed setting configuration: %s\n", libusb_error_name(ret));
	//		//	goto cleanup;
	//		//}
	//	}
	//	//libusb_set_auto_detach_kernel_driver(sldh, if_num);
	//	ret = 32;
	//	int rete;
	//	if ((rete = libusb_claim_interface(sldh, if_num)) < 0) {
	//		printf("%d\n", rete);
	//		fprintf(stderr, "Error claiming interface: %s\n", libusb_error_name(rete));
	//		goto cleanup;
	//	}
	//}
		
		if ((ret = libusb_claim_interface(sldh, 0)) < 0) {
			printf("ret : %ld\n", ret);
			fprintf(stderr, "Error claiming interface: %s\n", libusb_error_name(ret));
			goto cleanup;
		}
	puts("claimed");










	

	unsigned char buffer[1024];
	//libusb_fill_control_setup(buffer, slcs->bmRequestType,
		//slcs->bRequest, slcs->wValue, slcs->wIndex, slcs->wLength);	
	//printf("buffer slcs: %s\n", buffer);
	//setup_packet(slcs);



	
	char *data ="G28"; // autohome
	
	printf("data : %s\n", data);
	//slt->timeout 	= 100;
	//// slt->libusb_device_handle = dev;
	//slt->flags 	= 0;

	////slt->endpoint 	= 0;
	////slt->type 	= slcs->bmRequestType;
	//// slt->status	= 
	//slt->length = 10;
	//// slt->actual_length
	//slt->user_data 	= data;
	//libusb_submit_transfer(slt);


	strncpy(buffer, data, 1024);

	printf("buffer %s\n", buffer);

	// static unsigned char* libusb_control_transfer_get_data 
	
	struct libusb_transfer *slt = libusb_alloc_transfer(32);
	slt->flags |= LIBUSB_TRANSFER_FREE_TRANSFER;
	printf("slt struct :\n");
	printf("slt->flags %hhu\nslt->type : %c\nslt->legth : %d\n",slt->flags, slt->type, slt->length);

	//libusb_fill_control_setup(buffer, slcs->bmRequestType, slcs->bRequest, slcs->wValue, slcs->wIndex, slcs->wLength);
	//libusb_fill_control_transfer(slt, sldh, buffer, NULL, NULL, 10); 	
	printf("buffer %s\n", buffer);
	//libusb_fill_control_setup(

	libusb_fill_bulk_transfer(slt, sldh, 0x02, buffer, 1024,NULL, NULL,9000);



	puts("sending");





// teste code
ssize_t cnt;    
    int e = 0,config2;    
    int i = 0;    
    char str1[64], str2[64];    
    char found = 0;   


//   Communicate     

    char *my_string, *my_string1;    
    int transferred = 0;    
    int received = 0;    
    int length = 0;    
int nbytes = 10;
    my_string = (char *)malloc(nbytes + 1);    
    my_string1 = (char *)malloc(nbytes + 1);    

    memset(my_string,'\0',64);    
    memset(my_string1,'\0',64);    

    strcpy(my_string,"G28");    
    length = strlen(my_string);    

    printf("\nTo be sent : %s",my_string);    

#define BAUDRATE 115200
#define BULK_EP_OUT     0x82    
#define BULK_EP_IN      0x02   

    e = libusb_bulk_transfer(sldh,BULK_EP_IN,my_string,length,&transferred,0);    
    if(e == 0 && transferred == length)    
    {    
        printf("\nWrite successful!");    
        printf("\nSent %d bytes with string: %s\n", transferred, my_string);    
    }    
    else    
        printf("\nError in write! e = %d and transferred = %d\n",e,transferred);    

    sleep(3);    
    i = 0;    

    for(i = 0; i < length; i++)    {    
        e = libusb_bulk_transfer(sldh,BULK_EP_OUT,my_string1,32,&received,0);  //64 : Max Packet Lenght    
        if (e == 0) {    
            printf("\nReceived: ");    
            printf("%c",my_string1[i]);    //will read a string from lcp2148
            sleep(1);    
        } else    
        {    
            printf("\nError in read! e = %d and received = %d\n",e,received);    
	    goto cleanup;
        }    
   }  






















	
	//if ((ret = libusb_submit_transfer(slt)) < 0) {
	//		fprintf(stderr, "error submitting transfer: %s\n", libusb_error_name(ret));
	//		goto cleanup;
	//}

	//if ((ret = libusb_bulk_transfer(sldh, 0x02, buffer,1024,NULL,10)) < 0) {
			//fprintf(stderr, "error submitting transfer bulk: %s\n", libusb_error_name(ret));
			//goto cleanup;
	//}


	printf("status of transfer %u ret : %ld\n", slt->status, ret);




	goto cleanup;


	cleanup:
		puts("cleaning");
		if (slt) 
			//libusb_free_transfer(slt);
		if (slcd)
			libusb_free_config_descriptor(slcd);
		if (sldh) {
			libusb_release_interface(sldh, if_num);
			libusb_close(sldh);
		}
		libusb_exit(NULL);
		exit(-1);
}





void print_device(libusb_device *devp, struct libusb_device_descriptor *p) 
{
	printf("%04x:%04x (bus %d, device %d)",
		p->idVendor, p->idProduct,
		libusb_get_bus_number(devp), libusb_get_device_address(devp));
}


