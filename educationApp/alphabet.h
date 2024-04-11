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
    void getPointFromView(QPoint pt);
    void getImageFromView(QImage image);
    void draw(QPoint endPoint);
    void erase(QPoint endPoint);
    void cleanCanvas();
signals:
    void givePointToView(QPoint pt);
    void giveImageToView(QImage image);
    void update(QPixmap);
};

#endif // ALPHABET_H
