
/*------------------------------ Get HumanPosition class-----------------*/
/*--------------------------------------------------------------------------*/


class HumanPosition
 {
  public: float * returnHumanPosition();
   float human_position[3];
 };
      


  float * HumanPosition::returnHumanPosition()
  {
    

    
    std::ifstream file("human.txt");

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
            data >>std::setprecision(2)>>human_position[i]; //>>hand_position[1]>>hand_position[2];
            i++;
        }
        std::stringstream data(line);
        data >>std::setprecision(2)>>human_position[2];
        //  std::cout << hand_position[0] << std::endl<<hand_position[1] << std::endl<< hand_position[2] << std::endl;
     //   std::cout<<line<<std::endl;
    }
    else
        std::cout << "Unable to open file.\n";
       return human_position;
}

/*----------------------------End of HumanPosition Class------------------*/
/*---------------------------------------------------------------------*/

