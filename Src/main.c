/**
  ******************************************************************************
  * File Name          : main.c
  * Description        : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2018 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"

/* USER CODE BEGIN Includes */
#include "screen.h"
#include "micro_servo.h"
#include "echo_locator.h"

#define SystemCoreClockInMHz (SystemCoreClock/1000000)
#define ECHOPort GPIOD

/*
 * Echo_Locator
 * ECHOPort GPIOD
 * echo_locator_1 ECHOI1_Pin - PD14; TRIG1_Pin - PD13; ECHOPort
 * echo_locator_2 ECHOI2_Pin - PD12; TRIG2_Pin - PD11; ECHOPort
 *
 * Display/Screen
 * 1. GND - GND
 * 2. Light - GND
 * 3. VCC - VCC
 * 4. CLK - PB13 - LCD1_CLK_Pin
 * 5. DIN - PB15 - LCD1_DATA_Pin
 * 6. DC - PB12 - LCD1_DC_Pin
 * 7. CE - PB14 - LCD1_CS_Pin
 * 8. RST - PB11 - LCD1_RST_Pin
 *
 * MicroServo
 * TIM3_CH2 - PE3
 */

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

Echo_Locator * echo_locator_1;
Echo_Locator * echo_locator_2;
volatile uint32_t tim6_overflows = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/
inline void TIM6_reinit()
{
 HAL_TIM_Base_Stop(&htim6);
 __HAL_TIM_SET_PRESCALER( &htim6, (SystemCoreClockInMHz-1) );
 __HAL_TIM_SET_COUNTER( &htim6, 0 );
 tim6_overflows = 0;
 HAL_TIM_Base_Start_IT(&htim6);
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if( htim->Instance == TIM6 )
  {
   ++tim6_overflows;
  }
}

uint32_t get_tim6_us()
{
 __HAL_TIM_DISABLE_IT(&htim6, TIM_IT_UPDATE); //! Disable IRQ
 //__disable_irq();
 uint32_t total_tick = tim6_overflows * 10000 + __HAL_TIM_GET_COUNTER(&htim6);
 //__enable_irq();
 __HAL_TIM_ENABLE_IT(&htim6, TIM_IT_UPDATE);
 return total_tick;
}

void udelay_TIM6(uint32_t useconds) {
 uint32_t before = get_tim6_us();
 while( get_tim6_us() < before+useconds){}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
 if (GPIO_Pin == ECHOI1_Pin)
 {
	 echo_locator_callback(echo_locator_1);
 }
 else if(GPIO_Pin == ECHOI2_Pin)
 {
	 echo_locator_callback(echo_locator_2);
 }
}

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */




/* USER CODE END 0 */

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_SPI2_Init();
  MX_TIM6_Init();

  /* USER CODE BEGIN 2 */



  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
  TIM6_reinit();
  LCD_INIT();


  LCD_PRINT_UI();

  echo_locator_1 = Echo_Locator__create(ECHOPort, ECHOI1_Pin, ECHOPort, TRIG1_Pin);
  echo_locator_2 = Echo_Locator__create(ECHOPort, ECHOI2_Pin, ECHOPort, TRIG2_Pin);

  int angle = 0;

  Set_Min_Position();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */

	  angle = ((int)(angle + 1)) % 360;
	  if (angle > 180) {
		  Set_Position(360-angle);
	  } else {
		  Set_Position(	angle);
	  }
	  u_LCD_DRAWPOINT(angle % 180, filtered_measurement(echo_locator_1, 5));
	  u_LCD_DRAWPOINT(180+(angle % 180), filtered_measurement(echo_locator_2, 5));
//	  udelay_TIM6(1000);

  }
  /* USER CODE END 3 */

}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void _Error_Handler(char * file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1) 
  {
  }
  /* USER CODE END Error_Handler_Debug */ 
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
    ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */

}

#endif

/**
  * @}
  */ 

/**
  * @}
*/ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
