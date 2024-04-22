#ifndef ALPHABET_H
#define ALPHABET_H

#include<QObject>
#include <QImage>
#include <QVector>
#include<QMouseEvent>
#include<QPoint>
#include<QColor>
#include<QPainter>
#include<QSize>

class Alphabet:public QObject
{
    Q_OBJECT
public:
    explicit Alphabet(QObject *parent = nullptr);
private:
    QImage currentImage;
    int myPenWidth;
    QColor myPenColor;
    QPoint currentPoint;
    QPainter painter;
public slots:

    ///
    /// \brief gets mouse position from view to update the model.
    /// \param pt : Current mouse position.
    ///
    void getPointFromView(QPoint pt);

    ///
    /// \brief gets Qimage from view to update the model.
    /// \param image : Current image the is being displayed.
    ///
    void getImageFromView(QImage image);

    ///
    /// \brief using painter draws a line from the point updated from view to endpoint which is given.
    /// \param endPoint : latest point the line needs to be drawn until.
    ///
    void draw(QPoint endPoint);

    ///
    /// \brief using painter draw a white a line from the point updated from view to endpoint which is given.
    /// \param endPoint : latest point the whiteline needs to be drawn until.
    ///
    void erase(QPoint endPoint);

    ///
    /// \brief sets the entire canvas to white.
    ///
    void cleanCanvas();
signals:

    //sends a Qpoint to view
    void givePointToView(QPoint pt);
    //sends a Qimage to view
    void giveImageToView(QImage image);
    //tells the view to update.
    void update(QPixmap);
};

#endif // ALPHABET_H
