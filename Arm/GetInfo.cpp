
/*-------------------------------- GetInfomation of the robot Class------------------*/
/*----------------------------------------------------------------------------*/

class GetInfo
{
 public:   float * returnInfo();
 public: float data[3];
};
   float * GetInfo::returnInfo()
   {
	int result;
        
	CartesianPosition dataCommand;
	CartesianPosition dataPosition;

	//Handle for the library's command layer.
	void * commandLayer_handle;

	//Function pointers to the functions we need
	int (*MyInitAPI)();
	int (*MyCloseAPI)();
	int (*MyGetCartesianCommand)(CartesianPosition &);
	int (*MyGetCartesianPosition)(CartesianPosition &);
	int (*MyGetDevices)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result);
	int (*MySetActiveDevice)(KinovaDevice device);

	//We load the library
	commandLayer_handle = dlopen("Kinova.API.USBCommandLayerUbuntu.so",RTLD_NOW|RTLD_GLOBAL);

	//We load the functions from the library
	MyInitAPI = (int (*)()) dlsym(commandLayer_handle,"InitAPI");
	MyCloseAPI = (int (*)()) dlsym(commandLayer_handle,"CloseAPI");
	MyGetCartesianCommand = (int (*)(CartesianPosition &)) dlsym(commandLayer_handle,"GetCartesianCommand");
	MyGetCartesianPosition = (int (*)(CartesianPosition &)) dlsym(commandLayer_handle,"GetCartesianPosition");
	MyGetDevices = (int (*)(KinovaDevice devices[MAX_KINOVA_DEVICE], int &result)) dlsym(commandLayer_handle,"GetDevices");
	MySetActiveDevice = (int (*)(KinovaDevice devices)) dlsym(commandLayer_handle,"SetActiveDevice");

	//If the was loaded correctly
	if((MyInitAPI == NULL) || (MyCloseAPI == NULL) || (MyGetCartesianCommand == NULL) || (MyGetDevices == NULL)
	|| (MyGetCartesianPosition == NULL) || (MySetActiveDevice == NULL))
	{
		cout << "* * *  E R R O R   D U R I N G   I N I T I A L I Z A T I O N  * * *" << endl;
	}
	else
	{
		//cout << "I N I T I A L I Z A T I O N   C O M P L E T E D" << endl << endl;

		result = (*MyInitAPI)();

	//	cout << "Initialization's result :" << result << endl;

		KinovaDevice list[MAX_KINOVA_DEVICE];

		int devicesCount = MyGetDevices(list, result);

		for(int i = 0; i < devicesCount; i++)
		{
//			cout << "Found a robot on the USB bus (" << list[i].SerialNumber << ")" << endl;

			//Setting the current device as the active device.
			MySetActiveDevice(list[i]);

			(*MyGetCartesianCommand)(dataCommand);
			(*MyGetCartesianPosition)(dataPosition);

		        data[0]=dataPosition.Coordinates.X; 
                        data[1]=dataPosition.Coordinates.Y; 
                        data[2]=dataPosition.Coordinates.Z;			
		}
                cout<<"Data in Get info"<<endl<<data[0]<<data[1]<<data[2];
		cout << endl << "C L O S I N G   A P I" << endl;
		result = (*MyCloseAPI)();
	}

	dlclose(commandLayer_handle);

	return data;
   }

