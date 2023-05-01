#include "stm32f10x.h"

void SysInit(void)
{
    /* Set HSION bit */
    /* Internal Clock Enable */
    RCC->CR |= (uint32_t)0x00000001; //HSION

    /* Reset SW, HPRE, PPRE1, PPRE2, ADCPRE and MCO bits */
    RCC->CFGR &= (uint32_t)0xF0FF0000;

    /* Reset HSEON, CSSON and PLLON bits */
    RCC->CR &= (uint32_t)0xFEF6FFFF;

    /* Reset HSEBYP bit */
    RCC->CR &= (uint32_t)0xFFFBFFFF;

    /* Reset PLLSRC, PLLXTPRE, PLLMUL and USBPRE/OTGFSPRE bits */
    RCC->CFGR &= (uint32_t)0xFF80FFFF;

    /* Reset PLL2ON and PLL3ON bits */
    RCC->CR &= (uint32_t)0xEBFFFFFF;

    /* Disable all interrupts and clear pending bits  */
    RCC->CIR = 0x00FF0000;

    /* Reset CFGR2 register */
    RCC->CFGR2 = 0x00000000;
}

void SetSysClock(void)
{
    volatile uint32_t StartUpCounter = 0, HSEStatus = 0;
    /* SYSCLK, HCLK, PCLK2 and PCLK1 configuration ---------------------------*/
    /* Enable HSE */
    RCC->CR |= ((uint32_t)RCC_CR_HSEON);
    /* Wait till HSE is ready and if Time out is reached exit */
    do
    {
        HSEStatus = RCC->CR & RCC_CR_HSERDY;
        StartUpCounter++;
    } while ((HSEStatus == 0) && (StartUpCounter != HSE_STARTUP_TIMEOUT));

    if ((RCC->CR & RCC_CR_HSERDY) != RESET)
    {
        HSEStatus = (uint32_t)0x01;
    }
    else
    {
        HSEStatus = (uint32_t)0x00;
    }

    if (HSEStatus == (uint32_t)0x01)
    {
        /* Enable Prefetch Buffer */
        FLASH->ACR |= FLASH_ACR_PRFTBE;
        /* Flash 0 wait state */
        FLASH->ACR &= (uint32_t)((uint32_t)~FLASH_ACR_LATENCY);
        FLASH->ACR |= (uint32_t)FLASH_ACR_LATENCY_0;

        //@TODO - Set the clock PCLK2 = 16 MHz/////////////////////////////////////////////////////////////////////////////////////////////////////////
        /* HCLK = SYSCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_HPRE_DIV1;
        /* PCLK2 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE2_DIV2; // 이부분을 통해서 32MHz인 system clock을 16MHz로 바꾼다.
                                                    /* PCLK1 = HCLK */
        RCC->CFGR |= (uint32_t)RCC_CFGR_PPRE1_DIV1;

        //@TODO - Set the clock SYSCLK = 32 MHz   ,           : 25 / 5 * 8 / 5 * 4 ////////////////////////////////////////////////////////////////////
        /* Configure PLLs ------------------------------------------------------*/
        RCC->CFGR &= (uint32_t) ~(RCC_CFGR_PLLXTPRE | RCC_CFGR_PLLSRC | RCC_CFGR_PLLMULL); // CFGR SET
        // 실험실에서 했던거 RCC->CFGR |= (uint32_t)(RCC_CFGR_SW_PLL | RCC_CFGR_PLLMULL4 | RCC_CFGR_PLLSRC_PREDIV1);
        RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLXTPRE_PREDIV1 | RCC_CFGR_PLLSRC_PREDIV1 | RCC_CFGR_PLLMULL4);
        RCC->CFGR2 &= (uint32_t) ~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL | RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC); // CFGR2 SET
        //RCC->CFGR2 &= (uint32_t)~(RCC_CFGR2_PREDIV2 | RCC_CFGR2_PLL2MUL | RCC_CFGR2_PREDIV1 | RCC_CFGR2_PREDIV1SRC);
        RCC->CFGR2 |= (uint32_t)(RCC_CFGR2_PLL2MUL8 | RCC_CFGR2_PREDIV2_DIV5 | RCC_CFGR2_PREDIV1_DIV5 | RCC_CFGR2_PREDIV1SRC_PLL2); // PLL 2 선택 .
                                                                                                                                    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        /* Enable PLL2 */
        RCC->CR |= RCC_CR_PLL2ON;
        /* Wait till PLL2 is ready */
        while ((RCC->CR & RCC_CR_PLL2RDY) == 0)
        {
        }
        /* Enable PLL */
        RCC->CR |= RCC_CR_PLLON;
        /* Wait till PLL is ready */
        while ((RCC->CR & RCC_CR_PLLRDY) == 0)
        {
        }
        /* Select PLL as system clock source */
        RCC->CFGR &= (uint32_t)((uint32_t) ~(RCC_CFGR_SW));
        RCC->CFGR |= (uint32_t)RCC_CFGR_SW_PLL;
        /* Wait till PLL is used as system clock source */
        while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS) != (uint32_t)0x08)
        {
        }
        /* Select System Clock as output of MCO */
        //@TODO - Set the MCO port for system clock output///////////////////////////////////////////////////////////////////////////////////////////
        RCC->CFGR &= ~(uint32_t)RCC_CFGR_MCO;
        RCC->CFGR |= RCC_CFGR_MCO_SYSCLK;
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }
    else
    {
        /* If HSE fails to start-up, the application will have wrong clock
        configuration. User can add here some code to deal with this error */
    }
}

