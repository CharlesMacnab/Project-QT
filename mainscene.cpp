#include "mainscene.h"
#include <QKeyEvent>
#include <QMediaPlayer>
#include <QDebug>
#include <QUrl>
#include <QFileSystemModel>
#include <QFontDatabase>



MainScene::MainScene()
{


    // Creation des elements de decors

    this->music->setMedia(QUrl("feels3.mp3")); // Tous droits reserve a Calvin Harris : remix de la chanson "feels"
    this->background.load("CharlesRetro3.png"); // Image de fond faites sur Photoshop avec l'aide d'un ami : tous droits reserve a moi et mon ami
    prism = new Prism("personnage.png"); // Image du prism faites sur Photoshop : tous droits reserve a moi
    int loadedFontID = QFontDatabase::addApplicationFont ( "Retro Gaming.ttf" ); // j'ai telecharge la police sur un site tous droist reserve : https://www.dafont.com
    creationDeLimites();


    // Mise en place des elements de decors

    this->music->setVolume(50);
    this->music->play();
    this->setSceneRect(0, 0, background.width(), background.height());
    prism->setPos(0,670);
    this->addItem(prism);

    menu();

    // Mise en place des timers

    this->timer->start(30); // Timer pour la fonction de rafraichissement
    this->timer2 = new QTimer(this); // Timer pour la creation de gravite
    this->timer3->start(); // Chronometre

    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(gravity()));


}


void MainScene::printWin()
{
    this->music->stop();

    // Appel d'une musique de "victoire"

    this->victory->setMedia(QUrl("victory.mp3")); // Tous droits au film Rocky III, j'ai accéléré la musique et changé le ton.
    this->victory->play();


    // Si la partie recommence on creer une nouvelle victoire

    compteur2++;
    if (compteur2 > 1){
          win->setVisible(true);
    }


    // Recuperation du chrono finale

    this->milliesecondes = this->timer3->elapsed();
    this->timer->stop();


    // Creation de la texture da la vignette interactive (police et couleurs)

    QFont test("Retro Gaming", 80, QFont::Normal);
    win->setStyleSheet("background-color: black");
    win->setFont(test);
    QPalette palette = win->palette();
    palette.setColor(win->backgroundRole(), Qt::yellow);
    palette.setColor(win->foregroundRole(), Qt::yellow);
    win->setPalette(palette);


    // Creation du texte

    win->setText("YOU WIN!\n\nYour time is "+getTime()+" seconds\n\nClick to start again");


    // Modifications des parametres par default de la vignette interactive

    win->resize(1600,900);
    win->move(prism->x()-1500,prism->y()-405);
    this->addWidget(win);
    connect(win, SIGNAL(clicked()), this, SLOT(startAgain2()));
}

void MainScene::gameOver()
{
    // Arret des timers

    this->timer->stop();
    this->music->stop();

    // Appel de la vignette d'ineractivite

    printLoose();
}

void MainScene::printLoose()
{

    // Appel d'une musique de "mort"

    this->death->setMedia(QUrl("oof.mp3")); // Son gratuit, tous droits libre sur https://www.myinstants.com/categories/sound%20effects/
    this->death->play();


    // Si la partie recommence on creer une nouvelle defaite

    compteur ++;
    if (compteur > 1){
          loose->setVisible(true);
    }


    // Creation de la texture da la vignette interactive (police et couleurs)

    QFont test("Retro Gaming", 80, QFont::Normal);
    loose->setStyleSheet("background-color: black");
    loose->setFont(test);
    QPalette palette = loose->palette();
    palette.setColor(loose->backgroundRole(), Qt::red);
    palette.setColor(loose->foregroundRole(), Qt::red);
    loose->setPalette(palette);


    // Creation du texte

    loose->setText("Game over\n\nClick to try again");


    // Modifications des parametres par default de la vignette interactive

    loose->resize(1600,900);
    loose->move(prism->x()-750,prism->y()-750);
    this->addWidget(loose);
    connect(loose, SIGNAL(clicked()), this, SLOT(startAgain()));
}

void MainScene::startAgain()
{
    loose->setVisible(false);
    prism->setPos(0,670);
    prism->setSpeedY(10);
    this->timer->start(30);
    this->timer3->restart();
    this->music->setMedia(QUrl("feels3.mp3"));
    this->music->play();
}

