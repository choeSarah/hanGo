#include "game.h"

Game::Game(QObject *parent) : QObject(parent), world(b2Vec2(0.0f, -10.0f))
{
    // // b2Vec2 gravity(0.0f, -10.0f);
    // // world = new b2World(gravity);

    // b2BodyDef myBodyDef;
    // myBodyDef.type = b2_dynamicBody;
    // myBodyDef.position.Set(-10, -20);
    // myBodyDef.angle = 0;

    // b2Body* dynamicBody = world.CreateBody(&myBodyDef);

    // b2PolygonShape boxShape;
    // boxShape.SetAsBox(1,1);

    // b2FixtureDef boxFixtureDef;
    // boxFixtureDef.shape = &boxShape;
    // boxFixtureDef.density = 1.0f;
    // //boxFixtureDef.friction = 0.3f;
    // dynamicBody->CreateFixture(&boxFixtureDef);

    // //connect(&timer, &QTimer::timeout, this, &Game::updateWorld);
    // //timer.start(1000);
}

void Game::updateWorld() {
    // // Update the Box2D world
    // world.Step(1.0f / 60.0f, 6, 2);

    // // Retrieve the position of the body and do something with it
    // b2Vec2 position = body->GetPosition();
    // qDebug() << "Body position: (" << position.x << ", " << position.y << ")";
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


