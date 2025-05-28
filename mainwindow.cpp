#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , f16(new F16Widget)
{
    ui->setupUi(this);

    ui->verticalLayout_2->addWidget(f16);
}

MainWindow::~MainWindow()
{
    delete ui;
}

