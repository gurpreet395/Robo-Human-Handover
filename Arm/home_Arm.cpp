#include <iostream>
#include <dlfcn.h>
#include <vector>
#include "Lib_Examples/Kinova.API.CommLayerUbuntu.h"
#include "Lib_Examples/KinovaTypes.h"
#include <stdio.h>
#include <unistd.h>

using namespace std;
class home_ARM
   {
      public: void gotoHOME();
   };
   
   void home_ARM::gotoHOME()
   {
        
	int result;

	CartesianPosition currentCommand;

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
	int (*MyGetQuickStatus)(QuickStatus &);
	int (*MyGetCartesianCommand)(CartesianPosition &);

	//We load the library
	commandLayer_handle = dlopen("Kinova.API.USBCommandLayerUbuntu.so",RTLD_NOW|RTLD_GLOBAL);

	//We load the functions from the library (Under Windows, use GetProcAddress)
	MyInitAPI = (int (*)()) dlsym(commandLayer_handle,"InitAPI");
	MyCloseAPI = (int (*)()) dlsym(commandLayer_handle,"CloseAPI");
	MyMoveHome = (int (*)()) dlsym(commandLayer_handle,"MoveHome");
	MyInitFingers = (int (*)()) dlsym(commandLayer_handle,"InitFingers");
	MyGetDevices = (int (*)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result)) dlsym(commandLayer_handle,"GetDevices");
	MySetActiveDevice = (int (*)(KinovaDevice devices)) dlsym(commandLayer_handle,"SetActiveDevice");
	MySendBasicTrajectory = (int (*)(TrajectoryPoint)) dlsym(commandLayer_handle,"SendBasicTrajectory");
	MyGetQuickStatus = (int (*)(QuickStatus &)) dlsym(commandLayer_handle,"GetQuickStatus");
	MyGetCartesianCommand = (int (*)(CartesianPosition &)) dlsym(commandLayer_handle,"GetCartesianCommand");

	if((MyInitAPI == NULL) || (MyCloseAPI == NULL) ||
	   (MyGetQuickStatus == NULL) || (MySendBasicTrajectory == NULL) ||
	   (MySendBasicTrajectory == NULL) || (MyMoveHome == NULL) || (MyInitFingers == NULL) ||
	   (MyGetCartesianCommand == NULL))
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

			cout << "Send the robot to HOME position" << endl;
			MyMoveHome();

			//cout << "Initializing the fingers" << endl;
			//MyInitFingers();

			//TrajectoryPoint pointToSend;
			//pointToSend.InitStruct();

			//cout << "Send the robot to HOME position" << endl;
			//MyMoveHome();

			

			cout << "*********************************" << endl << endl << endl;
		}

		cout << endl << "C L O S I N G   A P I" << endl;
		result = (*MyCloseAPI)();
	}

	dlclose(commandLayer_handle);
   }
int main()
{
 home_ARM obj;
 obj.gotoHOME();
 return 0;
}
