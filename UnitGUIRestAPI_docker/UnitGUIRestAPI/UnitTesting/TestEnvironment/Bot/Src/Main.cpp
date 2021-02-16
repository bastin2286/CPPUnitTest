/**
* File Name      : Main.cpp
*  
* Description    : This file is responsible Bot related
*					processing in the system
*
* Modifiled Date : 22/09/2020
*
*/

#include <iostream>
#include <thread>
#include "Application/Patient.h"
#include "Application/Battery.h"
#include "Bot/Bot.h"
#include "Dds/DataPacketPubSubTypes.h"
#include "Dds/AUTUtility.h"

/** 
* 
*Function Name : main
*
* Description  : This is the main function of the Bot in the Test Environment.
* 		    2 threads are running in this main to run the RTPS system in BOT
* 		   one for the publisher(to publish the result) and 
* 		   other for the subscriber (to receive the function call)			   
* 
* Parameters   : None
* 
* Return Value :  0
* 
* 
*/

int main()
{
	Bot bot;
	std::cout << "Result for getPatientName: " << bot.RunUnitTest("getPatientName int") << std::endl;
	std::cout << "Result for add double 10 20: " << bot.RunUnitTest("add double 10 20") << std::endl;
	std::cout << "Result for subtract double 10 20: " << bot.RunUnitTest("subtract double 10 20") << std::endl;
	std::cout << "Result for setBatteryPercentage void 75: " << bot.RunUnitTest("setBatteryPercentage void 75") << std::endl;
	std::cout << "Result for Wrong Function: " << bot.RunUnitTest("Wrong Function") << std::endl;	
	
	AUTUtility Aut;
	std::thread t1(SubscriberMain, &Aut);  
	std::thread t2(PublisherMain, &Aut);	


	while(1)
	{
		if(Aut.getMsg()!= "")
		{	std::string result = bot.RunUnitTest(Aut.getMsg());	
			Aut.setResultMsgPub(result);
		 	if(Aut.getMsg() == "divide double 10 15 ")
			{
				Aut.setMsg("");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				Aut.m_stop = true;
				break;
			}
		 
			Aut.setMsg("");
		}
	}

	std::cout << "B4 T1 join"<<std::endl;
	t1.join();
	std::cout << "B4 T2 join"<<std::endl;
	std::cout <<Aut.getMsg() <<std::endl;

	t2.join();	
	std::cout << "After T2 join"<<std::endl;

	return 0;
}
