#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QString>


class Prism : public QGraphicsPixmapItem{

private:

    int speedX; //Vitesse du prism sur l'axe X
    int speedY; //Vitesse du prism sur l'axe Y

public:

    // Ajout de l'image du prism : image faite sur Photoshop par moi-même.

    Prism(QString imageFileName);


    // Getters and Setters

    int getSpeedX(){return this->speedX;}
    int getSpeedY(){return this->speedY;}
    void setSpeedX(int a){this->speedX = a;}
    void setSpeedY(int a){this->speedY = a;}

    // La fonction qui gere les depalcements du prism

    void action();

};

#endif // RECTANGLE_H
