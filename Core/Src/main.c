/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef htim1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

UART_HandleTypeDef huart3;
DMA_HandleTypeDef hdma_usart3_rx;
DMA_HandleTypeDef hdma_usart3_tx;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_DMA_Init(void);
static void MX_TIM2_Init(void);
static void MX_TIM3_Init(void);
static void MX_TIM1_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

uint8_t ready = 0;

uint8_t begin_stra_gait = 0;
uint8_t leg2_12and3_34_stra_gait = 0;
uint8_t leg3_12and2_34_stra_gait = 0;

uint8_t begin_spin_gait = 0;
uint8_t leg2_12and3_34_spin_gait = 0;
uint8_t leg3_12and2_34_spin_gait = 0;

// straight gait 1

int RBpalForeAlphaTIM[] = {44, 45, 46, 47, 49, 50, 52, 54, 55, 57, 59}; //1
int RBpalForeBetaTIM[] = {63, 62, 61, 61, 61, 61, 62, 63, 64, 65, 67}; //1

int RBpalBackAlphaTIM[] = {33, 33, 33, 34, 35, 36, 37, 39, 40, 42, 44}; 
int RBpalBackBetaTIM[] = {67, 65, 64, 63, 62, 61, 61, 61, 61, 62, 63}; 

int RBpalAlphaGaitTIM[] = {33, 33, 34, 36, 38, 41, 44, 48, 52, 55, 59}; //3
int RBpalBetaGaitTIM[] = {67, 64, 61, 59, 58, 57, 58, 59, 61, 64, 67}; //3


int RBstraForeAlphaTIM[] = {59, 57, 56, 54, 53, 51, 50, 48, 47, 45, 44}; //4
int RBstraForeBetaTIM[] = {67, 66, 66, 65, 65, 64, 64, 64, 63, 63, 63}; //4

int RBstraBackAlphaTIM[] = {44, 43, 41, 40, 39, 38, 37, 36, 35, 34, 33};
int RBstraBackBetaTIM[] = {63, 63, 63, 64, 64, 64, 65, 65, 66, 66, 67};

int RBstraAlphaGaitTIM[] = {59, 56, 53, 50, 47, 44, 41, 39, 37, 35, 33}; //2
int RBstraBetaGaitTIM[] = {67, 66, 65, 64, 63, 63, 63, 64, 65, 66, 67}; //2



int LBpalAlphaGaitTIM[] = {117, 117, 116, 114, 112, 109, 106, 102, 98, 95, 91}; //3
int LBpalBetaGaitTIM[] = {83, 86, 89, 91, 92, 93, 92, 91, 89, 86, 83}; //3
	
int LBpalBackAlphaTIM[] = {117, 117, 117, 116, 115, 114, 113, 111, 110, 108, 106};
int LBpalBackBetaTIM[] = {83, 85, 86, 87, 88, 89, 89, 89, 89, 88, 87};

int LBpalForeAlphaTIM[] = {106, 105, 104, 103, 101, 100, 98, 96, 95, 93, 91}; //1
int LBpalForeBetaTIM[] = {87, 88, 89, 89, 89, 89, 88, 87, 86, 85, 83}; //1


int LBstraAlphaGaitTIM[] = {91, 94, 97, 100, 103, 106, 109, 111, 113, 115, 117}; //2
int LBstraBetaGaitTIM[] = {83, 84, 85, 86, 87, 87, 87, 86, 85, 84, 83}; //2

int LBstraBackAlphaTIM[] = {106, 107, 109, 110, 111, 112, 113, 114, 115, 116, 117};
int LBstraBackBetaTIM[] = {87, 87, 87, 86, 86, 86, 85, 85, 84, 84, 83};

int LBstraForeAlphaTIM[] = {91, 93, 94, 96, 97, 99, 100, 102, 103, 105, 106}; //4
int LBstraForeBetaTIM[] = {83, 84, 84, 85, 85, 86, 86, 86, 87, 87, 87}; //4



