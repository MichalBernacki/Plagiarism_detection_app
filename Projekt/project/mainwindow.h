#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "Project.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    void error(QString);
    void opened();
    void mustChoose();
    void choosed();

public slots:
    void open();
    void checkChoose();
    void errorFunction();
    void compare();

private:
    Ui::MainWindow *ui;

    QString fileName;
    std::vector<Project> projects;
};

#endif // MAINWINDOW_H
