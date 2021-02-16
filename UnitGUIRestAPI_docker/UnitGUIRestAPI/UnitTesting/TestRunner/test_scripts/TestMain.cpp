/******************************************************************************
* File Name	    	: TestMain.cpp
*  
* Description	  	: This source file contains the main function which call 
*					  the test cases using gtest
*
* Modifiled Date	: 07/12/2020
*
******************************************************************************/

#include <fstream>
#include <algorithm>
#include <iostream>
#include <thread>
#include "TestMain.h"
#include <gtest/gtest.h>
#include "../dds/DataPacketPubSubTypes.h"
#include <fastrtps/Domain.h>
#include <fastrtps/log/Log.h>
#include "../dds/optionparser.h"
#include "../logger/Logger.h"

using namespace std;
using namespace CPlusPlusLogging;
using namespace eprosima;
using namespace fastrtps;
using namespace rtps;

TestUtility s1;
/******************************************************************************
*Function Name : main
*
* Description  : This is the main function of the Test Runner.
*	   		     In this function a sample conan execution is showcased.
* 		         Similarly to showcase the working of Eprosima DDS in 2 
* 		         threads; one for the publisher and other for the subscriber
* 		         At the end both will join if every process is successfully 
* 		         completed				   
* 
* Parameters   : Testcase filename (*.csv)
* 
* Return Value : integer (if all test cases are passed '0' else '1')
*		    	 This is to skip the futher steps in jenkins if any failure
* 		    	 in the google test
* 
******************************************************************************/
int main(int argc, char **argv) 
{
    std::thread t1(SubscriberMain, &s1);  
    std::thread t2(PublisherMain, &s1);	
    LOG_DEBUG("B4 T1 join:");
    testing::InitGoogleTest(&argc, argv);
    LOG_INFO("B4 Return all test;");
    int retVal = RUN_ALL_TESTS();
    LOG_INFO("B4 threads are joined");
    s1.setStopMain(true);
    LOG_INFO("B4 threads are joined");
    t1.join();
    t2.join();		
    LOG_DEBUG("Ending the main");
    std::cout << "retVal = " << retVal <<std::endl;
    return retVal; 
}
