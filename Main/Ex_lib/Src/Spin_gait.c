#include "stm32f1xx_hal.h"
#include "Spin_gait.h"
#include <stdint.h>

extern uint8_t leg2_12and3_34_spin_gait; 
extern uint8_t leg3_12and2_34_spin_gait; 
extern uint8_t begin_spin_gait;

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;

void check_begin_spin_gait(int* arr14, int* arr21, int* arr22, int* arr13, int* arr23, int* arr24, int* arr11, int* arr33, int* arr34, int* arr12, int* arr31, int* arr32) {
	for(int i = 0; i < 11; i++) {
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, arr14[i]);  // halfOutsidePalShoulderTIM1
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr21[i]);  // RBhalfOutsidePalAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr22[i]);  // RBhalfOutsidePalBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, arr13[i]);  // halfOutsideStraShoulderTIM2
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, arr23[i]);  // LBhalfOutsideStraAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, arr24[i]);  // LBhalfOutsideStraBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, arr11[i]);  // halfOutsidePalShoulderTIM1
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr33[i]);  // LBhalfOutsidePalAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr34[i]);  // LBhalfOutsidePalBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, arr12[i]);  // halfOutsideStraShoulderTIM2
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr31[i]);  // RBhalfOutsideStraAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arr32[i]);  // RBhalfOutsideStraBetaGaitTIM
		
		HAL_Delay(30);
	}
	HAL_Delay(50);
	
	begin_spin_gait = 1;
}

void first_step_spin_gait(int* arr14, int* arr21, int* arr22, int* arr13, int* arr23, int* arr24, int* arr11, int* arr33, int* arr34, int* arr12, int* arr31, int* arr32) {
	for(int i = 0; i < 11; i++) {
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, arr14[i]);  // fullStraShoulderTIM1
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr21[i]);  // RBfullStraAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr22[i]);  // RBfullStraBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, arr13[i]);  // fullPalShoulderTIM2
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, arr23[i]);  // LBfullPalAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, arr24[i]);  // LBfullPalBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, arr11[i]);  // fullStraShoulderTIM1
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr33[i]);  // LBfullStraAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr34[i]);  // LBfullStraBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, arr12[i]);  // fullPalShoulderTIM2
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr31[i]);  // RBfullPalAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arr32[i]);  // RBfullPalBetaGaitTIM

		HAL_Delay(30);
	}
	HAL_Delay(50);
	
	leg2_12and3_34_spin_gait = 2;  // when these leg just end stra rotation
	leg3_12and2_34_spin_gait = 1;  // when these leg just end pal rotation
}

void second_step_spin_gait(int* arr14, int* arr21, int* arr22, int* arr13, int* arr23, int* arr24, int* arr11, int* arr33, int* arr34, int* arr12, int* arr31, int* arr32) {
	for(int i = 0; i < 11; i++) {
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, arr14[i]);  // fullPalShoulderTIM1
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr21[i]);  // RBfullPalAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr22[i]);  // RBfullPalBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, arr13[i]);  // fullStraShoulderTIM2
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, arr23[i]);  // LBfullStraAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, arr24[i]);  // LBfullStraBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, arr11[i]);  // fullPalShoulderTIM1
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr33[i]);  // LBfullPalAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr34[i]);  // LBfullPalBetaGaitTIM
		
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, arr12[i]);  // fullStraShoulderTIM2
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr31[i]);  // RBfullStraAlphaGaitTIM
		__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arr32[i]);  // RBfullStraBetaGaitTIM
		
		HAL_Delay(30);
	}
	HAL_Delay(50);
	
	leg2_12and3_34_spin_gait = 1;  // when these leg just end pal rotation
	leg3_12and2_34_spin_gait = 2;  // when these leg just end stra rotation
}

void check_end_spin_gait(int* arr14, int* arr21, int* arr22, int* arr13, int* arr23, int* arr24, int* arr11, int* arr33, int* arr34, int* arr12, int* arr31, int* arr32,
                        int* arr14_2, int* arr21_2, int* arr22_2, int* arr13_2, int* arr23_2, int* arr24_2, int* arr11_2, int* arr33_2, int* arr34_2, int* arr12_2, int* arr31_2, int* arr32_2) {
	if(leg2_12and3_34_spin_gait == 1) {
		for(int i = 0; i < 11; i++) {
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, arr14[i]);   // halfOutsideStraShoulderTIM1
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr21[i]);   // RBhalfOutsideStraAlphaGaitTIM
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr22[i]);   // RBhalfOutsideStraBetaGaitTIM
				
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, arr13[i]);   // halfOutsidePalShoulderTIM2
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, arr23[i]);   // LBhalfOutsidePalAlphaGaitTIM
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, arr24[i]);   // LBhalfOutsidePalBetaGaitTIM
				
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, arr11[i]);   // halfOutsideStraShoulderTIM1
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr33[i]);   // LBhalfOutsideStraAlphaGaitTIM
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr34[i]);   // LBhalfOutsideStraBetaGaitTIM
				
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, arr12[i]);   // halfOutsidePalShoulderTIM2
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr31[i]);   // RBhalfOutsidePalAlphaGaitTIM
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arr32[i]);   // RBhalfOutsidePalBetaGaitTIM
				
				HAL_Delay(30);
		}
	} else if (leg3_12and2_34_spin_gait == 1) {
		for(int i = 0; i < 11; i++) {
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, arr14_2[i]);  // halfInsidePalShoulderTIM1
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, arr21_2[i]);  // RBhalfInsidePalAlphaGaitTIM
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_2, arr22_2[i]);  // RBhalfInsidePalBetaGaitTIM
				
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, arr13_2[i]);  // halfInsideStraShoulderTIM2
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_3, arr23_2[i]);  // LBhalfInsideStraAlphaGaitTIM
				__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_4, arr24_2[i]);  // LBhalfInsideStraBetaGaitTIM
				
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, arr11_2[i]);  // halfInsidePalShoulderTIM1
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_3, arr33_2[i]);  // LBhalfInsidePalAlphaGaitTIM
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_4, arr34_2[i]);  // LBhalfInsidePalBetaGaitTIM
				
				__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, arr12_2[i]);  // halfInsideStraShoulderTIM2
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, arr31_2[i]);  // RBhalfInsideStraAlphaGaitTIM
				__HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, arr32_2[i]);  // RBhalfInsideStraBetaGaitTIM
				
				HAL_Delay(30);
		}
	}
	
	leg2_12and3_34_spin_gait = 0;
	leg3_12and2_34_spin_gait = 0;
	begin_spin_gait = 0;
}

