# Insect-Robot
 Using Q-Learning to control the robot to turn  

## Introduction
 One IR sensor and two sonic sensor.  
 There are 18 motors with the robot.6 legs with 3 motors per leg.  
 IR sensor : to detect is there is wall in front of robot within 30 centimeters.  
 sonic sensor : to detect the closest wall in front of robot at the right and left hand side.  
## Q-Learning
 Divide the responses of sonic sensor into 10 parts.(0-10,10-20......80-90,>90)  
 Creat a 10*10*10 vector where -90<value<90.(<0 means turn left)  
 Using right and left sonic sensor as X and Y.  
 Pick the min val in (X,Y,Z) for Z in 0~9 as the degree that robot has to turn.  
 After the turn, using value of sonic sensor to check if it is parallel with wall.  
 If not, then multiply by a value in range -1<value<0.(Give a random value when it is 0.)  
## Demo
 Walk  
![](Walk.gif)  

 Turn  
![](Turn.gif)  
