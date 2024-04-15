#include "mainwindow.h"
#include "alphabet.h"
#include "vocabulary.h"
#include "game.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Vocabulary vocabulary;
    Alphabet alphabet;
    Game game;
    MainWindow w(vocabulary, alphabet, game);
    w.show();
    return a.exec();
}
