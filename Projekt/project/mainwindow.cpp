#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStateMachine>
#include <QHistoryState>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto stateMachine = new QStateMachine{this};

    //ALL STATES
    auto stateStartup = new QState(stateMachine);
    auto stateOpen = new QState{stateMachine};
    auto stateErrorOpen = new QState{stateMachine};
    auto stateErrorCompare = new QState{stateMachine};
    auto stateView = new QState{stateMachine};
    auto stateChoose = new QState{stateMachine};
    auto stateCompare = new QState{stateMachine};

    //STARTUP
    stateStartup->assignProperty(ui->pbOpen, "enabled", true);
    stateStartup->assignProperty(ui->pbStart, "enabled", false);
    stateStartup->assignProperty(ui->teText1, "enabled", false);
    stateStartup->assignProperty(ui->teText1, "placeholderText", "Load files to start...");
    stateStartup->assignProperty(ui->teText2, "enabled", false);
    stateStartup->assignProperty(ui->teText2, "placeholderText", "Load files to start...");
    stateStartup->assignProperty(ui->cbBox1, "enabled", false);
    stateStartup->assignProperty(ui->cbBox2, "enabled", false);

    stateStartup->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);


    //OPEN
    connect(stateOpen, SIGNAL(entered()), this, SLOT(open()));
    stateOpen->addTransition(this, SIGNAL(error()), stateErrorOpen);
    stateOpen->addTransition(this, SIGNAL(opened()), stateView);


    //ERROR OPEN
    stateErrorOpen->assignProperty(ui->pbOpen, "enabled", true);
    stateErrorOpen->assignProperty(ui->pbStart, "enabled", false);
    stateErrorOpen->assignProperty(ui->cbBox1, "enabled", false);
    stateErrorOpen->assignProperty(ui->cbBox2, "enabled", false);

    connect(stateErrorOpen, SIGNAL(entered()), this, SLOT(errorOpen()));
    stateErrorOpen->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);


    //ERROR COMPARE
    stateErrorCompare->assignProperty(ui->pbOpen, "enabled", true);
    stateErrorCompare->assignProperty(ui->pbStart, "enabled", false);
    stateErrorCompare->assignProperty(ui->cbBox1, "enabled", false);
    stateErrorCompare->assignProperty(ui->cbBox2, "enabled", false);

    connect(stateErrorCompare, SIGNAL(entered()), this, SLOT(errorCompare()));
    stateErrorCompare->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);


    //VIEW
    stateView->assignProperty(ui->pbOpen, "enabled", true);
    stateView->assignProperty(ui->pbStart, "enabled", true);
    stateView->assignProperty(ui->cbBox1, "enabled", true);
    stateView->assignProperty(ui->cbBox2, "enabled", true);
    stateView->assignProperty(ui->teText1, "enabled", true);
    stateView->assignProperty(ui->teText2, "enabled", true);

    stateView->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);
    stateView->addTransition(ui->pbStart, SIGNAL(clicked()), stateChoose);


    //CHOOSE
    connect(stateChoose, SIGNAL(entered()), this, SLOT(checkChoose()));
    stateChoose->addTransition(this, SIGNAL(mustChoose()), stateView);
    stateChoose->addTransition(this, SIGNAL(choosed()), stateView);


    //COMPARE
    connect(stateCompare, SIGNAL(entered()), this, SLOT(compare()));
    stateCompare->addTransition(this, SIGNAL(error()), stateErrorCompare);
    //TODO: Zdefiniowac akcje jak porowna poprawnie, nie wiem gdzie sie definiuje otwarcie nowego okna

    stateMachine->setInitialState(stateStartup);
    stateMachine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open(){
    emit error();
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

void MainWindow::errorOpen(){
    //QMessageBOX
    //TODO: Wyswietlic MessageBox co poszlo nie tak z otwieraniem katalogu i plikow w nim
}

void MainWindow::errorCompare(){
    //QMessageBOX
    //TODO: Wyswietlic MessageBox co poszlo nie tak z porownaniem
}

void MainWindow::compare(){
    emit error();
    //TODO: Porownywanie i otwieranie nowego okna z wynikami, jest cos jakiego jak tableView w QT
}

