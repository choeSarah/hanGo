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
