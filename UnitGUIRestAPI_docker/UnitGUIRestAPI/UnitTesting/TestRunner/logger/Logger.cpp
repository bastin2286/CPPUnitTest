 /**
 * File Name      : Logger.cpp
 *  
 * Description    : Implemented complete logging mechanism, Supporting multiple
 *		     logging type like as file based logging, console based
 *		     logging & etc. It also supported for different log type.
 *
 * Modifiled Date : 22/09/2020
 *
 */

// C++ Header File(s)
#include <iostream>
#include <cstdlib>
#include <ctime>

// Code Specific Header Files(s)
#include "Logger.h"

using namespace std;
using namespace CPlusPlusLogging;

Logger* Logger::m_Instance = 0;

// Log file name. File name should be change from here only
const string logFileName = "MyLogFile.log";
    

  /** 
  * 
  *Function Name : Logger
  *
  * Description  : This function is a default constructor 				   
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */
Logger::Logger()
{
   m_File.open(logFileName.c_str(), ios::out|ios::app);
   m_LogLevel	= LOG_LEVEL_DEBUG;
   m_LogType	= FILE_LOG;

   // Initialize mutex
#ifdef WIN32
   InitializeCriticalSection(&m_Mutex);
#else
   int ret=0;
   ret = pthread_mutexattr_settype(&m_Attr, PTHREAD_MUTEX_ERRORCHECK_NP);
   if(ret != 0)
   {   
      printf("Logger::Logger() -- Mutex attribute not initialize!!\n");
      exit(0);
   }   
   ret = pthread_mutex_init(&m_Mutex,&m_Attr);
   if(ret != 0)
   {   
      printf("Logger::Logger() -- Mutex not initialize!!\n");
      exit(0);
   }   
#endif
}

  /** 
  * 
  *Function Name : Logger
  *
  * Description  : This function is a default destructor 				   
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */
Logger::~Logger()
{
   m_File.close();
#ifdef WIN32
   DeleteCriticalSection(&m_Mutex);
#else
   pthread_mutexattr_destroy(&m_Attr);
   pthread_mutex_destroy(&m_Mutex);
#endif
}
   

 /** 
  * 
  *Function Name : getInstance
  *
  * Description  : This function returns a reference Logger instance 				   
  * 
  * Parameters   : None
  * 
  * Return Value : Reference to Logger object
  * 
  * 
  */
Logger* Logger::getInstance() throw ()
{
   if (m_Instance == 0) 
   {
      m_Instance = new Logger();
   }
   return m_Instance;
}


 /** 
  * 
  *Function Name : lock
  *
  * Description  : This function is a wrapper function for lock				   
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */
void Logger::lock()
{
#ifdef WIN32
   EnterCriticalSection(&m_Mutex);
#else
   pthread_mutex_lock(&m_Mutex);
#endif
}

 /** 
  * 
  *Function Name : unlock
  *
  * Description  : This function is a wrapper function for unlock				   
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */
void Logger::unlock()
{
#ifdef WIN32
   LeaveCriticalSection(&m_Mutex);
#else
   pthread_mutex_unlock(&m_Mutex);
#endif
}

 /** 
  * 
  *Function Name : logIntoFile
  *
  * Description  : This function is the Interface to log into File				   
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */
  
void Logger::logIntoFile(std::string& data)
{
   lock();
   m_File << getCurrentTime() << "  " << data << endl;
   unlock();
}

 /** 
  * 
  *Function Name : logOnConsole
  *
  * Description  : This function is the Interface to log into Console				   
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */

void Logger::logOnConsole(std::string& data)
{
   std::cout << getCurrentTime() << "  " << data << std::endl;
}


 /** 
  * 
  *Function Name : getCurrentTime
  *
  * Description  : This function to get the current time.
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */
string Logger::getCurrentTime()
{
   string currTime;
   //Current date/time based on current time
   time_t now = time(0); 
   // Convert current time to string
   currTime.assign(ctime(&now));

   // Last charactor of currentTime is "\n", so remove it
   string currentTime = currTime.substr(0, currTime.size()-1);
   return currentTime;
}

 /** 
  * 
  *Function Name : error
  *
  * Description  : This function is the Interface for Error Log
  * 
  * Parameters   : text to be printed as error
  * 
  * Return Value : None
  * 
  * 
  */
void Logger::error(const char* text) throw()
{
   string data;
   data.append("[ERROR]: ");
   data.append(text);

   // ERROR must be captured always
   if(m_LogType == FILE_LOG)
   {
      logIntoFile(data);
   }
   else if(m_LogType == CONSOLE)
   {
      logOnConsole(data);
   }
}

 /** 
  * 
  *Function Name : error
  *
  * Description  : This function is the Interface for Error Log
  * 
  * Parameters   : text to be printed as error
  * 
  * Return Value : None
  * 
  * 
  */
  
void Logger::error(const std::string& text) throw()
{
   error(text.data());
}

 /** 
  * 
  *Function Name : error
  *
  * Description  : This function is the Interface for Error Log
  * 
  * Parameters   : text to be printed as error
  * 
  * Return Value : None
  * 
  * 
  */
void Logger::error(std::ostringstream& stream) throw()
{
   string text = stream.str();
   error(text.data());
}


 /** 
  * 
  *Function Name : warn
  *
  * Description  : This function is the Interface for Warning Log
  * 
  * Parameters   : text to be printed as warning
  * 
  * Return Value : None
  * 
  * 
  */
  
