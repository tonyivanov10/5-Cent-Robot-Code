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
#define ch1T1Angle 30`
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
#define DEGREES_PER_TIC 4
#define CIRCUMFERENCE 8.639379797
#define redMinRange .5
#define redMaxRange .75

FEHMotor right_motor(FEHMotor::Motor1,7.2);
FEHMotor left_motor(FEHMotor::Motor3,7.2);
AnalogInputPin sensor(FEHIO::P0_0);
DigitalEncoder right_encoder(FEHIO::P0_5);
DigitalEncoder left_encoder(FEHIO::P0_3);



void movement(double distance){
    double revolutions = distance / CIRCUMFERENCE;
    double tics = revolutions * 360 / DEGREES_PER_TIC;
    double percent = 70;

    if(distance < 0) {
        tics *= -1;
        percent *= -1;
    }

    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    right_motor.SetPercent(-percent);
    left_motor.SetPercent(percent);

    while(right_encoder.Counts() < tics && left_encoder.Counts() < tics);

    right_motor.Stop();
    left_motor.Stop();
}
void turn(double angle){
    double tics = angle / DEGREES_PER_TIC;
    double percent = 25;
    if (angle < 0) {
        tics += -1;
        percent *= -1;
    }

    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);
    
    while(right_encoder.Counts() < tics && left_encoder.Counts() < tics);

    right_motor.Stop();
    left_motor.Stop();
}


int main(){
    while(!(redMinRange < sensor.Value() && sensor.Value() < redMaxRange)){}

    Sleep(5.0);
    movement(5.75);
    Sleep(0.5);

    movement(5.75);
    Sleep(0.5);
    turn(135);
    Sleep(0.5);
    movement(8);
    turn(-90);
    Sleep(0.5);
    movement(8);
    // getUpRamp();
    movement(20);
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
}
