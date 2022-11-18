#include "PIDdrv.h"

void PID_init(float K_p, float K_i, float K_d, float timestep, struct PID_DATA *pid){
    pid->K_p = K_p;
    pid->K_i = K_i;
    pid->K_d = K_d;
    pid->prev_error = 0;
    pid->error = 0;
    pid->timestep = timestep;
}

int PID_ctrl(int input, int current_value, struct PID_DATA *pid){
    int error, p_calc, i_calc, d_calc, error_temp, calc; 
    //Get the difference between the chosen input and the encoder value
    error = input - current_value;
	//Calculate the contribution from K_p
    p_calc = pid->K_p * error;
    //Calculate the contribution from K_i over the chosen timestep
    i_calc = pid->K_i*pid->timestep * pid->error;
    //Calculate the contribution from K_D over the chosen timestep
    d_calc = (pid->K_d / pid->timestep) * (error - pid->prev_error);
    //Save the value to be used in the next iteration
    pid->prev_error = current_value;
    //Add all the contributions up
    calc = p_calc + i_calc + d_calc;
    //Make sure the output isn't higher than the motor can handle
    if (calc > MAX_OUTPUT) {
        calc = MAX_OUTPUT;
    }
    else if (calc < -MAX_OUTPUT) {
        calc = -MAX_OUTPUT;
    }
    return calc;

}