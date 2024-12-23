#ifndef GPIO_H
#define GPIO_H

//#include <stdint.h>
//#include "addresses.h"

typedef enum {
	GPIO_MODE_INPUT = 0,
	GPIO_MODE_OUTPUT = 1,
	GPIO_MODE_ALTERNATE = 2,
	GPIO_MODE_ANALOG = 3
} GPIO_MODE;

//typedef struct {
//	GPIOType* port;
//	GPIO_MODE moder;
//	uint32_t pin;
//} GPIO_DATA;
//
//
//void enable_gpio_data(GPIO_DATA gpio_data);
//void write_gpio_data(GPIO_DATA gpio_data, int value);
//int read_gpio_data(GPIO_DATA gpio_data);
//int read_button(int button);
//void seven_segment_display(int num);
//void turn_on_LED_RED(void);
//void turn_on_LED_BLUE(void);
//void turn_on_LED_GREEN(void);
//void turn_off_LEDs(void);
//void GPIO_initialization(void);


//#ifndef GPIO_H
//#define GPIO_H

#include <stdint.h>



typedef struct {
	uint32_t turn_counter;
	uint32_t timer;
	uint8_t current_display;
	uint8_t turn_indicator;
	uint8_t button_indicator;
} Display;

extern Display display;
void setup_gpio();

#endif

