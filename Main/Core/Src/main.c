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

#include "Straight_gait.h"
#include "Spin_gait.h"

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

uint8_t id;


uint8_t rxData[4];

uint8_t forward = 0;
uint8_t back = 0;
uint8_t right = 0;
uint8_t left = 0;


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
	


// reversed array
// straight gait 1
int RBpalForeAlphaTIMRe[11];
int RBpalForeBetaTIMRe[11];

int RBpalBackAlphaTIMRe[11];
int RBpalBackBetaTIMRe[11];

int RBpalAlphaGaitTIMRe[11];
int RBpalBetaGaitTIMRe[11];

int RBstraForeAlphaTIMRe[11];
int RBstraForeBetaTIMRe[11];

int RBstraBackAlphaTIMRe[11];
int RBstraBackBetaTIMRe[11];

int RBstraAlphaGaitTIMRe[11];
int RBstraBetaGaitTIMRe[11];

int LBpalAlphaGaitTIMRe[11];
int LBpalBetaGaitTIMRe[11];

int LBpalBackAlphaTIMRe[11];
int LBpalBackBetaTIMRe[11];

int LBpalForeAlphaTIMRe[11];
int LBpalForeBetaTIMRe[11];

int LBstraAlphaGaitTIMRe[11];
int LBstraBetaGaitTIMRe[11];

int LBstraBackAlphaTIMRe[11];
int LBstraBackBetaTIMRe[11];

int LBstraForeAlphaTIMRe[11];
int LBstraForeBetaTIMRe[11];

// spin gait
int fullPalShoulderTIM1Re[11];
int halfInsidePalShoulderTIM1Re[11];
int halfOutsidePalShoulderTIM1Re[11];

int fullStraShoulderTIM1Re[11];
int halfInsideStraShoulderTIM1Re[11];
int halfOutsideStraShoulderTIM1Re[11];

int fullPalShoulderTIM2Re[11];
int halfInsidePalShoulderTIM2Re[11];
int halfOutsidePalShoulderTIM2Re[11];

int fullStraShoulderTIM2Re[11];
int halfInsideStraShoulderTIM2Re[11];
int halfOutsideStraShoulderTIM2Re[11];

// right from backside
int RBfullPalAlphaGaitTIMRe[11];
int RBfullPalBetaGaitTIMRe[11];

int RBhalfInsidePalAlphaGaitTIMRe[11];
int RBhalfInsidePalBetaGaitTIMRe[11];

int RBhalfOutsidePalAlphaGaitTIMRe[11];
int RBhalfOutsidePalBetaGaitTIMRe[11];

int RBfullStraAlphaGaitTIMRe[11];
int RBfullStraBetaGaitTIMRe[11];

int RBhalfInsideStraAlphaGaitTIMRe[11];
int RBhalfInsideStraBetaGaitTIMRe[11];

int RBhalfOutsideStraAlphaGaitTIMRe[11];
int RBhalfOutsideStraBetaGaitTIMRe[11];

// left from backside
int LBfullPalAlphaGaitTIMRe[11];
int LBfullPalBetaGaitTIMRe[11];

int LBhalfInsidePalAlphaGaitTIMRe[11];
int LBhalfInsidePalBetaGaitTIMRe[11];

int LBhalfOutsidePalAlphaGaitTIMRe[11];
int LBhalfOutsidePalBetaGaitTIMRe[11];

int LBfullStraAlphaGaitTIMRe[11];
int LBfullStraBetaGaitTIMRe[11];

int LBhalfInsideStraAlphaGaitTIMRe[11];
int LBhalfInsideStraBetaGaitTIMRe[11];

int LBhalfOutsideStraAlphaGaitTIMRe[11];
int LBhalfOutsideStraBetaGaitTIMRe[11];



// function to reverse the array
void reverseArray(int* arr, int* reversedArr) {
    for (int i = 0; i < 11; i++) {
        reversedArr[i] = arr[11 - 1 - i];
    }
}



// function for straight gait 1

