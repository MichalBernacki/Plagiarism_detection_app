#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "levenshteindistance.h"
#include "simplealg.h"
#include "prepare.h"
#include <iostream>
#include <QStateMachine>
#include <QHistoryState>
#include <QFileDialog>
#include <QListView>
#include <QTreeView>
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QColor>
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
    auto stateShow = new QState{stateMachine};
    auto stateClear = new QState{stateMachine};
    //STARTUP
    stateStartup->assignProperty(ui->pbOpen, "enabled", true);
    stateStartup->assignProperty(ui->pbStart, "enabled", false);
    stateStartup->assignProperty(ui->taCompare, "enabled", false);
    stateStartup->assignProperty(ui->leLabel, "text", "Load directory to start...");
    stateStartup->assignProperty(ui->cbBox1, "enabled", false);
    stateStartup->assignProperty(ui->cbBox2, "enabled", false);
    stateStartup->assignProperty(ui->cbBox3, "enabled", false);
    stateStartup->assignProperty(ui->cbBox4, "enabled", false);
    stateStartup->assignProperty(ui->cbBox5, "enabled", false);
    stateStartup->assignProperty(ui->frResult, "enabled", false);

    stateStartup->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);


    //OPEN
    stateStartup->assignProperty(ui->frResult, "enabled", false);
    connect(stateOpen, SIGNAL(entered()), this, SLOT(open()));
    stateOpen->addTransition(this, SIGNAL(error(QString)), stateError);
    stateOpen->addTransition(this, SIGNAL(opened()), stateView);



    //ERROR
    stateError->assignProperty(ui->pbOpen, "enabled", true);
    stateError->assignProperty(ui->pbStart, "enabled", false);
    stateError->assignProperty(ui->cbBox1, "enabled", false);
    stateError->assignProperty(ui->cbBox2, "enabled", false);
    stateError->assignProperty(ui->cbBox3, "enabled", false);
    stateError->assignProperty(ui->cbBox4, "enabled", false);
    stateError->assignProperty(ui->cbBox5, "enabled", false);
    stateError->assignProperty(ui->taCompare, "enabled", false);

    connect(stateError, SIGNAL(entered()), this, SLOT(errorFunction()));
    stateError->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);


    //VIEW
    connect(stateView, SIGNAL(entered()), this, SLOT(view()));
    stateView->assignProperty(ui->pbOpen, "enabled", true);
    stateView->assignProperty(ui->pbStart, "enabled", true);
    stateView->assignProperty(ui->taCompare, "enabled", false);
    stateView->assignProperty(ui->cbBox1, "enabled", true);
    stateView->assignProperty(ui->cbBox2, "enabled", true);
    stateView->assignProperty(ui->cbBox3, "enabled", true);
    stateView->assignProperty(ui->cbBox4, "enabled", true);
    stateView->assignProperty(ui->cbBox5, "enabled", true);

    stateView->addTransition(ui->pbOpen, SIGNAL(clicked()), stateOpen);
    stateView->addTransition(ui->pbStart, SIGNAL(clicked()), stateChoose);
    //stateView->addTransition(ui->pbStart, SIGNAL(clicked()), stateShow);


    //CHOOSE
    connect(stateChoose, SIGNAL(entered()), this, SLOT(checkChoose()));
    stateChoose->addTransition(this, SIGNAL(mustChoose()), stateView);
    stateChoose->addTransition(this, SIGNAL(choosed()), stateCompare);


    //COMPARE
    stateCompare->assignProperty(ui->taCompare, "enabled", true);
    connect(stateCompare, SIGNAL(entered()), this, SLOT(compare()));
    stateCompare->addTransition(this, SIGNAL(error(QString)), stateError);
    //connect(ui->taCompare->horizontalHeader(), SIGNAL(sectionClicked()), this, SLOT(Table_HeaderClick()) );
    stateCompare->addTransition(ui->pbOpen,SIGNAL(clicked(bool)),stateClear);

    //CLEAR
    connect(stateClear, SIGNAL(entered()), this, SLOT(clear()));
    stateClear->addTransition(this,SIGNAL(cleared()),stateOpen);


    //SHOW

    connect(ui->pbFileM1, SIGNAL(clicked()), this, SLOT(showResultsInPanel()));
    connect(ui->pbFileM2, SIGNAL(clicked()), this, SLOT(showResultsInPanel()));
    connect(ui->pbFileM3, SIGNAL(clicked()), this, SLOT(showResultsInPanel()));
    connect(ui->pbFileM4, SIGNAL(clicked()), this, SLOT(showResultsInPanel()));
    stateShow->assignProperty(ui->frResult, "enabled", true);



    stateMachine->setInitialState(stateStartup);
    stateMachine->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open(){

    QFileDialog w;
    w.setFileMode(QFileDialog::DirectoryOnly);
    w.setOption(QFileDialog::DontUseNativeDialog,true);
    //w.setOption(QFileDialog::ShowDirsOnly,false); //Decide whether we want to see other files, more intuitive navigation, weird selection "quirks"

    QListView *lView = w.findChild<QListView*>("listView");
    if (lView)
        lView->setSelectionMode(QAbstractItemView::MultiSelection);
    QTreeView *tView = w.findChild<QTreeView*>();
    if (tView)
        tView->setSelectionMode(QAbstractItemView::MultiSelection);

    if(w.exec() == 0){
        emit opened();  //User canceled
        return;
    }

    //1. Just gets a single directory, simple, no complications
    //QString filepath = QFileDialog::getExistingDirectory(this, tr("Open directory"), "..", QFileDialog::DontResolveSymlinks | QFileDialog::DontUseNativeDialog);

    //2. Able to select multiple paths, shows other files (but can also choose them, so Project::ctor just ignores them)
    for(auto& filepath: w.selectedFiles()){
        try {
            projects.emplace(filepath.toStdString());
        }catch(const NotADirectory& e){
            std::cerr<<e.what()<<'\n';//best to just ignore it
        }
        catch (const std::exception& e) {
            emit error(e.what());   //works only if error is not a state, but a function
                                    //can also try to build-up an error state, or error message
                                    //and send it afterwards,
                                    //decide whether to discard
                                    //all projects, or just invalid ones
        }
    }
    emit opened();
}

