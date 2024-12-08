#include"Motor.h"
#include<stdint.h>
#include"stm32f1xx_hal.h"
#include"gpio.h"
#include"tim.h"

void MotorLSetPWM(int32_t pwm_val){
    if(pwm_val > 0){
        //set motor to forward
        //set pwm value
        HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
    }
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_1, pwm_val);
}

void MotorRSetPWM(int32_t pwm_val){
    if(pwm_val > 0){
        //set motor to forward
        //set pwm value                                                                                                                                                                                     
        HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
        HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
    }else{
        HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
    }
    __HAL_TIM_SetCompare(&htim1, TIM_CHANNEL_4, pwm_val);
}
