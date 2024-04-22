#ifndef VOCABULARY_H
#define VOCABULARY_H

#include <QDebug>
#include <QObject>
#include <QVector>
#include <QString>
#include <QFile>
#include <QStringList>
#include <QByteArray>
#include <QRandomGenerator>
#include <QPoint>
#include <QHBoxLayout>
#include <QPixmap>
#include <QLabel>
#include <QWidget>


class Vocabulary : public QObject
{
     Q_OBJECT
public:
    explicit Vocabulary(QObject *parent = nullptr);

public slots:

    ///
    /// \brief Gets a random word from the list created from reading the .csv
    ///
    void generateNewWord();

    ///
    /// \brief Adds vocab to the list for the game.
    /// \param word : Current word that needs to be added to the list.
    /// \param definition : Current word's definition that needs to be added to the list.
    ///
    void handleAddVocab(QString word, QString definition);

signals:
    // Tells the view to show vocab.
    void showVocab(QString vocab, QString pronunciation, QString definition, QString sentence, QString translation);

    // Tells the number of draw panels view needs to have based on vocab.
    void getNumPanels(int size);

    // sends the list of vocab, which were selected, to the game.
    void sendVocabToGame(QVector<QString>);

    // sends the list of vocab, which were selected, to the game.
    void sendDefToGame(QVector<QString>);

private:
    QVector<QString> vocab;
    QVector<QString> pronunciation;
    QVector<QString> definition;
    QVector<QString> sentence;
    QVector<QString> translation;

    QString currentVocab;
    QString currentPronunciation;
    QString currentDefinition;
    QString currentSentence;
    QString currentTranslation;

    QVector<QString> myVocab;
    QVector<QString> myDefinition;

};

#endif // VOCABULARY_H

