/******************************************************************************
 * File Name      : CsvRead.cpp
 *  
 * Description    : This file contains the library functions which are used 
 *					while testing. 
 *
 * Modifiled Date : 07/12/2020
 *
 *****************************************************************************/
#include <iostream>
#include <gtest/gtest.h>
#include <string>
#include <vector> 
#include <algorithm>
#include "CsvRead.h"

using namespace std;
/* Defining string vectors which are used in test files */
vector<string> words;
vector<string> words1;
vector<string> read_csv;
/******************************************************************************
*Function Name : getFileContent(std::string fileName, 
*				 std::vector<std::string> & vecOfStrs)
*
* Description  : This function will get the file content line by line and store
*				 it in a string vector.	   
* 
* Parameters   : std::string fileName, std::vector<std::string> & vecOfStrs
* 
* Return Value : bool
* 
******************************************************************************/
bool getFileContent(std::string fileName, std::vector<std::string> & vecOfStrs)
{
	/* Open the File */
	std::ifstream in(fileName.c_str());
	/* Check if object is valid */
    if(!in)
    {
    	return false;
    }
    std::string str;
    /* Read the next line from File untill it reaches the end. */
    while (std::getline(in, str))
    {
       	/* Line contains string of length > 0 then save it in vector */
       	if(str.size() > 0)
           	vecOfStrs.push_back(str);
    }
    /*Close The File */
    in.close();
    return true;
}
/******************************************************************************
*Function Name : void CsvReader(std::string filename)
*
* Description  : This function will get the file content and seperate the input 
*				 and ouput from the csv file and store it in the respective vectors. 
* 
* Parameters   : std::string filename
* 
* Return Value : None
* 
******************************************************************************/
void CsvReader(std::string filename)
{
	words.clear();
	words1.clear();
	read_csv.clear();
	std::vector<std::string> vecOfStr;
	std::string tmp,tmp2,r_dtype,input;
	char delim = ';'; 
	bool result = getFileContent(filename, vecOfStr);
	std::cout<<"result "<<result<<endl;
	if(result)
    {
    	for(std::string & line : vecOfStr)        
       	{
			std::string lCopy = line;
			replace(lCopy.begin(),lCopy.end(),',',' ');
			std::stringstream str_strm1(lCopy);
		    int c=0;
            while (std::getline(str_strm1, tmp, delim)) 
			{
			   	if (c == 0)
			   	{
			   		words.push_back(tmp);
		   	   		std::cout<<"tmp string : "<<tmp <<endl;
		   	   		std::stringstream str_stream(tmp);
		   	   		while (std::getline(str_stream, input, ' '))
		   	   		{
		   	   			read_csv.push_back(input);	   	
		   	   		}
		   	   		c++;   	
		   		}
		   		else
		   		{
					std::cout <<"Seperated value"<<tmp<<endl;		
		  			std::stringstream str_strm2(tmp);
					int c1=0;
		   			while(std::getline(str_strm2,tmp2,'%'))
					{
						if(c1 == 0)
						{
							r_dtype = tmp2;
							c1++;
						}
						else
						{
							if(r_dtype == "int")
							{
								int data_type;
								data_type = stoi(tmp2);
								tmp2 = to_string(data_type);
								std::cout <<"tmp2 = "<<tmp2<<endl;
								words1.push_back(tmp2);
								c1=0;
							}
							else if(r_dtype == "float")
							{
								float data_type;
								data_type = stof(tmp2);
								tmp2 = to_string(data_type);
								std::cout << "tmp2 = "<<tmp2<<endl;
								words1.push_back(tmp2);
								c1=0;
							}
							else if(r_dtype == "double")
							{
								double data_type;
								data_type = stod(tmp2);
								tmp2 = to_string(data_type);
								std::cout << "tmp2 = "<<tmp2<<endl;
								words1.push_back(tmp2);
								c1=0;
							}
							else
							{
								std::cout << "else tmp2 = "<<tmp2<<endl;
								words1.push_back(tmp2);
                               	c1=0;
							}
						}
					}
					c = 0;						
			   	}   
		   	}
       	}
   	}
}


