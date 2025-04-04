
#include <stdint.h>
#include "tm4c123gh6pm.h"

void DisableInterrupts(void);
void EnableInterrupts(void);
void WaitForInterrupt(void);
void GPIOPortF_Init(void);
void GPIOPortF_Handler(void);
void delay(int);


void GPIOPortF_Init(void)
{
SYSCTL_RCGC2_R |= 0x00000020;       /* 1) activate clock for Port F */
    GPIO_PORTF_LOCK_R = 0x4C4F434B; /* 2) unlock GPIO Port F */
    GPIO_PORTF_CR_R = 0x1F;         /* allow changes to PF4-0 */
    GPIO_PORTF_AMSEL_R = 0x00;      /* 3) disable analog on PF */
    GPIO_PORTF_PCTL_R = 0x00000000; /* 4) PCTL GPIO on PF4-0 */
    GPIO_PORTF_DIR_R = 0x0E;        /* 5) PF4,PF0 in, PF3-1 out */
    GPIO_PORTF_AFSEL_R = 0x00;      /* 6) disable alt funct on PF7-0 */
    GPIO_PORTF_PUR_R = 0x11;        /* enable pull-up on PF0 and PF4 */
    GPIO_PORTF_DEN_R = 0x1F;        /* 7) enable digital I/O on PF4-0 */
    GPIO_PORTF_IS_R &= ~0x11;       /*  PF4,PF0 is edge-sensitive */
    GPIO_PORTF_IBE_R &= ~0x11;      /*  PF4,PF0 is not both edges */
    GPIO_PORTF_IEV_R &= ~0x11;      /*  PF4,PF0 falling edge event */
    GPIO_PORTF_ICR_R = 0x11;        /*  Clear flag4,flag0 */
    GPIO_PORTF_IM_R |= 0x11;        /*  arm interrupt on PF4,PF0 */
    NVIC_PRI7_R = (NVIC_PRI7_R & 0xFF1FFFFF) | 0x00A00000; /*  priority 5 */
    NVIC_EN0_R = 0x40000000;        /*  Enable interrupt 30 in NVIC */
    EnableInterrupts();             /* Enable global Interrupt flag (I) */
}

void GPIOPortF_Handler(void)
{
    volatile int readback,i;
    if ((GPIO_PORTF_MIS_R & 0x10))      /* PF4 - SW1 - blink Green led thrice*/
    {
        GPIO_PORTF_ICR_R = 0x10;
        GPIO_PORTF_DATA_R = 0x00;
        for(i=0;i<6;i++)
        {
            GPIO_PORTF_DATA_R ^= (1<<3);    /* toggle Green LED */
            delay(500000);
        }
        GPIO_PORTF_DATA_R = 0x00;
        readback = GPIO_PORTF_ICR_R;    /* a read to force clearing of interrupt flag */
        readback = readback;
    }
    if ((GPIO_PORTF_MIS_R & 0x01))  /* PF1 - SW2 - blink Blue Led thrice */
    {
        GPIO_PORTF_ICR_R = 0x01;
        GPIO_PORTF_DATA_R = 0x00;
        for(i=0;i<6;i++)
        {
            GPIO_PORTF_DATA_R ^= (1<<2);    /* toggle Blue LED */
            delay(500000);
        }
        GPIO_PORTF_DATA_R = 0x00;
        readback = GPIO_PORTF_ICR_R;    /* a read to force clearing of interrupt flag */
        readback = readback;
    }
    else{}
}

int main(void)
{
    GPIOPortF_Init();               /* initialize GPIO Port F interrupt */
    while(1) {
        GPIO_PORTF_DATA_R ^= (1<<1);
        delay(500000);
    }
}

void delay(int n){
    int i;
    for(i=0;i<n;i++);
}


/*********** DisableInterrupts ***************
*
* disable interrupts
*
* inputs:  none
* outputs: none
*/
void DisableInterrupts(void)
{
    __asm ("    CPSID  I\n");
}
/*********** EnableInterrupts ***************
*
* emable interrupts
*
* inputs:  none
* outputs: none
*/
void EnableInterrupts(void)
{
    __asm  ("    CPSIE  I\n");
}
/*********** WaitForInterrupt ************************
*
* go to low power mode while waiting for the next interrupt
*
* inputs:  none
* outputs: none
*/
void WaitForInterrupt(void)
{
    __asm  ("    WFI\n");
}
