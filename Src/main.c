/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
#include "string.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
struct
{
	uint8_t  var1;
	uint16_t var2;
	uint32_t var3;
} test_struct;//структура для записи данных  в ячейку  памяти
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define flashADDR   0x0801F800//адрес 126 страницы
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void parametrs(char*);
//uint32_t current_value();
//void new_value();
uint8_t writeFlash(uint32_t);//объявление функции(прототип)
uint32_t readFlash(uint32_t);//объявление функции(прототип)
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int ch,FILE *f)
{
	HAL_UART_Transmit(&huart1,(uint8_t *)&ch,1,HAL_MAX_DELAY);
	return ch;
}
int fgetc(FILE *f)
{
	uint8_t ch;
	HAL_UART_Receive( &huart1,(uint8_t*)&ch,1, HAL_MAX_DELAY );
	return ch;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

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
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	char str[]={""};
	//char *str_array[]={"AT+SPD","AT+SPD=?","AT+SPD="};
	char str_array[12][25]={
		"AT+SPD=?",
		"AT+LNOPEN=?",
		"AT+LNHLOPEN=?",
        "AT+CURERRLOCK1=?",
        "AT+CURERRLOCK2=?", 
        "AT+CURERRDRIVE1=?", 
        "AT+CURERRDRIVE2=?", 
        "AT+CURERRDRIVE3=?", 
        "AT+CURERRDRIVE4=?", 
        "AT+CURERRTIME=?",
        "AT+STOTIMELOCK=?", 
        "AT+STOTIMEDRIVE=?" 
    };
    char str_array1[12][25]={
		"AT+SPD?",
		"AT+LNOPEN?",
		"AT+LNHLOPEN?",
        "AT+CURERRLOCK1?",
        "AT+CURERRLOCK2?", 
        "AT+CURERRDRIVE1?", 
        "AT+CURERRDRIVE2?", 
        "AT+CURERRDRIVE3?", 
        "AT+CURERRDRIVE4?", 
        "AT+CURERRTIME?",
        "AT+STOTIMELOCK?", 
        "AT+STOTIMEDRIVE?" 
    };
    char str_array2[12][25]={
		"AT+SPD=",
		"AT+LNOPEN=",
		"AT+LNHLOPEN=",
        "AT+CURERRLOCK1=",
        "AT+CURERRLOCK2=", 
        "AT+CURERRDRIVE1=", 
        "AT+CURERRDRIVE2=", 
        "AT+CURERRDRIVE3=", 
        "AT+CURERRDRIVE4=", 
        "AT+CURERRTIME=",
        "AT+STOTIMELOCK=", 
        "AT+STOTIMEDRIVE=" 
    };
  while (1)
  {
    /* USER CODE END WHILE */
		printf("Enter AT command\r\n");
		scanf("%s",str);
		printf("You enter AT command: %s\r\n",str);
		for(int i=0;i<=sizeof(str_array);i++)
		{
			if(strcmp(str,str_array[i])==0)//если эти строки равны
                parametrs(str);//показать какие параметры может принимать команда 
            //if(strcmp(str,str_array1[i])==0)//если эти строки равны
                //current_value();//текущее значение
            //if(strcmp(str,str_array2[i])==0)//если эти строки равны
                //new_value();//новое значение
				/*switch(i)
				{
					case 0: parametrs(str);//показать какие параметры может принимать команда AT+SPD
						break;
					case 1: printf("%s%d\r\n",str,current_value());//показать текущее значение AT+SPD=? 
						break;
					case 2: new_value(4);//задать новое значение AT+SPD=
						break;
				}*/
		}
    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void parametrs(char *s)
{
    s+=2;//удаляем  первые два символа
	printf("%s:(01,02,03,04)\r\n",s);
}
uint32_t current_value()
{
    uint32_t cur_val=readFlash(flashADDR);
	return cur_val;
}
void new_value()
{
	
}
uint8_t writeFlash (uint32_t addr)
{
	HAL_StatusTypeDef status;
	uint32_t structureSize = sizeof(test_struct);          // замеряем размер структуры
	FLASH_EraseInitTypeDef FlashErase;                     // переменная для структуры, которая выполняет функцию стирания страницы
	uint32_t Error = 0;                                // переменная для записи информации об ошибках в процессе стирания

	//__disable_irq();                                       // запрещаем прерывания
	HAL_FLASH_Unlock();									     //разблокировка FLASH
    /*определил параметр для стирания*/
	FlashErase.TypeErase = FLASH_TYPEERASE_PAGES;          // стирать постранично(1кбайт)
	FlashErase.PageAddress = addr;                         // адрес страницы для стирания
	FlashErase.NbPages = structureSize / 1024 + 1;         // считаем количество страниц, чтобы наш массив поместился
	if (HAL_FLASHEx_Erase(&FlashErase, &Error) != HAL_OK)   // вызов функции стирания
	{
		HAL_FLASH_Lock();                                  // если не смог стереть, то закрыть память и вернуть ошибку
		return HAL_ERROR;
	}

    uint32_t *dataPtr = (uint32_t *)&test_struct;          // создаем указатель на нашу структуру и записываем ее кусочками по 32 бита
	for (int i = 0; i < structureSize / 4; i++)            // 4 байта = 32 бита
    {
		status += HAL_FLASH_Program(FLASH_TYPEPROGRAM_WORD, addr, dataPtr[i]);
        addr += 4;                                         // сдвигаем адрес на 4 байта
    }
	//__enable_irq();                                        // включаем прерывания обратно
	HAL_FLASH_Lock();
	return status;
}
uint32_t readFlash (uint32_t addr)
{
	uint32_t structureSize = sizeof(test_struct);
	uint32_t *dataPtr = (uint32_t *)&test_struct;
	for (int i = 0; i < structureSize / 4; i++)
	{
		dataPtr[i] = *(__IO uint32_t*)addr;
		addr += 4;
	}
    return *dataPtr;
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
