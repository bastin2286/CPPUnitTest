#! /bin/bash

echo "======================Setting PWD========================"
cd /home/pi/TestEnvironment/Bot/
echo "=====================cmake operation===================="
cmake CMakeLists.txt
echo "=====================make operation====================="
make clean all
echo "==============Execution of the Binary=================="
./BOT
echo "===============================Completed========================"
