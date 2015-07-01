#include <QMessageBox>
#include <QPixmap>
#include <QtGui>
#include <QInputDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
//#include "NetworkTester.h"

/*constructor function*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    /*Initialize variables*/
    ui->progressBar->setValue(0); // set progress bar to 0
    ui->NameEdit->setPlaceholderText("Fulano"); // example name inside of line
    ui->DomainEdit->setPlaceholderText("google.com"); // example domain inside of line
    ui->HostEdit->setPlaceholderText("localhost");
    ui->UsernameEdit->setPlaceholderText("ChannelJuan");
    ui->DatabaseEdit->setPlaceholderText("test");
    ui->PasswordEdit->setPlaceholderText("********");
    ui->EmailEdit->setPlaceholderText("example@email.com");
    ui->DisplayLogsCheck->setChecked(true); // by default sets as a check


}

MainWindow::~MainWindow(){
    delete ui;
}

/*GLOBAL VARIABLES TO ORQUESTRATE THE GUI*/
//====================================
std::string AttemptingDomain = ""; //NOTNULL
std::string NameOfComputer = ""; //NOTNULL
std::string RequestInterval = ""; //NOTNULL
std::string TimeoutValue = ""; //NOTNULL
std::string HOST = ""; //NOTNULL
std::string USERNAME = ""; //NOTNULL
std::string PASSWORD = ""; // can be null
std::string DATABASE = ""; // NOTNULL
int DomainChanges = 0;
int NameChanges = 0;
int RequestChanges = 0;
int IntervalChanges = 0;
int HostChanges = 0;
int UsernameChanges = 0;
int PasswordChanges = 0;
int DatabaseChanges = 0;
bool loggingStarted = false;
bool displayLogs = true;
//=====================================


/* function that executes the actual program*/
void executeStuff(){
    // check to see if the inputted stuff is valid
    // if valid continue
    // else try inputting again
    std::cout << "WE ARE ABOUT TO RUN THE MAIN PROGRAM!!" << std::endl;
    loggingStarted = true;
}

//=====================
/*Signal Handlers*/
//=====================


//**** PROGRESS BAR ****
void MainWindow::on_progressBar_valueChanged(int value){
    if(AttemptingDomain == ""){
        ui->progressBar->setValue(ui->progressBar->value()-1);
    }
}

//** TEXT BOXES ****
void MainWindow::on_DomainEdit_textChanged(const QString &arg1){
    QString input = ui->DomainEdit->text();
    AttemptingDomain = input.toStdString();
}
void MainWindow::on_NameEdit_textChanged(const QString &arg1){
    QString input = ui->NameEdit->text();
    NameOfComputer = input.toStdString();
}
void MainWindow::on_HostEdit_textChanged(const QString &arg1){
    QString input = ui->HostEdit->text();
    HOST = input.toStdString();
}
void MainWindow::on_UsernameEdit_textChanged(const QString &arg1){
    QString input = ui->UsernameEdit->text();
    USERNAME = input.toStdString();
}
void MainWindow::on_DatabaseEdit_textChanged(const QString &arg1){
    QString input = ui->DatabaseEdit->text();
    DATABASE = input.toStdString();
}
void MainWindow::on_PasswordEdit_textChanged(const QString &arg1){
    QString input = ui->PasswordEdit->text();
    PASSWORD = input.toStdString();
}
void MainWindow::on_EmailEdit_textChanged(const QString &arg1){

}

//******** REQUEST SLIDER AND BOX ******
int REQUESTSLIDERGLOBAL = 0; // request slider global variable
void MainWindow::on_RequestTimeBox_valueChanged(const QString &arg1){
    REQUESTSLIDERGLOBAL = ui->RequestTimeBox->value();
    ui->RequestSlider->setValue(REQUESTSLIDERGLOBAL);

    /*convert from int to string*/
    std::stringstream ss;
    ss << REQUESTSLIDERGLOBAL;
    RequestInterval = ss.str();
}
void MainWindow::on_RequestSlider_sliderMoved(int position){
    REQUESTSLIDERGLOBAL = ui->RequestSlider->value();
    ui->RequestTimeBox->setValue(REQUESTSLIDERGLOBAL);

    /*convert from int to string*/
    std::stringstream ss;
    ss << REQUESTSLIDERGLOBAL;
    RequestInterval = ss.str();
}
void MainWindow::on_RequestSlider_sliderPressed(){
    REQUESTSLIDERGLOBAL = ui->RequestSlider->value();
    ui->RequestTimeBox->setValue(REQUESTSLIDERGLOBAL);

    /*convert from int to string*/
    std::stringstream ss;
    ss << REQUESTSLIDERGLOBAL;
    RequestInterval = ss.str();
}

