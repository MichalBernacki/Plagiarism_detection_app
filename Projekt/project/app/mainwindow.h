#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nxndialog.h"
#include <QButtonGroup>
#include <QListWidgetItem>

#include "project.h"
#include "result.h"
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
    //void toShow();

public slots:
    void open();
    void checkChoose();
    void errorFunction(QString);
    void compare();
    void view();
    void clear();
    void showResultsInPanel();
    void onTableClicked(int, int );
    void onListElemClicked(QListWidgetItem *item);


private:
    Ui::MainWindow *ui;
    NxNDialog *ndial;

    std::unordered_set<Project> projects;
    std::vector<std::vector<Result>> results;

    int xParam{};
    int yParam{};
    int resultIndex{};

};

#endif // MAINWINDOW_H
