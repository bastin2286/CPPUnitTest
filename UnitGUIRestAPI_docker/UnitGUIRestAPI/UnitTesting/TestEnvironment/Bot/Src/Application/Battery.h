/*!
 * @file Battery.h
 * This header file contains the functions for Battery class.
 * This is part of the sample code developed for demostration of end to end application
 */
#pragma once

/*!
 * @brief This enum is used to represent the current status of Battery
 */
enum BATT
{
    BATT_WORKING,
    BATT_SERVICE,
    BATT_FAILURE
};

/*!
 * @brief This class represents the Battery and its related variables and functions
 */
class Battery
{
private:
    /*!
     * @brief private variables
     */
    double m_batteryPercentage;
    BATT m_batteryStatus;

public:
    /*!
     * @brief default constructor
     */
    Battery();
    
    /*!
     * @brief default destructor
     */
    ~Battery();
    
    /*!
     * @brief This function returns the current battery percentage
     * @return the current battery percentage
     */
    double getBatteryPercentage();
    
    /*!
     * @brief This function sets the current battery percentage
     * @param current battery percentage
     */
    void setBatteryPercentage(double percentage);
    
    /*!
     * @brief This function returns the current battery status
     * @return current battery status
     */
    BATT getBatteryStatus();
    
    /*!
     * @brief This function sets the current battery status
     * @param current battery status
     */
    void setBatteryStatus(BATT status);
};

