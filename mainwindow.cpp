#include "mainwindow.h"

#include <QHBoxLayout>
#include <iostream>

MainWindow::MainWindow()
{
    /* Set up the layouts (parent-child diagram):
     *
     *                 hLayout
     *                 /     \
     *           vLayout      glWidget (canvas)
     *          |
     * labels,buttons
     *
     */

    setWindowTitle("Lab 4: Transforms");

    QHBoxLayout *hLayout = new QHBoxLayout;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->setAlignment(Qt::AlignTop);
    hLayout->addLayout(vLayout);

    glRenderer = new GLRenderer;
    glRenderer->setEnabled(true);
    hLayout->addWidget(glRenderer, 1);

    this->setLayout(hLayout);

    obj1Button = new QPushButton("Apply Obj1 Matrix");
    obj2Button = new QPushButton("Apply Obj2 Matrix");
    obj3Button = new QPushButton("Apply Obj3 Matrix");
    viewButton = new QPushButton("Apply View Matrix");
    resetButton = new QPushButton("Reset Transformation");

    vLayout->addWidget(obj1Button);
    vLayout->addWidget(obj2Button);
    vLayout->addWidget(obj3Button);
    vLayout->addWidget(viewButton);
    vLayout->addWidget(resetButton);

    connect(obj1Button, &QPushButton::released, this, &MainWindow::obj1Press);
    connect(obj2Button, &QPushButton::released, this, &MainWindow::obj2Press);
    connect(obj3Button, &QPushButton::released, this, &MainWindow::obj3Press);
    connect(viewButton, &QPushButton::released, this, &MainWindow::viewPress);
    connect(resetButton, &QPushButton::released, this, &MainWindow::resetPress);
}

MainWindow::~MainWindow()
{
}

void MainWindow::obj1Press() {
    glRenderer->buttonPressed(Button::OBJECT1);
}

void MainWindow::obj2Press() {
    glRenderer->buttonPressed(Button::OBJECT2);
}

void MainWindow::obj3Press() {
    glRenderer->buttonPressed(Button::OBJECT3);
}

void MainWindow::viewPress() {
    glRenderer->buttonPressed(Button::VIEW);
}

void MainWindow::resetPress() {
    glRenderer->buttonPressed(Button::RESET);
}
