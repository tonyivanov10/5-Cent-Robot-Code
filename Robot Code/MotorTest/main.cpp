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
#define DEGREES_PER_TIC 4
#define CIRCUMFERENCE 8.639379797
#define AXLE_CIRCUMFERENCE 18.06415776
#define redMinRange .5
#define redMaxRange .75

FEHMotor right_motor(FEHMotor::Motor1,7.2);
FEHMotor left_motor(FEHMotor::Motor3,7.2);
AnalogInputPin sensor(FEHIO::P0_0);
DigitalEncoder right_encoder(FEHIO::P0_5);
DigitalEncoder left_encoder(FEHIO::P0_3);

//Movement function
void movement(double distance){
    //The number of revolutions the wheel needs to travel.
    double revolutions = distance / CIRCUMFERENCE;
    //The number of tics the encoder needs to read.
    double tics = revolutions * 360 / DEGREES_PER_TIC;
    //The power of the motors.
    double percent = 70;

    //Formatting if the distance is negative.
    if(distance < 0) {
        tics *= -1;
        percent *= -1;
    }

    //Reset the analog encoder tics to zero.
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Right motor travels backwards and left motor travels forward.
    right_motor.SetPercent(-percent);
    left_motor.SetPercent(percent);

    //Run until the number of tics on the encoder reaches the outlined number (distance).
    while(right_encoder.Counts() < tics && left_encoder.Counts() < tics){}

    //Stop the motors.
    right_motor.Stop();
    left_motor.Stop();
}

//Turning function
void turn(double angle){

    //The proportion of 360 the robot must turn.
    double proportion = angle / 360;

    //The desired distance on the axle circumference the robot must turn.
    double desiredDistance = proportion * AXLE_CIRCUMFERENCE;

    //The distance each wheel travels per tic.
    double wheelDistancePerTic = CIRCUMFERENCE * (DEGREES_PER_TIC/360.0);

    //The number of tics the robot must read to turn the desired distance.
    double tics = (desiredDistance / 2) / wheelDistancePerTic;

    //The power of the motors.
    double percent = 25;

    //Formatting if the angle was negative.
    if (angle < 0) {
        tics += -1;
        percent *= -1;
    }

    //Setting the encoder counts to zero.
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Starting the motors.
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);
    
    //Run until the number of tics reaches the desired number of tics.
    while(right_encoder.Counts() < tics && left_encoder.Counts() < tics){}

    //Stop the motors.
    right_motor.Stop();
    left_motor.Stop();
}

//Main function
int main(){
    //Wait until the starting light.
    while(!(redMinRange < sensor.Value() && sensor.Value() < redMaxRange)){}
    Sleep(1.0);

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
    turn(-20);
    Sleep(.5);

    //Move forward 4 inches.
    movement(4);
    Sleep(.5);

    //Turn left 70 degrees.
    turn(-70);
    Sleep(0.5);

    //Move forward 6.5 inches.
    movement(6.5);
    Sleep(0.5);

    //Turn right 90 degrees.
    turn(90);
    Sleep(0.5);

    //Move forward 20 inches (hit the boarding pass section).
    movement(20);
}
