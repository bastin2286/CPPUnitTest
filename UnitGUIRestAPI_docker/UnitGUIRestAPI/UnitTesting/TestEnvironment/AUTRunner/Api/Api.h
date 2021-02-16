#pragma once
#include <string>
#include "../Application/Patient.h"
#include "../Application/Battery.h"
#include "../MathLib.h"
/*!
 * @brief This class represents the Bot variables and functions
 */
class Api
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
	Api();
    /*!
     * @brief Default destructor.
     */
	~Api();

    /*!
     * @brief This function runs the test case passed to it and sent back the result after processing
     * @param testcase contains the testcase string to be processed
     * @return the result for the given test case
     */
	std::string Run(std::string testcase);

};