//************TIMEOUT SLIDER AND BOX ***********
int TIMEOUTSLIDERGLOBAL = 0;
void MainWindow::on_TimeoutTimeBox_valueChanged(const QString &arg1){
    TIMEOUTSLIDERGLOBAL = ui->TimeoutTimeBox->value();
    ui->TimeoutSlider->setValue(TIMEOUTSLIDERGLOBAL);

    /*convert from int to string*/
    std::stringstream ss;
    ss << TIMEOUTSLIDERGLOBAL;
    TimeoutValue = ss.str();
}
void MainWindow::on_TimeoutSlider_sliderMoved(int position){
    TIMEOUTSLIDERGLOBAL = ui->TimeoutSlider->value();
    ui->TimeoutTimeBox->setValue(TIMEOUTSLIDERGLOBAL);

    /*convert from int to string*/
    std::stringstream ss;
    ss << TIMEOUTSLIDERGLOBAL;
    TimeoutValue = ss.str();
}
void MainWindow::on_TimeoutSlider_sliderPressed(){
    TIMEOUTSLIDERGLOBAL = ui->TimeoutSlider->value();
    ui->TimeoutTimeBox->setValue(TIMEOUTSLIDERGLOBAL);

    /*convert from int to string*/
    std::stringstream ss;
    ss << TIMEOUTSLIDERGLOBAL;
    TimeoutValue = ss.str();
}


//**** CHECKBOXES *******
void MainWindow::on_DisplayLogsCheck_clicked(bool checked){
    if(!ui->DisplayLogsCheck->isChecked()){
       QMessageBox msgBox;
        msgBox.setText("HA! You can't disable this feature");
        msgBox.exec();
        displayLogs = true;
        ui->DisplayLogsCheck->setChecked(true);

    }
    else {
        QMessageBox msgBox;
        msgBox.setText("You have enabled log viewing");
        displayLogs =  true;
        msgBox.exec();

    }
}
void MainWindow::on_AlertIfErrorCheckBox_clicked(){
    if(!ui->AlertIfErrorCheckBox->isChecked()){
        QMessageBox msgBox;
        msgBox.setText("Do you want to disable error notifications?");
        msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        QMessageBox msgBox2;
        switch(ret) {
            case QMessageBox::Yes:
                // stop logging
                msgBox2.setText("You have disabled email notifications");
                msgBox2.exec();
                ui->AlertIfErrorCheckBox->setChecked(false);
                ui->EmailEdit->setText("");
                break;
            case QMessageBox::No:
                // do nothing
                msgBox2.setText("Okay, you will still recieve notifications");
                msgBox2.exec();
                break;
        }
    }
    else {
        bool ok;
        QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"), tr("Email:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty()){
                ui->EmailEdit->setText(text);
            }
            else {
                ui->AlertIfErrorCheckBox->setChecked(false);
                ui->EmailEdit->setText("");
            }
    }
}


//**** BUTTONS ******
void MainWindow::on_StopLoggingButton_clicked(){
    QMessageBox msgBox;
    if(loggingStarted == false){
        msgBox.setText("You have not started logging yet");
        msgBox.exec();

    }
    else {
        msgBox.setText("You are currently logging");
        msgBox.setInformativeText("Do you want to stop logging?");
        msgBox.setStandardButtons(QMessageBox::Yes| QMessageBox::No);
        msgBox.setDefaultButton(QMessageBox::No);
        int ret = msgBox.exec();
        QMessageBox msgBox2;
        switch(ret) {
            case QMessageBox::Yes:
                // stop logging
                msgBox2.setText("You have stopped logging");
                msgBox2.exec();
                loggingStarted = false;
                std::cout << "WE STOPPED LOGGING!" << std::endl;
                break;
            case QMessageBox::No:
                // do nothing
                msgBox2.setText("Okay, you are still logging");
                msgBox2.exec();
                break;
        }
    }
}

void MainWindow::on_ApplyChangesButton_clicked(){
    QMessageBox msgBox;
    if(AttemptingDomain == "" || NameOfComputer == "" || RequestInterval == "" || TimeoutValue == "" || HOST == "" || USERNAME == "" || DATABASE == ""){
        msgBox.setText("You need to provide valid information");
        msgBox.exec();
    }
    else {
        msgBox.setText("Do you want to apply the changes?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        if(loggingStarted == false){
            msgBox.setInformativeText("This will begin the logging process");
        }
        else {
            msgBox.setInformativeText("This will interrupt the current logging process");
        }
        int ret = msgBox.exec();
        QMessageBox msgBox2;
        switch(ret){
            case QMessageBox::Yes:
                msgBox2.setText("Your changes have been applied");
                msgBox2.exec();
                executeStuff();
                break;
            case QMessageBox::No:
                msgBox2.setText("Okay, you have made no changes");
                msgBox2.exec();
                break;
        }
    }
}

















