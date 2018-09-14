#include <QtGui>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>
#include "gamewidget.h"

/* Erstelle gameWidget (Spielfenster) und gameArea (Spielfeld) */
gameWidget::gameWidget(QWidget *parent) : QWidget(parent)
{
    /* Definition der Buttons innerhalb des Spiels */
    /* Start-Pause-Button */
    startstop = new QPushButton(tr("Start"));
    startstop->setFont(QFont("Times", 20, QFont::Bold));
    connect(startstop, SIGNAL(clicked()), this, SLOT(startStop()));

    /* Speichern-Button*/
    QPushButton *saveGame = new QPushButton(tr("Speichern"));
    saveGame->setFont(QFont("Times", 20, QFont::Bold));
    connect(saveGame, SIGNAL(clicked()), this, SLOT(saveGame()));

    /* Laden-Button */
    QPushButton *loadGame = new QPushButton(tr("Laden"));
    loadGame->setFont(QFont("Times", 20, QFont::Bold));
    connect(loadGame, SIGNAL(clicked()), this, SLOT(loadGame()));

    /* Label für Punkteanzeige */
    QLabel *pointCounter = new QLabel("Punkte");
    pointCounter->setFont(QFont("Times", 16));

    /* Neues Spielfeld wird erstellt */
    mygameArea = new gameArea;
    mygameArea->setFixedSize(700, 500);


    /* Buttons, Punktelabel und Spielfeld werden im Spielfenster (Widget) erstellt */
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(startstop, 0, 0);
    gridLayout->addWidget(saveGame, 2, 0);
    gridLayout->addWidget(loadGame, 4, 0);
    gridLayout->addWidget(pointCounter, 0, 3);
    gridLayout->addWidget(mygameArea, 1, 1, 7, 7);
    setLayout(gridLayout);

}


/* Sorgt dafür, dass sich der Status des Spielfeldes verändert (running true oder false)
 * und verändert den Text auf dem Start-Pause-Button */
void gameWidget::startStop(void)
{
    if(mygameArea->getRunning()) {
        mygameArea->setRunning(false);
        startstop->setText(tr("Start"));
    }else{
        mygameArea->setRunning(true);
        startstop->setText(tr("Pause"));
    }
 }


/* Spielstand speichern */
void gameWidget::saveGame(){

    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,
                                      tr("Speichern als"), ".", tr("mySavedGame (*.mysg)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        }

        mygameArea->serialize(file);
        file.close();
        return;
    }
}

/* Alten Spielstand laden */
void gameWidget::loadGame(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this,
                                      tr("Speichern als"), ".", tr("mySavedGame (*.mysg)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht geoeffnet werden: ") + fileName,QMessageBox::Ok);
        }

        mygameArea->deserialize(file);
        file.close();
        return;
    }
}
