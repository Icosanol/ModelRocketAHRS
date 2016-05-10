#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "serialdevice.h"
#include "serialexception.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_quitButton_clicked();
    void on_recordButton_clicked();
    void on_waitButton_clicked();
    void on_eraseButton_clicked();
    void on_downloadButton_clicked();
    void on_saveButton_clicked();

private:
    void closeEvent(QCloseEvent* event);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
