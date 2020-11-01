#include "MIAT_InsectRobot.h"
#include "mbed.h"
#include "Ping.h"
#include "Pinmap.h"




void stand(void);
void Return_Stroke_raise(int legNumber, double angle, char n);
void Return_Stroke_down(int legNumber, char n);
void Power_Stroke(int legNumber, double angle, char n);
void rotate_R(int degree);
void rotate_L(int degree);
void f_wave();
InsectRobot insectRobot(PC_8, PA_5, PA_6, PB_8, PD_15, PC_7, PE_9, PE_11, PB_11, PC_9, PE_5, PB_15, PE_13, PF_8, PE_6, PB_5, PF_9, PF_7);
Ping Ultrasonic_L(D14);
Ping Ultrasonic_R(D10);
DigitalIn IRSensor(D8);
Serial pc(SERIAL_TX,SERIAL_RX);
int finish = 0;
int main() 
{
	srand( time(NULL) );
	int State[]={0,0,0};
	int QL[500]={50};
	int changeStateToRotate=0,changeStateToReward=0,changeStateToNormal=0;
	int IR;
	int range_L,range_R;
	IR = IRSensor.read();
	int SonicRange_L,SonicRange_R;
	int i =0 ;
	int num=0;
	int Degree=0;
	int point_Z=0,point_X=0,point_Y=0,point_value=-1;
	State[0]=1;
	//because rand() can't be used, so I set the initial value by myself 
	for(int counter=0;counter<100;counter++) {
		QL[counter]=-60;
		QL[counter+100]=-30;
		QL[counter+200]=0;
		QL[counter+300]=30;
		QL[counter+400]=60;
	}
	
	pc.printf("D:%d\n",QL[3]);
	stand();
	while(true){
		//-----change state-----
		if(State[0]==1 && changeStateToRotate==1){
			State[0]=0;
			State[1]=1;
			changeStateToRotate=0;
		}
		else if(State[1]==1 && changeStateToReward==1){
			State[1]=0;
			State[2]=1;
			changeStateToReward=0;
		}
		else if(State[2]==1 && changeStateToNormal==1){
			State[2]=0;
			State[0]=1;
			changeStateToNormal=0;
		}
		
		//--------NORMAL STATE--------
		if (State[0]==1){
			changeStateToNormal=0;
			f_wave();
			IR = IRSensor.read();
			if(IR==0){
				changeStateToRotate=1;
				pc.printf("There are something\n");
				stand();
				wait(0.1);
			}
		}
		//--------ROTATE STATE--------
		if (State[1]==1){
			//pc.printf("A\n");
			Ultrasonic_L.Send();
			Ultrasonic_R.Send();
			wait_ms(30);
			range_L = Ultrasonic_L.Read_cm();
			range_R = Ultrasonic_R.Read_cm();
			pc.printf("C\n");
			if(range_L>=130) point_X=9;
			else if(range_L<=30) point_X=0;
			else point_X=(range_L-30)/10;
			if(range_R>=130) point_Y=9;
			else if(range_R<=30) point_Y=0;
			else point_Y=(range_R-30)/10;
			pc.printf("%d  %d  %d  %d\n",range_L,range_R,point_X,point_Y);
			point_Z=0;
			point_value=-80;
			for(int counter=0;counter<5;counter++){
				if(QL[point_Y+10*point_X+100*counter]>point_value){
					point_Z=counter;
					point_value=QL[point_Y+10*point_X+100*counter];
				}
			}
			//pc.printf("B\n");
			pc.printf("D:%d\r\n",Degree);
			Degree=point_value;
			if(Degree>0) {
				while(Degree>30){
					rotate_R(30);
					Degree=Degree-30;
				}
				rotate_R(Degree);
			}
			else{ 
				while(Degree<-30){
					//pc.printf("E:%d\r\n",Degree);
					rotate_L(-30);
					Degree=Degree+30;
				}
				rotate_L(Degree);
			}
			stand();
			wait(0.1);
			pc.printf("rotate finish\r\n");
			changeStateToReward=1;
		}
		//--------REWARD STATE--------
		if (State[2]==1){
			IR = IRSensor.read();
			if(IR==0){
				QL[point_Y+10*point_X+100*point_Z]=10*QL[point_Y+10*point_X+100*point_Z]/8;
				if(QL[point_Y+10*point_X+100*point_Z]>80 || QL[point_Y+10*point_X+100*point_Z]<-80 || abs(QL[point_Y+10*point_X+100*point_Z])<5){
					//The best way is random another, but there is something problom,so we make it be the smallest
					//that others have oppotunity to be chosed.
					QL[point_Y+10*point_X+100*point_Z]=-81;
				}
				pc.printf("change value\n");
			}
			stand();
			wait(0.1);
			pc.printf("reward finish\r\n");
			changeStateToNormal=1;
		}
	}
	stand();
	return 0;
}

