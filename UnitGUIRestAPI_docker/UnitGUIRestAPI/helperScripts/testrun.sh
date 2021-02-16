#! /bin/bash

cd jenkinsDocker/UnitGUIRestAPI/UnitTesting/TestRunner/build
./Gtest_Exec --gtest_output="xml:Gtestapi.xml" 
