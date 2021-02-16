#pragma once

#include <string>
class Patient
{
private:
    /*!
     * @brief This enum is used to represent the current status of Battery
     */
    std::string m_patientName;
    long m_age;
    char m_gender;
    std::string m_patientID;

public:    
    /*!
     * @brief default constructor
     */
    Patient();
    /*!
     * @brief default destructor
     */
    ~Patient();
    
    /*!
     * @brief This function returns the patient name
     * @return the patient name
     */
    std::string getPatientName();
    
    /*!
     * @brief This function sets the patient name
     * @param name patient name
     */
    void setPatientName(std::string name);
    
    /*!
     * @brief This function sets the age
     * @return patient age
     */
    long getAge();
    
    /*!
     * @brief This function returns the age of patient
     * @param age is the patient age
     */
    void setAge(long age);
    
    /*!
     * @brief This function returns the gender of patient
     * @return the patient gender
     */
    char getGender();
    
    /*!
     * @brief This function returns the gender of patient
     * @param gender is the patient gender
     */
    void setGender(char gender);
    
    /*!
     * @brief This function returns the patient ID
     * @param ID is the patient
     */
    std::string getPatientID();
    
    /*!
     * @brief This function generates a random patientID
     */
    void generatePatientID();
};

