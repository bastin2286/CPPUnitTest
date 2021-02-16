/**
 * File Name      : Bot.cpp
 *  
 * Description    : This file is responsible for all Bot related usage used in the system
 *
 * Modifiled Date : 22/09/2020
 *
 */
#include <string>
#include <sstream>
#include <iostream>
#include "Bot.h"

/** 
* 
*Function Name : Bot
*
* Description  : This function is a default constructor 				   
* 
* Parameters   : None
* 
* Return Value : None
* 
* 
*/
Bot::Bot()
{

}


/** 
* 
*Function Name : Bot
*
* Description  : This function is a default destructor 				   
* 
* Parameters   : None
* 
* Return Value : None
* 
* 
*/
Bot::~Bot() 
{

}
/** 
* 
*Function Name : RunUnitTest
*
* Description  : This function runs the test case passed to it and sent back the 
*		  result after processing 				   
* 
* Parameters   : testcase contains the testcase string to be processed
* 
* Return Value : String which return to the test runner (the result for the given test case).
* 
* 
*/
std::string Bot::RunUnitTest(std::string testcase)
{
	std::string result = "Fail";

	std::stringstream s(testcase); // Used for breaking words   
	std::string fn;
	std::string returnType;
	std::string arg1;
	std::string arg2;
	std::string arg3;
	short count = 0;

	if (s >> fn)
	{
		if (s >> returnType)
		{
			if (s >> arg1)
			{
				count++;
				if (s >> arg2)
				{
					count++;
					if (s >> arg3)
					{
						count++;
					}
					else
					{
						std::cout << "Invalid arg3" << std::endl;
					}
				}
				else
				{
					std::cout << "Invalid arg2" << std::endl;
				}
			}
			else
			{
				std::cout << "Invalid arg1" << std::endl;
			}

		}
		else
		{
			std::cout << "Invalid return type" << std::endl;
		}
	}
	else
	{
		std::cout << "Invalid function" << std::endl;
	}
	std::cout << "Count: " << count <<  std::endl;


	switch (count)
	{
	case 0:
		if ("getPatientName" == fn)
		{
			result = m_patient.getPatientName();
		}
		else if ("getBatteryPercentage" == fn)
		{
			result = std::to_string(m_batt.getBatteryPercentage());
		}
		else if ("getBatteryStatus" == fn)
		{
			result = std::to_string(m_batt.getBatteryStatus());
		}
		else if ("getAge" == fn)
		{
			result = std::to_string(m_patient.getAge());
		}
		else if ("getPatientID" == fn)
		{
			result = m_patient.getPatientID();
		}
		else if ("getGender" == fn)
		{
			result = m_patient.getGender();
		}
		else if ("generatePatientID" == fn)
		{
			m_patient.generatePatientID();
			result = "Success";
		}
		break;
	case 1:
		if ("setBatteryPercentage" == fn)
		{
			m_batt.setBatteryPercentage(stod(arg1));
			result = "Success";
		}
		else if ("setBatteryStatus" == fn)
		{
			m_batt.setBatteryStatus(static_cast<BATT>(stol(arg1)));
			result = "Success";
		}
		else if ("setPatientName" == fn)
		{
			m_patient.setPatientName(arg1);
			result = "Success";
		}
		else if ("setGender" == fn)
		{
			m_patient.setGender(arg1.at(0));
			result = "Success";
		}
		else if ("setAge" == fn)
		{
			m_patient.setAge(stol(arg1));
			result = "Success";
		}
		break;
	case 2:
		if ("add" == fn)
		{
			result = std::to_string(m_arithmetic.Add(stod(arg1), stod(arg2)));
		}
		else if ("subtract" == fn)
		{
			result = std::to_string(m_arithmetic.Subtract(stod(arg1), stod(arg2)));
		}
		else if ("multiply" == fn)
		{
			result = std::to_string(m_arithmetic.Multiply(stod(arg1), stod(arg2)));
		}
		else if ("divide" == fn)
		{
			result = std::to_string(m_arithmetic.Divide(stod(arg1), stod(arg2)));
		}
		break;	
	default:
		result = "Fail";
		break;

	}
	return result;
}
