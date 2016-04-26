
/*-------------------------Start of FollowHuman Class--------------------------*/
/*--------------------------------------------------------------------------*/

class FollowHuman: public HumanPosition, public GetInfo,public XYZClosed, public HumanHand
{
public: float * returnInfo();
public: float * returnHumanPosition();
public: void checkStatus();
public: float * returnHumanHand();
float *h;
float *r;
float *hh;
float Xvalue,Yvalue,Zvalue;
};

void FollowHuman::checkStatus()
{

   do
     {
     HumanPosition obj3;
     h=obj3.returnHumanPosition();
     Xvalue=*h;
     Yvalue=*(h+1);
     Zvalue=*(h+2);
     GetInfo obj1;
     r=obj1.returnInfo();
     XYZClosed Xobj;
     
    // Xobj.gotoXYZ(Xvalue,Yvalue,Zvalue);
     
   //  Xobj.gotoXYZ(0.59,.11,.4);
    // sleep(8);
    // cout<<"second function"<<endl;
     //XYZ Xobj1;
     //Xobj1.gotoXYZ(0.58, 0.11, 0.42);
    // sleep(8);
     if(Xvalue > 0.65 || Yvalue>0.6 || Zvalue>0.6 )
     {
      cout<<Xvalue<<Yvalue<<Zvalue<<endl;
      cout<<"user out of Range"<<endl;
      continue;
     }
     if(Xvalue <=.58 && Zvalue>0.4)
     { cout<<"Height is more than arm range";}
     else
     {
    // Xobj.gotoXYZ(0.5,.2,.4);
   //  sleep(8);
     Xobj.gotoXYZClosed(Xvalue,Yvalue,Zvalue);
     sleep(4); 
     }
     //sleep(6);
     //Xobj1.gotoXYZ(0.5, -0.118, 0.3);
     
     //sleep(6);
     
     cout<<Xvalue<<Yvalue<<Zvalue<<endl;
     cout<<"r values"<<*r<<*(r+1)<<*(r+2)<<endl;
     cout<<"h values"<<*h<<*(h+1)<<*(h+2)<<endl;
     HumanHand hp;
     hh=hp.returnHumanHand();
   }
   while((((*hh)-(*r))>0.005) || (((*(hh+1))-(*(r+1)))>0.005) || (((*(hh+2))-(*(r+2)))>0.005));
   
 // sleep(3);
  //cout<<"Stopping Now"<<endl;
}