void stand(void){

//--------------���C���A����     --------//
     insectRobot.Set_servo(1, 0, 'r', 'a');
     insectRobot.Set_servo(1, -30, 'r', 'r');
		 insectRobot.Set_servo(1, -70, 'r', 'b');
	wait(0.1);
	   insectRobot.Set_servo(2, 0, 'r', 'a');
     insectRobot.Set_servo(2, -30, 'r', 'r');
		 insectRobot.Set_servo(2, -70, 'r', 'b');
	   wait(0.1);
	   insectRobot.Set_servo(3, 0, 'r', 'a');
     insectRobot.Set_servo(3, -30, 'r', 'r');
		 insectRobot.Set_servo(3, -70, 'r', 'b');
		 wait(0.1);
	   insectRobot.Set_servo(1, 0, 'l','a');
	   insectRobot.Set_servo(1, 30, 'l','r');
		 insectRobot.Set_servo(1, 70, 'l','b');
	  wait(0.1);
     insectRobot.Set_servo(2, 0, 'l','a');
	    insectRobot.Set_servo(2, 30, 'l','r');
		 insectRobot.Set_servo(2, 70, 'l','b');
	wait(0.1);
	   insectRobot.Set_servo(3, 0, 'l','a');
     insectRobot.Set_servo(3, 30, 'l', 'r');
		 insectRobot.Set_servo(3, 70, 'l','b');
//--------------���T�����毸��     --------//
//		 insectRobot.Set_servo(1, 50, 'r', 'a');
//     insectRobot.Set_servo(1, 30, 'r', 'r');
//		 insectRobot.Set_servo(1, 70, 'r', 'b');
//	
//	   insectRobot.Set_servo(2, 0, 'r', 'a');
//     insectRobot.Set_servo(2, 30, 'r', 'r');
//		 insectRobot.Set_servo(2, 70, 'r', 'b');
//	   
//	   insectRobot.Set_servo(3, -40, 'r', 'a');
//     insectRobot.Set_servo(3, 30, 'r', 'r');
//		 insectRobot.Set_servo(3, 70, 'r', 'b');
//		 
//	   insectRobot.Set_servo(1, -50, 'l','a');
//	   insectRobot.Set_servo(1, -30, 'l','r');
//		 insectRobot.Set_servo(1, -70, 'l','b');
//	  
//     insectRobot.Set_servo(2, 0, 'l','a');
//	   insectRobot.Set_servo(2, -30, 'l','r');
//		 insectRobot.Set_servo(2, -70, 'l','b');
//	
//	   insectRobot.Set_servo(3, 40, 'l','a');
//     insectRobot.Set_servo(3, -30, 'l', 'r');
//		 insectRobot.Set_servo(3, -70, 'l','b');
	wait(1);
}
void Return_Stroke_raise(int legNumber, double angle, char n){
	   
     
		 insectRobot.Set_servo(legNumber, 0, n, 'b');
	   if(n=='l'){
			insectRobot.Set_servo(legNumber, angle, n, 'a');
			insectRobot.Set_servo(legNumber, 30, n, 'r');
		 }
			else if(n=='r'){
			insectRobot.Set_servo(legNumber, -angle, n, 'a');
			insectRobot.Set_servo(legNumber, -30, n, 'r');
		}
	
}

