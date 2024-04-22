/**
 * Name: Cheng-han Pai, Jerry Wu, Sarah Choe, Anand Palukuri
 * review: Anand Palukuri
 * Class: CS3505
 *
 * @title Assignment : educationalApp
 * @brief This is the model for the game page.
 */



#ifndef GAME_H
#define GAME_H

#include<QObject>
#include "./Box2D/Box2D.h"
#include <QTimer>
#include <QString>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>

#include <QPoint>

class Game: public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

    void boost();

private:
    b2World world;
    b2Body* body;
    b2Body* groundBody;


    QVector<QString> words;
    QVector<QString> definitions;

    QString gameWord;
    QString gameDef;

    QVector<QString> oldWords;
    QVector<QString> oldDefinitions;

    int level;
    int maxWords;


public slots:

    ///
    /// \brief Sends information about ramp start, end and object positions taken from box2D 60 times a second,
    /// then emites signal to mainwindow to display for the user.
    ///
    void updateWorld();

    ///
    /// \brief Updates the vocab list for game. if there are less than 5 words than woun't let u play.
    /// \param myVocab : List of vocab add for the game.
    ///
    void handleVocab(QVector<QString> myVocab);

    ///
    /// \brief Udates the definitions list for game.
    /// \param myDef : List of definition.
    ///
    void handleDef(QVector<QString> myDef);

    ///
    /// \brief Chooses new word from the list the ask in the game.
    ///
    void newGameWord();

    ///
    /// \brief Checks if the answer user Inputed is correct.
    /// \param input : Answer by the user.
    ///
    void checkInput(QString input);

    ///
    /// \brief Resets Box2D world and sets the level back to "1". Then restarts the game.
    ///
    void playAgain();

signals:

    // sends the position of the car.
    void newDistance(int, int); //Signal for changing position of car

    // sends when about to level up.
    void updateLevel(QString);

    // sends vocab to display to update.
    void updateVocab (QString);

    //sends view that the game started.
    void enableStart(bool);

    // send the game word.
    void showGameWord(QString);

    // signal tell the mainwindow to draw the game.
    void drawSignal(QPoint, QPoint, QPoint);

    // tells the view user won.
    void userWins();

    //tells the view user lost.
    void userLoses();

    // tells to generate a new word for the game.
    void generateNew();

    // tells the view to change the level.
    void levelChange(int);

    // tells the view reset the timer
    void restartTimer();
};

#endif // GAME_H
