#ifndef GAME_H
#define GAME_H

#include<QObject>
#include "./Box2D/Box2D.h"
#include <QTimer>
#include <QString>
#include <QVector>
#include <QRandomGenerator>
#include <QDebug>

class Game: public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

private:
    b2World world;
    b2Body* body;
    QTimer timer;

    QVector<QString> words;
    QVector<QString> definitions;

    QString gameWord;
    QString gameDef;

    QVector<QString> oldWords;
    QVector<QString> oldDefinitions;


public slots:
    void updateWorld();
    void handleVocab(QVector<QString> myVocab);
    void handleDef(QVector<QString> myDef);
    void newGameWord();
    void checkInput(QString input);

signals:
    void newDistance(int, int); //Signal for changing position of car
    void updateLevel(QString);
    void updateVocab (QString);
    void enableStart(bool);
    void showGameWord(QString);
};

#endif // GAME_H
