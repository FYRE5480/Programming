#include "WPILib.h"
#include "string"
#include <cmath>
#include <iostream>

class FYRERobot: public IterativeRobot
{
	//Command *autonomousChooser;
	//SendableChooser *chooser;
	RobotDrive *m_robotDrive;		// RobotDrive object using PWM 1-4 for drive motors
	Joystick *m_driveStick;         // Joystick object on USB port 1 (mecanum drive)
	Talon *m_robotLift;
	Joystick *m_liftStick;
	Encoder *m_liftEncoder;
	//Encoder *m_leftEncoder;
	//Encoder *m_rightEncoder;
	DoubleSolenoid *m_solenoid;

	float rightXboxY;
	bool rightBumper;
	bool leftBumper;
	bool m_topLimit;
	bool m_bottomLimit;
	float driveStickX;
	float driveStickY;
	float driveThrottle;
	bool solenoidValue;
	int level;
	bool XboxA;
	bool XboxB;
	float newLiftEncoder;

public:

	FYRERobot(void)
	{

		//auto choose

		// Create a RobotDrive object using PWMS 1, 2, 3, and 4
		m_robotDrive = new RobotDrive(0, 1);
		// Define joystick being used at USB port #1 on the Drivers Station
		m_driveStick = new Joystick(0);
		// Twist is on Axis 3 for the Extreme 3D Pro
		m_driveStick->SetAxisChannel(Joystick::kTwistAxis, 3);
		// Create a RobotDrive object using PWMS 5
		m_robotLift = new Talon(2);
		// encoders and pnuematics
		m_liftEncoder = new Encoder(0, 1, true);
		//m_liftEncoder -> SetDistancePerPulse(22.7272727272727272);
		//m_leftEncoder = new Encoder(2,3);
		//m_leftEncoder -> SetDistancePerPulse(39.7890543494609 );
		//m_rightEncoder = new Encoder(4,5);
		//m_rightEncoder -> SetDistancePerPulse(39.7890543494609 );

		m_solenoid = new DoubleSolenoid (0,1);
		// Define joystick being used at USB port #2 on the Drivers Station
		m_liftStick = new Joystick(1);
		// Define two swtiches


		//the camera name (ex "cam0") can be found through the roborio web interface

	}

private:
	LiveWindow *lw;

	void RobotInit()
	{
		/*chooser = new SendableChooser();
		chooser->AddDefault("Bin Auto", AutonomousBin());
		chooser->AddObject("Tote Auto", AutonomousTote());*/
		//SmartDashboard::PutData("Autonomous Modes", chooser);
		CameraServer::GetInstance()->SetQuality(50);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
		/*lw->AddActuator("Drive Train", "Left", new Jaguar(0));
		lw->AddActuator("Drive Train", "Right", new Jaguar(1));
		lw->AddActuator("Lift Arm", "Motor", new Talon(2));
		lw->AddActuator("Lift Arm", "Brakes", new Solenoid(1,1));*/
		lw = LiveWindow::GetInstance();
	}

	void AutonomousInit()
	{
		//m_liftEncoder->Reset();
		//m_leftEncoder->Reset();
		//m_rightEncoder->Reset();

		/*autonomousChooser = (Command *) chooser->GetSelected();
		autonomousChooser -> Start();*/

	}

	/*void AutonomousBin()
	{
		while(m_liftEncoder->Get()<280){
			m_solenoid -> Set(m_solenoid-> kReverse);
			m_robotLift -> Set(.5);

		}

		m_robotLift -> Set(0);
		m_solenoid -> Set(m_solenoid-> kForward);
		while(m_leftEncoder->Get()<21840 && m_rightEncoder->Get()<21840){
			m_robotDrive -> Drive(.5,0);
		}

		m_robotDrive -> Drive(0,0);

		while(m_bottomLimitSwitch->Get() == false){
			m_solenoid -> Set(m_solenoid-> kReverse);
			m_robotLift -> Set(-.5);
		}

		m_robotLift -> Set(0);
		while(m_leftEncoder->Get()>18905 && m_rightEncoder->Get()<18905){
			m_robotDrive -> Drive(-.5,0);
		}
		m_robotDrive -> Drive(0,0);
	}

	void AutonomousTote()
	{
		while(m_liftEncoder->Get()<280){
			m_solenoid -> Set(m_solenoid-> kReverse);
			m_robotLift -> Set(.5);

		}

		m_robotLift -> Set(0);
		m_solenoid -> Set(m_solenoid-> kForward);

		while(m_leftEncoder->Get()<5376)
		{
			m_robotDrive -> Drive(0,.5);
		}
		m_robotDrive -> Drive(0,0);
		m_leftEncoder -> Reset();
		m_rightEncoder-> Reset();
		while(m_leftEncoder->Get()<21840 && m_rightEncoder->Get()<21840){
			m_robotDrive -> Drive(.5,0);
		}

		m_robotDrive -> Drive(0,0);

		while(m_bottomLimitSwitch->Get() == false){
			m_solenoid ->(m_solenoid-> kReverse);.
			m_robotLift -> Set(-.5);
		}

		m_robotLift -> Set(0);
		while(m_leftEncoder->Get()>18905 && m_rightEncoder->Get()<18905){
			m_robotDrive -> Drive(-.5,0);
		}
		m_robotDrive -> Drive(0,0);
	}*/

