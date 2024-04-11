#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "vocabulary.h"
#include "alphabet.h"
#include "vocabhelp.h"
#include <QDebug>
#include <QString>
#include <QLayout>
#include <QWidget>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QPoint>
#include <QImage>
#include <QPainter>
#include <QPen>
#include <QPixmap>


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum ToolMode
{
    pen,
    eraser
};

enum PageMode
{
    alpha,
    vocab,
    game
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    //alphabet
    void changeToPen();
    void changeToEraser();
    void getPointFromAlphabetModel(QPoint pt);
    void getImageFromAlphabetModel(QImage image);
    void updateCanvas(QPixmap pixmap);
    void changeRefImage(int index);

    //vocabulary
    void handleShowVocab(QString vocab, QString pronunciation, QString definition, QString sentence, QString translation);
    void handleAddList();
    void generateDrawingPanels();
    void handleNumPanels(int size);

signals:
    //alphabet
    void givePointToAlphabetModel(QPoint pt);
    void giveImageToALphabetModel(QImage image);
    void drawPen(QPoint pt);
    void erase(QPoint pt);
    void changeRef(int);
    void cleanCanvas();

    //vocabulary
    void needNewWord();
    void addToList(QString word, QString definition);
    void showPanels();
    void scribbleLogic (QImage image, int layoutItemIndex, QHBoxLayout* layout);
    // void givePointToModel();

public:
    MainWindow(Vocabulary& vocabulary, Alphabet& alphabet, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //Navigation Slots
    void on_alphabet_navBtn2_clicked();
    void on_alphabet_navBtn1_clicked();
    void on_alphabet_navBtn3_clicked();
    void on_vocabulary_navBtn1_clicked();
    void on_vocabulary_navBtn3_clicked();
    void on_vocabulary_navBtn2_clicked();
    void on_game_navBtn1_clicked();
    void on_game_navBtn3_clicked();
    void on_game_navBtn2_clicked();
    void on_help_btn_clicked();

    void penButton_vocab();
    void eraserButton_vocab();
    void clearButton_vocab();

protected:
    //Mouse events
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    Ui::MainWindow *ui;

    ToolMode alphaMode;
    PageMode pageMode;
    bool alphabet_scribbling = false;
    QPoint lastPoint;
    QImage ViewImage;
    QWidget* alphabet_container;
    QVBoxLayout* alphabet_layout;
    QVector<QPushButton*> buttons;
    QVector<QImage> alphabetImage;
    QVector<QImage> alphabetRefImage;

    QHBoxLayout* layout_vocab;
    QWidget* container_vocab;
    ToolMode mode_vocab;
    QPoint currentPoint;
    QImage currentImage1;
    QImage currentImage2;

    bool scribbling_vocab;
    int currentlyOnPanel;
    int wordSize;

    VocabHelp help_vocab;

    void scribble(QImage image, int layoutItemIndex);
};
#endif // MAINWINDOW_H
