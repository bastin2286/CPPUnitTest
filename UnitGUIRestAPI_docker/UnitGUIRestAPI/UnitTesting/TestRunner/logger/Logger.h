///////////////////////////////////////////////////////////////////////////////
// @File Name:     Logger.h                                                  //
// @Author:        				                               //
// @Version:       		                                              //
// @L.M.D:         					                       //
// @Description:   For Logging into file                                     //
//                                                                           // 
// Detail Description:                                                       //
// Implemented complete logging mechanism, Supporting multiple logging type  //
// like as file based logging, console base logging etc. It also supported   //
// for different log type.                                                   //
//                                                                           //
// Thread Safe logging mechanism. Compatible with VC++ (Windows platform)    //
// as well as G++ (Linux platform)                                           //
//                                                                           //
// Supported Log Type: ERROR, ALARM, ALWAYS, INFO, WARN, TRACE, DEBUG        //
//                                                                           //
// No control for ERROR, ALRAM and ALWAYS messages. These type of messages   //
// should be always captured.                                                //
//                                                                           //
// WARN log type should be use while logging raw warn or raw messages        //
//                                                                           //
// Having direct interface as well as C++ Singleton inface. can use          //
// whatever interface want.                                                  //
//                                                                           //
///////////////////////////////////////////////////////////////////////////////

/*!
 * @file Logger.h
 * This header file contains the declaration of the funcions required for logging into file and console.
 *
 */

#ifndef _LOGGER_H_
#define _LOGGER_H_

// C++ Header File(s)
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#ifdef WIN32
// Win Socket Header File(s)
#include <Windows.h>
#include <process.h>
#else
// POSIX Socket Header File(s)
#include <errno.h>
#include <pthread.h>
#endif

namespace CPlusPlusLogging
{
   
   // Direct Interface for logging into log file or console using MACRO(s)
   #define LOG_ERROR(x)    Logger::getInstance()->error(x)
   #define LOG_INFO(x)     Logger::getInstance()->info(x)
   #define LOG_WARN(x)   Logger::getInstance()->warn(x)
   #define LOG_DEBUG(x)    Logger::getInstance()->debug(x)

   // enum for LOG_LEVEL
   typedef enum LOG_LEVEL
   {
      DISABLE_LOG       = 1,
      LOG_LEVEL_WARN	 = 2,
      LOG_LEVEL_INFO	 = 3,
      LOG_LEVEL_DEBUG   = 4,
      ENABLE_LOG        = 5,
   }LogLevel;

   // enum for LOG_TYPE
   typedef enum LOG_TYPE
   {
      NO_LOG            = 1,
      CONSOLE           = 2,
      FILE_LOG          = 3,
   }LogType;

   /*!
    * @brief This class represents the Logger class to display error, warning, debug and info messages to file or console.
    * @ingroup CPlusPlusLogging
    */
   class Logger
   {
      public:    
         /*!
          * @brief This function returns a reference Logger instance
          * @return Reference to Logger object
          */
         static Logger* getInstance() throw ();
  
         /*!
          * @brief This function is the Interface for Error Log 
          * @param text to be printed as error
          */ 
         void error(const char* text) throw();
         /*!
          * @brief This function is the Interface for Error Log 
          * @param text to be printed as error
          */
         void error(const std::string& text) throw();
         /*!
          * @brief This function is the Interface for Error Log 
          * @param text to be printed as error
          */
         void error(std::ostringstream& stream) throw();

         /*!
          * @brief This function is the Interface for Warning Log 
          * @param text to be printed as warning
          */
         void warn(const char* text) throw();
         /*!
          * @brief This function is the Interface for Warning Log 
          * @param text to be printed as warning
          */
         void warn(const std::string& text) throw();
         /*!
          * @brief This function is the Interface for Warning Log 
          * @param text to be printed as warning
          */
         void warn(std::ostringstream& stream) throw();

         /*!
          * @brief This function is the Interface for Info Log 
          * @param text to be printed as info
          */
         void info(const char* text) throw();
         /*!
          * @brief This function is the Interface for Info Log 
          * @param text to be printed as info
          */
         void info(const std::string& text) throw();
         /*!
          * @brief This function is the Interface for Info Log 
          * @param text to be printed as info
          */
         void info(std::ostringstream& stream) throw();

         /*!
          * @brief This function is the Interface for Debug Log 
          * @param text to be printed as debug
          */
         void debug(const char* text) throw();
         /*!
          * @brief This function is the Interface for Debug Log 
          * @param text to be printed as debug
          */
         void debug(const std::string& text) throw();
         /*!
          * @brief This function is the Interface for Debug Log 
          * @param text to be printed as debug
          */
         void debug(std::ostringstream& stream) throw();

         /*!
          * @brief This function is the Interfaces to control log levels. All the levels above the parameter passed will be enabled
          * @param logLevel is considered as minimum level to be enabled
          */
         void updateLogLevel(LogLevel logLevel);
         /*!
          * @brief This function is the Interfaces to Enable all log levels
          */
         void enaleLog();
         /*!
          * @brief This function is the Interface to Disable all log levels, except error
          */
         void disableLog();

         /*!
          * @brief This function is the Interface to enable Console or File Logging
          * @param logType parameter which need to be enabled as logtype
          */
         void updateLogType(LogType logType);
         /*!
          * @brief This function is the Interface to enable Console Logging
          */
         void enableConsoleLogging();
         /*!
          * @brief This function is the Interface to enable File Logging
          */
         void enableFileLogging();

      protected:
         /*!
          * @brief Default Constructor
          */
         Logger();
         /*!
          * @brief Default Desctructor
          */
         ~Logger();

         /*!
          * @brief Wrapper function for lock
          */
         void lock();
      
         /*!
          * @brief Wrapper function for unlock
          */
         void unlock();
      
         /*!
          * @brief function to get the current time
          */
         std::string getCurrentTime();

      private:
         /*!
          * @brief This function is the Interface to log into File
          */
         void logIntoFile(std::string& data);
         /*!
          * @brief This function is the Interface to log into Console
          */
         void logOnConsole(std::string& data);
         /*!
          * @brief This function is copy Constructor
          */
         Logger(const Logger& obj) {}
         /*!
          * @brief This function is assignment operator
          */
         void operator=(const Logger& obj) {}

      private:
         static Logger*          m_Instance;
         std::ofstream           m_File;

#ifdef	WIN32
         CRITICAL_SECTION        m_Mutex;
#else
         pthread_mutexattr_t     m_Attr; 
         pthread_mutex_t         m_Mutex;
#endif

         LogLevel                m_LogLevel;
         LogType                 m_LogType;
   };

} // End of namespace

#endif // End of _LOGGER_H_


