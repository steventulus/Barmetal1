#include <stdint.h>

#define RCC_APB2ENR          (*(volatile uint32_t *)0x40021018)
#define RCC_APB2ENR_IOPCEN   (1 << 4)

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

void delay(uint32_t time) {
    for (uint32_t i = 0; i < time; i++) {
        for (volatile uint32_t j = 0; j < 2000; j++);  
    }
}

int main(void) {
    RCC_APB2ENR |= RCC_APB2ENR_IOPCEN;

    GPIOC->CRH &= ~(0xF << 20);   
    GPIOC->CRH |=  (0x2 << 20);  

    
    while (1) {
        
        GPIOC->BSRR = (1 << 13) << 16;  
        delay(90);

        
        GPIOC->BSRR = (1 << 13);       
        delay(100);
    }
}