// spin gait

// for 11 and 14
// pal
int fullPalShoulderTIM1[] = {71, 72, 73, 73, 74, 75, 76, 77, 77, 78, 79};
int halfInsidePalShoulderTIM1[] = {71, 71, 71, 73, 73, 73, 73, 73, 74, 75, 75};
int halfOutsidePalShoulderTIM1[] = {75, 75, 76, 76, 77, 77, 77, 77, 78, 78, 79};
//stra
int fullStraShoulderTIM1[] = {79, 78, 77, 77, 76, 75, 74, 73, 73, 72, 71}; // reversed
int halfInsideStraShoulderTIM1[] = {75, 75, 74, 73, 73, 73, 73, 73, 72, 71, 71}; // reversed
int halfOutsideStraShoulderTIM1[] = {79, 78, 77, 77, 77, 77, 77, 76, 76, 75, 75}; // reversed
 
// for 12 and 13
// pal
int fullPalShoulderTIM2[] = {73, 73, 73, 74, 74, 75, 76, 76, 76, 76, 77};
int halfInsidePalShoulderTIM2[] = {75, 75, 76, 76, 76, 76, 76, 76, 77, 77, 77};
int halfOutsidePalShoulderTIM2[] = {73, 73, 73, 73, 73, 73, 74, 74, 74, 75, 75};
//stra
int fullStraShoulderTIM2[] = {77, 77, 77, 76, 76, 75, 74, 74, 74, 74, 73}; // reversed
int halfInsideStraShoulderTIM2[] = {77, 77, 76, 76, 76, 76, 76, 76, 76, 75, 75}; // reversed
int halfOutsideStraShoulderTIM2[] = {75, 75, 74, 74, 74, 74, 74, 74, 74, 73, 73}; // reversed
 


// right from backside
// pal
int RBfullPalAlphaGaitTIM[] = {44, 43, 43, 42, 42, 42, 42, 43, 44, 45, 46};
int RBfullPalBetaGaitTIM[] = {63, 62, 60, 60, 58, 59, 60, 61, 63, 64, 67};

int RBhalfInsidePalAlphaGaitTIM[] = {43, 42, 41, 41, 41, 40, 41, 41, 42, 43, 44};
int RBhalfInsidePalBetaGaitTIM[] = {61, 60, 58, 57, 57, 56, 57, 58, 59, 61, 63};

int RBhalfOutsidePalAlphaGaitTIM[] = {45, 44, 43, 43, 42, 43, 43, 43, 44, 45, 46};
int RBhalfOutsidePalBetaGaitTIM[] = {65, 63, 62, 61, 60, 60, 61, 61, 63, 65, 67};

// stra
int RBfullStraAlphaGaitTIM[] = {46, 46, 46, 45, 45, 45, 45, 45, 44, 44, 44}; // reversed
int RBfullStraBetaGaitTIM[] = {67, 66, 66, 66, 66, 65, 64, 64, 64, 64, 63}; // reversed

int RBhalfInsideStraAlphaGaitTIM[] = {44, 44, 44, 44, 44, 44, 43, 43, 43, 43, 43}; // reversed
int RBhalfInsideStraBetaGaitTIM[] = {63, 63, 63, 63, 63, 63, 62, 62, 62, 61, 61}; // reversed

int RBhalfOutsideStraAlphaGaitTIM[] = {46, 46, 46, 46, 46, 45, 45, 45, 45, 45, 45}; // reversed
int RBhalfOutsideStraBetaGaitTIM[] = {67, 67, 66, 66, 66, 66, 66, 66, 66, 65, 65}; // reversed


// left from backside
// pal
int LBfullPalAlphaGaitTIM[] = {106, 107, 108, 109, 110, 110, 110, 110, 109, 108, 108};
int LBfullPalBetaGaitTIM[] = {87, 89, 91, 93, 94, 95, 95, 94, 93, 92, 90};

