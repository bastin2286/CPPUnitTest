#! /bin/bash

check()
{
        if test -f "$FILE"; then
                if test -f "$FILE1"; then
                        echo "exit 0"
                        return 0
                else
                        return 1
                fi
        fi
}

cd /src/jenkinsDocker/UnitGUIRestAPI/UnitTesting/TestEnvironment/AUTRunner
cmake . && make
cd /src/jenkinsDocker/UnitGUIRestAPI/UnitTesting/TestRunner/build
cmake . && make

FILE=/src/jenkinsDocker/UnitGUIRestAPI/UnitTesting/TestEnvironment/AUTRunner/AUT_Exec
FILE1=/src/jenkinsDocker/UnitGUIRestAPI/UnitTesting/TestRunner/Gtest_Exec

/bin/bash
