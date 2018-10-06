# SS18-Semesterarbeit-CPP2-Roland
Semesterarbeit von Kim Roland im BM3-Modul Softwaretechnologie, Seminar "Objektorientierte Programmierung: C++-Programmieren-2"

## Dokumentation
Im Rahmen dieser Semesterarbeit wurden die Stufen IV, III und II der Aufgabenstellung erfolgreich realisiert.

### Projekt herunterladen
- Projekt-Masterversion aus diesem Repository als ZIP-Ordner herunterladen und entpacken
- .pro-Datei des Projektes (*SS18-Semesterarbeit-CPP2-Roland.pro*) mit QT öffnen und konfigurieren
- Ausführen (Kompilieren erfolgreich getestet mit folgenden Programmversionen: Qt 5.9.2 (Clang 7.0 (Apple), 64 bit) und Qt Creator 4.4.1)
- Spielwidget öffnet sich

### Spielfunktionen

#### Spiel starten
Durch Anklicken des **Start**-Buttons in der oben linken Ecke des Spielfensters wird das Spiel gestartet. Der Button wechselt die Beschriftung zu **Pause**. Über erneutes Anklicken des Buttons kann das Spiel also pausiert werden.

#### Spielen
Der Spieler (schraffiertes Rechteck) kann sich mit den Tastatur-Pfeiltasten ⬅️ ➡️ am unteren Rand des Spielfeldes nach links und rechts bewegen und muss den herunterfallenden Elementen (Gegnern) ausweichen. Wird der Spieler von einem Gegnerelement getroffen (die beiden Spielobjekte berühren sich), verliert der Spieler ein Leben (⚪️🔴🔴: Lebensanzeige in der oberen rechten Spielfeldecke) und das Spiel friert kurz ein. Nach dieser kurzen Spielpause startet das Spiel wieder und läuft weiter. Wenn der Spieler getroffen wurde, wird er abgeschwächt dargestellt, je nach Anzahl der noch vorhandenen Leben. Insgesamt gibt es drei verschiedene optische Darstellungen des Spielers (bei vollen Leben, bei Verlust eines Lebens, bei nur noch einem vorhandenen Leben). Außerdem ist der Spieler nach der Kollision mit einem Gegnerelement für ein paar Sekunden unverwundbar (zugunsten des besseren Spielflusses, um eine direkt darauffolgende Kollision mit einem anderen Gegnerelement zu vermeiden). Danach kann er wieder von weiteren Gegnerelementen getroffen werden.
Verlorene Leben können durch die Berührung von herunterfallenden roten Kreis-Elementen 🔴, die optisch dem Aussehen der Lebensanzeige entsprechen, regeneriert werden. Bei der Kollision mit dieser Art von Elementen wird das Spiel ebenfalls kurz eingefroren, aber ein Leben hinzugefügt statt abgezogen. Die maximale Anzahl an Leben entspricht 3, bei voller Lebensanzahl können die Leben nicht weiter addiert werden.

#### Speichern und Laden
Die Buttons **Speichern** und **Laden** ermöglichen es dem Spieler, den aktuellen Spielstand für das Weiterspielen zu einem späteren Zeitpunkt zu speichern oder vor dem Spielstart einen alten gespeicherten Spielstand wieder herzustellen. Um diese Funktionen nutzen zu können, darf das Spiel nicht laufen, sondern muss pausiert sein. 
Im Rahmen der Speicherung lassen sich alle relevanten Spielinformationen speichern: die aktuelle Position des Spielers sowie seine aktuelle optische Darstellung, die Anzahl seiner vorhandenen Leben, die bisher erreichte Punktzahl sowie die Anzahl, Position und der jeweilige Element-Typ (regelt Form, Farbe und Fallgeschwindkeit) der sich momentan im Spielfeld befindenden Gegnerelemente.
Ein alter Spielstand kann sowohl direkt nach dem Start der Spielanwendung als nach dem Pausieren eines bereits gelaufenen Spiels geladen werden. Im Rahmen des Ladens werden die beschriebenen Spielinformationen vollständig wiederhergestellt und der Spieler kann durch Anklicken des **Start**-Buttons nach dem Laden genau mit diesem letzten Spielstand weiterspielen.

