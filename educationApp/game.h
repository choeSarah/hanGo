#ifndef GAME_H
#define GAME_H

#include<QObject>
#include "./Box2D/Box2D.h"
#include <QTimer>
#include <QString>
#include <QVector>


class Game: public QObject
{
    Q_OBJECT
public:
    explicit Game(QObject *parent = nullptr);

private:
    // b2World world;
    // b2Body* body;
    // QTimer timer;

    QVector<QString> words;
    QVector<QString> definitions;

    QVector<QString> oldWords;
    QVector<QString> oldDefinitions;


public slots:
    // void updateWorld();
    // void checkInput(QString);
    void handleVocab(QVector<QString> myVocab);
    void handleDef(QVector<QString> myDef);

signals:
    void newDistance(int, int); //Signal for changing position of car
    void updateLevel(QString);
    void updateVocab (QString);
    void enableStart(bool);
};

#endif // GAME_H
