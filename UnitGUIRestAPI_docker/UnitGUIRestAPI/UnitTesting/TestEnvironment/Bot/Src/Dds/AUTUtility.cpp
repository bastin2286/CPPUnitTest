#include "AUTUtility.h"
#include<iostream>

using namespace std;

/*!
 * @brief Default constructor.
 */
AUTUtility::AUTUtility(): m_msg("")
			, m_Resultmsg("")
			, messageCounter(0)
	                , m_stop(false)
{
}


/*!
 * @brief This function returns a message recieved from Server
 * @return recieved message(m_msgRecived)
 */
string AUTUtility::getMsg()
{
	return m_msg;
}

/*!
 * @brief This function sets message recieved from Server
 * @param recieved message
 */
void AUTUtility::setMsg(string msg)
{
	m_msg = msg;
	cout << "Setting setmg: "<< m_msg <<"####" <<endl;
}

/*!
 * @brief This function returns the result message string
 * @return Result Message string
 */  
string AUTUtility::getResultMsgPub()
{
      return m_Resultmsg;
}

/*!
 * @brief This function sets result message
 * @param msg Result message
 */
void AUTUtility::setResultMsgPub(string msg)
{
      m_Resultmsg = msg;
}
