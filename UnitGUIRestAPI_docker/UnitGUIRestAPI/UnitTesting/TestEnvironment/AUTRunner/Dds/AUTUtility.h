  
/*!
 * @file AUTUtility.h
 * This header file contains the declaration of Utility functions required for AUT.
 *
 */
 #include <string>

/*!
 * @brief This class represents the AUT Utility variables and functions
 */
 
class AUTUtility 
{	
  /*!
   * @brief Private member variables.
   */
  std::string m_msg;
  std::string m_Resultmsg;
  int messageCounter;
  
  public:    
    /*!
     * @brief Public member variables.
     */
    bool m_stop; 
    
    /*!
     * @brief This function returns a message recieved from Server
     * @return recieved message(m_msgRecived)
     */
     
    std::string getMsg();       
    
    /*!
     * @brief This function sets message recieved from Server
     * @param recieved message
     */
    void setMsg(std::string msg);    
    
    /*!
     * @brief This function returns the result message string
     * @return Result Message string
     */    
    std::string getResultMsgPub();    
    
    /*!
     * @brief This function sets result message
     * @param msg Result message
     */
    void setResultMsgPub(std::string msg);
 
     
    /*!
     * @brief Default constructor.
     */
    AUTUtility();

};

/*!
 * @brief Subscriber Main thread function to send the messages from Test runner to test environment
 * @param c ServerUtility class pointer
 */
void SubscriberMain(AUTUtility* c);

/*!
 * @brief Publisher Main thread function to recieve the messages from Test environment to test runner
 * @param c ServerUtility class pointer
 */
void PublisherMain(AUTUtility* c);
