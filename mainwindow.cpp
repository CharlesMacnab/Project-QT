#include "mainwindow.h"

Window::Window()
{
    // Paramtetres de la Window
    this->setWindowTitle("ChickyGame");
    this->setFixedSize(1600,900);


    // Paramtetres de la view
    QGraphicsView* view = new QGraphicsView();

    view->setScene(mainScene);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Centrer la view dans la window
    this->setCentralWidget(view);






}
