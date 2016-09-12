#include "main.h"

void USBH_UserProcess(USBH_HandleTypeDef* phost, uint8_t id) {

    UNUSED(phost);

    printf("USBH_UserProcess\n");

    switch (id) {

        case HOST_USER_SELECT_CONFIGURATION:
            USBH_DbgLog("HOST_USER_SELECT_CONFIGURATION\n");
            break;

        case HOST_USER_CLASS_ACTIVE:
            USBH_DbgLog("HOST_USER_CLASS_ACTIVE\n");
            break;

        case HOST_USER_CLASS_SELECTED:
            USBH_DbgLog("HOST_USER_CLASS_SELECTED\n");
            break;

        case HOST_USER_CONNECTION:
            USBH_DbgLog("HOST_USER_CONNECTION\n");
            break;

        case HOST_USER_DISCONNECTION:
            usb_device_ready= 0;
            USBH_DbgLog("HOST_USER_DISCONNECTION\n");
            break;

        case HOST_USER_UNRECOVERED_ERROR:
            USBH_DbgLog("HOST_USER_UNRECOVERED_ERROR\n");
            break;

        default:
            USBH_DbgLog("Default\n");
            break;

    }
}