void reverse_straight_gait() {
	reverseArray(RBpalBackAlphaTIM, RBpalBackAlphaTIMRe);
	reverseArray(RBpalBackBetaTIM, RBpalBackBetaTIMRe);
	reverseArray(LBpalBackAlphaTIM, LBpalBackAlphaTIMRe);
	reverseArray(LBpalBackBetaTIM, LBpalBackBetaTIMRe);
	reverseArray(LBstraForeAlphaTIM, LBstraForeAlphaTIMRe);
	reverseArray(LBstraForeBetaTIM, LBstraForeBetaTIMRe);
	reverseArray(RBstraForeAlphaTIM, RBstraForeAlphaTIMRe);
	reverseArray(RBstraForeBetaTIM, RBstraForeBetaTIMRe);
	reverseArray(RBstraAlphaGaitTIM, RBstraAlphaGaitTIMRe);
	reverseArray(RBstraBetaGaitTIM, RBstraBetaGaitTIMRe);
	reverseArray(LBstraAlphaGaitTIM, LBstraAlphaGaitTIMRe);
	reverseArray(LBstraBetaGaitTIM, LBstraBetaGaitTIMRe);
	reverseArray(LBpalAlphaGaitTIM, LBpalAlphaGaitTIMRe);
	reverseArray(LBpalBetaGaitTIM, LBpalBetaGaitTIMRe);
	reverseArray(RBpalAlphaGaitTIM, RBpalAlphaGaitTIMRe);
	reverseArray(RBpalBetaGaitTIM, RBpalBetaGaitTIMRe);
	reverseArray(RBpalForeAlphaTIM, RBpalForeAlphaTIMRe);
	reverseArray(RBpalForeBetaTIM, RBpalForeBetaTIMRe);
	reverseArray(LBpalForeAlphaTIM, LBpalForeAlphaTIMRe);
	reverseArray(LBpalForeBetaTIM, LBpalForeBetaTIMRe);
	reverseArray(LBstraBackAlphaTIM, LBstraBackAlphaTIMRe);
	reverseArray(LBstraBackBetaTIM, LBstraBackBetaTIMRe);
	reverseArray(RBstraBackAlphaTIM, RBstraBackAlphaTIMRe);
	reverseArray(RBstraBackBetaTIM, RBstraBackBetaTIMRe);
}

void rotate_straight_forward() { // move forward
	if (!begin_stra_gait) {
		check_begin_stra_gait(RBpalForeAlphaTIM, RBpalForeBetaTIM, LBpalForeAlphaTIM, LBpalForeBetaTIM, LBstraBackAlphaTIM, LBstraBackBetaTIM, RBstraBackAlphaTIM, RBstraBackBetaTIM);
	}
	first_step_stra_gait(RBstraAlphaGaitTIM, RBstraBetaGaitTIM, LBstraAlphaGaitTIM, LBstraBetaGaitTIM, LBpalAlphaGaitTIM, LBpalBetaGaitTIM, RBpalAlphaGaitTIM, RBpalBetaGaitTIM);

	if (!forward) {
		check_end_stra_gait(RBpalBackAlphaTIM, RBpalBackBetaTIM, LBpalBackAlphaTIM, LBpalBackBetaTIM, LBstraForeAlphaTIM, LBstraForeBetaTIM, RBstraForeAlphaTIM, RBstraForeBetaTIM,
												RBstraForeAlphaTIM, RBstraForeBetaTIM, LBstraForeAlphaTIM, LBstraForeBetaTIM, LBpalBackAlphaTIM, LBpalBackBetaTIM, RBpalBackAlphaTIM, RBpalBackBetaTIM);
		return;
	}

	second_step_stra_gait(RBpalAlphaGaitTIM, RBpalBetaGaitTIM, LBpalAlphaGaitTIM, LBpalBetaGaitTIM, LBstraAlphaGaitTIM, LBstraBetaGaitTIM, RBstraAlphaGaitTIM, RBstraBetaGaitTIM);
}

