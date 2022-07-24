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

    QPushButton *obj1Button;
    QPushButton *obj2Button;
    QPushButton *obj3Button;
    QPushButton *viewButton;
    QPushButton *resetButton;
    QLabel *transformLabel;
    QString transformStr;

private slots:
    void obj1Press();
    void obj2Press();
    void obj3Press();
    void viewPress();
    void resetPress();

    void addTransformLabel(QString matrix);
};
#endif // MAINWINDOW_H
