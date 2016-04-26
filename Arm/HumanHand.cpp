#include <iostream>
#include <fstream>
#include <limits>
#include <string>
#include <sstream>
using namespace std;
class HumanHand
 {
  public: double * returnHumanHand();
   double hand_position[3];
 };
    std::istream& ignoreline(std::ifstream& in, std::ifstream::pos_type& pos)
    {
    pos = in.tellg();
    return in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    std::string getLastLine(std::ifstream& in)
    {
        std::ifstream::pos_type pos = in.tellg();

        std::ifstream::pos_type lastPos;
        while (in >> std::ws && ignoreline(in, lastPos))
           pos = lastPos;

        in.clear();
        in.seekg(pos);

        std::string line;
        std::getline(in, line);
        return line;
    }


  double * HumanHand::returnHumanHand()
  {
    

    
    std::ifstream file("test.txt");

    if (file)
    {
        std::string line = getLastLine(file);
        //std::cout << line << '\n';
        std::string delimiter = " ";
        size_t pos = 0;
        std::string token;
        int i=0;
        while ((pos = line.find(delimiter)) != std::string::npos) 
        {
            token = line.substr(0, pos);
            //std::cout << token << std::endl;
            line.erase(0, pos + delimiter.length());
            std::stringstream data(token);
            data >>hand_position[i]; //>>hand_position[1]>>hand_position[2];
            i++;
        }
        std::stringstream data(line);
        data >>hand_position[2];
      //  std::cout << hand_position[0] << std::endl<<hand_position[1] << std::endl<< hand_position[2] << std::endl;
     //   std::cout<<line<<std::endl;
    }
    else
        std::cout << "Unable to open file.\n";
       return hand_position;
}
int main()
{
  double *p;
  HumanHand obj;
  p=obj.returnHumanHand();
  cout<<*p<<endl<<*(p+1)<<*(p+2)<<endl;
}
