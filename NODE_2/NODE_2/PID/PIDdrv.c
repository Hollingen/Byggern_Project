#include "PIDdrv.h"

void PID_init(float K_p, float K_i, float K_d, float timestep, int max_calc, struct PID_DATA *pid){
    pid->K_p = K_p;
    pid->K_i = K_i;
    pid->K_d = K_d;
    pid->prev_error = 0;
    pid->error = 0;
    pid->timestep = timestep;
}

int PID_ctrl(int input, int current_value, struct PID_DATA *pid){
    int error, p_calc, i_calc, d_calc, error_temp, calc; 

    error = input - current_value;

    p_calc = pid->K_p * error;

    i_calc = pid->K_i*pid->timestep * pid->error;


    pid->prev_error = current_value;

    calc = p_calc + i_calc + d_calc;

    if (calc > pid->max_calc) {
        calc = pid->max_calc;
    }
    else if (calc < -pid->max_calc) {
        calc = -pid->max_calc;
    }

    return calc;

}