int LBhalfInsidePalAlphaGaitTIM[] = {107, 108, 109, 110, 110, 110, 110, 110, 110, 109, 108};
int LBhalfInsidePalBetaGaitTIM[] = {89, 91, 93, 94, 95, 96, 95, 95, 94, 92, 90};

int LBhalfOutsidePalAlphaGaitTIM[] = {105, 106, 107, 108, 108, 108, 109, 108, 107, 107, 106};
int LBhalfOutsidePalBetaGaitTIM[] = {85, 87, 89, 90, 91, 92, 92, 91, 90, 89, 87};

// stra
int LBfullStraAlphaGaitTIM[] = {108, 107, 107, 107, 107, 107, 107, 107, 107, 106, 106}; // reversed
int LBfullStraBetaGaitTIM[] = {90, 90, 90, 89, 89, 89, 88, 88, 87, 87, 87}; // reversed

int LBhalfInsideStraAlphaGaitTIM[] = {108, 108, 107, 107, 107, 107, 107, 107, 107, 107, 107}; // reversed
int LBhalfInsideStraBetaGaitTIM[] = {90, 90, 90, 90, 90, 90, 89, 89, 89, 89, 89}; // reversed

int LBhalfOutsideStraAlphaGaitTIM[] = {106, 106, 106, 106, 106, 106, 106, 106, 106, 105, 105}; // reversed
int LBhalfOutsideStraBetaGaitTIM[] = {87, 87, 86, 86, 86, 86, 86, 86, 86, 85, 85}; // reversed
	



// function for straight gait 1

void check_begin_stra_gait() {
	for(int  i = 0; i < 11; i ++) {
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RBpalForeAlphaTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, RBpalForeBetaTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, LBpalForeAlphaTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, LBpalForeBetaTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, LBstraBackAlphaTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, LBstraBackBetaTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, RBstraBackAlphaTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, RBstraBackBetaTIM[i]);
		HAL_Delay(20);
	}
	HAL_Delay(50);
	
	begin_stra_gait = 1;
}
void first_step_stra_gait() {
	for(int  i = 0; i < 11; i ++) {
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RBstraAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, RBstraBetaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, LBstraAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, LBstraBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, LBpalAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, LBpalBetaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, RBpalAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, RBpalBetaGaitTIM[i]);
		
		HAL_Delay(20);
	}
	
	leg2_12and3_34_stra_gait = 2;
	leg3_12and2_34_stra_gait = 1;
	
	HAL_Delay(50);
}
void second_step_stra_gait() {
	for(int  i = 0; i < 11; i ++) {
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RBpalAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, RBpalBetaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, LBpalAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, LBpalBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, LBstraAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, LBstraBetaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, RBstraAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, RBstraBetaGaitTIM[i]);
		
		HAL_Delay(20);
	}
	
	leg2_12and3_34_stra_gait = 1;
	leg3_12and2_34_stra_gait = 2;
	
	HAL_Delay(50);
}
void check_end_stra_gait() {
	if(leg3_12and2_34_stra_gait == 1) {
		for(int  i = 0; i < 11; i ++) {
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RBpalBackAlphaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, RBpalBackBetaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, LBpalBackAlphaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, LBpalBackBetaTIM[i]);
			
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, LBstraForeAlphaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, LBstraForeBetaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, RBstraForeAlphaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, RBstraForeBetaTIM[i]);
			
			HAL_Delay(20);
		}
		leg2_12and3_34_stra_gait = 0;
		leg3_12and2_34_stra_gait = 0;
	} else if (leg2_12and3_34_stra_gait == 1) {
		for(int  i = 0; i < 11; i ++) {
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RBstraForeAlphaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, RBstraForeBetaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, LBstraForeAlphaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, LBstraForeBetaTIM[i]);
			
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, LBpalBackAlphaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, LBpalBackBetaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, RBpalBackAlphaTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, RBpalBackBetaTIM[i]);
			
			HAL_Delay(20);
		}
		leg2_12and3_34_stra_gait = 0;
		leg3_12and2_34_stra_gait = 0;
	}
	
	begin_stra_gait = 0;
	ready = 0;
}