void rotate_straight_backward() { // move backward
	reverse_straight_gait();
	
	if (!begin_stra_gait) {
		check_begin_stra_gait(RBpalBackAlphaTIMRe, RBpalBackBetaTIMRe, LBpalBackAlphaTIMRe, LBpalBackBetaTIMRe, LBstraForeAlphaTIMRe, LBstraForeBetaTIMRe, RBstraForeAlphaTIMRe, RBstraForeBetaTIMRe);
	}
	first_step_stra_gait(RBstraAlphaGaitTIMRe, RBstraBetaGaitTIMRe, LBstraAlphaGaitTIMRe, LBstraBetaGaitTIMRe, LBpalAlphaGaitTIMRe, LBpalBetaGaitTIMRe, RBpalAlphaGaitTIMRe, RBpalBetaGaitTIMRe);

	if (!back) {
		check_end_stra_gait(RBpalForeAlphaTIMRe, RBpalForeBetaTIMRe, LBpalForeAlphaTIMRe, LBpalForeBetaTIMRe, LBstraBackAlphaTIMRe, LBstraBackBetaTIMRe, RBstraBackAlphaTIMRe, RBstraBackBetaTIMRe,
												RBstraBackAlphaTIMRe, RBstraBackBetaTIMRe, LBstraBackAlphaTIMRe, LBstraBackBetaTIMRe, LBpalForeAlphaTIMRe, LBpalForeBetaTIMRe, RBpalForeAlphaTIMRe, RBpalForeBetaTIMRe);
		return;
	}

	second_step_stra_gait(RBpalAlphaGaitTIMRe, RBpalBetaGaitTIMRe, LBpalAlphaGaitTIMRe, LBpalBetaGaitTIMRe, LBstraAlphaGaitTIMRe, LBstraBetaGaitTIMRe, RBstraAlphaGaitTIMRe, RBstraBetaGaitTIMRe);
}









// function for spin gait

void reverse_spin_gait() {
    // Reverse shoulder TIM1 arrays
    reverseArray(fullPalShoulderTIM1, fullPalShoulderTIM1Re);
    reverseArray(halfInsidePalShoulderTIM1, halfInsidePalShoulderTIM1Re);
    reverseArray(halfOutsidePalShoulderTIM1, halfOutsidePalShoulderTIM1Re);
    reverseArray(fullStraShoulderTIM1, fullStraShoulderTIM1Re);
    reverseArray(halfInsideStraShoulderTIM1, halfInsideStraShoulderTIM1Re);
    reverseArray(halfOutsideStraShoulderTIM1, halfOutsideStraShoulderTIM1Re);

    // Reverse shoulder TIM2 arrays
    reverseArray(fullPalShoulderTIM2, fullPalShoulderTIM2Re);
    reverseArray(halfInsidePalShoulderTIM2, halfInsidePalShoulderTIM2Re);
    reverseArray(halfOutsidePalShoulderTIM2, halfOutsidePalShoulderTIM2Re);
    reverseArray(fullStraShoulderTIM2, fullStraShoulderTIM2Re);
    reverseArray(halfInsideStraShoulderTIM2, halfInsideStraShoulderTIM2Re);
    reverseArray(halfOutsideStraShoulderTIM2, halfOutsideStraShoulderTIM2Re);

    // Reverse right backside Pal arrays
    reverseArray(RBfullPalAlphaGaitTIM, RBfullPalAlphaGaitTIMRe);
    reverseArray(RBfullPalBetaGaitTIM, RBfullPalBetaGaitTIMRe);
    reverseArray(RBhalfInsidePalAlphaGaitTIM, RBhalfInsidePalAlphaGaitTIMRe);
    reverseArray(RBhalfInsidePalBetaGaitTIM, RBhalfInsidePalBetaGaitTIMRe);
    reverseArray(RBhalfOutsidePalAlphaGaitTIM, RBhalfOutsidePalAlphaGaitTIMRe);
    reverseArray(RBhalfOutsidePalBetaGaitTIM, RBhalfOutsidePalBetaGaitTIMRe);

    // Reverse right backside Stra arrays
    reverseArray(RBfullStraAlphaGaitTIM, RBfullStraAlphaGaitTIMRe);
    reverseArray(RBfullStraBetaGaitTIM, RBfullStraBetaGaitTIMRe);
    reverseArray(RBhalfInsideStraAlphaGaitTIM, RBhalfInsideStraAlphaGaitTIMRe);
    reverseArray(RBhalfInsideStraBetaGaitTIM, RBhalfInsideStraBetaGaitTIMRe);
    reverseArray(RBhalfOutsideStraAlphaGaitTIM, RBhalfOutsideStraAlphaGaitTIMRe);
    reverseArray(RBhalfOutsideStraBetaGaitTIM, RBhalfOutsideStraBetaGaitTIMRe);

    // Reverse left backside Pal arrays
    reverseArray(LBfullPalAlphaGaitTIM, LBfullPalAlphaGaitTIMRe);
    reverseArray(LBfullPalBetaGaitTIM, LBfullPalBetaGaitTIMRe);
    reverseArray(LBhalfInsidePalAlphaGaitTIM, LBhalfInsidePalAlphaGaitTIMRe);
    reverseArray(LBhalfInsidePalBetaGaitTIM, LBhalfInsidePalBetaGaitTIMRe);
    reverseArray(LBhalfOutsidePalAlphaGaitTIM, LBhalfOutsidePalAlphaGaitTIMRe);
    reverseArray(LBhalfOutsidePalBetaGaitTIM, LBhalfOutsidePalBetaGaitTIMRe);

    // Reverse left backside Stra arrays
    reverseArray(LBfullStraAlphaGaitTIM, LBfullStraAlphaGaitTIMRe);
    reverseArray(LBfullStraBetaGaitTIM, LBfullStraBetaGaitTIMRe);
    reverseArray(LBhalfInsideStraAlphaGaitTIM, LBhalfInsideStraAlphaGaitTIMRe);
    reverseArray(LBhalfInsideStraBetaGaitTIM, LBhalfInsideStraBetaGaitTIMRe);
    reverseArray(LBhalfOutsideStraAlphaGaitTIM, LBhalfOutsideStraAlphaGaitTIMRe);
    reverseArray(LBhalfOutsideStraBetaGaitTIM, LBhalfOutsideStraBetaGaitTIMRe);
}

