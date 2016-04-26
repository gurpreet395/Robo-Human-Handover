class Release
{
public double * returnInfo();
public double * returnHumanHand();
public void openFingers();
public void checkStatus();
double *h;
double *r;
}

void Release::checkStatus()
{
HumanHand obj;
h=obj.returnHumanHand();
GetInfo obj1;
r=obj1.returnInfo();

   while((*h != *r) || (*(h+1) != *(r+1)) || (*(h+2) != *(r+2)))
  {
     HumanHand obj3;
     h=obj.returnHumanHand();
     GetInfo obj1;
     r=obj1.returnInfo();
  }
sleep(3);
cout<<"Releasing Now"<<endl;
}