// function for spin gait

void check_begin_spin_gait() { // left current 
	for(int i = 0; i < 11; i++) {
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, halfOutsidePalShoulderTIM1[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RBhalfOutsidePalAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, RBhalfOutsidePalBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, halfOutsideStraShoulderTIM2[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, LBhalfOutsideStraAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, LBhalfOutsideStraBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, halfOutsidePalShoulderTIM1[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, LBhalfOutsidePalAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, LBhalfOutsidePalBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, halfOutsideStraShoulderTIM2[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, RBhalfOutsideStraAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, RBhalfOutsideStraBetaGaitTIM[i]);
		
		HAL_Delay(30);
	}
	HAL_Delay(50);
	
	begin_spin_gait = 1;
}

void first_step_spin_gait() {
	for(int i = 0; i < 11; i++) {
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, fullStraShoulderTIM1[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RBfullStraAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, RBfullStraBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, fullPalShoulderTIM2[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, LBfullPalAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, LBfullPalBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, fullStraShoulderTIM1[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, LBfullStraAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, LBfullStraBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fullPalShoulderTIM2[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, RBfullPalAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, RBfullPalBetaGaitTIM[i]);
	
		HAL_Delay(30);
	}
	HAL_Delay(50);
	
	leg2_12and3_34_spin_gait = 2; // when these leg just end stra rotation
	leg3_12and2_34_spin_gait = 1; // when these leg just end pal rotation
}

void second_step_spin_gait() {
	for(int i = 0; i < 11; i++) {
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, fullPalShoulderTIM1[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RBfullPalAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, RBfullPalBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, fullStraShoulderTIM2[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, LBfullStraAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, LBfullStraBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, fullPalShoulderTIM1[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, LBfullPalAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, LBfullPalBetaGaitTIM[i]);
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, fullStraShoulderTIM2[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, RBfullStraAlphaGaitTIM[i]);
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, RBfullStraBetaGaitTIM[i]);
		
		HAL_Delay(30);
	}
	HAL_Delay(50);
	
	leg2_12and3_34_spin_gait = 1; // when these leg just end pal rotatino
	leg3_12and2_34_spin_gait = 2; // when these leg just end stra rotation
}


void check_end_spin_gait() {
	if(leg2_12and3_34_spin_gait == 1) {
		for(int i = 0; i < 11; i ++) {
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, halfOutsideStraShoulderTIM1[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RBhalfOutsideStraAlphaGaitTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, RBhalfOutsideStraBetaGaitTIM[i]);
			
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, halfOutsidePalShoulderTIM2[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, LBhalfOutsidePalAlphaGaitTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, LBhalfOutsidePalBetaGaitTIM[i]);
			
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, halfOutsideStraShoulderTIM1[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, LBhalfOutsideStraAlphaGaitTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, LBhalfOutsideStraBetaGaitTIM[i]);
			
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, halfOutsidePalShoulderTIM2[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, RBhalfOutsidePalAlphaGaitTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, RBhalfOutsidePalBetaGaitTIM[i]);

			
			HAL_Delay(30);
		}
		
		leg2_12and3_34_spin_gait = 0; 
		leg3_12and2_34_spin_gait = 0; 

	} else if (leg3_12and2_34_spin_gait == 1) {
		for(int i = 0; i < 11; i ++) {
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, halfInsidePalShoulderTIM1[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, RBhalfInsidePalAlphaGaitTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, RBhalfInsidePalBetaGaitTIM[i]);
			
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, halfInsideStraShoulderTIM2[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, LBhalfInsideStraAlphaGaitTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, LBhalfInsideStraBetaGaitTIM[i]);
			
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, halfInsidePalShoulderTIM1[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, LBhalfInsidePalAlphaGaitTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, LBhalfInsidePalBetaGaitTIM[i]);
			
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, halfInsideStraShoulderTIM2[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, RBhalfInsideStraAlphaGaitTIM[i]);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, RBhalfInsideStraBetaGaitTIM[i]);
			
			HAL_Delay(30);
		}
		
		leg2_12and3_34_spin_gait = 0; 
		leg3_12and2_34_spin_gait = 0; 
	}
	
	begin_spin_gait = 0;
}






uint8_t rxData[4];

uint8_t forward = 0;
uint8_t back = 0;
uint8_t right = 0;
uint8_t left = 0;

int count = 0;

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART3) {  
			count ++;
      right = rxData[0];
			forward = rxData[1];
			back = rxData[2];
			left = rxData[3];
			
			HAL_UART_Receive_DMA(&huart3, rxData, 4);
    }
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
  MX_DMA_Init();
  MX_TIM2_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_USART3_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
	
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_4);
	
	HAL_UART_Receive_DMA(&huart3, rxData, 4);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {		
		int spin = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12);
		
		if(spin) {
			if(!begin_stra_gait) {
				check_begin_stra_gait();
			}
			first_step_stra_gait();
			second_step_stra_gait();
		} else {
			check_end_stra_gait();
		}
		
		if(forward) {
			if(!begin_spin_gait) {
				check_begin_spin_gait();
			}
			first_step_spin_gait();
			second_step_spin_gait();
		} else {
			check_end_spin_gait();
		}
				
		if(!ready) {
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 75);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 75);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 75);
			__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 75);

			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 44);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, 63);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, 106);
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, 87);
			
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 44);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, 63);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, 106);
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, 87);
		}
		
    /* USER CODE END WHILE */

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
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */

  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 1439;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */
  HAL_TIM_MspPostInit(&htim1);

}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 1439;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 999;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim2, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */
  HAL_TIM_MspPostInit(&htim2);

}