void MainScene::startAgain2()
{
    this->music->stop();
    this->victory->stop();
    win->setVisible(false);
    prism->setPos(0,670);
    prism->setSpeedY(10);
    this->timer->start(30);
    this->timer3->restart();
    this->music->setMedia(QUrl("feels3.mp3"));
    this->music->play();
}

void MainScene::keyPressEvent(QKeyEvent *event)
{

    if (event->key() == Qt::Key_Left){
        prism->setSpeedX(-13);
    }
    if (event->key() ==  Qt::Key_Right){
        prism->setSpeedX(13);
    }
    if (event->key() ==  Qt::Key_Up && jump==true){

        prism->setSpeedY(-20);
        this->timer2->start(300);
    }

}

void MainScene::keyReleaseEvent(QKeyEvent *event){
    if (event->key() == Qt::Key_Left){
        prism->setSpeedX(0);
    }
    if (event->key() ==  Qt::Key_Right){
        prism->setSpeedX(0);
    }
    if (event->key() ==  Qt::Key_Up){
        jump=false;
    }
}

void MainScene::gravity()
{
    prism->setSpeedY(10);
}

void MainScene::collision()
{
    //Borders

    //haut
    if (prism->collidesWithItem(this->InvisibleBorder[0])){
        prism->setPos(prism->x(),0);
    }

    //bas
    if (prism->collidesWithItem(this->InvisibleBorder[1])){
        prism->setPos(prism->x(),background.height()-100);

    }

    //left
    if (prism->collidesWithItem(this->InvisibleBorder[2])){
        prism->setPos(0,prism->y());

    }

    //right
    if (prism->collidesWithItem(this->InvisibleBorder[3])){
        prism->setPos(background.width()-100,prism->y());

    }

    //Platforme

    for (int var = 0; var < 11; var++) {
        if (prism->collidesWithItem(this->VisibleBorder[var])){
            if(var%2 == 0){
                jump = true;
                prism->setPos(prism->x(),670);
            }

            else{
                prism->setPos(prism->x(),750);
                gameOver();
            }
        }

    }



    // Plateforme Small Cube

    for (int var = 11; var < 17; var++) {
        if (prism->collidesWithItem(this->VisibleBorder[var])){
            jump = true;
            prism->setPos(prism->x(),600);
        }
    }


    // Plateforme Big Cube

    for (int var = 17; var < 20; var++) {
        if (prism->collidesWithItem(this->VisibleBorder[var])){
            jump = true;
            prism->setPos(prism->x(),505);

        }
    }


    // Plateforme Spikes

    for (int var = 20; var < 24; var++) {
        if (prism->collidesWithItem(this->VisibleBorder[var])){
            prism->setPos(prism->x(),750);
            gameOver();

        }
    }

    // Flying Plateforme

    for (int var = 24; var < 26; var++) {
        if (prism->collidesWithItem(this->VisibleBorder[var])){
            prism->setPos(prism->x(),750);
            gameOver();

        }
    }


    // 1st Small Cube

    if (prism->collidesWithItem(this->VisibleBorder[28])){
        prism->setPos(772,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[29])){
        prism->setPos(970,prism->y());
    }



    // 1st Big Cube

    if (prism->collidesWithItem(this->VisibleBorder[30])){
        prism->setPos(1382,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[31])){
        prism->setPos(1580,prism->y());
    }


    // 1st Spike

    if (prism->collidesWithItem(this->VisibleBorder[26])){
        prism->setPos(prism->x(),750);
        gameOver();
    }

    // 2nd Spike

    if (prism->collidesWithItem(this->VisibleBorder[27])){
        prism->setPos(prism->x(),750);
        gameOver();
    }

    //2nd Small Cube
    if (prism->collidesWithItem(this->VisibleBorder[32])){
        prism->setPos(2250,prism->y());
    }


    //3rd Small Cube
    if (prism->collidesWithItem(this->VisibleBorder[33])){
        prism->setPos(2360,prism->y());
    }

    // 3rd Spike
    if (prism->collidesWithItem(this->VisibleBorder[34])){
        prism->setPos(prism->x(),750);
        gameOver();
    }

    //4th Small Cube
    if (prism->collidesWithItem(this->VisibleBorder[35])){
        prism->setPos(4315,prism->y());
    }


    // 2nd Big Cube

    if (prism->collidesWithItem(this->VisibleBorder[36])){
        prism->setPos(5155,prism->y());
    }

    // 1st Huge Cube
    if (prism->collidesWithItem(this->VisibleBorder[37])){
        prism->setPos(5255,prism->y());

    }

    // Other traps
    if (prism->collidesWithItem(this->VisibleBorder[38])){
        jump = true;
        prism->setPos(prism->x(),405);
    }

    if (prism->collidesWithItem(this->VisibleBorder[39])){
        prism->setPos(7960,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[40])){
        prism->setPos(8055,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[41])){
        prism->setPos(8155,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[42])){
        jump = true;
        prism->setPos(prism->x(),405);
    }

    if (prism->collidesWithItem(this->VisibleBorder[43])){
        prism->setPos(8425,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[44])){
        prism->setPos(prism->x(),405);
        jump = true;
    }

    if (prism->collidesWithItem(this->VisibleBorder[45])){
        prism->setPos(8725,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[46])){
        jump = true;
        prism->setPos(prism->x(),505);
    }

    if (prism->collidesWithItem(this->VisibleBorder[47])){
        prism->setPos(9065,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[48])){
        jump = true;
        prism->setPos(prism->x(),405);
    }

    if (prism->collidesWithItem(this->VisibleBorder[50])){
        prism->setPos(prism->x(),600);
        jump = true;
    }

    if (prism->collidesWithItem(this->VisibleBorder[51])){
        prism->setPos(prism->x(),505);
        jump = true;
    }

    if (prism->collidesWithItem(this->VisibleBorder[52])){
        prism->setPos(10900,405);
        printWin();
    }

    if (prism->collidesWithItem(this->VisibleBorder[53])){
        prism->setPos(10600,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[54])){
        prism->setPos(10700,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[55])){
        prism->setPos(10800,prism->y());
    }

    if (prism->collidesWithItem(this->VisibleBorder[56])){
        prism->setPos(8355,prism->y());
        jump = true;
    }

    if (prism->collidesWithItem(this->VisibleBorder[57])){
        prism->setPos(5460,prism->y());
        jump = true;
    }

}

