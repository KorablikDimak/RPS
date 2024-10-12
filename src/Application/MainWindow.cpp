#include "RPS/Application/MainWindow.h"
#include "ui_MainWindow.h"

namespace RPS
{
    MainWindow::MainWindow(QWidget *parent) :
            QWidget(parent), ui(new Ui::MainWindow)
    {
        ui->setupUi(this);
    }

    MainWindow::~MainWindow()
    {
        delete ui;
    }
}