void spin_left() {
	if (!begin_spin_gait) {
		check_begin_spin_gait(
			halfOutsidePalShoulderTIM1, RBhalfOutsidePalAlphaGaitTIM, RBhalfOutsidePalBetaGaitTIM,
			halfOutsideStraShoulderTIM2, LBhalfOutsideStraAlphaGaitTIM, LBhalfOutsideStraBetaGaitTIM,
			halfOutsidePalShoulderTIM1, LBhalfOutsidePalAlphaGaitTIM, LBhalfOutsidePalBetaGaitTIM,
			halfOutsideStraShoulderTIM2, RBhalfOutsideStraAlphaGaitTIM, RBhalfOutsideStraBetaGaitTIM
		);
	}

	first_step_spin_gait(
		fullStraShoulderTIM1, RBfullStraAlphaGaitTIM, RBfullStraBetaGaitTIM,
		fullPalShoulderTIM2, LBfullPalAlphaGaitTIM, LBfullPalBetaGaitTIM,
		fullStraShoulderTIM1, LBfullStraAlphaGaitTIM, LBfullStraBetaGaitTIM,
		fullPalShoulderTIM2, RBfullPalAlphaGaitTIM, RBfullPalBetaGaitTIM
	);

	if (!left) {
		check_end_spin_gait(
			halfOutsideStraShoulderTIM1, RBhalfOutsideStraAlphaGaitTIM, RBhalfOutsideStraBetaGaitTIM,
			halfOutsidePalShoulderTIM2, LBhalfOutsidePalAlphaGaitTIM, LBhalfOutsidePalBetaGaitTIM,
			halfOutsideStraShoulderTIM1, LBhalfOutsideStraAlphaGaitTIM, LBhalfOutsideStraBetaGaitTIM,
			halfOutsidePalShoulderTIM2, RBhalfOutsidePalAlphaGaitTIM, RBhalfOutsidePalBetaGaitTIM,
		
			halfInsidePalShoulderTIM1, RBhalfInsidePalAlphaGaitTIM, RBhalfInsidePalBetaGaitTIM,
			halfInsideStraShoulderTIM2, LBhalfInsideStraAlphaGaitTIM, LBhalfInsideStraBetaGaitTIM,
			halfInsidePalShoulderTIM1, LBhalfInsidePalAlphaGaitTIM, LBhalfInsidePalBetaGaitTIM,
			halfInsideStraShoulderTIM2, RBhalfInsideStraAlphaGaitTIM, RBhalfInsideStraBetaGaitTIM
		);
		return;
	}

	second_step_spin_gait(
		fullPalShoulderTIM1, RBfullPalAlphaGaitTIM, RBfullPalBetaGaitTIM,
		fullStraShoulderTIM2, LBfullStraAlphaGaitTIM, LBfullStraBetaGaitTIM,
		fullPalShoulderTIM1, LBfullPalAlphaGaitTIM, LBfullPalBetaGaitTIM,
		fullStraShoulderTIM2, RBfullStraAlphaGaitTIM, RBfullStraBetaGaitTIM
	);
}

