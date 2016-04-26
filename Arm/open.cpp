#include <iostream>
#include <dlfcn.h>
#include <vector>
#include "Lib_Examples/Kinova.API.CommLayerUbuntu.h"
#include "Lib_Examples/KinovaTypes.h"
#include <stdio.h>
#include <unistd.h>

using namespace std;

class OpenFingers
{
public: void openFingers();
};
void OpenFingers::openFingers()
{
	int result;

	AngularPosition currentCommand;

	//Handle for the library's command layer.
	void * commandLayer_handle;

	//Function pointers to the functions we need
	int (*MyInitAPI)();
	int (*MyCloseAPI)();
	int (*MySendBasicTrajectory)(TrajectoryPoint command);
	int (*MyGetDevices)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result);
	int (*MySetActiveDevice)(KinovaDevice device);
	int (*MyMoveHome)();
	int (*MyInitFingers)();
	int (*MyGetAngularCommand)(AngularPosition &);

	//We load the library
	commandLayer_handle = dlopen("Kinova.API.USBCommandLayerUbuntu.so",RTLD_NOW|RTLD_GLOBAL);

	//We load the functions from the library
	MyInitAPI = (int (*)()) dlsym(commandLayer_handle,"InitAPI");
	MyCloseAPI = (int (*)()) dlsym(commandLayer_handle,"CloseAPI");
	MyMoveHome = (int (*)()) dlsym(commandLayer_handle,"MoveHome");
	MyInitFingers = (int (*)()) dlsym(commandLayer_handle,"InitFingers");
	MyGetDevices = (int (*)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result)) dlsym(commandLayer_handle,"GetDevices");
	MySetActiveDevice = (int (*)(KinovaDevice devices)) dlsym(commandLayer_handle,"SetActiveDevice");
	MySendBasicTrajectory = (int (*)(TrajectoryPoint)) dlsym(commandLayer_handle,"SendBasicTrajectory");
	MyGetAngularCommand = (int (*)(AngularPosition &)) dlsym(commandLayer_handle,"GetAngularCommand");

	if((MyInitAPI == NULL) || (MyCloseAPI == NULL) || (MySendBasicTrajectory == NULL) ||
	   (MySendBasicTrajectory == NULL) || (MyMoveHome == NULL) || (MyInitFingers == NULL))
	{
		cout << "* * *  E R R O R   D U R I N G   I N I T I A L I Z A T I O N  * * *" << endl;
	}
	else
	{
		cout << "I N I T I A L I Z A T I O N   C O M P L E T E D" << endl << endl;

		result = (*MyInitAPI)();

		cout << "Initialization's result :" << result << endl;

		KinovaDevice list[MAX_KINOVA_DEVICE];

		int devicesCount = MyGetDevices(list, result);

		for(int i = 0; i < devicesCount; i++)
		{
			cout << "Found a robot on the USB bus (" << list[i].SerialNumber << ")" << endl;

			//Setting the current device as the active device.
			MySetActiveDevice(list[i]);

//			cout << "Send the robot to HOME position" << endl;
//			MyMoveHome();

			cout << "Initializing the fingers" << endl;
			MyInitFingers();

			TrajectoryPoint pointToSend;
			pointToSend.InitStruct();

			

			//We specify that this point will be an angular(joint by joint) position.
			pointToSend.Position.Type = ANGULAR_POSITION;

			//We get the actual angular command of the robot.
			MyGetAngularCommand(currentCommand);

			pointToSend.Position.Actuators.Actuator1 = currentCommand.Actuators.Actuator1 ;
			pointToSend.Position.Actuators.Actuator2 = currentCommand.Actuators.Actuator2;
			pointToSend.Position.Actuators.Actuator3 = currentCommand.Actuators.Actuator3;
			pointToSend.Position.Actuators.Actuator4 = currentCommand.Actuators.Actuator4;
			pointToSend.Position.Actuators.Actuator5 = currentCommand.Actuators.Actuator5;
			pointToSend.Position.Actuators.Actuator6 = currentCommand.Actuators.Actuator6;
                        pointToSend.Position.Fingers.Finger1 =100;
                        pointToSend.Position.Fingers.Finger2 =100;
                        pointToSend.Position.Fingers.Finger3 =100;
			cout << "*********************************" << endl;
			cout << "Sending finger" << endl;
			MySendBasicTrajectory(pointToSend);


			cout << "*********************************" << endl << endl << endl;
		}

		cout << endl << "WARNING: Your robot is now set to angular control. If you use the joystick, it will be a joint by joint movement." << endl;
		cout << endl << "C L O S I N G   A P I" << endl;
		result = (*MyCloseAPI)();
	}

	dlclose(commandLayer_handle);

	}

int main()
{
OpenFingers obj;
obj.openFingers();
}
