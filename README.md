# C4log WIN
C++ Library,check README!!.txt for more tips and explainations

Main.exe is runnable and as well you can try the class

# Use

1.PUT Logger.h && Logger.cpp IN THE SAME FOLDER

2.#include "Logger.h" || #include "../ownfolder/Logger.h"

3.HAVE FUN 


# Running

1. Download the project and extract it.
2. Run main 

#Library explaining

#THIS IS A C++ EASY LIBRARY#

USE IS VERY SIMPLY  

    1)PUT Logger.h && Logger.cpp IN THE SAME FOLDER

    2)#include "Logger.h" || #include "../ownfolder/Logger.h"

    3)HAVE FUN 


#LOGGER CLASS
* PRIVATE ATTRIBUTES:
**  CHAR *DIR_PATH -> CONTAINS THE DIR'S PATH 
**  STRING LOGFILE_PATH -> CONTAINS LOGFILE_PATH = str+log_FileName+randomString_GENERATOR()+ ".log";
* PRIVATE METHODS:
** randomString_GENERATOR() -> RETURN A UNIQUE STRING OF NUMBER
** currentDateTime() -> RETURN A CURRENT DATE-TIME (format : "%d-%m-%Y %X")
* PUBLIC METHODS:
** Logger(string log_FileName) -> COSTRUCTOR USER PUT THE NAME OF THE FILE AND IT BUILD A LOG OBJECT WITH OWN PERSONAL FILE
** writeOnFile(std::string log) -> WRITE ON LOG FILE A STRING AND ATTACCHED A CURRRENT DATE TIME
** deleteLogFile(std::string fileName) -> DELETE A FILE WITH FILE NAME
** returnLogFile() -> RETURN A STRING WITH ALL YOUR LOG
  
#\LOGGER CLASS

//--------DEVELOPED BY ROBERTO SCANDALE c4LOG--------//
