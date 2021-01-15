#include "mainwindow.h"
#include <QApplication>
#include "prepare.h"
#include "levenshteindistance.h"
int main(int argc, char *argv[])
{
    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    std::ifstream ifs("test");
    std::string str;
    getline(ifs,str,'\0');
    std::cout << "Przed: \n" << str << std::endl;
    Prepare p{};
    LevenshteinDistance ld{};
    std::string test = p.DeleteComments(str);
    std::cout<< "Po:\n" << test << std::endl;
    std::cout<< "podobienstwo " << ld.compare("abba","abba");
    //return a.exec();
    return 0;
}
