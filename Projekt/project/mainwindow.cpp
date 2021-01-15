#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStateMachine>
#include <QHistoryState>
#include <QFileDialog>
#include <QDebug>
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto stateMachine = new QStateMachine{this};

    //ALL STATES
    auto stateStartup = new QState(stateMachine);
    auto stateOpen = new QState{stateMachine};
    auto stateError = new QState{stateMachine};
    auto stateView = new QState{stateMachine};
    auto stateChoose = new QState{stateMachine};
    auto stateCompare = new QState{stateMachine};

    //STARTUP
    stateStartup->assignProperty(ui->pbOpen, "enabled", true);
    stateStartup->assignProperty(ui->pbStart, "enabled", false);
    stateStartup->assignProperty(ui->taCompare, "enabled", false);
    stateStartup->assignProperty(ui->leLabel, "text", "Load directory to start...");
    stateStartup->assignProperty(ui->cbBox1, "enabled", false);
    stateStartup->assignProperty(ui->cbBox2, "enabled", false);

    stateStartup->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);


    //OPEN
    //connect(stateOpen, SIGNAL(entered()), this, SLOT(open()));
    connect(stateOpen, SIGNAL(entered()), this, SLOT(view()));//-> na czas testu generowania tablic !
    stateOpen->addTransition(this, SIGNAL(error(QString)), stateError);
    stateOpen->addTransition(this, SIGNAL(opened()), stateView);


    //ERROR OPEN
    stateError->assignProperty(ui->pbOpen, "enabled", true);
    stateError->assignProperty(ui->pbStart, "enabled", false);
    stateError->assignProperty(ui->cbBox1, "enabled", false);
    stateError->assignProperty(ui->cbBox2, "enabled", false);
    stateError->assignProperty(ui->taCompare, "enabled", false);

    connect(stateError, SIGNAL(entered()), this, SLOT(errorFunction()));
    stateError->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);


    //VIEW
    stateView->assignProperty(ui->pbOpen, "enabled", true);
    stateView->assignProperty(ui->pbStart, "enabled", true);
    stateView->assignProperty(ui->taCompare, "enabled", false);
    stateView->assignProperty(ui->cbBox1, "enabled", true);
    stateView->assignProperty(ui->cbBox2, "enabled", true);

    stateView->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);
    stateView->addTransition(ui->pbStart, SIGNAL(clicked()), stateChoose);


    //CHOOSE
    connect(stateChoose, SIGNAL(entered()), this, SLOT(checkChoose()));
    stateChoose->addTransition(this, SIGNAL(mustChoose()), stateView);
    stateChoose->addTransition(this, SIGNAL(choosed()), stateView);


    //COMPARE
    stateCompare->assignProperty(ui->taCompare, "enabled", true);
    connect(stateCompare, SIGNAL(entered()), this, SLOT(compare()));
    stateCompare->addTransition(this, SIGNAL(error(QString)), stateError);

    stateMachine->setInitialState(stateStartup);
    stateMachine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open(){
    emit error("open");
    emit opened();
    //TODO: Otwieranie katalogu
    //TODO: Otwieranie katalogu drugiego
    //TODO: Wyswietlenie plikow w oknach
    //TODO: Zapisanie sciezek, albo jakiej "tablicy" z nazwami plikow
}

void MainWindow::checkChoose(){
    emit mustChoose();
    emit choosed();
    //TODO: Wyswietlic messagebox z informacja, ze trzeba wybrac algorytm jak nie jest nic zatikowane
}

void MainWindow::errorFunction(){
    //QMessageBOX
    //TODO: Wyswietlic MessageBox co poszlo nie tak z otwieraniem katalogu i plikow w nim
}

void MainWindow::compare(){
    emit error("compare");
    //TODO: Porownywanie i wprowadzenie wynikow do tabeli
}


void MainWindow::on_pushButton_clicked()
{
   // to jest do testu + potem to okno będzie do wyświetlania podobnych plików
   ndial = new NxNDialog(this);
   ndial->setModal(true);
   ndial->exec();

}

void MainWindow::view()
{
    this->projectCount = 5;

    ui->taCompare->clear();
    ui->taCompare->setRowCount(projectCount);
    ui->taCompare->setColumnCount(projectCount);
    for (auto r=0; r<projectCount; r++)
    {
        ui->taCompare->setHorizontalHeaderItem(r, new QTableWidgetItem("r"));
        ui->taCompare->setVerticalHeaderItem(r, new QTableWidgetItem("r"));
         for (auto c=0; c<projectCount; c++)
              ui->taCompare->setItem( r, c, new QTableWidgetItem("123456"));
    }
}