void Return_Stroke_down(int legNumber, char n){
		
			if(n=='l'){
			insectRobot.Set_servo(legNumber, 70, n, 'b');
			insectRobot.Set_servo(legNumber, 30, n, 'r');
			}
			else if(n=='r'){
		  insectRobot.Set_servo(legNumber, -70, n, 'b');
			insectRobot.Set_servo(legNumber, -30, n, 'r');
			}
}
void Power_Stroke(int legNumber, double angle, char n){
			
			if(n=='l'){
			insectRobot.Set_servo(legNumber, angle, n, 'a');
			insectRobot.Set_servo(3, 70, n,'b');
			insectRobot.Set_servo(legNumber, 30, n, 'r');
			}
			else if(n=='r'){
			insectRobot.Set_servo(legNumber, -angle, n, 'a');
			insectRobot.Set_servo(3, -70, n,'b');
			insectRobot.Set_servo(legNumber, -30, n, 'r');
      }
}
void f_wave(){
	Return_Stroke_down(1,'l');
	Return_Stroke_down(2,'r');	
	Return_Stroke_down(3,'l');
	wait(0.1);
	Return_Stroke_raise(1, -30, 'r');
	Return_Stroke_raise(2, -50, 'l');
	Return_Stroke_raise(3, -30, 'r');
	wait(0.1);
	Return_Stroke_down(1,'r');
	Return_Stroke_down(2,'l');
	Return_Stroke_down(3,'r');
	wait(0.1);
	Return_Stroke_raise(1, -50, 'l');
	Return_Stroke_raise(2, -30, 'r');
	Return_Stroke_raise(3, -50, 'l');
	wait(0.1);
	Power_Stroke(1,0,'r');
	Power_Stroke(2,0,'l');
	Power_Stroke(3,0,'r');
	wait(0.1);
	Return_Stroke_down(1,'l');
	Return_Stroke_down(2,'r');
	Return_Stroke_down(3,'l');
	wait(0.1);
	Power_Stroke(1,0,'l');
	Power_Stroke(2,0,'r');
	Power_Stroke(3,0,'l');
	wait(0.1);
}

void rotate_R(int degree){
		Return_Stroke_down(1,'l');
		Return_Stroke_down(2,'r');	
		Return_Stroke_down(3,'l');
		wait(0.1);
		Return_Stroke_raise(1, degree, 'r');
		Return_Stroke_raise(2, -degree, 'l');
		Return_Stroke_raise(3, degree, 'r');
		wait(0.1);
		Return_Stroke_down(1,'r');
		Return_Stroke_down(2,'l');
		Return_Stroke_down(3,'r');
		wait(0.1);
		Return_Stroke_raise(1, -degree, 'l');
		Return_Stroke_raise(2,  degree, 'r');
		Return_Stroke_raise(3, -degree, 'l');
		wait(0.1);
		Power_Stroke(1,0,'r');
		Power_Stroke(2,0,'l');
		Power_Stroke(3,0,'r');
		wait(0.1);
		Return_Stroke_down(1,'l');
		Return_Stroke_down(2,'r');
		Return_Stroke_down(3,'l');
		wait(0.1);
		Power_Stroke(1,0,'l');
		Power_Stroke(2,0,'r');
		Power_Stroke(3,0,'l');
		wait(0.1);
}

void rotate_L(int degree){
		Return_Stroke_down(1,'l');
		Return_Stroke_down(2,'r');	
		Return_Stroke_down(3,'l');
		wait(0.1);
		Return_Stroke_raise(1, degree, 'r');
		Return_Stroke_raise(2, -degree, 'l');
		Return_Stroke_raise(3, degree, 'r');
		wait(0.1);
		Return_Stroke_down(1,'r');
		Return_Stroke_down(2,'l');
		Return_Stroke_down(3,'r');
		wait(0.1);
		Return_Stroke_raise(1, -degree, 'l');
		Return_Stroke_raise(2,  degree, 'r');
		Return_Stroke_raise(3, -degree, 'l');
		wait(0.1);
		Power_Stroke(1,0,'r');
		Power_Stroke(2,0,'l');
		Power_Stroke(3,0,'r');
		wait(0.1);
		Return_Stroke_down(1,'l');
		Return_Stroke_down(2,'r');
		Return_Stroke_down(3,'l');
		wait(0.1);
		Power_Stroke(1,0,'l');
		Power_Stroke(2,0,'r');
		Power_Stroke(3,0,'l');
		wait(0.1);
}