#include "stm32f1xx_hal.h"
#include "Straight_gait.h"
#include <stdint.h>

extern uint8_t begin_stra_gait;
extern uint8_t leg2_12and3_34_stra_gait;
extern uint8_t leg3_12and2_34_stra_gait;

extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void check_begin_stra_gait(int* arr21, int* arr22, int* arr33, int* arr34, int* arr23, int* arr24, int* arr31, int* arr32) {
	for(int i = 0; i < 11; i++) {
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr21[i]); // RBpalForeAlphaTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr22[i]); // RBpalForeBetaTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr33[i]); // LBpalForeAlphaTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr34[i]); // LBpalForeBetaTIM
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, arr23[i]); // LBstraBackAlphaTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, arr24[i]); // LBstraBackBetaTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr31[i]); // RBstraBackAlphaTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arr32[i]); // RBstraBackBetaTIM
		HAL_Delay(20);
	}
	HAL_Delay(50);
	
	begin_stra_gait = 1;
}

void first_step_stra_gait(int* arr21, int* arr22, int* arr33, int* arr34, int* arr23, int* arr24, int* arr31, int* arr32) {
	for(int i = 0; i < 11; i++) {
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr21[i]); // RBstraAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr22[i]); // RBstraBetaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr33[i]); // LBstraAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr34[i]); // LBstraBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, arr23[i]); // LBpalAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, arr24[i]); // LBpalBetaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr31[i]); // RBpalAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arr32[i]); // RBpalBetaGaitTIM
		
		HAL_Delay(20);
	}
	
	leg2_12and3_34_stra_gait = 2;
	leg3_12and2_34_stra_gait = 1;
	
	HAL_Delay(50);
}

void second_step_stra_gait(int* arr21, int* arr22, int* arr33, int* arr34, int* arr23, int* arr24, int* arr31, int* arr32) {
	for(int i = 0; i < 11; i++) {
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr21[i]); // RBpalAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr22[i]); // RBpalBetaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr33[i]); // LBpalAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr34[i]); // LBpalBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, arr23[i]); // LBstraAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, arr24[i]); // LBstraBetaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr31[i]); // RBstraAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arr32[i]); // RBstraBetaGaitTIM
		
		HAL_Delay(20);
	}
	
	leg2_12and3_34_stra_gait = 1;
	leg3_12and2_34_stra_gait = 2;
	
	HAL_Delay(50);
}

void check_end_stra_gait(int* arr21, int* arr22, int* arr33, int* arr34, int* arr23, int* arr24, int* arr31, int* arr32, 
												 int* arr21_2, int* arr22_2, int* arr33_2, int* arr34_2, int* arr23_2, int* arr24_2, int* arr31_2, int* arr32_2) {
	if(leg3_12and2_34_stra_gait == 1) {
		for(int i = 0; i < 11; i++) {
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr21[i]); // RBpalBackAlphaTIM
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr22[i]); // RBpalBackBetaTIM
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr33[i]); // LBpalBackAlphaTIM
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr34[i]); // LBpalBackBetaTIM
			
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, arr23[i]); // LBstraForeAlphaTIM
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, arr24[i]); // LBstraForeBetaTIM
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr31[i]); // RBstraForeAlphaTIM
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arr32[i]); // RBstraForeBetaTIM
			
			HAL_Delay(20);
		}
	} else if (leg2_12and3_34_stra_gait == 1) {
		for(int i = 0; i < 11; i++) {
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr21_2[i]); // RBstraForeAlphaTIM
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr22_2[i]); // RBstraForeBetaTIM
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr33_2[i]); // LBstraForeAlphaTIM
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr34_2[i]); // LBstraForeBetaTIM
			
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, arr23_2[i]); // LBpalBackAlphaTIM
			__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, arr24_2[i]); // LBpalBackBetaTIM
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr31_2[i]); // RBpalBackAlphaTIM
			__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arr32_2[i]); // RBpalBackBetaTIM
			
			HAL_Delay(20);
		}
	}
	leg2_12and3_34_stra_gait = 0;
	leg3_12and2_34_stra_gait = 0;
	begin_stra_gait = 0;
}



