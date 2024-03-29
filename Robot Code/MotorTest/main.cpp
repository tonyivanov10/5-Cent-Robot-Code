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

#define DEREES_PER_SECOND 47.2
#define INCHES_PER_SECOND 8.74613
#define DEGREES_PER_TIC 2
#define CIRCUMFERENCE 8.639379797
#define AXLE_CIRCUMFERENCE 19.22654704
#define THEORETICAL_COUNTS_PER_INCH 20.8348
#define redMinRange .5
#define redMaxRange .75

FEHMotor right_motor(FEHMotor::Motor1,7.2);
FEHMotor left_motor(FEHMotor::Motor3,7.2);
AnalogInputPin CdsCell(FEHIO::P0_0);
DigitalEncoder left_encoder_dir(FEHIO::P0_7);
DigitalEncoder left_encoder_dis(FEHIO::P1_7);
DigitalEncoder right_encoder_dir(FEHIO::P3_0);
DigitalEncoder right_encoder_dis(FEHIO::P3_5);

void movement(double distance){

    //The number of tics the encoder needs to read.
    double tics = distance * THEORETICAL_COUNTS_PER_INCH;

    double percent = 60;

    //Formatting if the distance is negative.
    if(distance < 0) {
        tics *= -1;
        percent *= -1;
    }

    right_encoder_dis.ResetCounts();
    left_encoder_dis.ResetCounts();

    //Right motor travels backwards and left motor travels forward.
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(percent);

    while(right_encoder_dis.Counts() < tics && left_encoder_dis.Counts() < tics);

    //Stop the motors.
    right_motor.Stop();
    left_motor.Stop();
}

//Turning function
void turn(double angle){

    //The proportion of 360 the robot must turn.
    double proportion = angle / 360.0;

    //The desired distance on the axle circumference the robot must turn.
    double desiredDistance = proportion * AXLE_CIRCUMFERENCE;

    //The number of tics the robot must read to turn the desired distance.
    double tics = desiredDistance * THEORETICAL_COUNTS_PER_INCH;

    //The power of the motors.
    double percent = 25;

    //Formatting if the angle was negative.
    if (angle < 0) {
        tics *= -1;
        percent *= -1;
    }

    //Setting the encoder counts to zero.
    right_encoder_dis.ResetCounts();
    left_encoder_dis.ResetCounts();

    //Starting the motors.
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);
    
    //Run until the number of tics reaches the desired number of tics.
    while(right_encoder_dis.Counts() < tics && left_encoder_dis.Counts() < tics){}

    //Stop the motors.
    right_motor.Stop();
    left_motor.Stop();
}

//Main function
/**
 * NOTE: The theoretical counts per inch is a little too high causing the movement to overshoot 
 * by around .25-.75 inches. Chaning this would also impact the turning so it would be advised to 
 * increase the axle circumference a little bit.
*/
int main(){
    
    while(!(redMinRange < CdsCell.Value() && CdsCell.Value() < redMaxRange)){}

    //Move forward 5.75 inches.
    movement(5.75);
    Sleep(0.5);

    //Turn right 135 degrees.
    turn(135);
    Sleep(0.5);

    //Move forward 8 inches.
    movement(8);
    Sleep(.5);

    //Turn left 90 degrees.
    turn(-90);
    Sleep(0.5);

    //Move forward 8 inches.
    movement(8);

    //Move forward (up the ramp) 20 inches.
    movement(21);
    Sleep(.5);

    //Turn left 20 degree.
    turn(90);
    Sleep(.5);

    //Move forward 6.5 inches.
    movement(-7);
    Sleep(0.5);

    //Turn right 90 degrees.
    turn(-90);
    Sleep(0.5);

    //Move forward 20 inches (hit the boarding pass section).
    movement(-22);
    
}