void MainWindow::checkChoose(){
    if( !(ui->cbBox1->isChecked() || ui->cbBox2->isChecked()))
    {
        QMessageBox msgBox;
        msgBox.setText("You have to choose at least 1 algorithm!");
        msgBox.exec();
        emit mustChoose();
    }
    else
        emit choosed();
}

void MainWindow::errorFunction(){
    //QMessageBOX
    std::cerr<<"I errored!\n";
    //TODO: Wyswietlic MessageBox co poszlo nie tak z otwieraniem katalogu i plikow w nim
}


void MainWindow::clear(){
    ui->taCompare->clear();
    projects.erase(projects.begin(),projects.end());
    emit cleared();
}


void MainWindow::compare(){
    //emit error("compare");
    int l = 0;
    int k = 0;
    for (auto project:projects)
    {
        for(auto project2:projects)
        {
            if(k==l)
            {
                k++;
                continue;
            }
            std::vector p1 = project.GetFiles();
            std::vector p2 = project2.GetFiles();
            float percent = 0;
            float num_of_cmp = 0;
            for(int i=0; i<p1.size(); i++)
                for(int j=0; j<p2.size(); j++)
                {
                    std::string s1=p1.at(i).m_OriginalContent;
                    std::string s2=p2.at(j).m_OriginalContent;
                    Prepare p{"../project/cppkeywords.txt"};
                    if(ui->cbBox5->isChecked())
                    {
                        //komentarze
                        s1=p.DeleteComments(s1);
                        s2=p.DeleteComments(s2);
                    }
                    if(ui->cbBox3->isChecked())
                    {
                        //slowa kluczowe
                       s1=p.removeKeywords(s1);
                       s2=p.removeKeywords(s2);
                    }

                    if(ui->cbBox4->isChecked())
                    {
                        //puste linie
                        s1=p.removeEmptyLines(s1);
                        s2=p.removeEmptyLines(s2);
                    }

                    if(ui->cbBox1->isChecked())
                    {
                        num_of_cmp++;
                        LevenshteinDistance l{};


                        percent+=l.compare(s1,s2);
                    }
                    if(ui->cbBox2->isChecked())
                    {
                        num_of_cmp++;
                        SimpleAlg l{};
                        percent+=l.compare(s1,s2);
                    }
                }
            percent/=num_of_cmp;
            QTableWidgetItem *item = ui->taCompare->item(l,k);
            item= new QTableWidgetItem();
            ui->taCompare->setItem(l,k,item);
            item->setText(QString::number(percent*100)+"%");
            item->setBackground(QColor(255*percent,255-255*percent,0,255));
            k++;
        }
        k=0;
        l++;
    }
    ui->retranslateUi(this);
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
    ui->taCompare->clear();
    ui->taCompare->setRowCount(projects.size());
    ui->taCompare->setColumnCount(projects.size());
    size_t r = 0;
    for (auto& project:projects)
    {
        ui->taCompare->setHorizontalHeaderItem(r, new QTableWidgetItem(project.GetName().c_str()));
        ui->taCompare->setVerticalHeaderItem(r, new QTableWidgetItem(project.GetName().c_str()));
        ++r;
    }
}

void MainWindow::showResultsInPanel()
{
    ndial = new NxNDialog(this);
    ndial->setModal(true);
    ndial->exec();
}



