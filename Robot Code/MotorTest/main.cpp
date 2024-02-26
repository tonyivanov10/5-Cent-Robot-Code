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
#define degreesPerSecond 30
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

FEHMotor right_motor(FEHMotor::Motor2,9.0);
FEHMotor left_motor(FEHMotor::Motor3,9.0);
DigitalInputPin sensor(FEHIO::P0_0);

void movement(double duration, int power){
    right_motor.SetPercent(-power);
    left_motor.SetPercent(power);
    Sleep(duration);
    right_motor.Stop();
    left_motor.Stop();
}
void turn(double angle){
    right_motor.SetPercent(25);
    left_motor.SetPercent(25);
    double time = angle / degreesPerSecond;
    Sleep(time);
    right_motor.Stop();
    left_motor.Stop();
}
void checkpointOne(){
    while(!(redMinRange < sensor.Value() && sensor.Value() < redMaxRange)){}
    turn(ch1T1Angle);
    movement(ch1M1Duration,ch1M1Power);
    turn(ch1T2Angle);
    movement(ch1M2Duration,ch1M2Power);
    turn (ch1T3Angle);
    movement(ch1M3Duration,ch1M3Power);
    turn(ch1T4Angle);
    turn(ch1T5Angle);
    movement(ch1M4Duration,ch1M4Power);
}

int main(){
    Sleep(5.0);
    right_motor.SetPercent(25);
    left_motor.SetPercent(25);
    Sleep(10.0);
    right_motor.Stop();
    left_motor.Stop();
}
