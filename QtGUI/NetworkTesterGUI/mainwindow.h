#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow{

    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void sendMessage(QString message);

private slots:

    /*progress bar*/
    void on_progressBar_valueChanged(int value);

    /*Silders*/
    void on_RequestSlider_sliderMoved(int position);
    void on_RequestSlider_sliderPressed();

    void on_TimeoutSlider_sliderMoved(int position);
    void on_TimeoutSlider_sliderPressed();

    /*time boxes*/
    void on_RequestTimeBox_valueChanged(const QString &arg1);
    void on_TimeoutTimeBox_valueChanged(const QString &arg1);

    /*buttons*/
    void on_StopLoggingButton_clicked();
    void on_ApplyChangesButton_clicked();

    /*CheckBoxes*/
    void on_DisplayLogsCheck_clicked(bool checked);
    void on_AlertIfErrorCheckBox_clicked();

    /*TextBoxes*/
    void on_DomainEdit_textChanged(const QString &arg1);
    void on_NameEdit_textChanged(const QString &arg1);
    void on_HostEdit_textChanged(const QString &arg1);
    void on_UsernameEdit_textChanged(const QString &arg1);
    void on_DatabaseEdit_textChanged(const QString &arg1);
    void on_PasswordEdit_textChanged(const QString &arg1);
    void on_EmailEdit_textChanged(const QString &arg1);


private:
    Ui::MainWindow * ui;
    /*Execute Function*/
    void executeStuff();
    void stopExecution();


};

#endif // MAINWINDOW_H