void MainScene::menu()
{
    // Creation de la texture da la vignette interactive (police et couleurs)

    QFont font("Retro Gaming", 80, QFont::Normal);
    menuButton->setStyleSheet("background-color: black");
    menuButton->setFont(font);
    QPalette palette = menuButton->palette();
    palette.setColor(menuButton->backgroundRole(), Qt::darkMagenta);
    palette.setColor(menuButton->foregroundRole(), Qt::darkMagenta);
    menuButton->setPalette(palette);


    // Creation du texte

    menuButton->setText("Prism\n\nClick to play");


    // Modification des valeurs par default de la vignette

    menuButton->resize(1600,900);
    menuButton->move(prism->x(),prism->y()-670);
    this->addWidget(menuButton);
    connect(menuButton, SIGNAL(clicked()), this, SLOT(invisible()));
}

void MainScene::creationDeLimites()
{
    for(int i =0 ; i<4; i++){
        this->InvisibleBorder.push_back(new QGraphicsLineItem());
    }
    //Bordures limites

    //haut
    this->InvisibleBorder[0]->setLine(0,0,background.width(),0);
    //bas
    this->InvisibleBorder[1]->setLine(0,background.height(),background.width(),background.height());
    //gauche
    this->InvisibleBorder[2]->setLine(0,0,0,background.height());
    //droite
    this->InvisibleBorder[3]->setLine(background.width(),0,background.width(),background.height());


    //Obstacles
    for(int i =0 ; i<58; i++){
        this->VisibleBorder.push_back(new QGraphicsLineItem());
    }


    //Plateformes / Trous noirs

    this->VisibleBorder[0]->setLine(0,770,2985,770);

    this->VisibleBorder[1]->setLine(2990,770,3190,770);

    this->VisibleBorder[2]->setLine(3195,770,4440,770);

    this->VisibleBorder[3]->setLine(4445,770,4645,770);

    this->VisibleBorder[4]->setLine(4655,770,4755,770);

    this->VisibleBorder[5]->setLine(4760,770,4960,770);

    this->VisibleBorder[6]->setLine(4970,770,7700,770);

    this->VisibleBorder[7]->setLine(7710,770,7910,770);

    this->VisibleBorder[8]->setLine(7920,770,8465,770);

    this->VisibleBorder[9]->setLine(8475,770,9310,770);

    this->VisibleBorder[10]->setLine(9315,770,11000,770);


    // Plateforme Petit Cube

    this->VisibleBorder[11]->setLine(860,700,960,700);

    this->VisibleBorder[12]->setLine(2045,700,2145,700);

    this->VisibleBorder[13]->setLine(2460,700,2560,700);

    this->VisibleBorder[14]->setLine(4115,700,4215,700);

    this->VisibleBorder[15]->setLine(5155,700,5255,700);

    this->VisibleBorder[16]->setLine(8060,700,8160,700);


    //Plateforme Moyen Cube

    this->VisibleBorder[17]->setLine(1470,605,1570,605);

    this->VisibleBorder[18]->setLine(5255,605,5355,605);

    this->VisibleBorder[19]->setLine(8155,605,8255,605);


    // Plateforme pieges

    this->VisibleBorder[20]->setLine(1955,700,2040,700);

    this->VisibleBorder[20]->setLine(2565,700,2670,700);

    this->VisibleBorder[22]->setLine(4030,700,4110,700);

    this->VisibleBorder[23]->setLine(6475,700,6660,700);


    // Plateformes volantes

    this->VisibleBorder[24]->setLine(3430,670,3630,670);

    this->VisibleBorder[25]->setLine(6970,670,7365,670);



    // Bordures des obstacles

    this->VisibleBorder[26]->setLine(1955,700,1955,795);

    this->VisibleBorder[27]->setLine(2670,700,2670,795);

    this->VisibleBorder[28]->setLine(860,700,860,795);

    this->VisibleBorder[29]->setLine(960,700,960,795);

    this->VisibleBorder[30]->setLine(1470,605,1470,795);

    this->VisibleBorder[31]->setLine(1570,605,1570,795);

    this->VisibleBorder[32]->setLine(2145,700,2145,795);

    this->VisibleBorder[33]->setLine(2460,700,2460,795);

    this->VisibleBorder[34]->setLine(4030,700,4030,795);

    this->VisibleBorder[35]->setLine(4215,700,4215,795);

    this->VisibleBorder[36]->setLine(5255,605,5255,795);

    this->VisibleBorder[37]->setLine(5355,505,5355,795);

    this->VisibleBorder[38]->setLine(5355,505,5455,505);

    this->VisibleBorder[39]->setLine(8060,700,8060,795);

    this->VisibleBorder[40]->setLine(8155,605,8155,795);

    this->VisibleBorder[41]->setLine(8255,505,8255,795);

    this->VisibleBorder[42]->setLine(8255,505,8355,505);

    this->VisibleBorder[43]->setLine(8525,505,8525,605);

    this->VisibleBorder[44]->setLine(8525,505,8625,505);

    this->VisibleBorder[45]->setLine(8825,605,8825,700);

    this->VisibleBorder[46]->setLine(8825,605,8925,605);

    this->VisibleBorder[47]->setLine(9165,505,9165,605);

    this->VisibleBorder[48]->setLine(9165,505,9265,505);

    this->VisibleBorder[50]->setLine(10700,700,10800,700);

    this->VisibleBorder[53]->setLine(10700,700,10700,795);

    this->VisibleBorder[54]->setLine(10800,605,10800,795);

    this->VisibleBorder[51]->setLine(10800,605,10900,605);

    this->VisibleBorder[52]->setLine(10900,505,11000,505);

    this->VisibleBorder[55]->setLine(10900,505,10900,795);

    this->VisibleBorder[56]->setLine(8355,505,8355,795);

    this->VisibleBorder[57]->setLine(5460,505,5460,795);

}

void MainScene::drawBackground(QPainter *painter, const QRectF &rect) {

    // Inspirer de la fonction drawBackground du jeu que vous nous avez donné

    Q_UNUSED(rect);
    painter->drawPixmap(QRectF(0,0,background.width(), background.height()), background, sceneRect());
}

void MainScene::update() {

    // Inspirer de la fonction update du jeu que vous nous avez donné

    prism->action();
    collision();
    QGraphicsView * view = this->views().at(0);
    view->centerOn(prism);

}

void MainScene::invisible()
{
    menuButton->setVisible(false);
}