void RCC_Enable(void)
{
    //@TODO - RCC Setting////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /*---------------------------- RCC Configuration -----------------------------*/
    /* GPIO RCC Enable  */
    /* UART Tx, Rx, MCO port */
    RCC->APB2ENR |= (uint32_t)(RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPCEN);
    /* USART RCC Enable */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    //RCC->APB2ENR |= ??
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
void PortConfiguration(void)
{
    /* Reset(Clear) Port A CRH - MCO, USART1 TX,RX*/
    GPIOA->CRH &= ~(
        (GPIO_CRH_CNF8 | GPIO_CRH_MODE8) |
        (GPIO_CRH_CNF9 | GPIO_CRH_MODE9) |
        (GPIO_CRH_CNF10 | GPIO_CRH_MODE10));
    //@TODO - GPIO Configuration/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /* MCO Pin Configuration */
    // GPIOA->CRH |= ??

    //GPIOA->CRH &= ~(0x0000000F);
    GPIOA->CRH |= 0x0000000B; //MCO PIN A8 SET => Output mode => 1011
                              /* USART Pin Configuration */
                              // GPIOA->CRH |= ??
                              //GPIOA->CRH &= ~(0x000000F0);
    GPIOA->CRH |= 0x000000B0; //USART1 PIN A9 SET 송신 부분 -> Output mode -> 1011a

    /* Reset(Clear) Port D CRH - User S1 Button */
    GPIOD->CRH &= ~0XF000;
    // GPIOD->CRH &= ??
    /* User S1 Button Configuration */
    GPIOD->CRH |= 0X8000;
    // GPIOD->CRH |= ??
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //추기 가능 -> 조이스틱을 사용을 위한 Port 설정
    GPIOC->CRL &= ~0x0FFFF00; //Init mode PC2, PC3, PC4, PC5
    GPIOC->CRL |= 0x0888800;  //Configuration PC2, PC3, PC4, PC5
}

void UartInit(void)
{
    /*---------------------------- USART CR1 Configuration -----------------------*/
    /* Clear M, PCE, PS, TE and RE bits */
    USART1->CR1 &= ~(uint32_t)(USART_CR1_M | USART_CR1_PCE | USART_CR1_PS | USART_CR1_TE | USART_CR1_RE);
    /* Configure the USART Word Length, Parity and mode ----------------------- */
    /* Set the M bits according to USART_WordLength value */
    /* Set PCE and PS bits according to USART_Parity value */
    /* Set TE and RE bits according to USART_Mode value */
    //@TODO - : Enable Tx and Rx///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // USART1->CR1 |= ??
    USART1->CR1 |= (uint32_t)(USART_CR1_TE | USART_CR1_RE); // 요거 -> < Transmitter Enable  ,  < Receiver Enable
                                                            ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*---------------------------- USART CR2 Configuration -----------------------*/
    /* Clear STOP[13:12] bits */
    USART1->CR2 &= ~(uint32_t)(USART_CR2_STOP);
    /* Configure the USART Stop Bits, Clock, CPOL, CPHA and LastBit ------------*/
    USART1->CR2 &= ~(uint32_t)(USART_CR2_CPHA | USART_CR2_CPOL | USART_CR2_CLKEN);
    /* Set STOP[13:12] bits according to USART_StopBits value */
    /*---------------------------- USART CR3 Configuration -----------------------*/
    /* Clear CTSE and RTSE bits */
    USART1->CR3 &= ~(uint32_t)(USART_CR3_CTSE | USART_CR3_RTSE);
    /* Configure the USART HFC -------------------------------------------------*/
    /* Set CTSE and RTSE bits according to USART_HardwareFlowControl value */
    /*---------------------------- USART BRR Configuration -----------------------*/
    /* Configure the USART Baud Rate -------------------------------------------*/
    /* Determine the integer part */
    /* Determine the fractional part */
    //@TODO - : Calculate & configure BRR//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // USART1->BRR |= ??
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    //목표 수치
    //SYSCLK: 32MHz(단, 계산식 25 / 5 * 8 / 5 * 4 = 32 로 제한함)
    //PCLK2: 16MHz
    //Baud Rate: 2400
    // USARTDIV 가 416.6666666...7 나오므로
    //Mantissa는 417 = 1a1(16진수)이 되고,
    //Fraction은 0.66666666...7 * 16 = 10.72 => 11이므로 B가 된다.
    //그래서 Boud Rate = 0X1A1B가 된다.
    /////////////////////////////////
    USART1->BRR |= 0x1A1B; // 요거가 Boud Rate 라고 해서 1초당 몇개의 아스키코드를 전송할 수 있는지 나타낸다.
    /*---------------------------- USART Enable ----------------------------------*/
    /* USART Enable Configuration */
    //@TODO - : Enable UART (UE)///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    USART1->CR1 |= (uint32_t)USART_CR1_UE; // 요거 /*!< USART Enable */
    // USART1->CR1 |= ??
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

#define ARRAY_LEN(X) (sizeof(X) / sizeof(X[0])) // 배열 길이

_Bool check_push()
{
    return !((GPIOD->IDR) & GPIO_IDR_IDR11); // Push 됐다면 True 아니라면  False
}

_Bool check_Down()
{
    return !((GPIOC->IDR) & GPIO_IDR_IDR2); //Down Push 됐다면 True 아니라면  False
}

_Bool check_Left()
{
    return !((GPIOC->IDR) & GPIO_IDR_IDR3); // Left push 됐다면 True 아니라면  False
}

_Bool check_Right()
{
    return !((GPIOC->IDR) & GPIO_IDR_IDR4); //Right Push 됐다면 True 아니라면  False
}

_Bool check_Up()
{
    return !((GPIOC->IDR) & GPIO_IDR_IDR5); //Up Push 됐다면 True 아니라면  False
}

void delay(void)
{
    int i = 0;
    for (i = 0; i < 1000000; i++)
        ;
}

void SendData(uint16_t data)
{
    /* Transmit Data */
    USART1->DR = data;

    /* Wait till TC is set */
    while ((USART1->SR & USART_SR_TC) == 0)
        ;
}

int main()
{
    int i;
    char msg_User1[] = "Team05 USART\r\n";
    char msg_Down[] = "Down USART\r\n";
    char msg_Left[] = "Left USART\r\n";
    char msg_Right[] = "Right USART\r\n";
    char msg_Up[] = "Up USART\r\n";

    //printf("%d",msg.size());

    SysInit();
    SetSysClock();
    RCC_Enable();
    PortConfiguration();
    UartInit();

    // if you need, init pin values here

    while (1)
    {
        if (check_push())
        {
            delay(); // User1 Button push
            for (i = 0; i < ARRAY_LEN(msg_User1); ++i)
            {
                SendData(msg_User1[i]);
            }
        }
        else if (check_Down())
        { // Joystick Down push
            delay();
            for (i = 0; i < ARRAY_LEN(msg_Down); ++i)
            {
                printf("%c", msg_Down[i]);
                SendData(msg_Down[i]);
            }
        }
        else if (check_Left())
        { // Joystick Left push
            delay();
            for (i = 0; i < ARRAY_LEN(msg_Left); ++i)
            {
                SendData(msg_Left[i]);
            }
        }
        else if (check_Right())
        { // Joystick Right push
            delay();
            for (i = 0; i < ARRAY_LEN(msg_Right); ++i)
            {
                SendData(msg_Right[i]);
            }
        }
        else if (check_Up())
        { // Joystick Up push
            delay();
            for (i = 0; i < ARRAY_LEN(msg_Up); ++i)
            {
                SendData(msg_Up[i]);
            }
        }

        //@TODO - : Send the message when button is pressed, 1 byte       //////////////////////////////////////////////////////////////////////////////

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    }

} // end main