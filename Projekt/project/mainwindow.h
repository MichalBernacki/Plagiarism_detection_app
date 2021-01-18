#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "nxndialog.h"

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
    void sectionClicked();

public slots:
    void open();
    void checkChoose();
    void errorFunction();
    void compare();
    void view();
    void showResultsInPanel();
    void onTableClicked();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    NxNDialog *ndial;

    QString fileName;
    std::unordered_set<Project> projects;

    int projectCount{};
};

#endif // MAINWINDOW_H
