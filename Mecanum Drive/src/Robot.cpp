#include "WPILib.h"
#include "string"
#include <cmath>

class FYRERobot: public IterativeRobot
{

	RobotDrive *m_robotDrive;		// RobotDrive object using PWM 1-4 for drive motors
	Joystick *m_driveStick;         // Joystick object on USB port 1 (mecanum drive)
	Talon *m_robotLift;
	Joystick *m_liftStick;
	/*Encoder *m_liftEncoder;
	Encoder *m_leftEncoder;
	Encoder *m_rightEncoder;*/
	DigitalInput *m_topLimitSwitch;
	DigitalInput *m_bottomLimitSwitch;
	Compresser *m_compresser;
	Solenoid *m_solenoid
	float rightXboxY;
	bool rightBumper;
	bool m_topLimit;
	bool m_bottomLimit;
	float driveStickX;
	float driveStickY;
	float driveThrottle;

public:

	FYRERobot(void)
	{

		// Create a RobotDrive object using PWMS 1, 2, 3, and 4
		m_robotDrive = new RobotDrive(0, 1);
		// Define joystick being used at USB port #1 on the Drivers Station
		m_driveStick = new Joystick(0);
		// Twist is on Axis 3 for the Extreme 3D Pro
		m_driveStick->SetAxisChannel(Joystick::kTwistAxis, 3);
		// Create a RobotDrive object using PWMS 5
		m_robotLift = new Talon(2);
		/*m_liftEncoder = new Encoder(0, 1);
		m_liftEncoder -> SetDistancePerPulse(42069);
		m_leftEncoder = new Encoder(2,3);
		m_leftEncoder -> SetDistancePerPulse(42069);
		m_rightEncoder = new Encoder(4,5);
		m_rightEncoder -> SetDistancePerPulse(42069);
		m_compresser = new Compresser (4,2);
		m_solenoid = new Solenoid (1,1)*/
		// Define joystick being used at USB port #2 on the Drivers Station
		m_liftStick = new Joystick(1);
		// Define two swtiches
		m_topLimitSwitch = new DigitalInput(4);
		m_bottomLimitSwitch = new DigitalInput(5);


		//the camera name (ex "cam0") can be found through the roborio web interface

	}

private:
	LiveWindow *lw;

	void RobotInit()
	{
		/*CameraServer::GetInstance()->SetQuality(50);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");*/
		LiveWindow.addActuator("Drive Train", "Left", new Jaguar(0));
		LiveWindow.addActuator("Drive Train", "Right", new Jaguar(1));
		LiveWindow.addActuator("Lift Arm", "Motor", new Talon(2));
		LiveWindow.addActuator("Lift Arm", "Brakes", new Solenoid(1,1));
		lw = LiveWindow::GetInstance();
	}

	void AutonomousInit()
	{
		/*//liftEncoder->Reset();
		// lift box
		m_robotLift->Set(.5);
		Wait(1000);
		// while(m_liftEncoder<=1000) {
		// m_robotLift->Set(.5)
		//Wait(20)}
		m_robotLift->Set(0);

		//drive forward
		m_robotDrive->Drive(.5, 0);
		Wait(8000);
		m_robotDrive->Drive(0,0);

		// lower box
		m_robotLift->Set(-.5);
		Wait(1000);
		// while(m_liftEncoder>=500) {
		// m_robotLift->Set(.5)
		// Wait(20)}
		m_robotLift->Set(0);

		// drive backward
		m_robotDrive->Drive(-.5,0);
		Wait(1000);
		m_robotDrive->Drive(0,0);*/

		//liftEncoder -> Reset();
		//leftEncoder -> Reset();
		//rightEncoder -> Reset();
/*
		while(m_liftEncoder->Get()<18){
			m_robotLift -> Set(.5);
		}

		while(m_leftEncoder->Get()<117 && m_rightEncoder->Get()<117){
			m_robotDrive -> Drive(.5,0);
		}

		while(m_bottomLimitSwitch->Get() == false){
			m_robotLift -> Set(-.5);
		}

		while(m_leftEncoder->Get()>100 && m_rightEncoder->Get()<100){
			m_robotDrive -> Drive(-.5,0);
		}
*/
	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

		//m_liftEncoder->Reset();
		//m_compresser->Start();

	}

	void TeleopPeriodic()
	{
		// Update Variables
		rightXboxY = m_liftStick->GetRawAxis(5);
		rightBumper = m_liftStick->GetRawButton(6);
		m_topLimit = m_topLimitSwitch->Get();
		m_bottomLimit = m_bottomLimitSwitch->Get();
		driveStickX = (m_driveStick->GetX())*-1;
		driveStickY = m_driveStick->GetY();
		driveThrottle = (((((m_driveStick->GetThrottle())*-1)+1)/4)+.5);

		/*if (abs(driveStickX)>.5){
		}
		else
		{
			driveStickX = 0;
		}

		driveStickX = driveStickX * driveThrottle;
		driveStickY = driveStickY * driveThrottle;

		m_robotDrive->ArcadeDrive(driveStickY, driveStickX);*/

		/*if(m_bottomLimit == 1 && rightXboxY<=0){

			m_robotLift->Set(0);

		}
		else if(m_topLimit == 1 && rightXboxY >=0){

			m_robotLift->Set(0);

		}
		else{
			if (rightXboxY >= 0.2 || rightXboxY <= -0.2){
				m_robotLift->Set(rightXboxY);
			}
			else
			{
				m_robotLift->Set(0);
			}
		}*/
		m_robotLift->Set(rightXboxY);
	/*	if (rightBumper == true){

			m_robotLift->Set(rightXboxY);

		}*/
		//printf("%F",rightXboxY);
		printf("%F\n",rightXboxY);

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(FYRERobot);
