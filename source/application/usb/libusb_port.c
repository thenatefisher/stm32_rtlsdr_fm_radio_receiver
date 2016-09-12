#include "libusb.h"
#include "main.h"

struct libusb_transfer* LIBUSB_CALL libusb_alloc_transfer(int iso_packets) { return 0; }
int LIBUSB_CALL libusb_submit_transfer(struct libusb_transfer* transfer) { return 0; }
int LIBUSB_CALL libusb_cancel_transfer(struct libusb_transfer* transfer) { return 0; }
void LIBUSB_CALL libusb_free_transfer(struct libusb_transfer* transfer) { }
int LIBUSB_CALL libusb_init(libusb_context** ctx) { return 0; }
void LIBUSB_CALL libusb_exit(libusb_context* ctx) {  }
void LIBUSB_CALL libusb_set_debug(libusb_context* ctx, int level) {  }
const struct libusb_version* LIBUSB_CALL libusb_get_version(void) { return 0; }
int LIBUSB_CALL libusb_has_capability(uint32_t capability) { return 0; }
const char* LIBUSB_CALL libusb_error_name(int errcode) { return 0; }
ssize_t LIBUSB_CALL libusb_get_device_list(libusb_context* ctx,
        libusb_device** *list) { return 0; }
void LIBUSB_CALL libusb_free_device_list(libusb_device** list,
        int unref_devices) {  }
libusb_device* LIBUSB_CALL libusb_ref_device(libusb_device* dev) { return 0; }
void LIBUSB_CALL libusb_unref_device(libusb_device* dev) { }
int LIBUSB_CALL libusb_get_configuration(libusb_device_handle* dev,
        int* config) { return 0; }
int LIBUSB_CALL libusb_get_device_descriptor(libusb_device* dev,
        struct libusb_device_descriptor* desc) { return 0; }
int LIBUSB_CALL libusb_get_active_config_descriptor(libusb_device* dev,
        struct libusb_config_descriptor** config) { return 0; }
int LIBUSB_CALL libusb_get_config_descriptor(libusb_device* dev,
        uint8_t config_index, struct libusb_config_descriptor** config) { return 0; }
int LIBUSB_CALL libusb_get_config_descriptor_by_value(libusb_device* dev,
        uint8_t bConfigurationValue, struct libusb_config_descriptor** config) { return 0; }
void LIBUSB_CALL libusb_free_config_descriptor(
    struct libusb_config_descriptor* config) { }
uint8_t LIBUSB_CALL libusb_get_bus_number(libusb_device* dev) { return 0; }
uint8_t LIBUSB_CALL libusb_get_device_address(libusb_device* dev) { return 0; }
int LIBUSB_CALL libusb_get_device_speed(libusb_device* dev) { return 0; }
int LIBUSB_CALL libusb_get_max_packet_size(libusb_device* dev,
        unsigned char endpoint) { return 0; }
int LIBUSB_CALL libusb_get_max_iso_packet_size(libusb_device* dev,
        unsigned char endpoint) { return 0; }

int libusb_control_transfer(libusb_device_handle* dev_handle,
                            uint8_t request_type, uint8_t bRequest, uint16_t wValue, uint16_t wIndex,
                            unsigned char* data, uint16_t wLength, unsigned int timeout) {

    hUSBHost.Control.setup.b.bmRequestType = request_type;
    hUSBHost.Control.setup.b.bRequest      = bRequest;
    hUSBHost.Control.setup.b.wValue.w      = wValue;
    hUSBHost.Control.setup.b.wIndex.w      = wIndex;
    hUSBHost.Control.setup.b.wLength.w     = wLength;

    int status;
    
    do {
        status = USBH_CtlReq(&hUSBHost, data, wLength);
    } while (status == 1);

    if (status != USBH_OK)  {
        hUSBHost.RequestState = CMD_SEND;
        return 0;

    } else {
        return wLength;
    }

}

int libusb_bulk_transfer(libusb_device_handle* dev_handle,
                         unsigned char endpoint, unsigned char* data, int length,
                         int* actual_length, unsigned int timeout) {

    USBH_BulkReceiveData(&hUSBHost,
                         data, // rx buffer
                         length, // data count to rx
                         InPipe); //in pipe

    return 1;

}

int LIBUSB_CALL libusb_open(libusb_device* dev, libusb_device_handle** handle) { return 0; }
void LIBUSB_CALL libusb_close(libusb_device_handle* dev_handle) { }
libusb_device* LIBUSB_CALL libusb_get_device(libusb_device_handle* dev_handle) { return 0; }
int LIBUSB_CALL libusb_set_configuration(libusb_device_handle* dev,
        int configuration) { return 0; }
int LIBUSB_CALL libusb_claim_interface(libusb_device_handle* dev,
                                       int interface_number) { return 0; }
int LIBUSB_CALL libusb_release_interface(libusb_device_handle* dev,
        int interface_number) { return 0; }
libusb_device_handle* LIBUSB_CALL libusb_open_device_with_vid_pid(
    libusb_context* ctx, uint16_t vendor_id, uint16_t product_id) { return 0; }
int LIBUSB_CALL libusb_set_interface_alt_setting(libusb_device_handle* dev,
        int interface_number, int alternate_setting) { return 0; }
int LIBUSB_CALL libusb_clear_halt(libusb_device_handle* dev,
                                  unsigned char endpoint) { return 0; }
int LIBUSB_CALL libusb_reset_device(libusb_device_handle* dev) { return 0; }
int LIBUSB_CALL libusb_kernel_driver_active(libusb_device_handle* dev,
        int interface_number) { return 0; }
int LIBUSB_CALL libusb_detach_kernel_driver(libusb_device_handle* dev,
        int interface_number) { return 0; }
int LIBUSB_CALL libusb_attach_kernel_driver(libusb_device_handle* dev,
        int interface_number) { return 0; }

int LIBUSB_CALL libusb_interrupt_transfer(libusb_device_handle* dev_handle,
        unsigned char endpoint, unsigned char* data, int length,
        int* actual_length, unsigned int timeout) { return 0; }

int LIBUSB_CALL libusb_get_string_descriptor_ascii(libusb_device_handle* dev,
        uint8_t desc_index, unsigned char* data, int length) { return 0; }

int LIBUSB_CALL libusb_try_lock_events(libusb_context* ctx) { return 0; }

void LIBUSB_CALL libusb_lock_events(libusb_context* ctx) { }

void LIBUSB_CALL libusb_unlock_events(libusb_context* ctx) { }

int LIBUSB_CALL libusb_handle_events_timeout(libusb_context* ctx, void* tv) { return 0; }

int LIBUSB_CALL libusb_event_handling_ok(libusb_context* ctx) { return 0; }

int LIBUSB_CALL libusb_event_handler_active(libusb_context* ctx) { return 0; }

void LIBUSB_CALL libusb_lock_event_waiters(libusb_context* ctx) { }

void LIBUSB_CALL libusb_unlock_event_waiters(libusb_context* ctx) { }

int LIBUSB_CALL libusb_handle_events(libusb_context* ctx) { return 0; }

int LIBUSB_CALL libusb_handle_events_completed(libusb_context* ctx, int* completed) { return 0; }

int LIBUSB_CALL libusb_pollfds_handle_timeouts(libusb_context* ctx) { return 0; }
