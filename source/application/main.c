#include "main.h"

static void SystemClock_Config(void);

int main(void) {

    // verify semihosting active
    DEBUG_PRINT("Starting Application\n");

    // enable cpu instruction line cache
    SCB_EnableICache();

    // enable cpu data line cache
    SCB_EnableDCache();

    // STM32F7xx HAL library initialization
    HAL_Init();

    // configure the system clock to 216 MHz
    SystemClock_Config();

    // configure trace function
    trace_config();

    // init audio device
    audio_init();

    // init usb host library, set host process signaling
    //  callback to USBH_UserProcess(); set 'driver id' to 0
    USBH_Init(&hUSBHost, USBH_UserProcess, 0);

    // init usb host process
    USBH_Start(&hUSBHost);

    // wait for connection from USB device
    while (1) {

        // usb host background task
        USBH_Process(&hUSBHost);

        // usb pipe init
        if (hUSBHost.gState == HOST_CHECK_CLASS && !usb_device_ready) {

            // attempt a connection on the control endpoint
            // note: max packet size 64 bytes for FS and 512 bytes for HS
            InPipe = USBH_AllocPipe(&hUSBHost, USB_PIPE_NUMBER);
            USBH_StatusTypeDef status = USBH_OpenPipe(&hUSBHost,
                                        InPipe,
                                        USB_PIPE_NUMBER,
                                        hUSBHost.device.address,
                                        hUSBHost.device.speed,
                                        USB_EP_TYPE_BULK,
                                        USBH_MAX_DATA_BUFFER);

            // continue connection attempt until successful
            if (status == USBH_OK) {
                usb_device_ready = 1;
            }

        }

        // only execute application after USB control pipe is configured
        if (usb_device_ready) {

            // USB device connected, begin application
            fmradio_process();

        }

    }

}

// the following clock settings are taken directly from ST CubeM7 reference code
/**
    @brief  System Clock Configuration
            The system Clock is configured as follow :
               System Clock source            = PLL (HSE)
               SYSCLK(Hz)                     = 216000000
               HCLK(Hz)                       = 216000000
               AHB Prescaler                  = 1
               APB1 Prescaler                 = 4
               APB2 Prescaler                 = 2
               HSE Frequency(Hz)              = 25000000
               PLL_M                          = 25
               PLL_N                          = 432
               PLL_P                          = 2
               PLL_Q                          = 9
               VDD(V)                         = 3.3
               Main regulator output voltage  = Scale1 mode
               Flash Latency(WS)              = 7
    @param  None
    @retval None
*/
static void SystemClock_Config(void) {
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInitStruct;
    HAL_StatusTypeDef ret = HAL_OK;

    /* Enable HSE Oscillator and activate PLL with HSE as source */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 25;
    RCC_OscInitStruct.PLL.PLLN = 432;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
    RCC_OscInitStruct.PLL.PLLQ = 9;

    ret = HAL_RCC_OscConfig(&RCC_OscInitStruct);

    if (ret != HAL_OK) {
        while (1) { ; }
    }

    /* Activate the OverDrive to reach the 216 MHz Frequency */
    ret = HAL_PWREx_EnableOverDrive();

    if (ret != HAL_OK) {
        while (1) { ; }
    }

    /* Select PLLSAI output as USB clock source */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_CLK48;
    PeriphClkInitStruct.Clk48ClockSelection = RCC_CLK48SOURCE_PLLSAIP;
    PeriphClkInitStruct.PLLSAI.PLLSAIN = 192;
    PeriphClkInitStruct.PLLSAI.PLLSAIQ = 4;
    PeriphClkInitStruct.PLLSAI.PLLSAIP = RCC_PLLSAIP_DIV4;
    ret = HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

    if (ret != HAL_OK) {
        while (1) { ; }
    }

    /* Select PLL as system clock source and configure the HCLK, PCLK1 and PCLK2 clocks dividers */
    RCC_ClkInitStruct.ClockType = (RCC_CLOCKTYPE_SYSCLK | RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2);
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

    ret = HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_7);

    if (ret != HAL_OK) {
        while (1) { ; }
    }
}

void BSP_AUDIO_OUT_ClockConfig(SAI_HandleTypeDef* hsai,
                            uint32_t AudioFreq,
                            void* Params)
{

    UNUSED(Params);
    UNUSED(hsai);

    RCC_PeriphCLKInitTypeDef RCC_ExCLKInitStruct;

    HAL_RCCEx_GetPeriphCLKConfig(&RCC_ExCLKInitStruct);

    /* Set the PLL configuration according to the audio frequency */
    if ((AudioFreq == AUDIO_FREQUENCY_11K) || (AudioFreq == AUDIO_FREQUENCY_22K) || (AudioFreq == AUDIO_FREQUENCY_44K)) {
        /* Configure PLLSAI prescalers */
        /*  PLLI2S_VCO: VCO_429M
            SAI_CLK(first level) = PLLI2S_VCO/PLLSAIQ = 429/2 = 214.5 Mhz
            SAI_CLK_x = SAI_CLK(first level)/PLLI2SDivQ = 214.5/19 = 11.289 Mhz */
        RCC_ExCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SAI2;
        RCC_ExCLKInitStruct.Sai2ClockSelection = RCC_SAI2CLKSOURCE_PLLI2S;
        RCC_ExCLKInitStruct.PLLI2S.PLLI2SP = 8;
        RCC_ExCLKInitStruct.PLLI2S.PLLI2SN = 429;
        RCC_ExCLKInitStruct.PLLI2S.PLLI2SQ = 2;
        RCC_ExCLKInitStruct.PLLI2SDivQ = 19;
        HAL_RCCEx_PeriphCLKConfig(&RCC_ExCLKInitStruct);

    } else { /* AUDIO_FREQUENCY_8K, AUDIO_FREQUENCY_16K, AUDIO_FREQUENCY_48K, AUDIO_FREQUENCY_96K */
        /*  SAI clock config
            PLLI2S_VCO: VCO_344M
            SAI_CLK(first level) = PLLI2S_VCO/PLLSAIQ = 344/7 = 49.142 Mhz
            SAI_CLK_x = SAI_CLK(first level)/PLLI2SDivQ = 49.142/1 = 49.142 Mhz */
        RCC_ExCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SAI2;
        RCC_ExCLKInitStruct.Sai2ClockSelection = RCC_SAI2CLKSOURCE_PLLI2S;
        RCC_ExCLKInitStruct.PLLI2S.PLLI2SN = 344;
        RCC_ExCLKInitStruct.PLLI2S.PLLI2SQ = 7;
        RCC_ExCLKInitStruct.PLLI2SDivQ = 1;
        HAL_RCCEx_PeriphCLKConfig(&RCC_ExCLKInitStruct);
    }
}
