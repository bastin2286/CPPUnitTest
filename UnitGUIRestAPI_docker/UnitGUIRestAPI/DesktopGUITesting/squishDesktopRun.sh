#! /bin/bash

echo "======================Setting PWD========================"
echo jenkins | sudo -S ls
cd /home/bastin/squish-for-qt-6.6.1/bin
export SQUISH_LICENSEKEY_DIR="/home/bastin"
echo "==============Running Desktop API Application================"
./squishrunner --host localhost --port 4322 --testsuite /home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/DesktopGUITesting/suite_js --reportgen xmljunit,results_Desktop.xml

echo "=================Copying the generated file to the workspace=============="
echo jenkins | sudo -S cp results_Desktop.xml /var/lib/jenkins/workspace/UnitGUIRestfulAPI_Test/
