#! /bin/bash

echo "======================Setting PWD========================"
cd /home/bastin/JavaTest/simple-java-maven-app-master/

echo "======================Maven Sonarqube cmd========================"
mvn sonar:sonar   -Dsonar.projectKey=Google_Test   -Dsonar.host.url=http://localhost:9000   -Dsonar.login=956434bd432b6190c47fd6843147b1fc6ceb89d5
