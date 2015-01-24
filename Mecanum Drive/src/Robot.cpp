#include "WPILib.h"
#include "string"

class Robot: public IterativeRobot
{

	RobotDrive *m_robotDrive;		// RobotDrive object using PWM 1-4 for drive motors
	Joystick *m_driveStick;         // Joystick object on USB port 1 (mecanum drive)
	Talon *m_robotLift;
	Joystick *m_liftStick;
	Encoder *m_liftEncoder;
	float rightXboxY;
	bool rightBumper;

public:

	Robot(void)
	{
		// Create a RobotDrive object using PWMS 1, 2, 3, and 4
		m_robotDrive = new RobotDrive(0, 1);
		// Define joystick being used at USB port #1 on the Drivers Station
		m_driveStick = new Joystick(0);
		// Twist is on Axis 3 for the Extreme 3D Pro
		m_driveStick->SetAxisChannel(Joystick::kTwistAxis, 3);
		// Create a RobotDrive object using PWMS 5
		m_robotLift = new Talon(2);
		m_liftEncoder = new Encoder(0, 1);
		// Define joystick being used at USB port #2 on the Drivers Station
		m_liftStick = new Joystick(1);
		lw = LiveWindow::GetInstance();
		rightXboxY = 0;
		rightBumper = false;
		//


	}

private:
	LiveWindow *lw;

	void RobotInit()
	{

	}

	void AutonomousInit()
	{

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

		rightXboxY = m_liftStick->GetRawAxis(5);

		m_robotDrive->ArcadeDrive(m_driveStick);

		if (abs(rightXboxY) >= 0.001){
			m_robotLift->Set(rightXboxY);
		}
		else
		{
			m_robotLift->Set(0);
		}
		//printf("%F",rightXboxY);

		printf("%F\n", m_liftEncoder->GetDistance());

	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);
