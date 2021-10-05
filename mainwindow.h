#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>



#include "mainscene.h"

class Window : public QMainWindow{

    Q_OBJECT

private:
   MainScene* mainScene =  new MainScene();

public:
   Window();
};


#endif // MAINWINDOW_H
