* Settings *
Documentation     This test case ensure that the application under test is executed from Targer Envirnment
Library           SSHLibrary
Variables      Configuration.py
* Test Cases *
Execute AUT_Exec from Target
   
    SSHLibrary.Open Connection    ${HOST}    port=${PORT}    timeout=30s 
    Login    ${USERNAME}    ${PASSWORD} 
    Execute Command    chmod 777 -R ${HALTestFolderPath} 
    Execute Command    ${HALTestFolderPathAutExec}
