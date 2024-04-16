#include "game.h"

Game::Game(QObject *parent) : QObject(parent)
{
    // world (b2Vec2(0.0f, -10.0f));

    // // Define the ground body.
    // b2BodyDef groundBodyDef;
    // groundBodyDef.position.Set(0.0f, -10.0f);

    // b2Vec2 gravity(0.0f, -10.0f); // Original gravity
    // world.SetGravity(b2Vec2(gravity.x, gravity.y * 0.1f));

}

void Game::handleVocab(QVector<QString> myVocab) {
    words.clear();
    words = myVocab;

    if (words.size() >= 5){
        emit enableStart(false);
    }
}

void Game::handleDef(QVector<QString> myDef) {
    definitions.clear();
    definitions = myDef;
}

void Game::newGameWord() {
    int currentIndex = QRandomGenerator::global()->bounded(words.size());

    gameWord = words.at(currentIndex);
    gameDef = definitions.at(currentIndex);

    oldWords.append(gameWord);
    oldDefinitions.append(gameDef);

    words.removeAt(words.indexOf(gameWord));
    definitions.removeAt(definitions.indexOf(gameDef));

    emit showGameWord(gameWord);
}

void Game::checkInput(QString input) {
    QString lowerCase = input.toLower();

    QString whiteTrim = lowerCase.trimmed();

    if (whiteTrim == gameDef) {
        qDebug() << "correct";
    } else {
        qDebug() << "incorrect";
    }
}
