/******************************************************************************
 * File Name      : TestUtility.h
 *  
 * Description    : This header file contains the declaration of Utility 
 *					functions required for server. 
 *				    
 * Modifiled Date : 07/12/2020
 *
 *****************************************************************************/
#ifndef TEST_UTILITY_H
#define TEST_UTILITY_H


#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <iostream>
#include <map>

using namespace std;
/****************************************************************************** 
* Class Name  : ConfigReader 
*
* Description : The responsibility of this class is to parse the
*				Config file and store it in the std::map
*				Defined getter function getValue() to get the
*				data from the std::map.		    
* 
******************************************************************************/
class ConfigReader
{
	private:       
		/**** Define the map to store data from the config file*************/
        std::map<std::string, std::string> m_ConfigSettingMap;
        /*Static pointer instance to make this class singleton.*/ 
        static ConfigReader* m_pInstance;
    public:         
        /* Public static method getInstance(). This function is
           responsible for object creation. */
        static ConfigReader* getInstance();
        /* Parse the config file. */
        bool parseFile(std::string fileName = 
        "/src/jenkinsDocker/UnitGUIRestAPI/UnitTesting/TestRunner/configuration/ConfigurationFile");
        /*Overloaded getValue() function.
          Value of the tag in cofiguration file could be
          string or integer. So the caller need to take care this.
          Caller need to call appropiate function based on the
          data type of the value of the tag. */
          bool getValue(std::string tag, int& value);
          bool getValue(std::string tag, std::string& value);
          /*Function dumpFileValues is for only debug purpose*/
          void dumpFileValues();

	private:
          /* Define constructor in the private section to make this
             class as singleton.*/
          ConfigReader();
          /* Define destructor in private section, so no one can delete 
             the instance of this class.*/
         ~ConfigReader();
          /* Define copy constructor in the private section, so that no one can 
             voilate the singleton policy of this class */
          ConfigReader(const ConfigReader& obj){}             
          /* Define assignment operator in the private section, so that no one can 
             voilate the singleton policy of this class */
           void operator=(const ConfigReader& obj){}
          /* Helper function to trim the tag and value. These helper function is
             calling to trim the un-necessary spaces. */
           std::string trim(const std::string& str, const std::string& whitespace = " \t");
           std::string reduce(const std::string& str,
           const std::string& fill = " ",
           const std::string& whitespace = " \t");
};
/****************************************************************************** 
* Class Name  : TestUtility 
*
* Description : This class represents the Server Utility variables and functions		    
* 
******************************************************************************/
class TestUtility
{
    
    /*Private member variables.*/
    string m_msgRecived;
    string m_msgPublish;
    bool m_stop_main;
  
  public:
     
    /*Public member variables. */
    vector<string> words;
    vector<string> words1;
    /*This function returns filepath of the file,fileName read from the
	  configuration file */
    string getCsvFilePath(std::string fileName);
    /*This function returns a message recieved from AUT*/
    string getMsg();
    /* This function sets message recieved from AUT*/
    void setMsg(string msg);
    /*This function sets boolean variable to stop sending test message*/
    void setStopMain(bool s);
    /*This function gets boolean variable to stop sending test message*/
    bool getStopMain();
	/*This function gets the message to be published to AUT*/
    string getMsgPublish();
    /*This function sets the message to be published to AUT(m_msgPublish)*/
    void setMsgPublish(string msg);
    /*This function evaluate the test case by sending the string*/
    string evaluvateTestcase(string msg);
    /*read the csv file line by line and save it in a vector and seperate the 
    test cases and expected results*/
    void readCSV(std::string filename);
    void readCSV1(std::string filename);
    /*read the csv file line by line and save it in a vector*/
    static bool getFileContent(std::string fileName, std::vector<std::string> & vecOfStrs);
    /*Default constructor*/
    TestUtility (): m_msgRecived("")
	     , m_msgPublish("")
	     , m_stop_main(false)
   {
	
   }
};
/******************************************************************************
*Function Name    : void SubscriberMain(TestUtility* s);
*
*Description      : Subscriber Main thread function to send the messages from 
*					Test runner to test environment 		   
* 
*Input Parameters : s ServerUtility class pointer
* 
* Return Value    : None
* 
******************************************************************************/
void SubscriberMain(TestUtility* s);
/******************************************************************************
*Function Name    : PublisherMain(TestUtility* s);
*
*Description      : Publisher Main thread function to recieve the messages from
*					Test environment to test runner		   
* 
*Input Parameters : s ServerUtility class pointer
* 
* Return Value    : None
* 
******************************************************************************/
/*!
 * @brief Publisher Main thread function to recieve the messages from Test environment to test runner
 * @param s ServerUtility class pointer
 */
void PublisherMain(TestUtility* s);


#endif
