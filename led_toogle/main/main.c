//Librerias ANSI C
#include <stdio.h>

//Librerias ESP-IDF
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/projdefs.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "hal/gpio_types.h"
#include "portmacro.h"

#define LED GPIO_NUM_2
#define PIN_MASK_OUTPUT (1ULL << GPIO_NUM_2)

const char *TAG = "LED";

void gpio_init(void)
{
	gpio_config_t gpio_cfg_out = {
		.pin_bit_mask = PIN_MASK_OUTPUT,
		.mode = GPIO_MODE_OUTPUT,
		.pull_up_en = GPIO_PULLUP_DISABLE,
		.pull_down_en = GPIO_PULLDOWN_DISABLE,
		.intr_type = GPIO_INTR_DISABLE,
	};
	
	gpio_config(&gpio_cfg_out);
}

void app_main(void)
{
	gpio_init();
	
	uint32_t ledstate = 0;
	
	TickType_t xLastWakeTime;
	
	xLastWakeTime = xTaskGetTickCount();
	
    while(1)
    {
		ledstate = !ledstate;
		gpio_set_level(LED, ledstate);
		ESP_LOGI(TAG, "LED %s", ledstate ? "PRENDIDO" : "APAGADO");
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000));
	}

}
