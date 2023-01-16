#ifndef INC_POWER_H_
#define INC_POWER_H_

#define DEV_GPIO_PORT GPIOA

#define PREAMP GPIO_PIN_7
#define FILTER GPIO_PIN_6
#define SERVO  GPIO_PIN_5

#define POWER_ON(device) \
{\
    DEV_GPIO_PORT->BSRR |= device; \
}

#define POWER_OFF(device) \
{\
    DEV_GPIO_PORT->BRR |= device; \
}

#endif /* INC_POWER_H_ */
