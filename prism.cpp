#include "prism.h"
#include <QString>

Prism::Prism(QString imageFileName) : QGraphicsPixmapItem(QPixmap(imageFileName))
{
    //Les vitesses du prism par default en X et Y

    this->setSpeedX(0);
    this->setSpeedY(10);
}

void Prism::action()
{
    QPointF pos = this->pos();

    int newX = pos.x() + this->speedX;
    int newY = pos.y() + this->speedY;

    this->setPos(newX, newY);
}
