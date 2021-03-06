#include <QtGui>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QFileDialog>
#include <QMessageBox>

#include "gamewidget.h"
#include "gamearea.h"
#include "element.h"

/* Konstruktor der Klasse gameWidget:
 * erstellt Spielfenster, definiert Aufbau, Buttons, deren Methoden
 * und intialisiert Renderbereich für Spielfeld */
gameWidget::gameWidget(QWidget *parent) : QWidget(parent)
{
    /* Definition der Buttons innerhalb des Spiels */

    /* Start-Pause-Button */
    startStopButton = new QPushButton(tr("Start"));
    startStopButton->setFont(QFont("Times", 20, QFont::Bold));
    connect(startStopButton, SIGNAL(clicked()), this, SLOT(startStopGame()));

    /* Speichern-Button*/
    saveButton = new QPushButton(tr("Speichern"));
    saveButton->setFont(QFont("Times", 20, QFont::Bold));
    connect(saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));

    /* Laden-Button */
    loadButton = new QPushButton(tr("Laden"));
    loadButton->setFont(QFont("Times", 20, QFont::Bold));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(loadGame()));

    /* Ende-Button: Anwendung beenden, Widget schließen */
    endButton = new QPushButton(tr("Ende"));
    endButton->setFont(QFont("Times", 20, QFont::Bold));
    connect(endButton, SIGNAL(clicked()), qApp, SLOT(quit()));

    /* Label für Punkteanzeige */
    gamePoints = new QLabel("Punkte");
    gamePoints->setFont(QFont("Helvetica", 16));

    /* Neues Spielfeld auf Basis der Klasse gameArea wird erstellt */
    myGameArea = new gameArea;

    /* Punktelabel werden verknüpft */
    myGameArea->setGamePoints(gamePoints);

    /* Buttons, Punktelabel und Spielfeld werden im Spielfenster (Widget) erstellt */
    QGridLayout *gridLayout = new QGridLayout;
    gridLayout->addWidget(startStopButton, 0, 0);
    gridLayout->addWidget(saveButton, 2, 0);
    gridLayout->addWidget(loadButton, 4, 0);
    gridLayout->addWidget(endButton, 6,0);
    gridLayout->addWidget(gamePoints, 0, 1);
    gridLayout->addWidget(myGameArea, 1, 1, 7, 7);
    setLayout(gridLayout);

}

/* Sorgt dafür, dass sich der Status des Spielfeldes verändert (running true oder false)
 * und verändert den Text auf dem Start-Pause-Button */
void gameWidget::startStopGame(void)
{
    if(myGameArea->getRunning()) {
        //das Spiel ist nicht aktiv
        myGameArea->setRunning(false);
        //der Start-Pause-Button hat die Beschriftung 'Start'
        startStopButton->setText(tr("Start"));

        //Anklicken der Buttons Speichern & Laden möglich,
        //wenn Spiel pausiert ist (muss vom User aktiv über Klick des
        //Start-Pause-Buttons pausiert werden)
        saveButton->setEnabled(true);
        loadButton->setEnabled(true);

    }

    else {
        //das Spiel ist aktiv
        myGameArea->setRunning(true);
        //der Start-Pause-Button hat die Beschriftung 'Pause'
        startStopButton->setText(tr("Pause"));

        //wenn das Spiel läuft, ist speichern & laden nicht möglich
        saveButton->setEnabled(false);
        loadButton->setEnabled(false);

    }
}

/* Methode des Button 'Speichern': Spielstand speichern */
void gameWidget::saveGame(){

    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getSaveFileName(this,
                                      tr("Speichern als"), ".", tr("mySaveGame (*.mysg)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht verwendet werden: ") + fileName,QMessageBox::Ok);
        }

        //rufe die Methode gameArea::serialize(); zum Speichern der Spielinformationen auf
        myGameArea->serialize(file);
        file.close();
        return;
    }
}

/* Methode des Button 'Laden': Gespeicherten Spielstand laden */
void gameWidget::loadGame(void)
{
    QFileDialog dialog(this);
    QString fileName;
    QFile file;

    dialog.setFileMode(QFileDialog::AnyFile);
    fileName = dialog.getOpenFileName(this,
                                      tr("Speichern als"), ".", tr("mySaveGame (*.mysg)"));

    if (fileName.isNull()==false)
    {
        file.setFileName(fileName);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QMessageBox::warning(this, tr("Dateifehler"),
                                 tr("Folgende Datei kann nicht geoeffnet werden: ") + fileName,QMessageBox::Ok);
        }

        //rufe die Methode gameArea::deserialize(); zum Laden der Spielinformationen auf
        myGameArea->deserialize(file);
        file.close();
        return;
    }
}