void Logger::warn(const char* text) throw()
{
   // Buffer is the special case. So don't add log level
   // and timestamp in the warn message. Just log the raw bytes.
   if((m_LogType == FILE_LOG) && (m_LogLevel >= LOG_LEVEL_WARN))
   {
      lock();
      m_File << text << endl;
      unlock();
   }
   else if((m_LogType == CONSOLE) && (m_LogLevel >= LOG_LEVEL_WARN))
   {
      cout << text << endl;
   }
}

/** 
  * 
  *Function Name : warn
  *
  * Description  : This function is the Interface for Warning Log
  * 
  * Parameters   : text to be printed as warning
  * 
  * Return Value : None
  * 
  * 
  */
void Logger::warn(const std::string& text) throw()
{
   warn(text.data());
}

/*!
 * @brief This function is the Interface for Warning Log 
 * @param text to be printed as Warning
 */ 
void Logger::warn(std::ostringstream& stream) throw()
{
   string text = stream.str();
   warn(text.data());
}
/** 
  * 
  *Function Name : info
  *
  * Description  : This function is the Interface for info Log
  * 
  * Parameters   : text to be printed as Info
  * 
  * Return Value : None
  * 
  * 
  */

void Logger::info(const char* text) throw()
{
   string data;
   data.append("[INFO]: ");
   data.append(text);

   if((m_LogType == FILE_LOG) && (m_LogLevel >= LOG_LEVEL_INFO))
   {
      logIntoFile(data);
   }
   else if((m_LogType == CONSOLE) && (m_LogLevel >= LOG_LEVEL_INFO))
   {
      logOnConsole(data);
   }
}

/** 
  * 
  *Function Name : info
  *
  * Description  : This function is the Interface for info Log
  * 
  * Parameters   : text to be printed as Info
  * 
  * Return Value : None
  * 
  * 
  */
void Logger::info(const std::string& text) throw()
{
   info(text.data());
}

/*!
 * @brief This function is the Interface for Info Log 
 * @param text to be printed as Info
 */
void Logger::info(std::ostringstream& stream) throw()
{
   string text = stream.str();
   info(text.data());
}
/** 
  * 
  *Function Name : debug
  *
  * Description  : This function is the Interface for Debug Log
  * 
  * Parameters   : text to be printed as Debug
  * 
  * Return Value : None
  * 
  * 
  */
  
void Logger::debug(const char* text) throw()
{
   string data;
   data.append("[DEBUG]: ");
   data.append(text);

   if((m_LogType == FILE_LOG) && (m_LogLevel >= LOG_LEVEL_DEBUG))
   {
      logIntoFile(data);
   }
   else if((m_LogType == CONSOLE) && (m_LogLevel >= LOG_LEVEL_DEBUG))
   {
      logOnConsole(data);
   }
}

/** 
  * 
  *Function Name : debug
  *
  * Description  : This function is the Interface for Debug Log
  * 
  * Parameters   : text to be printed as Debug
  * 
  * Return Value : None
  * 
  * 
  */
void Logger::debug(const std::string& text) throw()
{
   debug(text.data());
}

/** 
  * 
  *Function Name : debug
  *
  * Description  : This function is the Interface for Debug Log
  * 
  * Parameters   : text to be printed as Debug
  * 
  * Return Value : None
  * 
  * 
  */
void Logger::debug(std::ostringstream& stream) throw()
{
   string text = stream.str();
   debug(text.data());
}

/** 
  * 
  *Function Name : updateLogLevel
  *
  * Description  : This function is the Interfaces to control log levels. 
  *		    All the levels above the parameter passed will be enabled
  * 
  * Parameters   : logLevel is considered as minimum level to be enabled
  * 
  * Return Value : None
  * 
  * 
  */

void Logger::updateLogLevel(LogLevel logLevel)
{
   m_LogLevel = logLevel;
}
/** 
  * 
  *Function Name : enaleLog
  *
  * Description  : This function is the Interfaces to Enable all log levels
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */
  
void Logger::enaleLog()
{
   m_LogLevel = ENABLE_LOG; 
}
/** 
  * 
  *Function Name : disableLog
  *
  * Description  : This function is the Interfaces to Disable all log levels, 
  *		    except error
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */
void Logger:: disableLog()
{
   m_LogLevel = DISABLE_LOG;
}


/** 
  * 
  *Function Name : updateLogType
  *
  * Description  : This function is the Interface to enable Console or 
  *		    File Logging
  * 
  * Parameters   : logType parameter which need to be enabled as logtype
  * 
  * Return Value : None
  * 
  * 
  */
  
  
void Logger::updateLogType(LogType logType)
{
   m_LogType = logType;
}

/** 
  * 
  *Function Name : enableConsoleLogging
  *
  * Description  : This function is the Interface to enable Console Logging 
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */
void Logger::enableConsoleLogging()
{
   m_LogType = CONSOLE; 
}
/** 
  * 
  *Function Name : enableFileLogging
  *
  * Description  : This function is the Interface to enable File Logging 
  * 
  * Parameters   : None
  * 
  * Return Value : None
  * 
  * 
  */
void Logger::enableFileLogging()
{
   m_LogType = FILE_LOG ;
}
