#ifndef _pid_H
#define _pid_H

#include "stm32f10x.h"

typedef enum
{
	INIT,
	DONE,
}INIT_STATUS;

enum
{
	NOW_ERR = 0,
	LAST_ERR,
	LLAST_ERR,
};

typedef struct pid
{
	float set;
	float get;
	float error[3];
  
	float kp;
	float ki;
	float kd;
	
	float pout;
	float iout;
	float dout;
	float out; 
	
	
	int32_t maxout;
	int32_t integral_limit;
  float output_deadband;//����
	
	void (*f_pid_init)(struct pid *pid_t,
										float p,
										float i,
										float d,
										int32_t max_out,
										int32_t integral_limit);
	void (*f_pid_reset)(struct pid *pid_t,
										float p,
										float i,
										float d);
										
}pid_t;


float pid_calc(pid_t *pid,float get,float set);
float fuzzy_pid_calc(pid_t *pid, float get, float set);

void PID_Struct_Init(pid_t *pid,
										 float p,
										 float i,
										 float d,
										 int32_t max_out,
										 int32_t integral_limit,
										 INIT_STATUS init_status);


extern pid_t pid_spd[4];
extern pid_t pid_chassis_angle;
extern pid_t pid_rescue[3];
extern pid_t pid_rescue_spd[3];
extern pid_t pid_clamp[2];
extern pid_t pid_clamp_spd[2];
extern pid_t pid_clamp_attitude_adjustment;
extern pid_t pid_clamp_attitude_adjustment_spd;
extern pid_t pid_upraise[2];
extern pid_t pid_upraise_spd[2];
extern pid_t pid_barrier_carry[2];
extern pid_t pid_barrier_carry_spd[2];
extern pid_t pid_heat_limit;
extern pid_t pid_exchange;
extern pid_t pid_exchange_spd;
extern pid_t pid_slide[2];
extern pid_t pid_slide_spd[2];            
#endif
