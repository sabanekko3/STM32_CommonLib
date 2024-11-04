/*
 * pwm.hpp
 *
 *  Created on: Jun 25, 2024
 *      Author: gomas
 */

#ifndef PWM_HPP_
#define PWM_HPP_

#include "main.h"


namespace SabaneLib{

	class IPWM{
	public:
		virtual void operator()(float val) = 0;

		virtual ~IPWM(){}
	};

	////////////////////////////////////////////////////////////
	//Hardware PWM class////////////////////////////////////////
	////////////////////////////////////////////////////////////
#ifdef HAL_TIM_MODULE_ENABLED
	class PWMHard:public IPWM{
	private:
		TIM_HandleTypeDef *tim;
		const uint32_t ch;
	public:
		PWMHard(TIM_HandleTypeDef *_tim,uint32_t _ch)
			: tim(_tim),
			  ch(_ch){
		}

		void operator()(float duty) override{//0.0~1.0f
			__HAL_TIM_SET_COMPARE(tim, ch, tim->Init.Period*duty);
		}

		float get_duty(void){
			return static_cast<float>(__HAL_TIM_GET_COMPARE(tim, ch))/static_cast<float>(tim->Init.Period);
		}

		void start(void){
			HAL_TIM_PWM_Start(tim, ch);
			HAL_TIMEx_PWMN_Start(tim,ch);
			__HAL_TIM_SET_COMPARE(tim, ch,0);
		}

		void stop(void){
			HAL_TIM_PWM_Stop(tim, ch);
			HAL_TIMEx_PWMN_Stop(tim,ch);
			__HAL_TIM_SET_COMPARE(tim, ch,0);
		}

	};
#endif //HAL_TIM_MODULE_ENABLED
}

#endif /* PWM_HPP_ */