void spin_right() {
	reverse_spin_gait();
	
	if (!right) {
		check_begin_spin_gait(
			halfInsidePalShoulderTIM1Re, RBhalfInsidePalAlphaGaitTIMRe, RBhalfInsidePalBetaGaitTIMRe,
			halfInsideStraShoulderTIM2Re, LBhalfInsideStraAlphaGaitTIMRe, LBhalfInsideStraBetaGaitTIMRe,
			halfInsidePalShoulderTIM1Re, LBhalfInsidePalAlphaGaitTIMRe, LBhalfInsidePalBetaGaitTIMRe,
			halfInsideStraShoulderTIM2Re, RBhalfInsideStraAlphaGaitTIMRe, RBhalfInsideStraBetaGaitTIMRe
		);
	}
	first_step_spin_gait(
		fullStraShoulderTIM1Re, RBfullStraAlphaGaitTIMRe, RBfullStraBetaGaitTIMRe,
		fullPalShoulderTIM2Re, LBfullPalAlphaGaitTIMRe, LBfullPalBetaGaitTIMRe,
		fullStraShoulderTIM1Re, LBfullStraAlphaGaitTIMRe, LBfullStraBetaGaitTIMRe,
		fullPalShoulderTIM2Re, RBfullPalAlphaGaitTIMRe, RBfullPalBetaGaitTIMRe
	);
	if (!HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12)) {
		check_end_spin_gait(
			halfInsideStraShoulderTIM1Re, RBhalfInsideStraAlphaGaitTIMRe, RBhalfInsideStraBetaGaitTIMRe,
			halfInsidePalShoulderTIM2Re, LBhalfInsidePalAlphaGaitTIMRe, LBhalfInsidePalBetaGaitTIMRe,
			halfInsideStraShoulderTIM1Re, LBhalfInsideStraAlphaGaitTIMRe, LBhalfInsideStraBetaGaitTIMRe,
			halfInsidePalShoulderTIM2Re, RBhalfInsidePalAlphaGaitTIMRe, RBhalfInsidePalBetaGaitTIMRe,
		
			halfOutsidePalShoulderTIM1Re, RBhalfOutsidePalAlphaGaitTIMRe, RBhalfOutsidePalBetaGaitTIMRe,
			halfOutsideStraShoulderTIM2Re, LBhalfOutsideStraAlphaGaitTIMRe, LBhalfOutsideStraBetaGaitTIMRe,
			halfOutsidePalShoulderTIM1Re, LBhalfOutsidePalAlphaGaitTIMRe, LBhalfOutsidePalBetaGaitTIMRe,
			halfOutsideStraShoulderTIM2Re, RBhalfOutsideStraAlphaGaitTIMRe, RBhalfOutsideStraBetaGaitTIMRe
		);
		return;
	}
	second_step_spin_gait(
		fullPalShoulderTIM1Re, RBfullPalAlphaGaitTIMRe, RBfullPalBetaGaitTIMRe,
		fullStraShoulderTIM2Re, LBfullStraAlphaGaitTIMRe, LBfullStraBetaGaitTIMRe,
		fullPalShoulderTIM1Re, LBfullPalAlphaGaitTIMRe, LBfullPalBetaGaitTIMRe,
		fullStraShoulderTIM2Re, RBfullStraAlphaGaitTIMRe, RBfullStraBetaGaitTIMRe
	);
}









