#include "main.h"

void USBH_UserProcess(USBH_HandleTypeDef* phost, uint8_t id) {
    
    printf("USBH_UserProcess\n");

    switch (id) {

        case HOST_USER_SELECT_CONFIGURATION:
            printf("USB: HOST_USER_SELECT_CONFIGURATION\n");
            break;

        case HOST_USER_CLASS_ACTIVE:
            printf("USB: HOST_USER_CLASS_ACTIVE\n");
            break;

        case HOST_USER_CLASS_SELECTED:
            printf("USB: HOST_USER_CLASS_SELECTED\n");
            break;

        case HOST_USER_CONNECTION:
            printf("USB: HOST_USER_CONNECTION\n");
            break;

        case HOST_USER_DISCONNECTION:
            isUSBConfigComplete = 0;
            printf("USB: HOST_USER_DISCONNECTION\n");
            break;

        case HOST_USER_UNRECOVERED_ERROR:
            printf("USB: HOST_USER_UNRECOVERED_ERROR\n");
            break;

        default:
            printf("USB: Default\n");
            break;

    }
}
