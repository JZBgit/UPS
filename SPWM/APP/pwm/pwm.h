#ifndef _pwm_H
#define _pwm_H

#include "system.h"

void TIM1_PWM_Init(void);
void TIM3_PWM_Init(u16 per,u16 psc);

#endif
