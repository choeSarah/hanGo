#include "vocabulary.h"

Vocabulary::Vocabulary(QObject *parent) : QObject(parent) {
    //Reading the vocabulary file and putting them into vectors
    QFile file (":/vocabList/CS3505 - App Dictionary - Sheet1 (1).csv");

    if (file.open(QIODevice::ReadOnly)) { //If the file is openable
        while (!file.atEnd()) { //While the file still has content
            QByteArray line = file.readLine(); //Read a line
            QStringList words = QString(line).split(','); //Split all the elements by commas

            vocab.append(words.at(0));
            pronunciation.append(words.at(1));
            definition.append(words.at(2));
            sentence.append(words.at(3));
            translation.append(words.at(4));
        }
    }

}

void Vocabulary::generateNewWord() {
    int currentIndex = QRandomGenerator::global()->bounded(100);

    currentVocab = vocab.at(currentIndex);
    currentPronunciation = pronunciation.at(currentIndex);
    currentDefinition = definition.at(currentIndex);
    currentSentence = sentence.at(currentIndex);
    currentTranslation = translation.at(currentIndex);

    emit getNumPanels(currentVocab.size());
    emit showVocab(currentVocab, currentPronunciation, currentDefinition, currentSentence, currentTranslation);
}

void Vocabulary::handleAddVocab(QString word, QString definition) {
    if (!myVocab.contains(word)) {
        myVocab.append(word);
        myDefinition.append(definition);

        emit sendVocabToGame(myVocab);
        emit sendDefToGame(myDefinition);
    }
}