#### Spielende
Hat der Spieler alle drei Leben verloren, wird das Spielende durch die Anzeige von "Game Over" und der in dem Spieldurchgang erreichten Punktzahl angezeigt. Danach werden die Spielinformationen zurückgesetzt (optische Spielerdarstellung, Lebensanzahl und Punktzahl), die aktuellen Gegner entfernt/neu erzeugt und das Spiel startet erneut. Alternativ kann die gesamte Spielanwendung auch über den Button **Ende** am unteren linken Spielfeldrand beendet werden.

## Programm-Erläuterungen: Wichtige Klassen und Methoden
1. Die `class gameWidget` erstellt das Spielfenster und definiert dessen Aufbau, die Funktions-Buttons (**Start/Pause**, **Speichern**, **Laden**, **Ende**), deren verknüpfte Methoden und intialisiert den Renderbereich für das Zeichenfeld, in dem das Spiel stattfindet, als `myGameArea` auf Basis der `class gameArea`.
  - `gameWidget::startStopGame()`: regelt aktiven und inaktiven Zustand des Spiels, verändert die Beschriftung des Button, setzt aktiven und inaktiven Zustand der Buttons **Speichern** und **Laden** anhand des Spielstatus.
  - `gameWidget::saveGame()`: löst Erzeugung der Datei für die Speicherung aus, ruft Methode `gameArea::serialize()`auf.
  - `gameWidget::loadGame()`: löst Lesen der Datei für das Laden aus, ruft Methode `gameArea::deserialize()`auf.

2. Die `class player` ist für die Definition des Spielerrechtecks zuständig und beinhaltet die nötigen Methoden zur Erzeugung und Bewegung des Spieleravatars:
  - Setter- und Getter-Methoden für die Positionsfestlegung (`playerX`, `playerY`), Abmessungen (`playerWidth`, `playerHeight`) des Spielers, für die Schrittweite der Spielerbewegung (`playerMove`) sowie für die veränderte optische Darstellung (Farbe und Füllmuster) des Spielers bei Lebensverlust (`playerColor`, `playerPattern`). Für letzteres außerdem Set- und Get-Methode für Verwaltung der veränderten Spielerdarstellung (`playerStyle`), anhand von drei numerischen Werten (0,1,2)
    - `playerStyle==0`: 'gesunde' Darstellung des Spielers bei vollen Leben, schraffiertes Quadrat
    - `playerStyle==1`: abgeschwächte Darstellung des Spielers Stufe 1: mittelblau und gepunktet
    - `playerStyle==2`: abgeschwächte Darstellung des Spielers Stufe 2: sehr helles blau, leerer Rahmen
  - `paintEvent` und `keyPressEvent` zur Zeichnung und Bewegungsfähigkeit des Spielers in der `gameArea`
  - Die `class movement` dient als Hilfsklasse für die `class player`, definiert die Bewegungen des Spielers in einem enum, um sie später in der `player::movePlayer()`-Methode verwenden zu können und initalisiert diese Methode dynamisch, mit dem enum und einem Ausgangswert

3. Die `class element` ist für die Gegnerelemente (enemies) im Spiel zuständig:
  - Die Variable `elementType` übernimmt dabei eine zentrale Rolle, da über sie ein numerischer Wert von 0-5 gespeichert wird, der jeweils für ein bestimmtes Gegenerelement steht. Mit diesen Werten werden die spezifischen Elementeigenschaften verknüpft.
  - Die Methode `element::newElement` sorgt für die zufällige Auswahl neuer Gegnerlemente, indem sie mit `rand()` zufällige X-Positionen und zufällige Werte des `elementType` generiert und mit diesen zufälligen Werten die Methode `element::setElement` aufruft. Außerdem definiert sie, dass das letzte Element der Gegnerliste (der rote Kreis, der Leben wieder hinzufügt) mit zehnprozentiger Wahrscheinlichkeit generiert werden soll.
  - Die Methode `element::setElement` enthält Vektoren zur Speicherung der möglichen Elementeigenschaften in Bezug auf die Größe/Abmessungen, die innere Farbe, die Farbe und Breite der Außenlinie, das Füllmuster und die Fallgeschwindigkeit eines Elements. Die Speicherung in den Vektoren erfolgt nach einer festen Reihenfolge, um Eigenschaften anhand ihrer Position im Vektor einem `elementType` zuordnen zu können. So werden die Elementeigenschaften jeweils in nur einer Hilfsvariable pro Eigenschaft (`rect`,`color`,`pattern`,`pen`,`penWidth`,`yMovement`) gespeichert, die veränderbar sind und anhand des (zufälligen) `elementType` bei der Erzeugung eines Elements festgelegt werden.
  - Die Methode `element::moveElement` erzeugt das Fallen der Gegnerelemente, also ihre Bewegung im Spielfeld von oben nach unten, über den Aufruf der `translate()`-Methode der Klasse `QRectF` mit dem elementspezifischen Vektorenwert `yMovement`.

