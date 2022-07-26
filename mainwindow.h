#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "glrenderer.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    GLRenderer *glRenderer;

    QPushButton *buttonA;
    QPushButton *buttonB;
    QPushButton *buttonC;
    QPushButton *buttonD;
    QPushButton *buttonView;

    QPushButton *buttonAInv;
    QPushButton *buttonBInv;
    QPushButton *buttonCInv;
    QPushButton *buttonDInv;
    QPushButton *buttonViewInv;

    QPushButton *buttonReset;

    QLabel *transformLabel;
    QString transformStr;

private slots:
    void pressA();
    void pressB();
    void pressC();
    void pressD();
    void pressView();

    void pressAInv();
    void pressBInv();
    void pressCInv();
    void pressDInv();
    void pressViewInv();

    void pressReset();

    void addTransformLabel(QString matrix);
};
#endif // MAINWINDOW_H
