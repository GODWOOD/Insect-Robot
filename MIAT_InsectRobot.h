/*MIAT InsectaRobot Library*/

#ifndef InsectRobot_H
#define InsectRobot_H

#include "mbed.h"
 
class InsectRobot
{
	private:
		PwmOut r1_a;
	  PwmOut r1_b;
	  PwmOut r1_r;
	
	  PwmOut r2_a;
	  PwmOut r2_b;
	  PwmOut r2_r;
	
	  PwmOut r3_a;
	  PwmOut r3_b;
	  PwmOut r3_r;
	
	  PwmOut l1_a;
	  PwmOut l1_b;
	  PwmOut l1_r;
	
	  PwmOut l2_a;
	  PwmOut l2_b;
	  PwmOut l2_r;
	
	  PwmOut l3_a;
	  PwmOut l3_b;
	  PwmOut l3_r;
//		TCS3200 tcs3200;
	
	  double period;
		double r1_aPwmRegister;
		double r1_bPwmRegister;
		double r1_rPwmRegister;
		double r2_aPwmRegister;
		double r2_bPwmRegister;
		double r2_rPwmRegister;
		double r3_aPwmRegister;
		double r3_bPwmRegister;
		double r3_rPwmRegister;
		double l1_aPwmRegister;
		double l1_bPwmRegister;
		double l1_rPwmRegister;
		double l2_aPwmRegister;
		double l2_bPwmRegister;
		double l2_rPwmRegister;
		double l3_aPwmRegister;
		double l3_bPwmRegister;
		double l3_rPwmRegister;
	
	public:
//		int red, green, blue, clear;
//		DigitalOut led;
    InsectRobot(PinName s1, PinName s2, PinName s3, PinName s4, PinName s5, PinName s6, PinName s7, PinName s8, PinName s9, PinName s10, PinName s11, PinName s12, PinName s13, PinName s14, PinName s15, PinName s16, PinName s17, PinName s18);
		void robotInit();

//		void stand();
//	  void Wave_Gait();
//	  void Ripple_Gait();
//	  void Tripod_Gait();
//	  void Turn_right();
//	  void Turn_left();
//	  void Return_Stroke_raise(int legNumber, double angle, char n);
//	  void Return_Stroke_down(int legNumber, char n);
//	  void Power_Stroke(int legNumber, double angle, char n);
		void Set_servo(int legNumber, double angle, char n, char c);

			
};

#endif