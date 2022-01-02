#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


#include <libusb-1.0/libusb.h>


#include "usb_device_enum.h"


static void loop_list_devices(libusb_device **devs, libusb_device **devp);



void get_device(libusb_device **devp)
{
	libusb_device **devs;
	int r;
	ssize_t cnt;


	// get a list of devices
	if (cnt = libusb_get_device_list(NULL, &devs) < 0) {
		fprintf(stderr, "getting device list");
		libusb_exit(NULL);
	}

	loop_list_devices(devs, devp);
	libusb_free_device_list(devs, 1);

}


static void loop_list_devices(libusb_device **devs, libusb_device **devpp)
{
	struct libusb_device_descriptor desc;
	ssize_t ret;
	int i = 0;

	
	// loop devices list
	while ((*devpp = devs[i++]) != NULL) {
	puts("looping");	

		if (ret = libusb_get_device_descriptor(*devpp, &desc) < 0) {
			fprintf(stderr, "failed to get device descriptor");
			return;
		}



		if (desc.idVendor == 0x1a86) {
			puts("found");
			return ;
		}

	}
	puts("null");

	


}





#define BULK_EP_OUT     0x82    
#define BULK_EP_IN      0x08    

int interface_ref = 0;    
int alt_interface,interface_number;   


struct libusb_endpoint_descriptor* active_config(struct libusb_device *dev,struct libusb_device_handle *handle)    
{    
    struct libusb_device_handle *hDevice_req;    
    struct libusb_config_descriptor *config;    
    struct libusb_endpoint_descriptor *endpoint;    
    int altsetting_index,interface_index=0,ret_active;    
    int i,ret_print;    

    hDevice_req = handle;    

    ret_active = libusb_get_active_config_descriptor(dev,&config);    

    for(interface_index=0;interface_index<config->bNumInterfaces;interface_index++)    
    {    

        const struct libusb_interface *iface = &config->interface[interface_index];    

        for(altsetting_index=0;altsetting_index<iface->num_altsetting;altsetting_index++)   {    
            const struct libusb_interface_descriptor *altsetting = &iface->altsetting[altsetting_index];    
            int endpoint_index;    

            for(endpoint_index=0;endpoint_index<altsetting->bNumEndpoints;endpoint_index++)    {    
                const struct libusb_endpoint_descriptor *ep = &altsetting->endpoint[endpoint_index];    
                endpoint = ep;      
                alt_interface = altsetting->bAlternateSetting;    
                interface_number = altsetting->bInterfaceNumber;    
            }    

            printf("\nEndPoint Descriptors: ");    
            printf("\n\tSize of EndPoint Descriptor : %d",endpoint->bLength);    
            printf("\n\tType of Descriptor : %d",endpoint->bDescriptorType);    
            printf("\n\tEndpoint Address : 0x0%x",endpoint->bEndpointAddress);    
            printf("\n\tMaximum Packet Size: %x",endpoint->wMaxPacketSize);    
            printf("\n\tAttributes applied to Endpoint: %d",endpoint->bmAttributes);    
            printf("\n\tInterval for Polling for data Tranfer : %d\n",endpoint->bInterval);    
        }    
    }    
    libusb_free_config_descriptor(NULL);    
    return endpoint;    
}    




