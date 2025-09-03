#include <stdint.h>

// RCC register
#define RCC_APB2ENR          (*(volatile uint32_t *)0x40021018)
#define RCC_APB2ENR_IOPCEN   (1 << 4)

// GPIOC register map
typedef struct {
    volatile uint32_t CRL;
    volatile uint32_t CRH;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t BRR;
    volatile uint32_t LCKR;
} GPIO_TypeDef;

#define GPIOC ((GPIO_TypeDef *)0x40011000)

// Simple delay (volatile to prevent compiler optimization)
void delay(uint32_t time) {
    for (uint32_t i = 0; i < time; i++) {
        for (volatile uint32_t j = 0; j < 2000; j++);  
    }
}

int main(void) {
    // 1. Enable GPIOC clock
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

    // 2. Configure PC13 as output push-pull, 2 MHz
    GPIOC->CRH &= ~(0xF << 20);   // clear bits for PC13
    GPIOC->CRH |=  (0x2 << 20);   // MODE13 = 10 (output 2 MHz), CNF13 = 00 (push-pull)

    // 3. Blink loop
    while (1) {
        // LED ON (active low → reset bit)
        GPIOC->BSRR = (1 << 13) << 16;  
        delay(500);

        // LED OFF (set bit)
        GPIOC->BSRR = (1 << 13);       
        delay(50);
    }
}