/**
* File Name      : Battery.cpp
*  
* Description    : This file is responsible for all battery related 
*			processing in the system
*
* Modifiled Date : 22/09/2020
*
*/
#include "Battery.h"

/** 
* 
*Function Name : Battery
*
* Description  : This function is a default constructor 				   
* 
* Parameters   : None
* 
* Return Value : None
* 
* 
*/
Battery::Battery()
{

}

/** 
* 
*Function Name : Battery
*
* Description  : This function is a default destructor 				   
* 
* Parameters   : None
* 
* Return Value : None
* 
* 
*/
Battery::~Battery()
{

}

/** 
* 
*Function Name : getBatteryPercentage
*
* Description  : This function returns the current battery percentage 				   
* 
* Parameters   : None
* 
* Return Value : the current battery percentage
* 
* 
*/
double Battery::getBatteryPercentage()
{
    return m_batteryPercentage;
}

/** 
* 
*Function Name : setBatteryPercentage
*
* Description  : This function sets the current battery percentage 				   
* 
* Parameters   : current battery percentage
* 
* Return Value : None
* 
* 
*/
void Battery::setBatteryPercentage(double percentage)
{
    m_batteryPercentage = percentage;
}

/** 
* 
*Function Name : getBatteryStatus
*
* Description  : This function returns the current battery status 				   
* 
* Parameters   : None
* 
* Return Value : the current battery status
* 
* 
*/
BATT Battery::getBatteryStatus()
{
    return m_batteryStatus;
}

/** 
* 
*Function Name : setBatteryStatus
*
* Description  : This function sets the current battery status 				   
* 
* Parameters   : current battery status
* 
* Return Value : None
* 
* 
*/
void Battery::setBatteryStatus(BATT status)
{
    m_batteryStatus = status;
}
