#include "mainwindow.h"
#include "alphabet.h"
#include "vocabulary.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vocabulary vocabulary;
    Alphabet alphabet;
    MainWindow w(vocabulary, alphabet);
    w.show();
    return a.exec();
}
