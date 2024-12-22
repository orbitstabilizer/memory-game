#include "gpio.h"

GPIO_DATA seven_segment_pins[] = {
	{GPIOA, GPIO_MODE_OUTPUT, 3},
	{GPIOA, GPIO_MODE_OUTPUT, 2},
	{GPIOC, GPIO_MODE_OUTPUT, 3},
	{GPIOB, GPIO_MODE_OUTPUT, 0},
	{GPIOC, GPIO_MODE_OUTPUT, 1},
	{GPIOC, GPIO_MODE_OUTPUT, 0},
	{GPIOB, GPIO_MODE_OUTPUT, 2},
	{GPIOB, GPIO_MODE_OUTPUT, 6},
};

GPIO_DATA input_pins[] = {
	{GPIOG, GPIO_MODE_INPUT, 0},
	{GPIOG, GPIO_MODE_INPUT, 1},
};

GPIO_DATA led_pins[] = {
	{GPIOA, GPIO_MODE_OUTPUT, 9},
	{GPIOB, GPIO_MODE_OUTPUT, 7},
	{GPIOC, GPIO_MODE_OUTPUT, 7},
};

void enable_gpio_data(GPIO_DATA gpio_data) {
	gpio_data.port->MODER &= ~(0b11 << (gpio_data.pin * 2));
	gpio_data.port->MODER |= (gpio_data.moder << (gpio_data.pin * 2));
}

void write_gpio_data(GPIO_DATA gpio_data, int value) {
	gpio_data.port->ODR &= ~(0b1 << (gpio_data.pin));
	gpio_data.port->ODR |= (value << (gpio_data.pin));
}

int read_gpio_data(GPIO_DATA gpio_data) {
	return (gpio_data.port->IDR >> gpio_data.pin) & 1;
}


int read_button(int button) {
    return read_gpio_data(input_pins[button]);
}

void seven_segment_display(int num) {

	int patterns[10] = {
		0b0111111, // 0
		0b0000110, // 1
		0b1011011, // 2
		0b1001111, // 3
		0b1100110, // 4
		0b1101101, // 5
		0b1111101, // 6
		0b0000111, // 7
		0b1111111, // 8
		0b1101111  // 9
	};


	num = num % 10;

	int pattern = patterns[num];
	for (int i = 0; i < 7; i++) {
		int segment_on = (pattern >> i) & 1;
		write_gpio_data(seven_segment_pins[i], segment_on ^ 1);
	}
}

void turn_on_LED_RED(void) {
    write_gpio_data(led_pins[0], 1);
    write_gpio_data(led_pins[1], 0);
    write_gpio_data(led_pins[2], 0);
}

void turn_on_LED_BLUE(void) {
    write_gpio_data(led_pins[0], 0);
    write_gpio_data(led_pins[1], 1);
    write_gpio_data(led_pins[2], 0);
}

void turn_on_LED_GREEN(void) {
    write_gpio_data(led_pins[0], 0);
    write_gpio_data(led_pins[1], 0);
    write_gpio_data(led_pins[2], 1);
}

void turn_off_LEDs(void) {
    write_gpio_data(led_pins[0], 0);
    write_gpio_data(led_pins[1], 0);
    write_gpio_data(led_pins[2], 0);
}


void GPIO_initialization(void) {
    RCC_AHB2ENR|= 0b1111111;

    for (int i = 0; i < sizeof(seven_segment_pins) / sizeof(GPIO_DATA); i++) {
    	enable_gpio_data(seven_segment_pins[i]);
    }
	for (int i = 0; i < sizeof(input_pins) / sizeof(GPIO_DATA); i++) {
		enable_gpio_data(input_pins[i]);
	}
	for (int i = 0; i < sizeof(led_pins) / sizeof(GPIO_DATA); i++) {
		enable_gpio_data(led_pins[i]);
	}
}
