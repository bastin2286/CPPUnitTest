
/*!
 * @file Bot.h
 * This header file contains the functions for Bot execution.
 *
 */
#pragma once
#include <string>
#include "../Application/Patient.h"
#include "../Application/Battery.h"
#include "../MathLib.h"

/*!
 * @brief This class represents the Bot variables and functions
 */
class Bot
{    
    /*!
     * @brief Private member variables.
     */
    Battery m_batt;
    Patient m_patient;
    MathLibrary::Arithmetic m_arithmetic;
public:
	
    /*!
     * @brief Default constructor.
     */
    Bot();
    /*!
     * @brief Default destructor.
     */
    ~Bot();

    /*!
     * @brief This function runs the test case passed to it and sent back the result after processing
     * @param testcase contains the testcase string to be processed
     * @return the result for the given test case
     */
    std::string RunUnitTest(std::string testcase);

};

