/********************************/
/*      Proteus Test Code       */
/*     OSU FEH Spring 2020      */
/*        Drew Phillips         */
/*    02/03/20  Version 3.0.1     */
/********************************/

// AM 02/03/20

/* Include preprocessor directives */
#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHServo.h>
#include <FEHAccel.h>
#include <FEHBattery.h>
#include <FEHBuzzer.h>
#include <FEHSD.h>
#include <string.h>
#include <stdio.h>

#define redMinRange 0
#define redMaxRange 3.3
#define DEREES_PER_SECOND 47.2
#define INCHES_PER_SECOND 8.74613
#define ch1T1Angle 30
#define ch1M1Duration 1
#define ch1M1Power 30
#define ch1T2Angle -30
#define ch1M2Duration 2
#define ch1M2Power 30
#define ch1T3Angle -15
#define ch1T4Angle 30
#define ch1M3Duration 2
#define ch1M3Power 30
#define ch1T5Angle -30
#define ch1M4Duration 1
#define ch1M4Power 30

FEHMotor right_motor(FEHMotor::Motor2,7.2);
FEHMotor left_motor(FEHMotor::Motor3,7.2);
DigitalInputPin sensor(FEHIO::P0_0);

void movement(double distance){
    double time;
    if (distance < 0){
        time = -distance / INCHES_PER_SECOND;
        right_motor.SetPercent(70);
        left_motor.SetPercent(-70);
    }
    else{
        time = distance / INCHES_PER_SECOND;
        right_motor.SetPercent(-70);
        left_motor.SetPercent(70);
    }
    Sleep(time);
    right_motor.Stop();
    left_motor.Stop();
}
void turn(double angle){
    double percent;
    double time;
    if (angle < 0) {
        percent = -26.5;
        time = -angle / DEREES_PER_SECOND;
    } else {
        percent = 23.5;
        time = angle / DEREES_PER_SECOND;
    }

    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);
    Sleep(time);
    right_motor.Stop();
    left_motor.Stop();
}

void checkpointOne(){
    while(!(redMinRange < sensor.Value() && sensor.Value() < redMaxRange)){}
}

void getUpRamp(){
    right_motor.SetPercent(-93);
    left_motor.SetPercent(90);
    Sleep(2.0);
    right_motor.Stop();
    left_motor.Stop();
}


int main(){
    // Sleep(5.0);
    // movement(14);
    // Sleep(1.0);
    // turn(-45);
    // Sleep(1.0);
    // movement(8.5);
    // Sleep(1.0);
    // turn(90);
    // Sleep(1.0);
    // movement(6.5);
    // getUpRamp();

    Sleep(5.0);
    movement(5.75);
    Sleep(0.5);
    turn(135);
    Sleep(0.5);
    movement(8);
    turn(-90);
    Sleep(0.5);
    movement(8);
    getUpRamp();
    movement(1);
    turn(-20);
    movement(4);
    turn(-70);
    Sleep(0.5);
    movement(6.5);
    Sleep(0.5);
    turn(90);
    Sleep(0.5);
    movement(20);



    // Sleep(4.0);
    // turn(-90);
    // Sleep(1.0);
    // turn(90);
}