/**
  * @brief TIM3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM3_Init(void)
{

  /* USER CODE BEGIN TIM3_Init 0 */

  /* USER CODE END TIM3_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};

  /* USER CODE BEGIN TIM3_Init 1 */

  /* USER CODE END TIM3_Init 1 */
  htim3.Instance = TIM3;
  htim3.Init.Prescaler = 1439;
  htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim3.Init.Period = 999;
  htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
  if (HAL_TIM_PWM_Init(&htim3) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_3) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_PWM_ConfigChannel(&htim3, &sConfigOC, TIM_CHANNEL_4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM3_Init 2 */

  /* USER CODE END TIM3_Init 2 */
  HAL_TIM_MspPostInit(&htim3);

}

/**
  * @brief USART3 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART3_UART_Init(void)
{

  /* USER CODE BEGIN USART3_Init 0 */

  /* USER CODE END USART3_Init 0 */

  /* USER CODE BEGIN USART3_Init 1 */

  /* USER CODE END USART3_Init 1 */
  huart3.Instance = USART3;
  huart3.Init.BaudRate = 115200;
  huart3.Init.WordLength = UART_WORDLENGTH_8B;
  huart3.Init.StopBits = UART_STOPBITS_1;
  huart3.Init.Parity = UART_PARITY_NONE;
  huart3.Init.Mode = UART_MODE_TX_RX;
  huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart3.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart3) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART3_Init 2 */

  /* USER CODE END USART3_Init 2 */

}

/**
  * Enable DMA controller clock
  */
static void MX_DMA_Init(void)
{

  /* DMA controller clock enable */
  __HAL_RCC_DMA1_CLK_ENABLE();

  /* DMA interrupt init */
  /* DMA1_Channel2_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel2_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel2_IRQn);
  /* DMA1_Channel3_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(DMA1_Channel3_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(DMA1_Channel3_IRQn);

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin : PB12 */
  GPIO_InitStruct.Pin = GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
