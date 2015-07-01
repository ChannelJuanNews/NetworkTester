/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QProgressBar *progressBar;
    QGroupBox *ConnectionInfo;
    QLineEdit *DomainEdit;
    QLabel *DomainLabel;
    QLabel *NameOfComputer;
    QLineEdit *NameEdit;
    QLabel *RequestInterval;
    QLabel *TimeoutValue;
    QSlider *TimeoutSlider;
    QSlider *RequestSlider;
    QSpinBox *RequestTimeBox;
    QSpinBox *TimeoutTimeBox;
    QGroupBox *MySQLinfo;
    QLabel *HostLabel;
    QLabel *UserNameLabel;
    QLabel *DatabaseLabel;
    QLabel *PasswordLabel;
    QLineEdit *HostEdit;
    QLineEdit *DatabaseEdit;
    QLineEdit *UsernameEdit;
    QLineEdit *PasswordEdit;
    QFrame *LeftLine;
    QScrollArea *LogScrollArea;
    QWidget *scrollAreaWidgetContents;
    QFrame *TopLine;
    QFrame *RightLine;
    QFrame *BottomLine;
    QGroupBox *Additionalinfo;
    QCheckBox *DisplayLogsCheck;
    QCheckBox *AlertIfErrorCheckBox;
    QPushButton *ApplyChangesButton;
    QPushButton *StopLoggingButton;
    QLCDNumber *lcdNumber;
    QGroupBox *groupBox;
    QLineEdit *EmailEdit;
    QLabel *label;
    QLabel *LogoLabel;
    QLabel *RequestCounterLabel;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(818, 623);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 550, 781, 23));
        progressBar->setValue(24);
        ConnectionInfo = new QGroupBox(centralWidget);
        ConnectionInfo->setObjectName(QStringLiteral("ConnectionInfo"));
        ConnectionInfo->setGeometry(QRect(460, 30, 331, 151));
        DomainEdit = new QLineEdit(ConnectionInfo);
        DomainEdit->setObjectName(QStringLiteral("DomainEdit"));
        DomainEdit->setGeometry(QRect(10, 110, 113, 21));
        DomainLabel = new QLabel(ConnectionInfo);
        DomainLabel->setObjectName(QStringLiteral("DomainLabel"));
        DomainLabel->setGeometry(QRect(10, 90, 111, 16));
        QFont font;
        font.setFamily(QStringLiteral("Helvetica"));
        font.setPointSize(13);
        font.setBold(false);
        font.setWeight(50);
        DomainLabel->setFont(font);
        DomainLabel->setCursor(QCursor(Qt::ArrowCursor));
        DomainLabel->setMouseTracking(false);
        NameOfComputer = new QLabel(ConnectionInfo);
        NameOfComputer->setObjectName(QStringLiteral("NameOfComputer"));
        NameOfComputer->setGeometry(QRect(10, 30, 131, 16));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        NameOfComputer->setFont(font1);
        NameEdit = new QLineEdit(ConnectionInfo);
        NameEdit->setObjectName(QStringLiteral("NameEdit"));
        NameEdit->setGeometry(QRect(10, 50, 113, 21));
        RequestInterval = new QLabel(ConnectionInfo);
        RequestInterval->setObjectName(QStringLiteral("RequestInterval"));
        RequestInterval->setGeometry(QRect(180, 30, 111, 16));
        RequestInterval->setFont(font1);
        TimeoutValue = new QLabel(ConnectionInfo);
        TimeoutValue->setObjectName(QStringLiteral("TimeoutValue"));
        TimeoutValue->setGeometry(QRect(180, 90, 101, 20));
        TimeoutValue->setFont(font1);
        TimeoutSlider = new QSlider(ConnectionInfo);
        TimeoutSlider->setObjectName(QStringLiteral("TimeoutSlider"));
        TimeoutSlider->setGeometry(QRect(170, 110, 101, 22));
        TimeoutSlider->setOrientation(Qt::Horizontal);
        RequestSlider = new QSlider(ConnectionInfo);
        RequestSlider->setObjectName(QStringLiteral("RequestSlider"));
        RequestSlider->setGeometry(QRect(170, 50, 101, 22));
        RequestSlider->setOrientation(Qt::Horizontal);
        RequestTimeBox = new QSpinBox(ConnectionInfo);
        RequestTimeBox->setObjectName(QStringLiteral("RequestTimeBox"));
        RequestTimeBox->setGeometry(QRect(276, 50, 51, 24));
        TimeoutTimeBox = new QSpinBox(ConnectionInfo);
        TimeoutTimeBox->setObjectName(QStringLiteral("TimeoutTimeBox"));
        TimeoutTimeBox->setGeometry(QRect(276, 110, 51, 24));
        MySQLinfo = new QGroupBox(centralWidget);
        MySQLinfo->setObjectName(QStringLiteral("MySQLinfo"));
        MySQLinfo->setGeometry(QRect(460, 180, 331, 201));
        HostLabel = new QLabel(MySQLinfo);
        HostLabel->setObjectName(QStringLiteral("HostLabel"));
        HostLabel->setGeometry(QRect(30, 50, 59, 16));
        UserNameLabel = new QLabel(MySQLinfo);
        UserNameLabel->setObjectName(QStringLiteral("UserNameLabel"));
        UserNameLabel->setGeometry(QRect(170, 50, 71, 16));
        DatabaseLabel = new QLabel(MySQLinfo);
        DatabaseLabel->setObjectName(QStringLiteral("DatabaseLabel"));
        DatabaseLabel->setGeometry(QRect(30, 110, 59, 16));
        PasswordLabel = new QLabel(MySQLinfo);
        PasswordLabel->setObjectName(QStringLiteral("PasswordLabel"));
        PasswordLabel->setGeometry(QRect(170, 110, 59, 16));
        HostEdit = new QLineEdit(MySQLinfo);
        HostEdit->setObjectName(QStringLiteral("HostEdit"));
        HostEdit->setGeometry(QRect(30, 70, 113, 21));
        DatabaseEdit = new QLineEdit(MySQLinfo);
        DatabaseEdit->setObjectName(QStringLiteral("DatabaseEdit"));
        DatabaseEdit->setGeometry(QRect(30, 130, 113, 21));
        UsernameEdit = new QLineEdit(MySQLinfo);
        UsernameEdit->setObjectName(QStringLiteral("UsernameEdit"));
        UsernameEdit->setGeometry(QRect(170, 70, 113, 21));
        PasswordEdit = new QLineEdit(MySQLinfo);
        PasswordEdit->setObjectName(QStringLiteral("PasswordEdit"));
        PasswordEdit->setGeometry(QRect(170, 130, 113, 21));
        LeftLine = new QFrame(centralWidget);
        LeftLine->setObjectName(QStringLiteral("LeftLine"));
        LeftLine->setGeometry(QRect(429, 20, 41, 521));
        LeftLine->setFrameShape(QFrame::VLine);
        LeftLine->setFrameShadow(QFrame::Sunken);
        LogScrollArea = new QScrollArea(centralWidget);
        LogScrollArea->setObjectName(QStringLiteral("LogScrollArea"));
        LogScrollArea->setGeometry(QRect(10, 110, 421, 401));
        LogScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 419, 399));
        LogScrollArea->setWidget(scrollAreaWidgetContents);
        TopLine = new QFrame(centralWidget);
        TopLine->setObjectName(QStringLiteral("TopLine"));
        TopLine->setGeometry(QRect(450, 10, 361, 21));
        TopLine->setFrameShape(QFrame::HLine);
        TopLine->setFrameShadow(QFrame::Sunken);
        RightLine = new QFrame(centralWidget);
        RightLine->setObjectName(QStringLiteral("RightLine"));
        RightLine->setGeometry(QRect(800, 20, 20, 521));
        RightLine->setFrameShape(QFrame::VLine);
        RightLine->setFrameShadow(QFrame::Sunken);
        BottomLine = new QFrame(centralWidget);
        BottomLine->setObjectName(QStringLiteral("BottomLine"));
        BottomLine->setGeometry(QRect(450, 520, 361, 51));
        BottomLine->setFrameShape(QFrame::HLine);
        BottomLine->setFrameShadow(QFrame::Sunken);
        Additionalinfo = new QGroupBox(centralWidget);
        Additionalinfo->setObjectName(QStringLiteral("Additionalinfo"));
        Additionalinfo->setGeometry(QRect(460, 380, 331, 61));
        DisplayLogsCheck = new QCheckBox(Additionalinfo);
        DisplayLogsCheck->setObjectName(QStringLiteral("DisplayLogsCheck"));
        DisplayLogsCheck->setGeometry(QRect(20, 30, 101, 20));
        AlertIfErrorCheckBox = new QCheckBox(Additionalinfo);
        AlertIfErrorCheckBox->setObjectName(QStringLiteral("AlertIfErrorCheckBox"));
        AlertIfErrorCheckBox->setGeometry(QRect(130, 30, 141, 20));
        ApplyChangesButton = new QPushButton(centralWidget);
        ApplyChangesButton->setObjectName(QStringLiteral("ApplyChangesButton"));
        ApplyChangesButton->setGeometry(QRect(460, 510, 331, 32));
        StopLoggingButton = new QPushButton(centralWidget);
        StopLoggingButton->setObjectName(QStringLiteral("StopLoggingButton"));
        StopLoggingButton->setGeometry(QRect(4, 520, 431, 32));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(140, 80, 61, 23));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(460, 440, 331, 61));
        EmailEdit = new QLineEdit(groupBox);
        EmailEdit->setObjectName(QStringLiteral("EmailEdit"));
        EmailEdit->setGeometry(QRect(60, 30, 251, 21));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 59, 16));
        LogoLabel = new QLabel(centralWidget);
        LogoLabel->setObjectName(QStringLiteral("LogoLabel"));
        LogoLabel->setGeometry(QRect(0, 10, 441, 71));
        LogoLabel->setPixmap(QPixmap(QString::fromUtf8(":/resources/images/NetworkTesterLogo.png")));
        LogoLabel->setScaledContents(true);
        RequestCounterLabel = new QLabel(centralWidget);
        RequestCounterLabel->setObjectName(QStringLiteral("RequestCounterLabel"));
        RequestCounterLabel->setGeometry(QRect(10, 80, 121, 20));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 818, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        ConnectionInfo->setTitle(QApplication::translate("MainWindow", "Connection Information", 0));
        DomainLabel->setText(QApplication::translate("MainWindow", "Domain", 0));
        NameOfComputer->setText(QApplication::translate("MainWindow", "Name of Computer", 0));
        RequestInterval->setText(QApplication::translate("MainWindow", "Request Interval", 0));
        TimeoutValue->setText(QApplication::translate("MainWindow", "Timeout Value", 0));
        MySQLinfo->setTitle(QApplication::translate("MainWindow", "MySQL Information", 0));
        HostLabel->setText(QApplication::translate("MainWindow", "Host", 0));
        UserNameLabel->setText(QApplication::translate("MainWindow", "Username", 0));
        DatabaseLabel->setText(QApplication::translate("MainWindow", "Database", 0));
        PasswordLabel->setText(QApplication::translate("MainWindow", "Password", 0));
        Additionalinfo->setTitle(QApplication::translate("MainWindow", "Additional Information", 0));
        DisplayLogsCheck->setText(QApplication::translate("MainWindow", "Display Logs", 0));
        AlertIfErrorCheckBox->setText(QApplication::translate("MainWindow", "Alert if error ocurs", 0));
        ApplyChangesButton->setText(QApplication::translate("MainWindow", "Apply Changes", 0));
        StopLoggingButton->setText(QApplication::translate("MainWindow", "Stop Logging", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "Error Alerts", 0));
        label->setText(QApplication::translate("MainWindow", "Email:", 0));
        LogoLabel->setText(QString());
        RequestCounterLabel->setText(QApplication::translate("MainWindow", "Request Counter:", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
