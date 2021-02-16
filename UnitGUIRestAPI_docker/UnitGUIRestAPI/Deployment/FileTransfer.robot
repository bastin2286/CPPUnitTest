* Settings *
Documentation     This test case ensure that the application under test, test scripts are deployed into remote hardware
...               from the Host test server
Library           SCPLibrary
Library           SSHLibrary
Variables      Configuration.py

* Test Cases *
Transfer the file to the target test folder
    [Timeout]    10 minutes
    SCPLibrary.Open Connection    ${HOST}    port=${PORT}    username=${USERNAME}    password=${PASSWORD}
    SCPLibrary.put directory    ${HALHostPath}    ${HALDeployPath}
    SCPLibrary.Close Connection
