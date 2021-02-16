#! /bin/bash

echo "======================Setting PWD========================"
cd /home/bastin/squish-for-web-6.6.1/bin
export SQUISH_LICENSEKEY_DIR="/home/bastin"
echo "==============Running WEB API Application================"
./squishrunner --host proxy60.rt3.io --port 38878 --testsuite /home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/WebGUITesting/suite_gwt1 --reportgen xmljunit,/var/lib/jenkins/workspace/UnitGUIRestfulAPI_Test/results_Web_GUI.xml
