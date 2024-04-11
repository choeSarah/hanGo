#include "alphabet.h"

Alphabet::Alphabet(QObject *parent) : QObject(parent)
{
    currentImage = QPixmap(200,200).toImage();
    currentImage.fill(Qt::white);
    myPenWidth = 10;
    myPenColor = Qt::black;
}
void Alphabet::getPointFromView(QPoint pt)
{
    currentPoint=pt;
}

void Alphabet::getImageFromView(QImage image)
{
    currentImage=image;
}
void Alphabet::draw(QPoint endPoint)
{
    QPainter painter(&currentImage);
    painter.setPen(QPen(myPenColor, myPenWidth, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(currentPoint, endPoint);
    currentPoint=endPoint;
    emit givePointToView(currentPoint);
    emit giveImageToView(currentImage);
    emit update(QPixmap::fromImage(currentImage));

}

void Alphabet::erase(QPoint endPoint)
{
    QPainter painter(&currentImage);
    painter.setPen(QPen(Qt::white, myPenWidth, Qt::SolidLine, Qt::RoundCap,Qt::RoundJoin));
    painter.drawLine(currentPoint, endPoint);
    currentPoint=endPoint;
    emit givePointToView(currentPoint);
    emit giveImageToView(currentImage);
    emit update(QPixmap::fromImage(currentImage));
}

void Alphabet::cleanCanvas()
{
    currentImage.fill(Qt::white);
    emit giveImageToView(currentImage);
    emit update(QPixmap::fromImage(currentImage));
}
