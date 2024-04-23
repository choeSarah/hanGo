/**
 * Name: Cheng-han Pai, Jerry Wu, Sarah Choe, Anand Palukuri
 * review: Cheng-han Pai
 * Class: CS3505
 *
 * @title Assignment : educationalApp
 * @brief This is the model for the game page.
 */



#include "game.h"

Game::Game(QObject *parent)
    : QObject(parent),
    world(b2Vec2(0.0f, -3.0f))
{
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0.0f, -100.0f);
    groundBodyDef.angle=-M_PI / 4;

    //Define gravity
    b2Vec2 gravity(0.0f, -3.0f);
    world.SetGravity(b2Vec2(gravity.x, gravity.y));

    // The body is also added to the world.
    groundBody = world.CreateBody(&groundBodyDef);

    // Define the ground box shape.
    b2PolygonShape groundBox;
    groundBox.SetAsBox(8000.0f, 10.0f);

    // Add the ground fixture to the ground body.
    groundBody->CreateFixture(&groundBox, 0.0f);

    // Define the dynamic body. We set its position and call the body factory.
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, -50.0f);
    body = world.CreateBody(&bodyDef);

    // Define another box shape for our dynamic body.
    b2CircleShape circle;
    circle.m_p.Set(100.0f, 0.0f);
    circle.m_radius = 20.0f;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &circle;

    // Set the box density to be non-zero, so it will be dynamic.
    fixtureDef.density = 1.0f;

    // Override the default friction.
    fixtureDef.friction = 0.0f;

    //set the restitution to 0.9
    fixtureDef.restitution = 0.0f;

    body->CreateFixture(&fixtureDef);

    level = 1;
}

void Game::updateWorld() {
    //Define timestep and iterations for world simulation
    float32 timeStep = 1.0f / 60.0f;
    int32 velocityIterations = 0;
    int32 positionIterations = 0;

    //Step the world simulation
    world.Step(timeStep, velocityIterations, positionIterations);

    //Get position of the dynamic body
    b2Vec2 position = body->GetPosition();
    QPoint sendPoint (position.x/2, -position.y/2);

    //Get position and angle of the ground body
    b2Vec2 groundPos = groundBody->GetPosition();
    float groundAngle = groundBody->GetAngle();
    float halfWidth = 1500.0f; // Half-width of the ground body
    float startX = -(halfWidth * cos(groundAngle)) + groundPos.x;
    float startY = -(halfWidth * sin(groundAngle)) + groundPos.y -100;
    float endX = (halfWidth * cos(groundAngle)) + groundPos.x;
    float endY = (halfWidth * sin(groundAngle)) + groundPos.y-100;

    // Convert Box2D coordinates to view coordinates
    QPoint startPoint(startX / 2, -startY / 2);
    QPoint endPoint(endX / 2, -endY / 2);

    emit drawSignal(sendPoint, startPoint, endPoint);

    //If the circle hits the bottom of the view, player loses
    if (position.y <= -950) {
        emit userLoses();
    }

}

void Game::handleVocab(QVector<QString> myVocab) {
    words.clear();
    words = myVocab;

    if (words.size() >= 5){
        emit enableStart(false);
        maxWords = words.size();
    }

}

void Game::handleDef(QVector<QString> myDef) {
    definitions.clear();
    definitions = myDef;
}

void Game::newGameWord() {
    int currentIndex = QRandomGenerator::global()->bounded(words.size());

    //Select random word and corresponding definition in user's list
    gameWord = words.at(currentIndex);
    gameDef = definitions.at(currentIndex);

    //Mark the selected word as 'old' and remove from user's list to prevent duplicates in a single level
    oldWords.append(gameWord);
    oldDefinitions.append(gameDef);
    words.removeAt(words.indexOf(gameWord));
    definitions.removeAt(definitions.indexOf(gameDef));

    emit showGameWord(gameWord); //Display the current random word
}

void Game::checkInput(QString input) {
    //Convert user input to lowercase and trim whitespace
    QString lowerCase = input.toLower();
    QString whiteTrim = lowerCase.trimmed();

    if (whiteTrim == gameDef) { //Check correctness of the user input
        if (oldWords.size() == maxWords) {
            emit userWins();
        } else {
            if (level == oldWords.size()) { //Reached end of level
                level++; //Move to next level
                emit levelChange(level);

                for (int i=0; i<oldWords.size(); i++) {
                    words.append(oldWords.at(i));
                    definitions.append(oldDefinitions.at(i));
                }

                oldWords.clear();
                oldDefinitions.clear();

                //Resetting the car
                b2Vec2 newPosition(0.0f, 0.0f);
                body->SetTransform(newPosition, body->GetAngle());
                emit generateNew();
            } else { //Still on a level
                boost();
                emit generateNew();
            }
        }

    }
}

void Game::boost() {
    b2Vec2 impulse (-200.0f, 0.0f); //Define an impulse vector
    body->SetLinearVelocity(body->GetLinearVelocity() + impulse); //Apply the impulse
}

void Game::playAgain() {
    level = 1;
    emit levelChange(level);

    for (int i=0; i<oldWords.size(); i++) {
        words.append(oldWords.at(i));
        definitions.append(oldDefinitions.at(i));
    }

    oldWords.clear();
    oldDefinitions.clear();

    b2Vec2 newPosition(0.0f, 0.0f);
    body->SetTransform(newPosition, body->GetAngle());
    emit generateNew();
    emit restartTimer();
}


