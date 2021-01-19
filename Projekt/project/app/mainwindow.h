#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nxndialog.h"
#include <QButtonGroup>

#include "Project.h"
#include <unordered_set>

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
    void cleared();
    void toShow();

public slots:
    void open();
    void checkChoose();
    void errorFunction();
    void compare();
    void view();
    void clear();
    void showResultsInPanel();
    void onTableClicked(int, int );
    void onButtonClicked(int );

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    NxNDialog *ndial;

    QString fileName;
    std::unordered_set<Project> projects;

    QButtonGroup* group;

    int xParam{};
    int yParam{};
    int option{};

};

#endif // MAINWINDOW_H
