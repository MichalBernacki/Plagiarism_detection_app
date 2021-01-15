#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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
};

#endif // MAINWINDOW_H
