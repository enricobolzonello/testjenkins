pipeline {
    agent any
    stages {
        stage('Build') {
            steps {
                sh 'cd webapp && npm install --production'
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
                sh './webapp/jenkins/deliver.sh' 
                //input message: 'Finished using the web site? (Click "Proceed" to continue)' 
                //sh './jenkins/scripts/kill.sh' 
            }
        }
    }
}