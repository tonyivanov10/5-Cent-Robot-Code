// Team C5

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
#define redMinRange 0.0
#define redMaxRange 0.8
#define blueMinRange 1.6
#define blueMaxRange 2.4
#define LUGGAGE_SERVO_MIN 500
#define LUGGAGE_SERVO_MAX 2425
#define ARM_SERVO_MIN 500
#define ARM_SERVO_MAX 2500

FEHMotor right_motor(FEHMotor::Motor1,7.2);
FEHMotor left_motor(FEHMotor::Motor3,7.2);
AnalogInputPin CdsCell(FEHIO::P0_0);
DigitalEncoder left_encoder_dir(FEHIO::P0_7);
DigitalEncoder left_encoder_dis(FEHIO::P1_7);
DigitalEncoder right_encoder_dir(FEHIO::P3_0);
DigitalEncoder right_encoder_dis(FEHIO::P3_5);
FEHServo ArmServo(FEHServo:: Servo0);
FEHServo LuggageServo(FEHServo:: Servo7);

enum ColorLight {
    RED_LIGHT,
    BLUE_LIGHT
};

void moveBothMotors(double distance, double percent){

    //The number of tics the encoder needs to read.
    double tics = distance * THEORETICAL_COUNTS_PER_INCH;

    //Formatting if the distance is negative.
    if(distance < 0) {
        tics *= -1;
        percent *= -1;
    }

    percent = (11.5 / Battery.Voltage()) * percent;
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

void moveRightMotor(double distance, double percent) {

    //The number of tics the encoder needs to read.
    double tics = distance * THEORETICAL_COUNTS_PER_INCH;

    //Formatting if the distance is negative.
    if(distance < 0) {
        tics *= -1;
        percent *= -1;
    }

    percent = (11.5 / Battery.Voltage()) * percent;
    right_encoder_dis.ResetCounts();

    //Right motor travels backwards and left motor travels forward.
    right_motor.SetPercent(-percent);

    while(right_encoder_dis.Counts() < tics);

    //Stop the motors.
    right_motor.Stop();
}

void moveLeftMotor(double distance, double percent) {

    //The number of tics the encoder needs to read.
    double tics = distance * THEORETICAL_COUNTS_PER_INCH;

    //Formatting if the distance is negative.
    if(distance < 0) {
        tics *= -1;
        percent *= -1;
    }
    left_encoder_dis.ResetCounts();

    percent = (11.5 / Battery.Voltage()) * percent;
    //Right motor travels backwards and left motor travels forward.
    left_motor.SetPercent(percent);

    while(left_encoder_dis.Counts() < tics);

    //Stop the motors.
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

    percent = (11.5 / Battery.Voltage()) * percent;
    
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

void waitForInitiationLight() {
    while(!(redMinRange < CdsCell.Value() && CdsCell.Value() < redMaxRange)){}
}

void driveToKioskLight() {
    moveLeftMotor((2*AXLE_CIRCUMFERENCE/4), 40);
    Sleep(1.0);
    moveBothMotors(3, 60);
    Sleep(1.0);
    moveRightMotor((2*AXLE_CIRCUMFERENCE/8 + .5), 40);
    Sleep(1.0);
    turn(180);
    Sleep(1.0);
    moveBothMotors(-21, 90);
    Sleep(1.0);
    moveLeftMotor(-(((45/360.0)*2*AXLE_CIRCUMFERENCE)), 40);
    Sleep(1.0);
    moveBothMotors(-30,60);
    moveBothMotors(3,60);
}

void driveAndTouchKioskButton(ColorLight lightColor) {
    if (lightColor == RED_LIGHT) {
        LCD.Write("RED");
        LCD.Write(CdsCell.Value());
        moveBothMotors(10, 60);
        moveLeftMotor(6, 40);
        moveBothMotors(-15.5, 60);
    }
    else {
        LCD.Write("BLUE");
        LCD.Write(CdsCell.Value());
        moveBothMotors(6, 60);
        moveLeftMotor(4.5, 40);
        moveBothMotors(-11, 60);
    }
}

void driveDownRamp(ColorLight lightColor) {
    moveBothMotors(11,60);
    turn(90);

    if (lightColor == RED_LIGHT) {
        moveBothMotors(6, 60);
    }
    else {
        moveBothMotors(4, 60);
    }

    moveRightMotor((2*AXLE_CIRCUMFERENCE / 4), 40);
    moveBothMotors(25, 60);
}

ColorLight readKioskLight() {
    ColorLight lightRead;
    while(!((redMinRange < CdsCell.Value() && CdsCell.Value() < redMaxRange) || (blueMinRange < CdsCell.Value() && CdsCell.Value() < blueMaxRange)))
    {
        LCD.WriteLine(CdsCell.Value());
    }

    if (redMinRange < CdsCell.Value() && CdsCell.Value() < redMaxRange) {
        lightRead = RED_LIGHT;
        LCD.WriteLine(lightRead);
    }
    else if (blueMinRange < CdsCell.Value() && CdsCell.Value() < blueMaxRange){
        lightRead = BLUE_LIGHT;
        LCD.WriteLine("0");
        LCD.WriteLine(lightRead);
    }
    else {
        lightRead = BLUE_LIGHT;
        LCD.WriteLine("1");
        LCD.WriteLine(lightRead);
    }
    return lightRead;
}

//Main function
/**
 * NOTE: The theoretical counts per inch is a little too high causing the movement to overshoot 
 * by around .25-.75 inches. Chaning this would also impact the turning so it would be advised to 
 * increase the axle circumference a little bit.
*/
int main(){
    ArmServo.SetMin(ARM_SERVO_MIN);
    ArmServo.SetMax(ARM_SERVO_MAX);
    Sleep(1.0);
    ArmServo.SetDegree(0);
    Sleep(1.0);
    ArmServo.SetDegree(180);
         // Initialize the RCS
    /*RCS.InitializeTouchMenu("B7p93noDy");
    // Get correct lever from the RCS
    int correctLever = RCS.GetCorrectLever();*/
     int correctLever = 1;
    // Check which lever to flip and perform some action
    if(correctLever == 0)
    {
        // Perform actions to flip left lever
        moveBothMotors(2,60);
        Sleep(1.0);
        turn(45);
        Sleep(1.0);
        moveBothMotors(6,60);
        Sleep(1.0);
        turn(-120);
        Sleep(1.0);
        moveBothMotors(3,60);
        Sleep(1.0);
        turn(-100);
        Sleep(1.0);
        moveBothMotors(4.5,60);
        Sleep(1.0);
        ArmServo.SetDegree(70);
        Sleep(5.0);
        moveBothMotors(-5,60);
        Sleep(1.0);
        ArmServo.SetDegree(60);
        Sleep(1.0);
        moveBothMotors(6,60);
        Sleep(1.0);
        ArmServo.SetDegree(160);
    } 
    else if(correctLever == 1)
    {
        // Perform actions to flip middle lever
    moveBothMotors(3,60);
        Sleep(1.0);
        turn(45);
        Sleep(1.0);
        moveBothMotors(6,60);
        Sleep(1.0);
        turn(-95);
        Sleep(1.0);
        moveBothMotors(14,60);
        LCD.SetBackgroundColor(BLACK);
        LCD.WriteLine(right_encoder_dis.Counts());
        LCD.WriteLine(left_encoder_dis.Counts());
        Sleep(1.0);
        turn(-95);
        Sleep(1.0);
        moveBothMotors(0.5,60);
        Sleep(1.0);
        ArmServo.SetDegree(70);
        Sleep(5.0);
        moveBothMotors(-5,60);
        Sleep(1.0);
        ArmServo.SetDegree(60);
        Sleep(1.0);
        turn(3);
        Sleep(1.0);
        moveBothMotors(6,60);
        Sleep(1.0);
        ArmServo.SetDegree(180);
    }
    else if(correctLever == 2)
    {
       // Perform actions to flip right lever
        moveBothMotors(2,60);
        Sleep(1.0);
        turn(45);
        Sleep(1.0);
        moveBothMotors(6,60);
        Sleep(1.0);
        turn(-120);
        Sleep(1.0);
        moveBothMotors(3,60);
        Sleep(1.0);
        turn(-100);
        Sleep(1.0);
        moveBothMotors(4.5,60);
        Sleep(1.0);
        ArmServo.SetDegree(70);
        Sleep(5.0);
        moveBothMotors(-5,60);
        Sleep(1.0);
        ArmServo.SetDegree(60);
        Sleep(1.0);
        moveBothMotors(6,60);
        Sleep(1.0);
        ArmServo.SetDegree(180);
    }

}