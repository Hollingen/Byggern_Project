#ifndef PIDDRV_H_
#define PIDDRV_H_

#define MAX_OUTPUT MAX_INT


typedef struct PID_DATA{
    float K_p;
    float K_i;
    float K_d;
    int error;
    int prev_error;
    int timestep;
    int max_calc;

} pidData_t;

void PID_init(float K_p, float K_i, float K_d, float timestep, int max_calc, struct PID_DATA *pid);
int PID_ctrl(int input, int current_value, struct PID_DATA *pid);

#endif