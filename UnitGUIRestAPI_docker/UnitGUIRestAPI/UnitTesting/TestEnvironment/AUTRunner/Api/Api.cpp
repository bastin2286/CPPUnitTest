/**
 * File Name      : Api.cpp
 *  
 * Description    : This file is responsible for all API's used in the system
 *
 * Modifiled Date : 22/09/2020
 *
 */
#include <string>
#include <sstream>
#include <iostream>
#include "Api.h"

/** 
* 
*Function Name : Api
*
* Description  : This function is a default constructor 				   
* 
* Parameters   : None
* 
* Return Value : None
* 
* 
*/
 
Api::Api()
{

}


/** 
* 
*Function Name : Api
*
* Description  : This function is a default destructor 				   
* 
* Parameters   : None
* 
* Return Value : None
* 
* 
*/

Api::~Api() 
{

}

/** 
* 
*Function Name : Run
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
 
std::string Api::Run(std::string testcase)
{
	std::string result = "Fail";

	int i_arg1;
	int i_arg2;
	int i_arg3;
	int i_result;

	char c_arg1;
	char c_arg2;
	char c_arg3;
	char c_result;

	float f_arg1;
	float f_arg2;
	float f_arg3;
	float f_result;

	double d_arg1;
	double d_arg2;
	double d_arg3;
	double d_result;
	
	std::stringstream s(testcase); // Used for breaking words
        std::string rule;	
	std::string fn;
	std::string returnType;
	std::string dtype_arg1;
	std::string arg1;
	std::string dtype_arg2;
	std::string arg2;
	std::string dtype_arg3;
	std::string arg3;
	short count = 0;
	
	if(s>>rule)
	{
		if(rule == "1")
		{
			if (s >> fn)
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
				std::cout << "Invalid function" << std::endl;
			}
		}
		else
		{
			if (s >> fn)
			{
				if (s >> dtype_arg1)
				{
					if (s >> arg1)
					{
						count++;
						if(s>> dtype_arg2)
						{
							if (s >> arg2)
							{
								count++;
								if(s >> dtype_arg3)
								{
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
									std::cout << "Invalid arg3 type" << std::endl;
								}
							}
							else
							{
								std::cout << "Invalid arg2" << std::endl;
							}
						}
						else
						{
							std::cout << "Invalid arg2 type" << std::endl;
						}
					}
					else
					{	
						std::cout << "Invalid arg1" << std::endl;
					}
				}
				else
				{
					std::cout << "Invalid arg1 type" << std::endl;
				}
			}
			else
			{
				std::cout << "Invalid function" << std::endl;
			}
		}
	}
				
	std::cout << "Count: " << count <<  std::endl;
/*
	switch (dtype_arg1)
	{
		case "int":
			i_arg1 = stoi(arg1);
			break;
		case "float":
			f_arg1 = stof(arg1);
			break;
		case "char":
			c_arg1 = *arg1;
			break;
		case "double":
			d_arg1 = stod(arg1);
			break;
		default:
			return 0;
	}
	switch (dtype_arg2)
	{
		case "int":
			i_arg1 = stoi(arg2);
			break;
		case "float":
			f_arg1 = stof(arg2);
			break;
		case "char":
			c_arg1 = *arg2;
			break;
		case "double":
			d_arg1 = stod(arg2);
			break;
		default:
			return 0;
	}
	switch (dtype_arg3)
	{
		case "int":
			i_arg1 = stoi(arg3);
			break;
		case "float":
			f_arg1 = stof(arg3);
			break;
		case "char":
			c_arg1 = *arg3;
			break;
		case "double":
			d_arg1 = stod(arg3);
			break;
		default:
			return 0;
	}
*/
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
		if(rule == "1")
		{
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
		}
		else
		{
			if ("add" == fn)
			{
				if ((dtype_arg1 == "int") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Add(stoi(arg1), stoi(arg2)));
				if ((dtype_arg1 == "int") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Add(stoi(arg1), stof(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Add(stof(arg1), stoi(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Add(stof(arg1), stof(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Add(stod(arg1), stoi(arg2)));
				if ((dtype_arg1 == "int") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Add(stoi(arg1), stod(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Add(stod(arg1), stod(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Add(stof(arg1), stod(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Add(stod(arg1), stof(arg2)));
			}
			else if ("subtract" == fn)
			{
				if ((dtype_arg1 == "int") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Subtract(stoi(arg1), stoi(arg2)));
				if ((dtype_arg1 == "int") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Subtract(stoi(arg1), stof(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Subtract(stof(arg1), stoi(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Subtract(stof(arg1), stof(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Subtract(stod(arg1), stoi(arg2)));
				if ((dtype_arg1 == "int") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Subtract(stoi(arg1), stod(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Subtract(stod(arg1), stod(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Subtract(stof(arg1), stod(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Subtract(stod(arg1), stof(arg2)));
			}
			else if ("multiply" == fn)
			{
				if ((dtype_arg1 == "int") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Multiply(stoi(arg1), stoi(arg2)));
				if ((dtype_arg1 == "int") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Multiply(stoi(arg1), stof(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Multiply(stof(arg1), stoi(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Multiply(stof(arg1), stof(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Multiply(stod(arg1), stoi(arg2)));
				if ((dtype_arg1 == "int") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Multiply(stoi(arg1), stod(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Multiply(stod(arg1), stod(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Multiply(stof(arg1), stod(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Multiply(stod(arg1), stof(arg2)));
			}
			else if ("divide" == fn)
			{
				if ((dtype_arg1 == "int") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Divide(stoi(arg1), stoi(arg2)));
				if ((dtype_arg1 == "int") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Divide(stoi(arg1), stof(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Divide(stof(arg1), stoi(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Divide(stof(arg1), stof(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "int"))
					result = std::to_string(m_arithmetic.Divide(stod(arg1), stoi(arg2)));
				if ((dtype_arg1 == "int") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Divide(stoi(arg1), stod(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Divide(stod(arg1), stod(arg2)));
				if ((dtype_arg1 == "float") && (dtype_arg2 == "double"))
					result = std::to_string(m_arithmetic.Divide(stof(arg1), stod(arg2)));
				if ((dtype_arg1 == "double") && (dtype_arg2 == "float"))
					result = std::to_string(m_arithmetic.Divide(stod(arg1), stof(arg2)));
			}
		}
		break;	
	default:
		result = "Fail";
		break;

	}
	return result;
}
