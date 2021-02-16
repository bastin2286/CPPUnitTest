pipeline 
{
    agent any
    stages 
	{
		/*Waiting for project github event*/
		stage('Build Trigger [SCM poll]') 
		{
		    
			steps 
			{
				echo "********Waiting for SCM event - IN PROGRESS***********"

				script 
				{
				    properties([pipelineTriggers([pollSCM('* * * * *')])])
				}
				echo "Waiting for SCM event - Done"
				git branch: 'master', credentialsId: 'nandu', url: 'https://github.com/nandunarayanan/UnitGUIRestAPI.git'
				echo "Testing for SCM event - Done"
			}
		}   
		
        	/*Checkout the test runner and test environment artifacts*/
		stage('Checkout')
		{
			steps 
			{
				echo "************Checkout SCM repository to the Host server - IN PROGRESS***********"
				sh label: '', script: '/home/bastin/JenkinsCmd/gitPull.sh'
				echo  "************Checkout SCM repository to the Host server - DONE ****************"
			}
		}
		/*Test automation and Product build chaining*/
		stage('Build Management')
		{
			steps 
			{
				echo "************Building the Test Runner files- IN PROGRESS ************"
				
				sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/UnitTesting/TestRunner/src/Build.sh'
				
				echo "************Building the Test Runner files - DONE************"
				echo "************Building the Test Environment files- IN PROGRESS ************"
				echo "************Building the Test Environment files- Done ************"
			}
		}  
		/*Deployment*/               
		stage('Deployment')
		{
			steps 
			{
				echo "************Deployment to Test Environment & Test Runner - IN PROGRESS ************"
				
				sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/Deployment/FileTransfer.sh'
				
				sh label: '', script: '''cd  /home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/SonarTesting/
                                    echo jenkins | sudo -S cp -R  ./* /var/lib/jenkins/workspace/UnitGUIRestfulAPI_Test/'''
				
				echo "************Deployment to Test Environment & Test Runner - DONE************"
			}
		}
            	/*Static code analyzing of AUT*/
		stage('Static Code Analyzing')
		{
			steps 
			{
				echo "************Sonarqube-AUT Static Code Analysing - IN PROGRESS ************"
				 sh 'mvn -B clean package'
				 sh 'mvn test'
				withSonarQubeEnv(installationName: 'SonarQube') 
            	{ 
                  sh 'mvn org.sonarsource.scanner.maven:sonar-maven-plugin:3.7.0.1746:sonar'
                }
				
				timeout(time: 1, unit: 'HOURS') 
				{
					waitForQualityGate abortPipeline: true
				}
				
				echo "************Sonarqube-AUT Static Code Analysing - DONE************"
			}
		}
            
		stage('C++ AUT-Unit testing')
		{
			steps 
			{
				parallel("Execute Google Test from [Host Server]":
				{
				
					echo "************Execution of Google Test from the Host server - IN PROGRESS************"
					
					//sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/UnitTesting/TestRunner/src/BotRun.sh'
					sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/UnitTesting/TestRunner/src/Gtest_Exec BotTestCase.csv --gtest_output="xml:ReportFromLinuxGtestBot.xml" --gtest_filter=-API*'
					//sh label: '', script: 'cp /home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/UnitTesting/TestRunner/src/ReportFromLinuxGtestBot.xml /var/lib/jenkins/workspace/UnitGUIRestfulAPI_Test/'
					
					echo "************Execution of Google Test from the Host server - DONE************"
							
					
				},
				"Execution of BOT level Testing":
				{
						
				   
					echo "************Execution of BOT level Testing - IN PROGRESS************"
					
					sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/Deployment/ExecutionBot.sh'
					
					echo "************Execution of BOT level Testing - DONE************"
						
				
				})
			}
		}
            	/*Test coverage*/
		stage('Test Coverage(C++ Unit Test)')
		{
			steps 
			{
				echo "************Sonarqube Coverage Reporting - IN PROGRESS************"
				//squish([host: 'proxy60.rt3.io', port: '36113', squishPackageName: 'Default', testSuite: 'home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/RestfulTesting/TestSuite/suite_Ex_bdd_suite2'])
				echo "************Sonarqube Coverage Reporting- DONE************"
			}
		}
            	/*Component level testing*/
		stage('C++ AUT-Component testing')
		{
			steps 
			{
				parallel("Execute Google Test from [Host Server]":
				{
				
					echo "************Execution of API level Testing in the Host server - IN PROGRESS************"
					
					//sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/UnitTesting/TestRunner/src/ApiRun.sh'
					sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/UnitTesting/TestRunner/src/Gtest_Exec ApiTestCase.csv --gtest_output="xml:ReportFromLinuxGtestApi.xml" --gtest_filter=API*:CSV*'
					//sh label: '', script: 'cp /home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/UnitTesting/TestRunner/src/ReportFromLinuxGtestApi.xml /var/lib/jenkins/workspace/UnitGUIRestfulAPI_Test/'
					
					echo "************Execution of API level Testing in the Host server - DONE************"
						
				
				},
				"Execution of API level Testing":
				{
						
				   
					echo "************Execution of API level Testing in TestRunner - IN PROGRESS************"
					
					sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/Deployment/ExecutionApi.sh'
					
					echo "************Execution of API level Testing in TestRunner - DONE************"
						
				
				})
			}
		}
            
            	/*Test coverage*/
		stage('Test Coverage(C++ AUT-Component test)')
		{
			steps 
			{
				echo "************Sonarqube Coverage Reporting - IN PROGRESS************"
				//squish([host: 'proxy60.rt3.io', port: '36113', squishPackageName: 'Default', testSuite: 'home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/RestfulTesting/TestSuite/suite_Ex_bdd_suite2'])
				echo "************Sonarqube Coverage Reporting- DONE************"
			}
		}
           
            	/*Desktop GUI testing*/
		stage('Desktop AUT- GUI Testing')
		{
			steps 
			{
				echo "************Squish Desktop from the [Host Server] - IN PROGRESS************"
				//sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/DesktopGUITesting/squishDesktopRun.sh'
				sh label: '', script: '''export SQUISH_LICENSEKEY_DIR="/home/bastin"
                                        echo "==============Running Desktop API Application================"'''
                sh label: '', script: '''/home/bastin/squish-for-qt-6.6.1/bin/squishrunner --host localhost --port 4322 --testsuite /home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/DesktopGUITesting/suite_js --reportgen xmljunit,results_Desktop.xml --exitCodeOnFail 1'''
				echo "************Squish Desktop from the [Host Server] - DONE************"
			}
		}
            	/*Test coverage*/
		stage('Test Coverage(Desktop AUT)')
		{
			steps 
			{
				echo "************Sonarqube Coverage Reporting - IN PROGRESS************"
				//squish([host: 'proxy60.rt3.io', port: '36113', squishPackageName: 'Default', testSuite: 'home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/RestfulTesting/TestSuite/suite_Ex_bdd_suite2'])
				echo "************Sonarqube Coverage Reporting- DONE************"
			}
		}
            	/*Web application GUI testing*/
		stage('Web AUT- GUI Testing')
		{
			steps 
			{
				echo "************Squish from the [Host Server] - IN PROGRESS************"
				//sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/WebGUITesting/SquishWebRun.sh'
				sh label: '', script: '''export SQUISH_LICENSEKEY_DIR="/home/bastin"
                                        echo "==============Running Desktop API Application================"'''
                sh label: '', script: '''/home/bastin/squish-for-web-6.6.1/bin/squishrunner --host proxy61.rt3.io --port 31633 --testsuite /home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/WebGUITesting/suite_gwt1 --reportgen xmljunit,results_Web_GUI.xml --exitCodeOnFail 1'''
				echo "************Squish from the [Host Server] - DONE************"
			}
		}
		/*Test coverage*/	
		stage('Test Coverage (Web AUT- GUI Testing)')
		{
			steps 
			{
				echo "************Sonarqube Coverage Reporting - IN PROGRESS************"
				//squish([host: 'proxy60.rt3.io', port: '36113', squishPackageName: 'Default', testSuite: 'home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/RestfulTesting/TestSuite/suite_Ex_bdd_suite2'])
				echo "************Sonarqube Coverage Reporting- DONE************"
			}
		}
		/*Web application rest api testing*/            
		stage('Web AUT- Restful API Testing')
		{
			steps 
			{
				echo "************Squish from the [Host Server] - IN PROGRESS************"
				//sh label: '', script: '/home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/RestfulTesting/SquishRun.sh'
				sh label: '', script: '''export SQUISH_LICENSEKEY_DIR="/home/bastin"
                                        echo "==============Running Desktop API Application================"'''
                sh label: '', script: '''/home/bastin/squish-for-web-6.6.1/bin/squishrunner --host proxy61.rt3.io --port 31633 --testsuite /home/bastin/UnitGUIRestAPI/UnitGUIRestAPI//RestfulTesting/TestSuite/suite_Ex_bdd_suite2 --reportgen xmljunit,results_RestAPI.xml --exitCodeOnFail 1'''
				echo "************Squish from the [Host Server] - DONE************"
			}
		}
            	/*test coverage*/
		stage('Test Coverage (Web AUT- Restful API)')
		{
			steps 
			{
				echo "************Sonarqube Coverage Reporting - IN PROGRESS************"
				//squish([host: 'proxy60.rt3.io', port: '36113', squishPackageName: 'Default', testSuite: 'home/bastin/UnitGUIRestAPI/UnitGUIRestAPI/RestfulTesting/TestSuite/suite_Ex_bdd_suite2'])
				echo "************Sonarqube Coverage Reporting- DONE************"
			}
		}
            
    	}/*End of stages*/
        
	post 
	{
		always 
		{
		    
			echo "************Publishing SonarQube test result - IN PROGRESS************"
			junit 'target/surefire-reports/*.xml'
			echo "************Publishing SonarQube test result - IN PROGRESS************"
			
			echo "************Publishing xUnit result  - IN PROGRESS************"
			xunit([GoogleTest(deleteOutputFiles: true, failIfNotNew: true, pattern: 'ReportFromLinuxGtest*.xml', skipNoTestFiles: false, stopProcessingIfError: true)])
			echo "************Publishing xUnit result from child node1 - Done************"
			
			echo "************Publishing Squish test result - IN PROGRESS************"
			step([$class: 'XUnitBuilder', testTimeMargin: '3000', thresholdMode: 1, thresholds: [], tools: [JUnit(deleteOutputFiles: true, failIfNotNew: true, pattern: 'results_*.xml', skipNoTestFiles: false, stopProcessingIfError: true)]])
			echo "************Publishing Squish test result - Done************"
		}
	}
}
