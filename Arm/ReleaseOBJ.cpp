

//--------------------Release the object----------------------/
//-------------------------------------------------------------*/
class Release: public HumanHand, public GetInfo, public OpenFingers
{
public: float * returnInfo();
public: float * returnHumanHand();
public: void openFingers();
public: void checkStatus();
float *h;
float *r;
};

void Release::checkStatus()
{
/*HumanHand obj;
h=obj.returnHumanHand();
GetInfo obj1;
r=obj1.returnInfo();
*/
   do
  {
     HumanHand obj3;
     h=obj3.returnHumanHand();
     GetInfo obj1;
     r=obj1.returnInfo();
     //sleep(2);
     cout<<"r values"<<*r<<*(r+1)<<*(r+2)<<endl;
     cout<<"h values"<<*h<<*(h+1)<<*(h+2)<<endl;
  }
  while((((*h)-(*r))>0.005) || (((*(h+1))-(*(r+1)))>0.005) || (((*(h+2))-(*(r+2)))>0.005));

cout<<"Releasing Now"<<endl;
OpenFingers of;
of.openFingers();
}

