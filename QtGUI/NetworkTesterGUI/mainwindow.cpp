#include <QMessageBox>
#include <QPixmap>
#include <QtGui>
#include <QInputDialog>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <string>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include "NetworkTester.h"

/*constructor function*/
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);

    /*Initialize variables*/
    ui->progressBar->setValue(0); // set progress bar to 0
    ui->NameEdit->setPlaceholderText("Fulano"); // example name inside of line
    ui->DomainEdit->setPlaceholderText("google.com"); // example domain inside of line
    ui->DomainEdit->setText("google.com");
    ui->HostEdit->setPlaceholderText("localhost");
    ui->UsernameEdit->setPlaceholderText("Username");
    ui->DatabaseEdit->setPlaceholderText("test");
    ui->PasswordEdit->setPlaceholderText("********");
    ui->EmailEdit->setPlaceholderText("example@email.com");
    ui->DisplayLogsCheck->setChecked(true); // by default sets as a check
    ui->LocationEdit->setReadOnly(true);
    //ui->EmailEdit->setReadOnly(true);

    // set LogMessage background color
    QPalette p = ui->LogMessage->palette();
    p.setColor(QPalette::Base, QColor(240, 240, 255));
    ui->LogMessage->setPalette(p);
    ui->LogMessage->setAcceptDrops(false); //
    ui->LogMessage->setEnabled(false); // makes is so you can't edit the logs
    ui->LogMessage->setTextColor(QColor(0,0,255,127)); // makes a semi-transparent blue
    ui->LogMessage->setStyleSheet("QTextEdit { padding-left:5; padding-top:5; padding-bottom:5; padding-right:5}");
    ui->NumFailures->setSegmentStyle(QLCDNumber::Filled);

    // SET LCD WIGETS TO LOOK GOOD
    /* get the palette */
    QPalette palette = ui->NumFailures->palette();
    /* foreground color */
    palette.setColor(palette.WindowText, QColor(10,10, 255));
    /* background color */
    palette.setColor(palette.Background, QColor(240, 240, 255));
    /* "light" border */
    palette.setColor(palette.Light, QColor(0, 0, 0));
    /* "dark" border */
    palette.setColor(palette.Dark, QColor(0, 0,0));
    /* set the palettes */
    ui->NumFailures->setPalette(palette);
    ui->NumFailures->setSegmentStyle(QLCDNumber::Filled);
    /* set second palette */
    ui->TimeDisplay->setPalette(palette);
    ui->TimeDisplay->setSegmentStyle(QLCDNumber::Filled);
}
MainWindow::~MainWindow(){
    delete ui;
    ui = NULL;
}
void MainWindow::sendMessage(QString message){
    QString cat = ui->LogMessage->toPlainText();
    ui->LogMessage->setText(message + cat);
}
/*GLOBAL VARIABLES TO ORQUESTRATE THE GUI*/
//====================================
std::string AttemptingDomain = ""; //NOTNULL
std::string NameOfComputer = ""; //NOTNULL
std::string RequestInterval = ""; //NOTNULL
std::string TimeoutValue = ""; //NOTNULL
std::string HOST = ""; //NOTNULL
std::string USERNAME = ""; //NOTNULL
std::string DATABASE = ""; // NOTNULL
std::string PASSWORD = ""; // can be null
std::string email = ""; // can be null
std::string SaveDirectory = ""; // CANNOT BE NULL

std::thread * SecondThread;

bool loggingStarted = false;
bool displayLogs = true;
bool NotifyEmail = false;
//=====================================


/* function that executes the actual program*/
void MainWindow::executeStuff(){
    // check to see if the inputted stuff is valid

    QMessageBox msgBox;
    if(AttemptingDomain == ""){
        msgBox.setText("Domain is not valid");
        msgBox.exec();
        return;
    }
    if (NameOfComputer == ""){
        msgBox.setText("Name is not valid");
        msgBox.exec();
        return;
    }
    if(RequestInterval == ""){
        msgBox.setText("Request interval is not valid");
        msgBox.exec();
        return;
    }
    if(TimeoutValue == ""){
        msgBox.setText("Timeout value is not valid");
        msgBox.exec();
        return;
    }
    if(HOST == ""){
        msgBox.setText("Host it not valid");
        msgBox.exec();
        return;
    }
    if(USERNAME == ""){
        msgBox.setText("Username is not valid");
        msgBox.exec();
        return;
    }
    if(DATABASE == ""){
        msgBox.setText("Database it not valid");
        msgBox.exec();
        return;
    }

    if((ui->EmailEdit->text() != "") && !(ui->AlertIfErrorCheckBox->isChecked())){
        QMessageBox msgBox;
        msgBox.setText("Please check the \"Alert if error occurs\" box and try again");
        msgBox.exec();
        return;
    }
    if(NotifyEmail){
        email = ui->EmailEdit->text().toStdString();
    }
    if(SaveDirectory == ""){
        QMessageBox msgBox;
        msgBox.setText("Please specify a save location");
        msgBox.exec();
        return;
    }

    SecondThread = InitializeNetworkTester(this,AttemptingDomain, NameOfComputer, RequestInterval,
                            TimeoutValue, HOST, USERNAME, DATABASE, PASSWORD, email,
                            SaveDirectory, ui->LogMessage);
    loggingStarted = true;
}

void MainWindow::stopExecution(){
    stopThread(); // sets terminate thread flag to true
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

/****************** TEXT BOXES *****************************/
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

//******** REQEUST AND TIMEOUT SILDERS AND BOXES  *************
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

/************************ CHECKBOXES ***********************/
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
                email = ui->EmailEdit->text().toStdString();
                NotifyEmail = false;
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
        QString text = QInputDialog::getText(this, tr("QInputDialog::getText()"),
                       tr("Email:"), QLineEdit::Normal, QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty()){
                ui->EmailEdit->setText(text);
                email = ui->EmailEdit->text().toStdString();
                NotifyEmail = true;
            }
            else {
                ui->AlertIfErrorCheckBox->setChecked(false);
                ui->EmailEdit->setText("");
                email = ui->EmailEdit->text().toStdString();
                NotifyEmail = false;
            }
    }
}
/********************* Apply changes and Stop logging Buttons ***************/
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
                stopExecution();
                sendMessage("You have stopped logging\n");
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
    if(AttemptingDomain == "" || NameOfComputer == "" || RequestInterval == ""
                              || TimeoutValue == "" || HOST == "" || USERNAME == ""
                              || DATABASE == "" || SaveDirectory == ""){
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
                stopExecution();
                executeStuff();
                ui->TimeDisplay->display(0);
                ui->NumFailures->display(0);
                sendMessage("Logging started\n");
                break;
            case QMessageBox::No:
                msgBox2.setText("Okay, you have made no changes");
                msgBox2.exec();
                break;
        }
    }
}

/******************* Specify Location Box *****************************/
void MainWindow::on_LocationEdit_textChanged(const QString &arg1){
    // does nothing since user will not be ale to edit text
}
void MainWindow::on_BrowseButton_clicked(){
    QString directory = QFileDialog::getExistingDirectory(this, tr("Destination Folder"), "~/");

    if(directory == ""){
        ui->LocationEdit->setText("");
    }
    else {
        ui->LocationEdit->setText(directory);
    }
    SaveDirectory = directory.toStdString();
}
