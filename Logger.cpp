#include <string>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <stdio.h>       
#include <fstream>
using std::ofstream;
using std::fstream;
using std::ifstream;

#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <sstream>
#include "Logger.h"

#include <windows.h>
#pragma comment(lib, "user32.lib")


//PUBLIC IMPLEMENTATION

    //-------------------------------COSTRUCTOR--------------------------------------//
    Logger::Logger(std::string log_FileName){

        std::string str(DIR_PATH); //convert *char -> string and create the path for the log file
        
        //INPUT CONTROL SECTION
            std::string dot = ".";
            if(strstr(log_FileName.c_str(),dot.c_str())){ // check if it contains a dot
                //log_FileName.erase(remove(log_FileName.begin(), log_FileName.end(), '.'), log_FileName.end()); //remove dot from log_Filename
                log_FileName = log_FileName.substr(0, log_FileName.find(dot));//if in the string there is a "." i cut all after this string
            }
            char invalidChar[11] = {'*', '.' ,'"','/' ,'[' ,']' ,':', ';', '|', ',' , '\\'};
            for(int i=0;i<11;i++)
                log_FileName.erase(remove(log_FileName.begin(), log_FileName.end(), invalidChar[i]), log_FileName.end()); //remove dot from log_Filename
        //END INPUT CONTROL SECTION

        LOGFILE_PATH = str+log_FileName+randomString_GENERATOR()+ ".log";
        
        if (mkdir(DIR_PATH) == -1) //this function accept *char parameter
            std::cerr << "Error :  " << std::strerror(errno) << std::endl;

        fstream logFile(LOGFILE_PATH, std::ios::out | std::ios::app);

        if (!logFile) {
            std::cerr << LOGFILE_PATH<<" not created";
        }
        else {            

            //SECTION: GET INFO FROM OPERATIVE SYSTEM
            SYSTEM_INFO siSysInfo; // Copy the hardware information to the SYSTEM_INFO structure. 
            GetSystemInfo(&siSysInfo);      // Display the contents of the SYSTEM_INFO structure.
            OSVERSIONINFOEX info;
            ZeroMemory(&info, sizeof(OSVERSIONINFOEX));
            info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
            GetVersionEx((LPOSVERSIONINFO)&info);//info requires typecasting
            //END SECTION: GET INFO FROM OPERATIVE SYSTEM

            std::cerr << LOGFILE_PATH<<" created || wrote successfully!"<<std::endl;
            logFile <<"Loggin started at   : ["<<currentDateTime()<<"]\n";

            logFile<< "File     \t\t    : "<< LOGFILE_PATH<< "\n";
            logFile<< "OEM ID      \t\t: "<< siSysInfo.dwOemId<<"\n";
            logFile<< "PEOCESSOR TYPE      : "<<siSysInfo.dwProcessorType<<"\n";
            logFile<< "Windows Version     : "<< info.dwMajorVersion<<"."<< info.dwMinorVersion<< "\n";
            logFile<<"------------------------------------------------------------------------------\n";
            logFile.close();
        }
    }

    //-------------------------------WRITE A STRING ON CURRENT LOGFILE-------------------------------//
    void Logger::writeOnFile(std::string log){

        fstream logFile(LOGFILE_PATH, std::ios::out | std::ios::app);

        if (!logFile) {
            std::cerr << LOGFILE_PATH<<" not created";
        }
        else {
            std::cerr << LOGFILE_PATH<<" wrote successfully!"<<std::endl;
            logFile << log<<" ["<<currentDateTime()<<"]\n";
            logFile.close();
        }     
    }

    //-------------------------------RETURN A STRING CONTAINS ALL INFORMATION IN THE LOGFILE--------------------------------------//
    std::string Logger::returnLogFile(){
            
        std::fstream accountFile; // fstream object
        accountFile.open(LOGFILE_PATH, std::ios::in); //open the file in input mode
        
        if (!accountFile.is_open()) // erorr
            return "Error file not open ";

        
        std::string word;//support variable
        std::vector<std::string>line;//vector line -> every vector cell contains a word then i put all into a string

        while (! accountFile.eof() ) // end of file so take all file word
        {   
            while(getline(accountFile, word,' ' )){  //first control with whitespaces
                std::stringstream ss(word);//ssstream object -> stream to pass the buffer flow
                while(getline(ss, word, '\n')){ //second control with \n charat
                    line.push_back(word);//push the word into a vector 
                }
            }
        }

        accountFile.close();

        std::string fileContent;

        for(int i=0;i<line.size();i++){
            fileContent += line[i];
        }

        return fileContent;
    }

    //-------------------------------DELETE A LOG FILE-------------------------------//
    void deleteLogFile(std::string fileName){ // you can delete a logFile
            std::string dot = ".";
        //if(!strstr(fileName.c_str(),dot.c_str())){
        //    fileName += ".log" 
        //}
        char arr[fileName.length() + 1]; 
        strcpy(arr,fileName.c_str()); 
        remove(arr);
    } 

//PRIVATE IMPLEMENTATION

    //-------------------------------GENERATE UNIVOQUE STRING -------------------------------//
    std::string Logger::randomString_GENERATOR(){ //generate a random univoque string to add at the logfile name as well the file name is unique
        srand(time(NULL)); // new seed to create an unique random number
        int random = rand();
        return std::to_string(random); //convert an int to string e return it
    }
    
    //-------------------------------CURRENT STRING DATE-TIME GENERETOR-------------------------------//
    const std::string Logger::currentDateTime(){
        time_t  now = time(0);
        struct tm  tstruct;
        char       buf[80];
        tstruct = *localtime(&now);

        strftime(buf, sizeof(buf), "%d-%m-%Y %X", &tstruct);

        return buf; // return a string conains date time to put into file log 
    }