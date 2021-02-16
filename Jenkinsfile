pipeline 
{
    agent none
    stages 
    {
        stage('SCM Poll') 
        {
            agent any
            steps 
            {  
               /*
                sh '''ssh \'318356@10.10.196.129\' /home/testVolume/copy_del.sh'''
                checkout([$class: 'GitSCM', 
				branches: [[name: "origin/master"]], 
				userRemoteConfigs: [[
                url: 'https://github.com/nandunarayanan/dockerJenkins.git']]
				])
				*/
				sh '''ssh \'318356@10.10.196.129\' ls -la /home/testVolume/'''
				sh '''ssh \'318356@10.10.196.129\' /home/testVolume/clone.sh'''
				sh '''ls -la'''
				sh '''pwd'''
                sh '''ssh \'318356@10.10.196.129\' docker volume create volBuild'''
                sh '''ssh \'318356@10.10.196.129\'  ssh \'853420@10.10.196.130\' docker volume create volAUT'''
            }
        }
        
        stage('BuildManager')
        {   
            agent any
            steps
            {
                
                sh '''ssh \'318356@10.10.196.129\' /home/testVolume/copy_vol.sh'''
                sh '''ssh \'318356@10.10.196.129\' docker pull localhost:5000/buildmanager_cpp:v1'''
                sh '''ssh \'318356@10.10.196.129\' docker run --name buildManager_cpp -v volBuild:/src localhost:5000/buildmanager_cpp:v1'''
                sh '''ssh \'318356@10.10.196.129\' /home/testVolume/copy.sh'''
            }
        }
        
        
        stage('AUT Runner[Deployment & Execution]')
        {   
            agent any
            steps
            {
                sh '''ssh \'318356@10.10.196.129\' ssh \'853420@10.10.196.130\' /nfs/home/testVolume/copy_130.sh'''
                sh '''ssh \'318356@10.10.196.129\' ssh \'853420@10.10.196.130\' docker pull 10.10.196.129:5000/aut_cpp:v1'''
                sh '''ssh \'318356@10.10.196.129\' ssh \'853420@10.10.196.130\' docker run -d -it -p 10.10.196.130:5100:5100 --name aut_cpp -v volAUT:/src 10.10.196.129:5000/aut_cpp:v1'''
            }
        }
        
        stage('TestRunner[Deployment & Execution]')
        {   
            agent any
            steps
            {
                sh '''ssh \'318356@10.10.196.129\' docker pull localhost:5000/testrunner_cpp:v2'''
                sh '''ssh \'318356@10.10.196.129\' docker run -p 10.10.196.129:5100:5100 --name testRunner_cpp --volumes-from buildManager_cpp localhost:5000/testrunner_cpp:v2'''
            }
        }
        
        stage('Publishing Results')
        {   
            agent any
            steps
            {
                sh '''ssh \'318356@10.10.196.129\' cat /home/testVolume/copy_xml.sh'''
                sh '''ssh \'318356@10.10.196.129\' /home/testVolume/copy_xml.sh'''
                xunit([GoogleTest(deleteOutputFiles: true, failIfNotNew: true, pattern: 'Gtest*.xml', skipNoTestFiles: false, stopProcessingIfError: true)])
            }
        }
        
        stage('Clearing Active Containers')
        {   
            agent any
            steps
            {
                sh ''' echo "Test"'''
                sh '''ssh \'318356@10.10.196.129\' ssh \'853420@10.10.196.130\' docker stop aut_cpp'''
                sh '''ssh \'318356@10.10.196.129\' ssh \'853420@10.10.196.130\' docker rm aut_cpp'''
                sh '''ssh \'318356@10.10.196.129\' docker stop testRunner_cpp'''
                sh '''ssh \'318356@10.10.196.129\' docker rm testRunner_cpp'''
                sh '''ssh \'318356@10.10.196.129\' docker stop buildManager_cpp'''
                sh '''ssh \'318356@10.10.196.129\' docker rm buildManager_cpp'''
                sh '''ssh \'318356@10.10.196.129\' docker volume rm volBuild'''
                sh '''ssh \'318356@10.10.196.129\'  ssh \'853420@10.10.196.130\' docker volume rm volAUT'''
            }
        }
    }
}
