pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                sh 'cd webapp && npm install'
            }
        }
        stage('Test') {
            steps {
                echo 'test'
                //sh './jenkins/scripts/test.sh'
            }
        }
        stage('Deliver') { 
            steps {
                echo 'deliver'
                //sh './jenkins/scripts/deliver.sh' 
                //input message: 'Finished using the web site? (Click "Proceed" to continue)' 
                //sh './jenkins/scripts/kill.sh' 
            }
        }
    }
}