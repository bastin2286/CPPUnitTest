#! /bin/bash

echo "======================Setting PWD========================"
cd /home/bastin/squish-for-web-6.6.1/bin
export SQUISH_LICENSEKEY_DIR="/home/bastin"
echo "==============Running REST API Application================"
./squishrunner --host proxy60.rt3.io --port 38878 --testsuite /home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/RestfulTesting/TestSuite/suite_Ex_bdd_suite2 --reportgen xmljunit,/var/lib/jenkins/workspace/UnitGUIRestfulAPI_Test/results_RestAPI.xml
