
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
AnalogInputPin CdsCell(FEHIO::P0_0);
DigitalEncoder left_encoder_dir(FEHIO::P0_7);
DigitalEncoder left_encoder_dis(FEHIO::P1_7);
DigitalEncoder right_encoder_dir(FEHIO::P3_0);
DigitalEncoder right_encoder_dis(FEHIO::P3_5);

int main(){
    left_encoder_dir.ResetCounts();
    left_encoder_dis.ResetCounts();
    right_encoder_dir.ResetCounts();
    right_encoder_dis.ResetCounts();
    
    left_motor.SetPercent(50);
    while (left_encoder_dis.Counts() < 360) {
        
    }
    left_motor.Stop();
}
