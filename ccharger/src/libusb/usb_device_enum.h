
void get_device(libusb_device **devp);
struct libusb_endpoint_descriptor* active_config(struct libusb_device *dev,struct libusb_device_handle *handle);