	void AutonomousPeriodic()
	{
			//Scheduler::GetInstance() -> Run();
	}

	void TeleopInit()
	{

		m_liftEncoder->Reset();
		solenoidValue = false;
		level = 0;
		newLiftEncoder = 0;

	}

	void TeleopPeriodic()
	{

		// Update Variables
		rightXboxY = m_liftStick->GetRawAxis(5);
		rightBumper = m_liftStick->GetRawButton(6);
		leftBumper = m_liftStick -> GetRawButton(5);
		//liftEncoder = m_liftEncoder -> Get();

		XboxA = m_liftStick -> GetRawButton(1);
		XboxB = m_liftStick -> GetRawButton(2);
		// Drive Stick Dead Zone

		setDriveTrain();

		/*if((m_bottomLimit == 1) && (rightXboxY<=0)){

			m_robotLift->Set(0);

		}
		else if((m_topLimit == 1) && (rightXboxY >=0)){

			m_robotLift->Set(0);

		}
		else{*/
		if(XboxA == true){

			if(level < 3){
				//m_robotDrive -> Drive(0,0);
				newLiftEncoder = m_liftEncoder->Get() + 670;
				m_solenoid -> Set(m_solenoid-> kForward);
				printf("%i/n", m_liftEncoder->Get());
				while(m_liftEncoder->Get()<= newLiftEncoder){
					m_robotLift -> Set(-1);
					printf("%i/n", m_liftEncoder->Get());
					setDriveTrain();
					// = m_liftEncoder -> Get();
				}


			}
			level = level + 1;
			m_solenoid -> Set(m_solenoid-> kReverse);

		}

		else if(XboxB == true){
			if(level > 0){
				m_robotDrive -> Drive(0,0);
				newLiftEncoder = m_liftEncoder -> Get() + 100;
				{
					m_robotLift -> Set(-.5);
				}
				 // make via encoder count
				newLiftEncoder = m_liftEncoder->Get() - 200;
				m_solenoid -> Set(m_solenoid-> kForward);
				while(m_liftEncoder->Get()>= newLiftEncoder){

					m_robotLift -> Set(.5);
					printf("%i\n", m_liftEncoder->Get());
					setDriveTrain();

				}

			}
			level = level - 1;
			m_solenoid -> Set(m_solenoid-> kReverse);
		}
		else{
			//if(abs(rightXboxY) >= .2){
				m_robotLift->Set(rightXboxY);
			/*}
			else
			{
				m_robotLift->Set(0);
			}*/
		}

		if (rightBumper == true){
			m_solenoid -> Set(m_solenoid-> kForward);
		}

		else if(leftBumper == true){
			m_solenoid -> Set(m_solenoid -> kReverse);


		}
		//printf("%F",rightXboxY);
		//printf("%i -- encoder\n", m_liftEncoder->Get());
		std::cout << m_liftEncoder->Get() << ": encoder" << std::endl;
		std::cout << level << ": level" << std::endl;
		//printf("%i -- level\n", level);
	}

	void setDriveTrain()
	{
		driveStickX = (m_driveStick->GetX())*-1;
		driveStickY = m_driveStick->GetY();
		driveThrottle = (((((m_driveStick->GetThrottle())*-1)+1)/4)+.5);
		/*if (abs(driveStickX)>.2){
		}
		else
		{
			driveStickX = 0;
		}*/
		// Applying the throttle
		driveStickX = driveStickX * driveThrottle;
		driveStickY = driveStickY * driveThrottle;
		m_robotDrive->ArcadeDrive(driveStickY, driveStickX);

	}
	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(FYRERobot);
