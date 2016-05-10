#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_recordButton_clicked()
{

}

void MainWindow::on_waitButton_clicked()
{

}

void MainWindow::on_eraseButton_clicked()
{

}

void MainWindow::on_downloadButton_clicked()
{

}

void MainWindow::on_saveButton_clicked()
{

}

void MainWindow::on_quitButton_clicked()
{
    this->close();
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    event->accept();
}
