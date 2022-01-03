#ifndef __LOGGER_H__
#define __LOGGER_H__


class Logger
{
private:

    const char *DIR_PATH = "./logFiles/"; //from the current directory the logfile will create into "logFiles" directory -> THIS STRING IS ATTACCHED AT THE START OF LOGFILE_PATH
    std::string LOGFILE_PATH;
    
    std::string randomString_GENERATOR();
    
    const std::string currentDateTime();
  
public:

    Logger(std::string log_FileName); // user put the name of the file

    void writeOnFile(std::string log); //write on you current istance file you log
    
    void deleteLogFile(std::string fileName); // delete a file if you want to delete the current log insert as well parameter loggerObj.getLOGFILE_PATH()

    std::string returnLogFile(); // return into a string all log into the  current instance file
    

    //-------------------------------GETTER--------------------------------------//    
    std::string getLOGFILE_PATH(){
        return LOGFILE_PATH;
    }
};




#endif // __LOGGER_H__