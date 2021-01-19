#include <QtTest>

// add necessary includes here
#include "prepare.h"
#include "levenshteindistance.h"
#include "simplealg.h"

class Test : public QObject
{
    Q_OBJECT

private slots:

    void test_removeEmptyLines()
    {
        Prepare p{"../../project/app/cppkeywords.txt"};
        std::string sin="\n\n\nDzien dobry\nHello World!\n\n\n\n\nLorem ipsum\n\nTest\n\n\n";
        std::string sout="Dzien dobry\nHello World!\nLorem ipsum\nTest\n";

        p.removeEmptyLines(sin);
        QVERIFY(sin==sout);
    }
    void test_removeKeywords()
    {
        Prepare p{"../../project/app/cppkeywords.txt"};
        std::string sin="avcreturnintforxDwhiletruefalsetrycatchcaseswitch123 break;";
        std::string sout="avcxD123 ;";

        p.removeKeywords(sin);
        QVERIFY(sin==sout);
    }
     void test_DeleteComments()
     {
        Prepare p{"../../project/app/cppkeywords.txt"};
        std::string sin="//komentarz w pliku\nLorem ipsum\nDzien dobry, macie ta Colke jeszcze?\nStanooooskiiiiiii\n/*tu jest komentarz\ngagas\nabababa*/\nDalej tekst";
        std::string sout="\nLorem ipsum\nDzien dobry, macie ta Colke jeszcze?\nStanooooskiiiiiii\n\nDalej tekst";

        p.DeleteComments(sin);
        QVERIFY(sin==sout);
     }

     void test_ConstructorTest()
     {
         Prepare p{"../../project/app/cppkeywords.txt"};
         QVERIFY(p.keywords.empty()==false);
         QVERIFY(p.keywords.size()==63);
     }
     void test_levenshteindistanceOne()
     {
         std::string s1="#include <iostream>\n\nint main()\n{\nstd::cout<<\"Hello World!\";\n}";
         LevenshteinDistance ld{};
         auto res=ld.compare(s1,s1);
         QVERIFY(res==1);
     }
     void test_levenshteindistanceTwo()
     {
         std::string s1="#include <iostream>\n\nint main()\n{\nstd::cout<<\"Hello World!\";\n}";
         std::string s2="Litwo, Ojczyzno moja! ty jestes jak zdrowie; ile cie trzeba cenic ten tylko sie dowie";
         LevenshteinDistance ld{};
         auto res=ld.compare(s1,s2);
         QVERIFY(res<0.20);
     }
     void test_levenshteindistanceThree()
     {
         std::string s1="dobry";
         std::string s2="odbry";
         LevenshteinDistance ld{};
         float res=ld.compare(s1,s2);
         QCOMPARE(res,(float)0.6);
     }
    void test_simplealgOne()
    {
        std::string s1="#include <iostream>\n\nint main()\n{\nstd::cout<<\"Hello World!\";\n}";
        std::string s2="std::cout<<\"Hello World!\";\n#include <iostream>\n\nint main()\n{\n}";
        SimpleAlg ld{};
        float res=ld.compare(s1,s2);
        QCOMPARE(res,(float)1.0);
    }
    void test_simplealgTwo()
    {
        std::string s1="#include <iostream>\n\nint main()\n{\nstd::cout<<\"Hello World!\";\n}";
        std::string s2="Litwo, Ojczyzno moja! ty jestes jak zdrowie; ile cie trzeba cenic ten tylko sie dowie";
        SimpleAlg ld{};
        float res=ld.compare(s1,s2);
        QCOMPARE(res,(float)0.0);
    }
    void test_simplealgThree()
    {
        std::string s1="Dzien dobry!\nHello World!\nNice to meet you!\nHello there!";
        std::string s2="How are you?\nMacie ta Colke jeszcze?\nHello there!\nDzien dobry!\nStanowski\nKurtka Najmana\nBuraki\nHi!\nNew Line";
        SimpleAlg ld{};
        float res=ld.compare(s1,s2);
        QCOMPARE(res,(float)0.5);
    }
    void test_simplealgFour()
    {
        std::string s1="Dzien dobry!\nHello World!\nNice to meet you!\nHello there!";
        std::string s2="How are you?\nMacie ta Colke jeszcze?\nHello there!\nDzien dobry!\nStanowski\nKurtka Najmana\nBuraki\nHi!";
        SimpleAlg ld{};
        float res=ld.compare(s2,s1);
        QCOMPARE(res,(float)0.25);
    }

};


QTEST_APPLESS_MAIN(Test)

#include "tst_test.moc"
