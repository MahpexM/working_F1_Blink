// Мигание встроенным светодиодом на STM32

#include <stm32f10x.h>
#include <stdio.h>

void SystemInit(void) {}

void sleep(uint32_t x){
    // Ключевое слово volatile не позволяет компилятору выкинуть пустой цикл
    volatile uint32_t i = x;
    while(i--)
        ;
}

int main(void)
{
    // Включаем тактирование GPIOA, GPIOB и GPIOC (на всякий, но нужен только PC)
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPCEN;

    // Настраиваем PC13 как выход (2 МГц, push‑pull)
    GPIOC->CRH &= ~(GPIO_CRH_MODE13 | GPIO_CRH_CNF13);
    GPIOC->CRH |= GPIO_CRH_MODE13_0;        // 2 MHz output
    // CNF13 оставляем 0 → push‑pull

    while(1)
    {
        GPIOC->ODR ^= GPIO_ODR_ODR13;
        sleep(577067); // Экспериментальная подгонка под 1 с
    }

//    return 0;
}
