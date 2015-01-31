#include "WPILib.h"
#include "string"
#include <cmath>

class FYRERobot: public IterativeRobot
{

	RobotDrive *m_robotDrive;		// RobotDrive object using PWM 1-4 for drive motors
	Joystick *m_driveStick;         // Joystick object on USB port 1 (mecanum drive)
	Talon *m_robotLift;
	Joystick *m_liftStick;
	Encoder *m_liftEncoder;
	DigitalInput *m_topLimitSwitch;
	DigitalInput *m_bottomLimitSwitch;
	LiveWindow *lw;
	float rightXboxY;
	bool rightBumper;
	bool m_topLimit;
	bool m_bottomLimit;
	float driveStickX;
	float driveStickY;
	float driveThrottle;
	float driveSpeed;
	float driveTurn;

public:

	FYRERobot(void)
	{
		// Create a RobotDrive object using PWMS 0 and 1
		m_robotDrive = new RobotDrive(0, 1);

		// Define joystick being used at USB port #1 on the Drivers Station
		m_driveStick = new Joystick(0);
		// Define joystick being used at USB port #2 on the Drivers Station
		m_liftStick = new Joystick(1);

		// Lift Motor declaration
		m_robotLift = new Talon(2);
		m_liftEncoder = new Encoder(0, 1);

		// Define two swtiches
		m_topLimitSwitch = new DigitalInput(4);
		m_bottomLimitSwitch = new DigitalInput(5);

		// Live Window declaration
		lw = new LiveWindow();


		// Variable Declarations
		driveStickX = 0;
		driveStickY = 0;
		rightXboxY = 0;
		rightBumper = 0;
		driveThrottle = 0;
		m_topLimit = 0;
		m_bottomLimit = 0;
		driveSpeed = 0;
		driveTurn = 0;

	}

private:

	void RobotInit()
	{
		lw = LiveWindow::GetInstance();
	}

	void AutonomousInit()
	{
		//liftEncoder->Reset();
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
		m_robotDrive->Drive(0,0);
	}

	void AutonomousPeriodic()
	{

	}

	void TeleopInit()
	{

		m_liftEncoder->Reset();

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

		driveThrottle = (((((m_driveStick->GetThrottle)*-1)+1)/4)+.5);


		// Dead zone for drive turning
		if (abs(driveStickX)<.5){
			driveStickX = 0;
		}

		// Applying throttle to inputs
		driveTurn = driveStickX * driveThrottle;
		driveSpeed = driveStickY * driveThrottle;

		// Driving the drive speeds
		m_robotDrive->ArcadeDrive(driveSpeed, driveTurn);

		// Arm motor shutoff at lower level
		if(m_bottomLimit == 1 && rightXboxY >=0){

			m_robotLift->Set(0);

		}

		// Arm motor shutoff upper level
		else if(m_topLimit == 1 && rightXboxY <=0){

			m_robotLift->Set(0);

		}
		else{
			// Arm motor deadzone and power
			if (rightXboxY >= 0.2 || rightXboxY <= -0.2){
				m_robotLift->Set(rightXboxY);
			}
			else
			{
				m_robotLift->Set(0);
			}
		}

		// Arm motor limit override
		if (rightBumper == true){

			m_robotLift->Set(rightXboxY);

		}

		// Test print lines
		//printf("%F",rightXboxY);
		//printf("%F\n", m_liftEncoder->GetDistance());

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(FYRERobot);
