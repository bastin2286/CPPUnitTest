 /**
 * File Name      : Patient.cpp
 *  
 * Description    : This file is responsible for all Patient related 
 *					processing in the system
 *
 * Modifiled Date : 22/09/2020
 *
 */
#include "Patient.h"

#include <time.h>
#include <iostream>
#include <stdlib.h>

/** 
* 
*Function Name : Patient
*
* Description  : This function is a default constructor 				   
* 
* Parameters   : None
* 
* Return Value : None
* 
* 
*/
  
Patient::Patient():
	m_patientName(""),
	m_age(0),
	m_gender('N'),
	m_patientID("INVALID")
{
}
/** 
* 
*Function Name : Patient
*
* Description  : This function is a default destructor 				   
* 
* Parameters   : None
* 
* Return Value : None
* 
* 
*/
Patient::~Patient()
{
}
/** 
* 
*Function Name : getPatientName
*
* Description  : This function returns the patient name			   
* 
* Parameters   : None
* 
* Return Value : the patient name
* 
* 
*/
 
std::string Patient::getPatientName()
{
	return m_patientName;
}

/** 
* 
*Function Name : setPatientName
*
* Description  : This function is a default destructor 				   
* 
* Parameters   : patient name
* 
* Return Value : None
* 
* 
*/

void Patient::setPatientName(std::string name)
{
	m_patientName = name;
}
/** 
* 
*Function Name : getAge
*
* Description  : This function sets the age of patient 				   
* 
* Parameters   : None
* 
* Return Value : gender of the patient
* 
* 
*/
long Patient::getAge()
{
	return m_age;
}
/** 
* 
*Function Name : setAge
*
* Description  : This function set the age of patient 				   
* 
* Parameters   : age of the patient
* 
* Return Value : None
* 
* 
*/
void Patient::setAge(long age)
{
	m_age = age;
}

/** 
* 
*Function Name : getGender
*
* Description  : This function returns the gender of patient 				   
* 
* Parameters   : None
* 
* Return Value : gender of the patient
* 
* 
*/
char Patient::getGender()
{
	return m_gender;
}
/** 
* 
*Function Name : setGender
*
* Description  : This function returns the gender of patient 				   
* 
* Parameters   : gender of the patient
* 
* Return Value : None
* 
* 
*/
void Patient::setGender(char gender)
{
	m_gender = gender;
}

/** 
* 
*Function Name : getPatientID
*
* Description  :  This function returns the patient ID 				   
* 
* Parameters   : None
* 
* Return Value : ID of the patient
* 
* 
*/

std::string Patient::getPatientID()
{
	return m_patientID;
}

/** 
* 
*Function Name : setPatientName
*
* Description  :  This function generates a random patientID 				   
* 
* Parameters   : None
* 
* Return Value : None
* 
* 
*/
void Patient::generatePatientID()
{
    srand(time(0));

    int len = 6;
    char valid[] = "1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char rand_array[250];
    const int l = 62;               // 62 is the length of string 'valid'

    for (int i = 0; i < len; ++i)
    {
        rand_array[i] = valid[rand() % l];
    }

    std::cout << "The Random Array is :\n" << rand_array;
}
