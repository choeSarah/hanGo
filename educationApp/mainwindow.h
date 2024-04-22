#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "alphabethelp.h"
#include "gamehelp.h"
#include "vocabulary.h"
#include "alphabet.h"
#include "game.h"
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
#include <QTimer>
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
    void handleCoverImage();

    //alphabet

    ///
    /// \brief selecting the pen tool
    ///
    void changeToPen();

    ///
    /// \brief selecting the erase tool
    ///
    void changeToEraser();

    ///
    /// \brief Gets a point to draw when in the alphbet stack
    /// \param pt : the point where mouse previously was.
    ///
    void getPointFromAlphabetModel(QPoint pt);

    ///
    /// \brief Gets a Qimage for the model.
    /// \param image : The Qimage sent from model
    ///
    void getImageFromAlphabetModel(QImage image);

    ///
    /// \brief udate canvas with new Qimage for drawing
    /// \param pixmap: The pixmap canvas is using to updating
    ///
    void updateCanvas(QPixmap pixmap);

    ///
    /// \brief Change the reference image for alphabet
    /// \param index: which reference to choose.c
    ///
    void changeRefImage(int index);

    //vocabulary

    ///
    /// \brief displays the all the information for vocab page.
    /// \param vocab : The korean word
    /// \param pronunciation : The pronounciation of the korean word
    /// \param definition : The definition of the korean words
    /// \param sentence : Example of vocab being used in a sentence
    /// \param translation : English meaning of the word.
    ///
    void handleShowVocab(QString vocab, QString pronunciation, QString definition, QString sentence, QString translation);

    ///
    /// \brief adds the korean word to game list.
    ///
    void handleAddList();

    ///
    /// \brief creates drawing panel base on number of consonance.
    ///
    void generateDrawingPanels();

    ///
    /// \brief sets the size of the word.
    /// \param size : number of consonants in the word
    ///
    void handleNumPanels(int size);

    //game

    ///
    /// \brief starts the game.
    ///
    void handleStartGame();

    ///
    /// \brief Draws and updates the game view at the 60fps using painter for the user.
    /// \param pt : Position of the car object.
    /// \param start : start position of the slope.
    /// \param end : end position of the slope.
    ///
    void draws(QPoint pt, QPoint start, QPoint end);

    ///
    /// \brief Displays the "you lose" screen, when the car falls all the way down the slope.
    ///
    void handleUserLoses();

    ///
    /// \brief Display the "you win" screen, when the user translates all the words in the list correctly.
    ///
    void handleUserWins();

    ///
    /// \brief Changes the level that is displayed.
    ///
    void handleLevelChange(int);

    ///
    /// \brief Takes in the user input and converts it to plain text and send it to model
    ///
    void handleUserInput();

    ///
    /// \brief Starts the timer.
    ///
    void handleRestartTimer();


signals:
    //alphabet
    // Gives mouse position to alphabet model.
    void givePointToAlphabetModel(QPoint pt);

    // Send a Qimage to the alphabet model.
    void giveImageToALphabetModel(QImage image);

    // Sends a signal to model to draw a line from previous point to given point.
    void drawPen(QPoint pt);

    // Sends a signal to model to draw a white line from previous point to given point.
    void erase(QPoint pt);

    // sends the index of the Qimage it changed it's reference image to
    void changeRef(int);

    // Sends a signal to model to set the whole Qimage view is displaying to white.
    void cleanCanvas();

    //vocabulary
    // Generates the next word and send it to view.
    void needNewWord();

    // Sends a signal tell model to add word to game list.
    void addToList(QString word, QString definition);

    // Generates a new drawing panel.
    void showPanels();

    // void scribbleLogic (QImage image, int layoutItemIndex, QHBoxLayout* layout);
    // void givePointToModel();

    //game
    // Sends the word user inputed to the model.
    void sendInputWord(QString);


public:
    ///
    /// \brief MainWindow sets all the connections sets up the ui.
    /// \param vocabulary : vocabulary model
    /// \param alphabet : alphabet model
    /// \param game : game model
    /// \param parent : parent model
    ///
    MainWindow(Vocabulary& vocabulary, Alphabet& alphabet, Game &game, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //Navigation Slots

    ///
    /// \brief switches to the alphabets stackedWidget when on alphabets stackedWidge.
    ///
    void on_alphabet_navBtn2_clicked();

    ///
    /// \brief switches to the vocabulary stackedWidget when on alphabets stackedWidget.
    ///
    void on_alphabet_navBtn1_clicked();

    ///
    /// \brief switches to the game stackedWidget when on alphabets stackedWidget.
    ///
    void on_alphabet_navBtn3_clicked();

    ///
    /// \brief switches to the alphabets stackedWidget when on vocabulary stackedWidget.
    ///
    void on_vocabulary_navBtn1_clicked();

    ///
    /// \brief switches to the game stackedWidget when on vocabulary stackedWidget.
    ///
    void on_vocabulary_navBtn3_clicked();

    ///
    /// \brief switches to the vocabulary stackedWidget when on vocabulary stackedWidget.
    ///
    void on_vocabulary_navBtn2_clicked();

    ///
    /// \brief switches to the alphabets stackedWidget when on game stackedWidget.
    ///
    void on_game_navBtn1_clicked();

    ///
    /// \brief switches to the game stackedWidget when on game stackedWidget.
    ///
    void on_game_navBtn3_clicked();

    ///
    /// \brief switches to the vocabulary stackedWidget when on game stackedWidget.
    ///
    void on_game_navBtn2_clicked();


    //void on_help_btn_clicked();
    ///
    /// \brief shows the help ui for vocab
    ///
    void on_help_btn_vocab_clicked();

    ///
    /// \brief shows the help ui for alphabet
    ///
    void on_help_btn_alphabet_clicked();

    ///
    /// \brief shows the help ui for game
    ///
    void on_help_btn_game_clicked();

    ///
    /// \brief seleting pen tool in vocabulary stack.
    ///
    void penButton_vocab();

    ///
    /// \brief selecting eraser tool in vocabulary stack
    ///
    void eraserButton_vocab();

    ///
    /// \brief clears all drawing done on the panel.
    ///
    void clearButton_vocab();

protected:
    //Mouse events

    ///
    /// \brief Takes in x and y of where ever mouse was pressed to draw.
    /// \param event : mouse action.
    ///
    void mousePressEvent(QMouseEvent *event);

    ///
    /// \brief Tracks mouse movement to draw on the labels mouse is on top of.
    /// \param event : mouse actions.
    ///
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

    // help menu
    VocabHelp help_vocab;
    AlphabetHelp help_alphabet;
    GameHelp help_game;

    QTimer timer;
    QTimer coverTimer;

    QImage gameImage;

    ///
    /// \brief Draws on the label with pixmap
    /// \param image : Qimage what was drawn in from previous the update.
    /// \param layoutItemIndex
    ///
    void scribble(QImage image, int layoutItemIndex);

};
#endif // MAINWINDOW_H
