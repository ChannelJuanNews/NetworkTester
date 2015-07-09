/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
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
    QGroupBox *Additionalinfo;
    QCheckBox *DisplayLogsCheck;
    QCheckBox *AlertIfErrorCheckBox;
    QPushButton *ApplyChangesButton;
    QPushButton *StopLoggingButton;
    QLCDNumber *TimeDisplay;
    QGroupBox *EmailBox;
    QLineEdit *EmailEdit;
    QLabel *EmailLabel;
    QLabel *CurrentTimeLabel;
    QTextEdit *LogMessage;
    QLabel *CopyrightEQ;
    QGroupBox *SpecifyBox;
    QLabel *LocationLabel;
    QPushButton *BrowseButton;
    QLineEdit *LocationEdit;
    QLabel *NumFailuresLabel;
    QLabel *NetworkTesterLogoLabel;
    QLCDNumber *NumFailures;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->setEnabled(true);
        MainWindow->resize(810, 644);
        MainWindow->setMinimumSize(QSize(810, 644));
        MainWindow->setMaximumSize(QSize(810, 644));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(10, 560, 791, 23));
        progressBar->setValue(24);
        ConnectionInfo = new QGroupBox(centralWidget);
        ConnectionInfo->setObjectName(QStringLiteral("ConnectionInfo"));
        ConnectionInfo->setGeometry(QRect(460, 60, 331, 141));
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
        MySQLinfo->setGeometry(QRect(460, 200, 331, 121));
        HostLabel = new QLabel(MySQLinfo);
        HostLabel->setObjectName(QStringLiteral("HostLabel"));
        HostLabel->setGeometry(QRect(30, 20, 59, 16));
        UserNameLabel = new QLabel(MySQLinfo);
        UserNameLabel->setObjectName(QStringLiteral("UserNameLabel"));
        UserNameLabel->setGeometry(QRect(170, 20, 71, 16));
        DatabaseLabel = new QLabel(MySQLinfo);
        DatabaseLabel->setObjectName(QStringLiteral("DatabaseLabel"));
        DatabaseLabel->setGeometry(QRect(30, 70, 59, 16));
        PasswordLabel = new QLabel(MySQLinfo);
        PasswordLabel->setObjectName(QStringLiteral("PasswordLabel"));
        PasswordLabel->setGeometry(QRect(170, 70, 59, 16));
        HostEdit = new QLineEdit(MySQLinfo);
        HostEdit->setObjectName(QStringLiteral("HostEdit"));
        HostEdit->setGeometry(QRect(30, 40, 113, 21));
        DatabaseEdit = new QLineEdit(MySQLinfo);
        DatabaseEdit->setObjectName(QStringLiteral("DatabaseEdit"));
        DatabaseEdit->setGeometry(QRect(30, 90, 113, 21));
        UsernameEdit = new QLineEdit(MySQLinfo);
        UsernameEdit->setObjectName(QStringLiteral("UsernameEdit"));
        UsernameEdit->setGeometry(QRect(170, 40, 113, 21));
        PasswordEdit = new QLineEdit(MySQLinfo);
        PasswordEdit->setObjectName(QStringLiteral("PasswordEdit"));
        PasswordEdit->setGeometry(QRect(170, 90, 113, 21));
        Additionalinfo = new QGroupBox(centralWidget);
        Additionalinfo->setObjectName(QStringLiteral("Additionalinfo"));
        Additionalinfo->setGeometry(QRect(460, 400, 331, 61));
        DisplayLogsCheck = new QCheckBox(Additionalinfo);
        DisplayLogsCheck->setObjectName(QStringLiteral("DisplayLogsCheck"));
        DisplayLogsCheck->setGeometry(QRect(20, 30, 101, 20));
        AlertIfErrorCheckBox = new QCheckBox(Additionalinfo);
        AlertIfErrorCheckBox->setObjectName(QStringLiteral("AlertIfErrorCheckBox"));
        AlertIfErrorCheckBox->setGeometry(QRect(130, 30, 141, 20));
        ApplyChangesButton = new QPushButton(centralWidget);
        ApplyChangesButton->setObjectName(QStringLiteral("ApplyChangesButton"));
        ApplyChangesButton->setGeometry(QRect(450, 520, 351, 32));
        StopLoggingButton = new QPushButton(centralWidget);
        StopLoggingButton->setObjectName(QStringLiteral("StopLoggingButton"));
        StopLoggingButton->setGeometry(QRect(4, 520, 441, 32));
        TimeDisplay = new QLCDNumber(centralWidget);
        TimeDisplay->setObjectName(QStringLiteral("TimeDisplay"));
        TimeDisplay->setGeometry(QRect(550, 30, 61, 23));
        TimeDisplay->setSmallDecimalPoint(true);
        TimeDisplay->setDigitCount(6);
        EmailBox = new QGroupBox(centralWidget);
        EmailBox->setObjectName(QStringLiteral("EmailBox"));
        EmailBox->setGeometry(QRect(460, 460, 331, 61));
        EmailEdit = new QLineEdit(EmailBox);
        EmailEdit->setObjectName(QStringLiteral("EmailEdit"));
        EmailEdit->setGeometry(QRect(60, 30, 251, 21));
        EmailLabel = new QLabel(EmailBox);
        EmailLabel->setObjectName(QStringLiteral("EmailLabel"));
        EmailLabel->setGeometry(QRect(20, 30, 59, 16));
        CurrentTimeLabel = new QLabel(centralWidget);
        CurrentTimeLabel->setObjectName(QStringLiteral("CurrentTimeLabel"));
        CurrentTimeLabel->setGeometry(QRect(460, 30, 91, 20));
        LogMessage = new QTextEdit(centralWidget);
        LogMessage->setObjectName(QStringLiteral("LogMessage"));
        LogMessage->setGeometry(QRect(10, 70, 431, 441));
        QFont font2;
        font2.setPointSize(10);
        LogMessage->setFont(font2);
        LogMessage->setReadOnly(false);
        CopyrightEQ = new QLabel(centralWidget);
        CopyrightEQ->setObjectName(QStringLiteral("CopyrightEQ"));
        CopyrightEQ->setGeometry(QRect(10, 570, 101, 41));
        SpecifyBox = new QGroupBox(centralWidget);
        SpecifyBox->setObjectName(QStringLiteral("SpecifyBox"));
        SpecifyBox->setGeometry(QRect(460, 320, 331, 81));
        LocationLabel = new QLabel(SpecifyBox);
        LocationLabel->setObjectName(QStringLiteral("LocationLabel"));
        LocationLabel->setGeometry(QRect(10, 40, 61, 21));
        BrowseButton = new QPushButton(SpecifyBox);
        BrowseButton->setObjectName(QStringLiteral("BrowseButton"));
        BrowseButton->setGeometry(QRect(230, 40, 91, 21));
        LocationEdit = new QLineEdit(SpecifyBox);
        LocationEdit->setObjectName(QStringLiteral("LocationEdit"));
        LocationEdit->setGeometry(QRect(70, 40, 151, 21));
        NumFailuresLabel = new QLabel(centralWidget);
        NumFailuresLabel->setObjectName(QStringLiteral("NumFailuresLabel"));
        NumFailuresLabel->setGeometry(QRect(670, 30, 51, 21));
        NetworkTesterLogoLabel = new QLabel(centralWidget);
        NetworkTesterLogoLabel->setObjectName(QStringLiteral("NetworkTesterLogoLabel"));
        NetworkTesterLogoLabel->setGeometry(QRect(0, 0, 451, 71));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(NetworkTesterLogoLabel->sizePolicy().hasHeightForWidth());
        NetworkTesterLogoLabel->setSizePolicy(sizePolicy);
        QFont font3;
        font3.setKerning(true);
        NetworkTesterLogoLabel->setFont(font3);
        NetworkTesterLogoLabel->setLineWidth(1);
        NetworkTesterLogoLabel->setMidLineWidth(0);
        NetworkTesterLogoLabel->setPixmap(QPixmap(QString::fromUtf8(":/resources/images/NetworkTesterLogo.png")));
        NetworkTesterLogoLabel->setScaledContents(true);
        NetworkTesterLogoLabel->setWordWrap(false);
        NetworkTesterLogoLabel->setOpenExternalLinks(false);
        NumFailures = new QLCDNumber(centralWidget);
        NumFailures->setObjectName(QStringLiteral("NumFailures"));
        NumFailures->setGeometry(QRect(730, 30, 61, 23));
        NumFailures->setSmallDecimalPoint(true);
        NumFailures->setDigitCount(6);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 810, 22));
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
        MySQLinfo->setTitle(QApplication::translate("MainWindow", "MySQL Connection Information", 0));
        HostLabel->setText(QApplication::translate("MainWindow", "Host", 0));
        UserNameLabel->setText(QApplication::translate("MainWindow", "Username", 0));
        DatabaseLabel->setText(QApplication::translate("MainWindow", "Database", 0));
        PasswordLabel->setText(QApplication::translate("MainWindow", "Password", 0));
        Additionalinfo->setTitle(QApplication::translate("MainWindow", "Additional Information and Alerts", 0));
        DisplayLogsCheck->setText(QApplication::translate("MainWindow", "Display Logs", 0));
        AlertIfErrorCheckBox->setText(QApplication::translate("MainWindow", "Alert if error ocurs", 0));
        ApplyChangesButton->setText(QApplication::translate("MainWindow", "Apply Changes", 0));
        StopLoggingButton->setText(QApplication::translate("MainWindow", "Stop Logging", 0));
        EmailBox->setTitle(QApplication::translate("MainWindow", "Error Alerts", 0));
        EmailLabel->setText(QApplication::translate("MainWindow", "Email:", 0));
        CurrentTimeLabel->setText(QApplication::translate("MainWindow", "Current Time:", 0));
        CopyrightEQ->setText(QApplication::translate("MainWindow", "\302\251 EquipoVision", 0));
        SpecifyBox->setTitle(QApplication::translate("MainWindow", "Specify Save Location For Log File", 0));
        LocationLabel->setText(QApplication::translate("MainWindow", "Location: ", 0));
        BrowseButton->setText(QApplication::translate("MainWindow", "Browse", 0));
        NumFailuresLabel->setText(QApplication::translate("MainWindow", "Failures:", 0));
#ifndef QT_NO_TOOLTIP
        NetworkTesterLogoLabel->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        NetworkTesterLogoLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
