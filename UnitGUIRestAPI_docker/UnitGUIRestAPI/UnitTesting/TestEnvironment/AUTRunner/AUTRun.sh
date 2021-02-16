#! /bin/bash

echo "======================Setting PWD========================"
cd /home/pi/TestEnvironment/AUTRunner/
echo "=====================cmake operation===================="
cmake CMakeLists.txt
echo "=====================make operation====================="
make clean all
echo "==============Execution of the Binary=================="
./AUT_Exec
echo "===============================Completed========================"
