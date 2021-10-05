#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QTimer>
#include <QString>
#include <QElapsedTimer>
#include <QString>

#include <QPixmap>
#include <QPainter>
#include <QPen>
#include <QRectF>
#include <QMediaPlayer>

#include <QPushButton>


#include "prism.h"


class MainScene : public QGraphicsScene
{
    Q_OBJECT

private:

    // Fichiers audios

    QMediaPlayer* music = new QMediaPlayer();
    QMediaPlayer* death = new QMediaPlayer();
    QMediaPlayer* victory = new QMediaPlayer();


    // Vignettes d'interactivite

    QPushButton* win = new QPushButton;
    QPushButton* loose = new QPushButton;
    QPushButton* menuButton = new QPushButton;


    // Creation de vectors pour les obstacles et bordures limites

    QVector <QGraphicsLineItem*> InvisibleBorder;
    QVector <QGraphicsLineItem*> VisibleBorder;


    // Compteurs

    int compteur =0;
    int compteur2 =0;


    // Creation du fond d'image du jeu

    QPixmap background;


    // Appel du prism

    Prism* prism;


    // Timers

    QTimer* timer = new QTimer();
    QTimer* timer2;
    QElapsedTimer* timer3 = new QElapsedTimer();


    float milliesecondes;
    bool jump = false;


public:

    MainScene();
    bool test(bool jump);
    void startTimer();
    //Fonction pour recuperer les actions du clavier

    void keyPressEvent (QKeyEvent * event);
    void keyReleaseEvent (QKeyEvent * event);


    // Fonctions de limites invisibles et visibles
    void creationDeLimites();
    void collision();


    // Creation du background
    void drawBackground(QPainter* painter, const QRectF& prism);


    // Fonctions de vignettes d'interactivite

    void menu();
    void printWin();
    void gameOver();
    void printLoose();


    // Getters

    Prism* getRect(){return prism;};
    QString getTime(){this->milliesecondes = this->milliesecondes/1000; QString s = QString::number(this->milliesecondes); return s;}


public slots :

    void update();
    void invisible();
    void startAgain();
    void startAgain2();
    void gravity();

};

#endif // MAINSCENE_H