void end_rotate(uint8_t id) {
	if(id == 1) { // forward
		check_end_stra_gait(RBpalBackAlphaTIM, RBpalBackBetaTIM, LBpalBackAlphaTIM, LBpalBackBetaTIM, LBstraForeAlphaTIM, LBstraForeBetaTIM, RBstraForeAlphaTIM, RBstraForeBetaTIM,
												RBstraForeAlphaTIM, RBstraForeBetaTIM, LBstraForeAlphaTIM, LBstraForeBetaTIM, LBpalBackAlphaTIM, LBpalBackBetaTIM, RBpalBackAlphaTIM, RBpalBackBetaTIM);
	} else if (id == 2) { // backward
		reverse_straight_gait();
		check_end_stra_gait(RBpalForeAlphaTIMRe, RBpalForeBetaTIMRe, LBpalForeAlphaTIMRe, LBpalForeBetaTIMRe, LBstraBackAlphaTIMRe, LBstraBackBetaTIMRe, RBstraBackAlphaTIMRe, RBstraBackBetaTIMRe,
												RBstraBackAlphaTIMRe, RBstraBackBetaTIMRe, LBstraBackAlphaTIMRe, LBstraBackBetaTIMRe, LBpalForeAlphaTIMRe, LBpalForeBetaTIMRe, RBpalForeAlphaTIMRe, RBpalForeBetaTIMRe);
	} else if (id == 3) { // left
		check_end_spin_gait(
			halfOutsideStraShoulderTIM1, RBhalfOutsideStraAlphaGaitTIM, RBhalfOutsideStraBetaGaitTIM,
			halfOutsidePalShoulderTIM2, LBhalfOutsidePalAlphaGaitTIM, LBhalfOutsidePalBetaGaitTIM,
			halfOutsideStraShoulderTIM1, LBhalfOutsideStraAlphaGaitTIM, LBhalfOutsideStraBetaGaitTIM,
			halfOutsidePalShoulderTIM2, RBhalfOutsidePalAlphaGaitTIM, RBhalfOutsidePalBetaGaitTIM,
		
			halfInsidePalShoulderTIM1, RBhalfInsidePalAlphaGaitTIM, RBhalfInsidePalBetaGaitTIM,
			halfInsideStraShoulderTIM2, LBhalfInsideStraAlphaGaitTIM, LBhalfInsideStraBetaGaitTIM,
			halfInsidePalShoulderTIM1, LBhalfInsidePalAlphaGaitTIM, LBhalfInsidePalBetaGaitTIM,
			halfInsideStraShoulderTIM2, RBhalfInsideStraAlphaGaitTIM, RBhalfInsideStraBetaGaitTIM
		);
	} else if (id == 4) { // right
		reverse_spin_gait();
		check_end_spin_gait(
			halfInsideStraShoulderTIM1Re, RBhalfInsideStraAlphaGaitTIMRe, RBhalfInsideStraBetaGaitTIMRe,
			halfInsidePalShoulderTIM2Re, LBhalfInsidePalAlphaGaitTIMRe, LBhalfInsidePalBetaGaitTIMRe,
			halfInsideStraShoulderTIM1Re, LBhalfInsideStraAlphaGaitTIMRe, LBhalfInsideStraBetaGaitTIMRe,
			halfInsidePalShoulderTIM2Re, RBhalfInsidePalAlphaGaitTIMRe, RBhalfInsidePalBetaGaitTIMRe,
		
			halfOutsidePalShoulderTIM1Re, RBhalfOutsidePalAlphaGaitTIMRe, RBhalfOutsidePalBetaGaitTIMRe,
			halfOutsideStraShoulderTIM2Re, LBhalfOutsideStraAlphaGaitTIMRe, LBhalfOutsideStraBetaGaitTIMRe,
			halfOutsidePalShoulderTIM1Re, LBhalfOutsidePalAlphaGaitTIMRe, LBhalfOutsidePalBetaGaitTIMRe,
			halfOutsideStraShoulderTIM2Re, RBhalfOutsideStraAlphaGaitTIMRe, RBhalfOutsideStraBetaGaitTIMRe
		);
	}
	id = 0;
}





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
		
		if(forward || left || right || back) {
			if (forward) {
				rotate_straight_forward();
				id = 1;
			} else if (left) {
				spin_left();
				id = 3;
			} else if (right) {
				spin_right();
				id = 4;
			} else {
				rotate_straight_backward();
				id = 2;
			}
		} else {
			end_rotate(id);
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
