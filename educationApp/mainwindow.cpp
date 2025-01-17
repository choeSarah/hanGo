/**
 * Name: Cheng-han Pai, Jerry Wu, Sarah Choe, Anand Palukuri
 * review: Jerry Wu
 * Class: CS3505
 *
 * @title Assignment : educationalApp
 * @brief This reprent the view of the educationalApp, which the user interacts with.
 */


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "vocabulary.h"
#include "alphabet.h"
#include "game.h"

MainWindow::MainWindow(Vocabulary &vocabulary, Alphabet &alphabet, Game &game, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->alphabet_canvas->setStyleSheet("border:1px solid #000000;");
    ui->alphabet_ref->setStyleSheet("border:1px solid #000000;");
    // ui->alphabet_penButton->setStyleSheet("border:2px solid #ff0000;");
    // ui->alphabet_eraserButton->setStyleSheet("border:0px solid #808080;");
    alphabet_container= new QWidget();
    alphabet_layout = new QVBoxLayout(alphabet_container);
    ui->alphabet_scrollArea->setWidgetResizable(true);
    ui->alphabet_scrollArea->setWidget(alphabet_container);

    ViewImage = QPixmap(300,300).toImage();
    ViewImage.fill(Qt::white);
    ui->alphabet_canvas->setPixmap(QPixmap::fromImage(ViewImage));

    currentImage1 = QPixmap(200,200).toImage();
    currentImage2 = QPixmap(200,200).toImage();
    currentImage1.fill(Qt::white);
    currentImage2.fill(Qt::white);

    scribbling_vocab = false;

    mode_vocab = pen;
    alphaMode = pen;

    ui->level_label->setVisible(false);
    ui->display_word->setVisible(false);
    ui->input->setVisible(false);
    ui->playAgain_button->setVisible(false);

    // ui->start_button->setStyleSheet("background-color: #000000;");
    ui->start_button->setDisabled(true);

    //Connections for Learn Alphabet page
    connect(ui->alphabet_penButton,
            &QAbstractButton::clicked,
            this,
            &MainWindow::changeToPen);
    connect(ui->alphabet_cleanButton,
            &QAbstractButton::clicked,
            &alphabet,
            &Alphabet::cleanCanvas);
    connect(this,
            &MainWindow::cleanCanvas,
            &alphabet,
            &Alphabet::cleanCanvas);
    connect(ui->alphabet_eraserButton,
            &QAbstractButton::clicked,
            this,
            &MainWindow::changeToEraser);
    connect(&alphabet, //Give user pt to View
            &Alphabet::givePointToView,
            this,
            &MainWindow::getPointFromAlphabetModel);
    connect(&alphabet, //Give canvas to View
            &Alphabet::giveImageToView,
            this,
            &MainWindow::getImageFromAlphabetModel);
    connect(&alphabet, //Update canvas
            &Alphabet::update,
            this,
            &MainWindow::updateCanvas);
    connect(this, //Give user pt to Model
            &MainWindow::givePointToAlphabetModel,
            &alphabet,
            &Alphabet::getPointFromView);
    connect(this, //Give canvas to Model
            &MainWindow::giveImageToALphabetModel,
            &alphabet,
            &Alphabet::getImageFromView);
    connect(this,
            &MainWindow::drawPen,
            &alphabet,
            &Alphabet::draw);
    connect(this,
            &MainWindow::erase,
            &alphabet,
            &Alphabet::erase);
    connect(this,
            &MainWindow::changeRef,
            this,
            &MainWindow::changeRefImage);

    //Connections for Learn Vocabulary page
    connect (ui->penButton,
            &QAbstractButton::clicked,
            this,
            &MainWindow::penButton_vocab);

    connect (ui->eraserButton,
            &QAbstractButton::clicked,
            this,
            &MainWindow::eraserButton_vocab);

    connect (ui->clearButton,
            &QAbstractButton::clicked,
            this,
            &MainWindow::clearButton_vocab);

    connect(&vocabulary,
            &Vocabulary::showVocab,
            this,
            &MainWindow::handleShowVocab);

    connect(ui->new_btn,
            &QAbstractButton::clicked,
            this,
            [=]() {emit needNewWord();});

    connect(ui->new_btn,
            &QAbstractButton::clicked,
            this,
            &MainWindow::clearButton_vocab);

    connect (this,
            &MainWindow::needNewWord,
            &vocabulary,
            &Vocabulary::generateNewWord);

    connect (ui->add_btn,
            &QAbstractButton::clicked,
            this,
            &MainWindow::handleAddList);

    connect (this,
            &MainWindow::addToList,
            &vocabulary,
            &Vocabulary::handleAddVocab);

    connect (this,
            &MainWindow::showPanels,
            this,
            &MainWindow::generateDrawingPanels);

    connect (&vocabulary,
            &Vocabulary::getNumPanels,
            this,
            &MainWindow::handleNumPanels);

    for(int i = 1; i<25; i++)
    {
        QString icon = QString(":/alphabet_icon/Artboard_1_%1.png").arg(i);
        //QString icon = QString(":/alphabet_icon/Artboard_1_1.png").arg(i);
        QString ex = QString(":/alphabet_example/EX_1_%1.png").arg(i);
        QImage imageEx(ex);
        QImage imageIcon(icon);
        alphabetImage.push_back(imageIcon);
        alphabetRefImage.push_back(imageEx);
    }
    for(int i = 0; i < 24; i ++)
    {
        QPushButton * button = new QPushButton(ui->alphabet_scrollArea);
        button->setFixedSize(100,100); //Set size for the button
        alphabet_layout->addWidget(button); //Adding the new button to the scrollarea
        buttons.push_back(button);
        //Reflecting the new frame to the button
        QIcon icon(QPixmap::fromImage(alphabetImage[i].scaled(100,100)));
        buttons[i]->setIcon(icon);
        buttons[i]->setIconSize(QSize(100,100));
        connect(buttons.at(i),
                &QPushButton::clicked,
                this,
                [=]() {emit changeRef(i);});
    }

    ui->alphabet_ref->setPixmap(QPixmap::fromImage(alphabetRefImage.at(0).scaled(300,300)));

    emit needNewWord();

    connect (&vocabulary,
            &Vocabulary::sendVocabToGame,
            &game,
            &Game::handleVocab);

    connect (&vocabulary,
            &Vocabulary::sendDefToGame,
            &game,
            &Game::handleDef);

    connect (ui->start_button,
            &QAbstractButton::clicked,
            this,
            &MainWindow::handleStartGame);

    connect (&game,
            &Game::enableStart,
            ui->start_button,
            &QAbstractButton::setDisabled);


    connect (ui->start_button,
            &QAbstractButton::clicked,
            &game,
            &Game::newGameWord);

    connect (&game,
            &Game::generateNew,
            &game,
            &Game::newGameWord);

    connect (&game,
            &Game::levelChange,
            this,
            &MainWindow::handleLevelChange);

    connect (&game,
            &Game::showGameWord,
            ui->display_word,
            &QLabel::setText);

    connect (ui->input,
            &QTextEdit::textChanged,
            this,
            &MainWindow::handleUserInput);

    connect (this,
            &MainWindow::sendInputWord,
            &game,
            &Game::checkInput);

    connect (
        &timer,
        &QTimer::timeout,
        &game,
        &Game::updateWorld);

    connect (&game,
            &Game::restartTimer,
            this,
            &MainWindow::handleRestartTimer);

    connect (&game,
            &Game::drawSignal,
            this,
            &MainWindow::draws);

    connect (&game,
            &Game::userLoses,
            this,
            &MainWindow::handleUserLoses);

    connect (&game,
            &Game::userWins,
            this,
            &MainWindow::handleUserWins);

    connect(ui->playAgain_button,
            &QAbstractButton::clicked,
            &game,
            &Game::playAgain);

    gameImage = QPixmap(500,500).toImage();

    coverTimer.start(2000);

    connect(&coverTimer,
            &QTimer::timeout,
            this,
            &MainWindow::handleCoverImage);

    QImage coverImage (":/coverImage/coverImage.png");
    QPixmap coverMap = QPixmap::fromImage(coverImage);
    ui->coverImage->setPixmap(coverMap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleCoverImage() {
    ui->coverImage->setVisible(false);
    coverTimer.stop();
}

//Learn Alphabet Slots
void MainWindow::changeToPen()
{
    ui->alphabet_penButton->setStyleSheet("border-radius: 15px; border: 2px solid #119DA4;");
    ui->alphabet_eraserButton->setStyleSheet("border-radius: 15px; border: 2px solid black;");
    alphaMode = pen;
}

void MainWindow::changeToEraser()
{
    ui->alphabet_penButton->setStyleSheet("border-radius: 15px; border: 2px solid black;");
    ui->alphabet_eraserButton->setStyleSheet("border-radius: 15px; border: 2px solid #119DA4;");
    alphaMode = eraser;
}

void MainWindow::getPointFromAlphabetModel(QPoint pt)
{
    lastPoint=pt;
}

void MainWindow::getImageFromAlphabetModel(QImage image)
{
    ViewImage=image;
}

void MainWindow::updateCanvas(QPixmap pixmap)
{
    ui->alphabet_canvas->setPixmap(pixmap); //Display the canvas on the drawing panel
    update();
}

void MainWindow::changeRefImage(int index)
{
    QImage ref = alphabetRefImage.at(index).scaled(300,300);
    ui->alphabet_ref->setPixmap(QPixmap::fromImage(ref));
    emit cleanCanvas();
}

//Learn Vocabulary Slots
void MainWindow::handleShowVocab(QString vocab, QString pronunciation, QString definition, QString sentence, QString translation) {
    ui->word->setText(vocab);
    ui->pronunciation->setText(pronunciation);
    ui->definition->setText(definition);
    ui->sentence->setText(sentence);
    ui->translation->setText(translation);

    emit showPanels();
}

void MainWindow::handleAddList () {
    QString currentWord = ui->word->text();
    QString currentDefinition = ui->definition->text();

    emit addToList(currentWord, currentDefinition);
}

void MainWindow::handleNumPanels(int size) {
    wordSize = size;
}

void MainWindow::generateDrawingPanels() {
    container_vocab= new QWidget();
    layout_vocab = new QHBoxLayout(container_vocab);
    ui->scrollArea->setWidget(container_vocab);

    if (wordSize == 1) {
        QLabel * label = new QLabel(ui->scrollArea);

        label->setFixedSize(200,200);
        label->setStyleSheet("border:1px solid #000000;");

        QPixmap pixmap = QPixmap::fromImage(currentImage1);
        label->setPixmap(pixmap);

        layout_vocab->addWidget(label);
    } else if (wordSize == 2) {
        QLabel * label1 = new QLabel(ui->scrollArea);
        QLabel * label2 = new QLabel(ui->scrollArea);

        label1->setFixedSize(200,200);
        label2->setFixedSize(200,200);

        label1->setStyleSheet("border:1px solid #000000;");
        label2->setStyleSheet("border:1px solid #000000;");

        QPixmap pixmap1 = QPixmap::fromImage(currentImage1);
        QPixmap pixmap2 = QPixmap::fromImage(currentImage2);
        label1->setPixmap(pixmap1);
        label2->setPixmap(pixmap2);

        layout_vocab->addWidget(label1);
        layout_vocab->addWidget(label2);
    }
}

//Drawing Slots
void MainWindow::penButton_vocab()
{
    ui->penButton->setStyleSheet("border:2px solid #119DA4; border-radius: 15px;");
    ui->eraserButton->setStyleSheet("border:2px solid #000000; border-radius: 15px;");
    ui->clearButton->setStyleSheet("border:2px solid #000000; border-radius: 15px;");

    mode_vocab = pen;
}

void MainWindow::eraserButton_vocab()
{
    ui->eraserButton->setStyleSheet("border:2px solid #119DA4; border-radius: 15px;");
    ui->penButton->setStyleSheet("border:2px solid #000000; border-radius: 15px;");
    ui->clearButton->setStyleSheet("border:2px solid #000000; border-radius: 15px;");

    mode_vocab = eraser;
}

void MainWindow::clearButton_vocab()
{
    ui->clearButton->setStyleSheet("border:2px solid #119DA4; border-radius: 15px;");
    ui->penButton->setStyleSheet("border:2px solid #000000; border-radius: 15px;");
    ui->eraserButton->setStyleSheet("border:2px solid #000000; border-radius: 15px;");

    currentImage1.fill(Qt::white);
    currentImage2.fill(Qt::white);

    QPixmap pixmap1 = QPixmap::fromImage(currentImage1);
    QPixmap pixmap2 = QPixmap::fromImage(currentImage2);

    QLayoutItem *item1 = layout_vocab->itemAt(0);
    QLayoutItem *item2 = layout_vocab->itemAt(1);

    // Check if the item exists and is a widget
    if (item1 && item1->widget()) {
        // Check if the widget is a QLabel
        if (QLabel *label = qobject_cast<QLabel*>(item1->widget())) {
            // Set the pixmap
            label->setPixmap(pixmap1);
            //qDebug() << "made it";
        }
    }

    // Check if the item exists and is a widget
    if (item2 && item2->widget()) {
        // Check if the widget is a QLabel
        if (QLabel *label2 = qobject_cast<QLabel*>(item2->widget())) {
            // Set the pixmap
            label2->setPixmap(pixmap2);
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    switch (pageMode) {
    case alpha:
        if (event->button() == Qt::LeftButton) {
            QPoint pos=ui->alphabet_canvas->pos(); //gets the position of the canvas label in relation to the whole window
            //int canvasLabelSize = ui->alphabet_canvas->width(); //gets the size of the actual label
            lastPoint = event->position().toPoint(); //gets the position of where the user clicked in relation to the whole window
            lastPoint -= pos; //making lastPoint = the point of where the user clicked within the label
            emit givePointToAlphabetModel(lastPoint);
            alphabet_scribbling=true;
        }
        break;
    case vocab:
        if (event->button() == Qt::LeftButton) {

            QPoint lastPoint = event->position().toPoint(); //gets the position of where the user clicked in relation to the whole window

            if (wordSize == 1) { //If there is one character

                QPoint panelPos = layout_vocab->itemAt(0)->widget()->pos(); //panel1
                QPoint scrollAreaPos = ui->scrollArea->pos(); //scrollarea
                QPoint finalPos = panelPos + scrollAreaPos; //final area

                double panelSize = layout_vocab->itemAt(0)->widget()->width(); //Getting the size of the one panel

                if ((finalPos.x() <= lastPoint.x()) && (lastPoint.x() <= finalPos.x() + panelSize)) { //If the user clicked within the canvas
                    if ((finalPos.y() <= lastPoint.y()) && (lastPoint.y() <= finalPos.y() + panelSize)) {

                        currentPoint = lastPoint - finalPos;
                        scribbling_vocab = true;
                    }
                }

            } else if  (wordSize == 2) { //If there are two characters
                QPoint scrollAreaPos = ui->scrollArea->pos(); //scrollarea
                QPoint panelPos1 = layout_vocab->itemAt(0)->widget()->pos();
                QPoint panelPos2 = layout_vocab->itemAt(1)->widget()->pos();

                QPoint finalPos1 = panelPos1 + scrollAreaPos;
                QPoint finalPos2 = panelPos2 + scrollAreaPos;

                double panelSize = layout_vocab->itemAt(0)->widget()->width();

                if ((finalPos1.x() <= lastPoint.x()) && (lastPoint.x() <= finalPos1.x() + panelSize)) { //If the user clicked within the canvas
                    if ((finalPos1.y() <= lastPoint.y()) && (lastPoint.y() <= finalPos1.y() + panelSize)) {
                        currentPoint = lastPoint - finalPos1;
                        scribbling_vocab = true;
                        currentlyOnPanel = 0;

                    }
                } else if ((finalPos2.x() <= lastPoint.x()) && (lastPoint.x() <= finalPos2.x() + panelSize)) {
                    if ((finalPos2.y() <= lastPoint.y()) && (lastPoint.y() <= finalPos2.y() + panelSize)) {
                        currentPoint = lastPoint - finalPos2;
                        scribbling_vocab = true;
                        currentlyOnPanel = 1;

                    }
                }
            }

        }

        break;

        case game:
        break;
    }

}

void MainWindow::scribble(QImage image, int layoutItemIndex){
    //Update drawing panels
    QPixmap pixmap = QPixmap::fromImage(image);

    QLayoutItem *item = layout_vocab->itemAt(layoutItemIndex);

    // Check if the item exists and is a widget
    if (item && item->widget()) {
        // Check if the widget is a QLabel
        if (QLabel *label = qobject_cast<QLabel*>(item->widget())) {
            // Set the pixmap
            label->setPixmap(pixmap);
            //qDebug() << "made it";
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    switch (pageMode) {
    case alpha:
        if ((event->buttons() & Qt::LeftButton) && alphabet_scribbling)
        {
            QPoint pos=ui->alphabet_canvas->pos();
            switch (alphaMode) {
            case pen:
                emit drawPen(((event->position().toPoint()) - pos));
                break;
            case eraser:
                emit erase(((event->position().toPoint()) - pos));
                break;
            }
        }

        break;
    case vocab:
        if ((event->buttons() & Qt::LeftButton) && scribbling_vocab == true)
        {
            if (wordSize == 1) {
                QPoint panelPos = layout_vocab->itemAt(0)->widget()->pos(); //panel1
                QPoint scrollAreaPos = ui->scrollArea->pos(); //scrollarea
                QPoint finalPos = panelPos + scrollAreaPos; //final point of label

                QPoint endPoint = event->position().toPoint() - finalPos;

                QPainter painter(&currentImage1);

                switch (mode_vocab)
                {
                    case pen:
                    {
                        //Drawing
                        painter.setPen(QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
                        painter.drawLine(currentPoint, endPoint);
                        currentPoint = endPoint;
                        scribble(currentImage1, 0);
                        update();
                        break;
                    }

                    case eraser:
                    {
                        qDebug() << "made it to eraser";
                        painter.setPen(QPen(Qt::white, 8, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
                        painter.drawLine(currentPoint, endPoint);
                        currentPoint = endPoint;
                        scribble(currentImage1, 0);
                        update();
                        break;
                    }
                }
            } else if (wordSize == 2) {
                if (currentlyOnPanel == 0) {
                    QPoint panelPos = layout_vocab->itemAt(0)->widget()->pos(); //panel1
                    QPoint scrollAreaPos = ui->scrollArea->pos(); //scrollarea
                    QPoint finalPos = panelPos + scrollAreaPos; //final point of label

                    QPoint endPoint = event->position().toPoint() - finalPos;

                    QPainter painter(&currentImage1);

                    switch (mode_vocab)
                    {
                    case pen:
                    {
                        //Drawing
                        painter.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
                        painter.drawLine(currentPoint, endPoint);
                        currentPoint = endPoint;
                        scribble(currentImage1, 0);
                        update();
                        break;
                    }
                    case eraser:
                    {
                        //Drawing
                        painter.setPen(QPen(Qt::white, 8, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
                        painter.drawLine(currentPoint, endPoint);
                        currentPoint = endPoint;
                        scribble(currentImage1, 0);
                        update();
                        break;
                    }
                    }
                } else if (currentlyOnPanel == 1) {
                    QPoint panelPos = layout_vocab->itemAt(1)->widget()->pos(); //panel1
                    QPoint scrollAreaPos = ui->scrollArea->pos(); //scrollarea
                    QPoint finalPos = panelPos + scrollAreaPos; //final point of label

                    QPoint endPoint = event->position().toPoint() - finalPos;

                    QPainter painter(&currentImage2);

                    switch (mode_vocab)
                    {
                    case pen:
                    {
                        //Drawing
                        painter.setPen(QPen(Qt::black, 10, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
                        painter.drawLine(currentPoint, endPoint);
                        currentPoint = endPoint;
                        scribble(currentImage2, 1);
                        update();
                        break;
                    }
                    case eraser:
                    {
                        //Drawing
                        painter.setPen(QPen(Qt::white, 8, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
                        painter.drawLine(currentPoint, endPoint);

                        //Saving the points
                        currentPoint = endPoint;
                        scribble(currentImage2, 1);

                        update();
                        break;
                    }
                    }
                }
            }
        }
        break;
        case game:
        break;
    }
}

void MainWindow::handleStartGame() {
    ui->level_label->setVisible(true);
    ui->display_word->setVisible(true);
    ui->input->setVisible(true);
    ui->start_button->setVisible(false);
    ui->warningLabel->setVisible(false);

    timer.start(1);

}

void MainWindow::draws(QPoint pt, QPoint start, QPoint end) {
    gameImage.fill(QColor(173, 216, 230));
    QPainter painter (&gameImage);
    QPen pen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin);
    painter.setBrush(Qt::black);
    painter.setPen(pen);

    //Draws the slope
    painter.drawLine(start, end);

    QPolygonF polygon;
    polygon << start << end << QPoint(end.x(), gameImage.height()) << QPoint(start.x(), gameImage.height());

    // Draw and fill the polygon with a color (e.g., light blue)
    painter.setBrush(QColor(139, 69, 19)); // Brown color
    painter.drawPolygon(polygon);

    QPixmap image(":/gameImg/car.png"); // Replace ":/path/to/image.png" with the path to your image file
    QPixmap rotatedImage = image.transformed(QTransform().rotate(45));
    painter.drawPixmap(pt, rotatedImage.scaled(100, 100)); // Scale the image to fit the specified size

    //Updates the canvas in the ui
    ui->game_canvas->setPixmap(QPixmap::fromImage(gameImage.scaled(450, 450)));
    update();
}

void MainWindow::handleUserLoses() {
    QImage userLost(":/gameImg/user_lost.png");
    ui->game_canvas->setPixmap(QPixmap::fromImage(userLost));
    timer.stop();
    ui->playAgain_button->setVisible(true);
}

void MainWindow::handleUserWins() {
    QImage userLost(":/gameImg/user_win.png");
    ui->game_canvas->setPixmap(QPixmap::fromImage(userLost));
    timer.stop();
    ui->playAgain_button->setVisible(true);
}

void MainWindow::handleLevelChange(int level) {
    ui->level_label->setText(QString("Level ") + QString::number(level));
}

void MainWindow::handleUserInput() {
    QString userInput = ui->input->toPlainText();
    if (!userInput.isEmpty() && userInput.right(1) == "\n") {
        emit sendInputWord(ui->input->toPlainText());
        ui->input->clear();
    }
}

void MainWindow::handleRestartTimer() {
    timer.start();
}

//Navigation Connections

void MainWindow::on_alphabet_navBtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    pageMode = alpha;
}

void MainWindow::on_alphabet_navBtn2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    pageMode = vocab;

}

void MainWindow::on_alphabet_navBtn3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    pageMode = game;
}


void MainWindow::on_vocabulary_navBtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    pageMode = alpha;
}


void MainWindow::on_vocabulary_navBtn3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    pageMode = game;
}


void MainWindow::on_vocabulary_navBtn2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    pageMode = vocab;
}


void MainWindow::on_game_navBtn1_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    pageMode = alpha;

}


void MainWindow::on_game_navBtn3_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
    pageMode = game;
}


void MainWindow::on_game_navBtn2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    pageMode = vocab;

}

void MainWindow::on_help_btn_vocab_clicked()
{
    help_vocab.setModal(true);
    help_vocab.show();
}

void MainWindow::on_help_btn_alphabet_clicked()
{
    help_alphabet.setModal(true);
    help_alphabet.show();
}

void MainWindow::on_help_btn_game_clicked()
{
    help_game.setModal(true);
    help_game.show();
}



