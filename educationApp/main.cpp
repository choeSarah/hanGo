/**
 * Name: Cheng-han Pai, Jerry Wu, Sarah Choe, Anand Palukuri
 * review: Jerry Wu
 * Class: CS3505
 *
 * @title Assignment : educationalApp
 * @brief It is the main, which contains MainWindow and other models for the application
 */



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