4. Die `class gameArea` definiert das Zeichenfeld des Spiels, in dem sich der Spieler und die Gegnerelemente bewegen. Sie ist zuständig für: den Spiel-Timer und die Punkteanzeige, die Aktualisierung, das Pausieren und das Ende des Spiels, für das Zeichnen der Gegner und der Leben, für die Kollisionsabfrage von Spieler und Gegnern sowie für das Auslösen der veränderten Darstellung des Spielers bei seiner Kollision mit einem Gegnerelement. Kurz gesagt regelt die Klasse alles, was innerhalb des Spiels passiert.
  - Im Konstruktor der `gameArea` wird das Spiel mit seinem Anfangszustand initalisiert. Auf Basis der Positions- und Layout-Definitionen der `class player` wird das Spielerrechteck im Zeichenfeld erzeugt. Die Methode `gameArea::setRunning` sowie ihre `bool`-Variable `running` werden auf `false` gesetzt, damit sich das Spielfenster im inaktiven Zustand des Spiels öffnet. Desweiteren werden die Spielpunkte, die Leben und die für die verschiedenen Pause- und Endzustände `unverwundbar`, `getroffen` und `gameOver` zuständigen Variablen und Timer mit Ausgangswerten initialisiert. Außerdem wird hier der Spieltimer hinzugefügt und definiert sowie der Vektor `std::vector<element*> enemies`, über den die Gegnerelemente hinzugefügt werden, mit neuen zufälligen Elementen befüllt.
  - Die Methode `gameArea::updateGame` regelt die Aktualisierung der Spielzustände und des Punktecounters. Sie wurde im Konstruktor mit dem Timer verknüpft. In ihr ist festgelegt, was während der verschiedenen Spielphasen geschehen soll. Während das Spiel läuft, soll die Punktzahl konstant erhöht werden. Außerdem werden hier die Zeitintervalle nach der Kollision mit einem Gegner und für die temporäre GameOver-Anzeige gestartet. Diese seperaten Zustands-Timer werden solange erhöht, bis sie den Wert des zugehörigen Timeouts (in `gameArea.h` konstant festgelegt) erreicht haben. Es wird definiert, was nach dem Timeout geschehen soll: 
    - Wenn der Spieler getroffen wurde, soll der Timer für das Timeout des `getroffen`-Zustandes gestartet werden, der Spieler `unverwundbar` gemacht (und damit auch der unverwundbar-Timer gestartet werden). Nach Ende des Timeouts wird das Spiel wieder in den aktiven Zustand versetzt, läuft also weiter. 
    - Wenn der Spieler `unverwundbar` ist, soll ebenfalls ein Timer für die Zeit der Unverwundbarkeit gestartet werden. So wird verhindert, dass der Spieler nicht direkt nach Ende des `getroffen`-Timeouts mit dem nächsten, eventuell direkt über ihm liegenden, aber eingefrorenen Gegner kollidiert, ohne die Chance zu haben, auszuweichen. Nach Ende des `unverwundbar`-Zustands kann der Spieler wieder von Gegnern getroffen werden. 
    - `gameOver`

  - Die Methode `gameArea::drawLives()`
  - Die Methode `gameArea::changePlayerStyle()`
  - Die Methode `gameArea::drawEnemies()`
  - Das `paintEvent` der `gameArea` löst die `drawLives()`- und `drawEnemies()`-Methoden aus. 
  - Die Methode `gameArea::gameIsOver()`
  - Die Methode `gameArea::setRunning()`
  - Die Methode `gameArea::serialize()`
  - Die Methode `gameArea::deserialize()`

