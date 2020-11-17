/**
 * IR control use one PWM pin to contr
 */

#include "platform_opts.h"

#include "sensor_service.h"
#include "ir_ctrl.h"

#include "pwmout_api.h"   // mbed

static pwmout_t pwm_ir_ctrl;

int ir_ctrl_init(void *param)
{
    pwmout_init(&pwm_ir_ctrl, PWM_IR_CTRL_PIN);
    pwmout_period_us(&pwm_ir_ctrl, PWM_PERIOD);
    pwmout_write(&pwm_ir_ctrl, 0);
    return 0;
}

int ir_ctrl_set_brightness(float brightness)
{
    pwmout_write(&pwm_ir_ctrl, brightness);
    return 0;
}