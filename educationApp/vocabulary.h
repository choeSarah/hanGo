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
    void generateNewWord();
    void handleAddVocab(QString word, QString definition);

signals:
    void showVocab(QString vocab, QString pronunciation, QString definition, QString sentence, QString translation);
    void getNumPanels(int size);
    void sendVocabToGame(QVector<QString>);
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

