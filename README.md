# SS18-Semesterarbeit-CPP2-Roland
Semesterarbeit von Kim Roland im BM3-Modul Softwaretechnologie, Seminar "Objektorientierte Programmierung: C++-Programmieren-2"

# Dokumentation
Im Rahmen dieser Semesterarbeit wurden die Stufen I, II und III der Aufgabenstellung erfolgreich realisiert.

### Projekt herunterladen
- Projekt-Masterversion aus diesem Repository als ZIP-Ordner herunterladen und entpacken
- .pro-Datei des Projektes (*SS18-Semesterarbeit-CPP2-Roland.pro*) mit QT öffnen und konfigurieren
- Ausführen (Kompilieren erfolgreich getestet mit folgenden Programmversionen: *Qt 5.9.2 (Clang 7.0 (Apple), 64 bit)* und *Qt Creator 4.4.1*)
- Spielwidget öffnet sich

### Spielfunktionen

#### Spiel starten
Durch Anklicken des **Start**-Buttons in der oben linken Ecke des Spielfensters wird das Spiel gestartet. Der Button wechselt die Beschriftung zu **Pause**. Über erneutes Anklicken des Buttons kann das Spiel pausiert werden.

#### Spielen
Der Spieler (schraffiertes Rechteck) kann sich mit den Tastatur-Pfeiltasten ⬅️ ➡️ am unteren Rand des Spielfeldes nach links und rechts bewegen und muss den herunterfallenden Elementen (Gegnern) ausweichen. Wird der Spieler von einem Gegnerelement getroffen (die beiden Spielobjekte berühren sich), verliert der Spieler ein Leben (⚪️🔴🔴: Lebensanzeige in der oberen rechten Spielfeldecke) und das Spiel friert kurz ein. Nach dieser kurzen Spielpause startet das Spiel wieder und läuft weiter. Wenn der Spieler getroffen wurde, wird er abgeschwächt dargestellt, je nach Anzahl der noch vorhandenen Leben. Insgesamt gibt es drei verschiedene optische Darstellungen des Spielers (bei vollen Leben, bei Verlust eines Lebens, bei nur noch einem vorhandenen Leben). Außerdem ist der Spieler nach der Kollision mit einem Gegnerelement für ein paar Sekunden unverwundbar (zugunsten des besseren Spielflusses, um eine direkt darauffolgende Kollision mit einem anderen Gegnerelement zu vermeiden). Danach kann er wieder von weiteren Gegnerelementen getroffen werden.
Verlorene Leben können durch die Berührung von herunterfallenden roten Kreis-Elementen 🔴, die optisch dem Aussehen der Lebensanzeige entsprechen, regeneriert werden. Bei der Kollision mit dieser Art von Elementen wird das Spiel ebenfalls kurz eingefroren, aber ein Leben hinzugefügt statt abgezogen. Die maximale Anzahl an Leben entspricht 3, bei voller Lebensanzahl können die Leben nicht weiter addiert werden.

#### Speichern und Laden
Die Buttons **Speichern** und **Laden** ermöglichen es dem Spieler, den aktuellen Spielstand für das Weiterspielen zu einem späteren Zeitpunkt zu speichern oder einen alten gespeicherten Spielstand wiederherzustellen. Um diese Funktionen nutzen zu können, darf das Spiel nicht laufen, sondern muss pausiert sein. 
Im Rahmen der Speicherung lassen sich alle relevanten Spielinformationen speichern: die aktuelle Position des Spielers sowie seine aktuelle optische Darstellung, die Anzahl seiner vorhandenen Leben, die bisher erreichte Punktzahl sowie die Position und der jeweilige Element-Typ (Form, Farbe und Fallgeschwindkeit) der sich momentan im Spielfeld befindenden Gegnerelemente.
Ein alter Spielstand kann sowohl direkt nach dem Start der Spielanwendung als auch nach dem Pausieren eines bereits gelaufenen Spiels geladen werden. Im Rahmen des Ladens werden die beschriebenen Spielinformationen vollständig wiederhergestellt und der Spieler kann durch Anklicken des **Start**-Buttons mit dem geladenen Spielstand weiterspielen.

#### Spielende
Hat der Spieler alle drei Leben verloren, wird das Spielende durch die Anzeige von "Game Over" und der in dem Spieldurchgang erreichten Punktzahl angezeigt. Die Spielinformationen werden zurückgesetzt (optische Spielerdarstellung, Lebensanzahl und Punktzahl), die aktuellen Gegner entfernt/neu erzeugt und das Spiel startet erneut. Alternativ kann die gesamte Spielanwendung auch über den Button **Ende** am unteren linken Spielfeldrand beendet werden.

## Programm-Erläuterungen: Wichtige Klassen und Methoden
1. Die `class gameWidget` erstellt das Spielfenster und definiert dessen Aufbau, die Funktions-Buttons (**Start/Pause**, **Speichern**, **Laden**, **Ende**), deren verknüpfte Methoden und intialisiert den Renderbereich für das Zeichenfeld, in dem das Spiel stattfindet, als `myGameArea` auf Basis der `class gameArea`.
    - `gameWidget::startStopGame()`: regelt aktiven und inaktiven Zustand des Spiels, verändert die Beschriftung des **Start**/**Pause**-Button, setzt aktiven und inaktiven Zustand der Buttons **Speichern** und **Laden** anhand des Spielstatus.
    - `gameWidget::saveGame()`: löst Erzeugung der Datei für die Speicherung aus, ruft Methode `gameArea::serialize()`auf.
    - `gameWidget::loadGame()`: löst Lesen der Datei für das Laden aus, ruft Methode `gameArea::deserialize()`auf.

2. Die `class player` ist für die Definition des Spielerrechtecks zuständig und beinhaltet die nötigen Methoden zur Erzeugung und Bewegung des Spieleravatars:
    - Setter- und Getter-Methoden für die Positionsfestlegung (`playerX`, `playerY`) und Abmessungen (`playerWidth`, `playerHeight`) des Spielers, für die Schrittweite der Spielerbewegung (`playerMove`) sowie für die veränderte optische Darstellung (Farbe und Füllmuster) des Spielers bei Lebensverlust (`playerColor`, `playerPattern`). Für letzteres enthält die Klasse außerdem eine Set- und Get-Methode zur Verwaltung der veränderten Spielerdarstellung (`playerStyle`), anhand von drei numerischen Werten (0,1,2)
      - `playerStyle==0`: 'gesunde' Darstellung des Spielers bei vollen Leben, vollblaues schraffiertes Quadrat
      - `playerStyle==1`: abgeschwächte Darstellung des Spielers Stufe 1: mittelblau und gepunktet
      - `playerStyle==2`: abgeschwächte Darstellung des Spielers Stufe 2: helles Blau, leerer Rahmen
    - `paintEvent` und `keyPressEvent` zur Zeichnung und Bewegungsfähigkeit des Spielers in der `gameArea`
    - Die `class movement` dient als Hilfsklasse für die `class player`, verwaltet die Bewegungen des Spielers über ein enum, um dieses in der `player::movePlayer()`-Methode verwenden zu können und initalisiert die Methode dynamisch mit dem enum und einem Ausgangswert

3. Die `class element` ist für die Definition und Erzeugung der Gegnerelemente (*enemies*) im Spiel zuständig:
    - Die Variable `elementType` übernimmt dabei eine zentrale Rolle, da über sie ein numerischer Wert von 0-5 gespeichert wird, der jeweils für ein bestimmtes Gegnerelement steht. Mit diesem Wert wird die Definition der spezifischen Elementeigenschaften in der Methode `element::setElement()` verknüpft.
    - Die Methode `element::newElement()` sorgt für die zufällige Auswahl neuer Gegnerlemente, indem sie mit `rand()` zufällige X-Positionen und zufällige Werte des `elementType` generiert und mit diesen zufälligen Werten die Methode `element::setElement()` aufruft. Außerdem definiert sie, dass das letzte Element der Gegnerliste (der rote Kreis, der Leben wieder hinzufügt) mit zehnprozentiger Wahrscheinlichkeit im Spiel auftreten werden soll. Die anderen neunzig Prozent des Gegneraufkommens werden zufällig aus den 5 anderen Elementen zusammengestellt.
    - Die Methode `element::setElement()` enthält Vektoren zur Speicherung der spezifischen Elementeigenschaften in Bezug auf die Größe/Abmessungen, die innere Farbe, die Farbe und Breite der Außenlinie, das Füllmuster und die Fallgeschwindigkeit eines Elements. Die Speicherung in den Vektoren erfolgt nach einer festen Reihenfolge, um Eigenschaften anhand ihrer Position im Vektor (ebenfalls 0-5) mit dem `elementType` zu verknüpfen. Die Elementeigenschaften werden jeweils in einer Hilfsvariable pro Eigenschaft (`rect`,`color`,`pattern`,`pen`,`penWidth`,`yMovement`) gespeichert. Diese werden dynamisch verwendet und anhand des `elementType` verändert. Die Gegnerelemente des Spiels basieren alle auf der Klasse `QRectF`.
    - Die Methode `element::moveElement()` erzeugt das Fallen der Gegnerelemente, also ihre Bewegung im Spielfeld von oben nach unten, über den Aufruf der `translate()`-Methode der Klasse `QRectF` mit dem elementspezifischen Vektorenwert `yMovement`.

4. Die `class gameArea` definiert das Zeichenfeld des Spiels, in dem sich der Spieler und die Gegnerelemente bewegen. Sie ist zuständig für: den Spiel-Timer und die Punkteanzeige, die Aktualisierung, das Pausieren und das Ende des Spiels, für das Zeichnen der Gegner und der Leben, für die Kollisionsabfrage von Spieler und Gegnern sowie für das Auslösen der veränderten Darstellung des Spielers bei seiner Kollision mit einem Gegnerelement. Kurz gesagt regelt die Klasse alles, was innerhalb des Spiels passiert. Die Klasse basiert auf der Qt-Klasse `QMainWindow`, um deren Framework zur Widgetgestaltung nutzen zu können. 
    - Im Konstruktor der `gameArea` wird der Anfangszustand des Spiels initalisiert. Auf Basis der Positions- und Layout-Definitionen und -Methoden der `class player` wird das Spielerrechteck im Zeichenfeld erzeugt (`gamePlayer`). Die Methode `gameArea::setRunning()` sowie ihre `bool`-Variable `running` werden auf `false` gesetzt, damit sich das Spielfenster mit inaktiven Spielzustand öffnet. Desweiteren werden Anfangswerte für Spielpunkte, Leben und die für die verschiedenen Pause- und Endzustände (`unverwundbar`, `getroffen` und `gameOver`) zuständigen Variablen und Timer festgelegt. Außerdem wird hier der Spieltimer auf Basis der Klasse `QTimer` erzeugt und definiert sowie der Vektor `std::vector<element*> enemies`, über den die Gegnerelemente in das Spiel implementiert werden, mit neuen zufälligen Elementen befüllt.
    - Die Methode `gameArea::updateGame()` regelt die Aktualisierung der Spielzustände und des Punktecounters. Sie wurde im Konstruktor mit dem Timer verknüpft. In ihr ist festgelegt, was während der verschiedenen Spielphasen geschehen soll. Während das Spiel läuft, soll die Punktzahl konstant erhöht werden. Außerdem werden hier die Zeitintervalle nach der Kollision mit einem Gegner und für die temporäre GameOver-Anzeige gestartet. Diese seperaten Zustands-Timer werden solange erhöht, bis sie den Wert des zugehörigen Timeouts (in `gameArea.h` konstant festgelegt) erreicht haben. Es wird definiert, was nach dem jeweiligen Timeout geschehen soll: 
        - Wenn der Spieler getroffen wurde, wird der Timer für das Timeout des `getroffen`-Zustandes gestartet und der Spieler `unverwundbar` gemacht (und damit auch der unverwundbar-Timer gestartet). Nach Ende des Timeouts wird das Spiel wieder in den aktiven Zustand versetzt, läuft also weiter. 
        - Wenn der Spieler `unverwundbar` ist, wird ebenfalls ein Timer für die Zeit der Unverwundbarkeit gestartet. So wird verhindert, dass der Spieler nicht direkt mit dem nächsten, eventuell direkt über ihm liegenden, aber eingefrorenen Gegner kollidiert, ohne die Chance zu haben, auszuweichen. Nach Ende des `unverwundbar`-Zustands kann der Spieler wieder von Gegnern getroffen werden. 
        - Wenn der Spieler das letzte Leben verliert, wird in der Methode `gameArea::drawEnemies()` durch den Aufruf der `gameArea::gameIsOver()`-Methode die bool-Variable `gameOver`auf true gesetzt (und `getroffen` auf `false`, um nicht den `getroffenTimer`auszulösen). Dadurch friert das Spiel ein, die Game Over-Anzeige erscheint und der gameOver-Timer wird gestartet. Nach dem Ende des gameOver-Timeouts wird die Game Over-Anzeige wieder vom Spielfeld entfernt sowie die Leben und die Spielerdarstellung zurückgesetzt.
    - Das `gameArea::paintEvent()` löst die `drawLives()`- und `drawEnemies()`-Methoden aus und übergibt diesen jeweils den im paintEvent erzeugten `painter`.
    - Die Methode `gameArea::drawLives()` ist für die Lebensanzeige zuständig. Durch ihre Anweisungen werden, abhängig von der Anzahl der Leben, die Lebens-Kreise ausgefüllt 🔴 oder als leerer Rahmen ⚪️ gezeichnet.
     - Die Methode `gameArea::changePlayerStyle()` regelt die richtige Setzung des `playerStyle`. Anhand der Anzahl der Leben wird in ihr mit dem entsprechenen Style-Wert von 0, 1 oder 2 die `player::setPlayerStyle()`-Methode aufgerufen, um die Darstellung des Spielers zu verändern, ihn bei Lebensverlust abgeschwächt darzustellen und seine Darstellung bei Berührung eines Leben-Elements 🔴 wieder zu verbessern. 
    - Die Methode `gameArea::drawEnemies()` ist für die Abbildung der Gegnerelemente des Vektors `std::vector<element*> enemies` anhand des `elementType` im Spielfeld zuständig und enthält auch die Kollisionsabfrage zwischen Spieler und Gegnern. Innerhalb einer `for`-Schleife wird mithilfe eines auf der `class element` basierenden Pointer-Objekts für jedes Vektorelement die optische Darstellung (QBrush: QColor, Qt::BrushStyle; QPen) festgelegt. In einem `switch`-case über den `elementType` wird die Zeichnung der Form dem jeweiligen Gegnerelement zugeordnet. Außerdem wird die Methode `element::moveElement()` aufgerufen, um alle Elemente mit ihrer individuellen Fallgeschwindigkeit (`yMovement`) im Spiel zu bewegen. Auch diese Zuweisung erfolgt über den `elementType`.
    - Für die Kollisionsabfrage in der Methode `gameArea::drawEnemies()` wird die Methode `intersects()` der QT-Klasse `QRectF` genutzt. Um die Methode verwenden zu können, wurden innerhalb der Methode zwei Verwaltungsobjekte des Typs `QRectF` erzeugt (`player` und `enemy`), auf die jeweils die Spieler- bzw. Elementeigenschaften übertragen werden. Vor der Kollisionsabfrage werden außerdem Breite und Höhe des helltürkisen Dreiecks (pie) angepasst, da sich Spieler und Pie-Element ansonsten zu früh schneiden würden (durch `painter.drawPie()` wird vermutlich ein ganzer Kreis gezeichnet, von dem jedoch nur ein definiertes Stück sichtbar ist. Dadurch haben sich der Spieler und das Element bereits berührt, bevor die Kollision für  sichtbar war. Dieses Problem wurde durch die Verkleinerung des Elements behoben und wirkt sich nicht auf die optische Darstellung des Dreiecks aus).
      Durch eine `if`-Bedingung, mit der überprüft wird, ob sich der Spieler mit einem Gegnerelement schneidet, während er verwundbar ist, werden die Zustände `unverwundbar`, `getroffen` oder `gameOver`und damit auch ihre Timer/Timeouts ausgelöst und das Spiel durch den Aufruf der `gameArea::setRunning()`-Methode in den inaktiven Zustand versetzt. Durch eine weitere `if`-Bedingung wird überprüft, ob es sich bei dem vom Spieler berührten Element um einen roten Kreis 🔴 handelt, da dann Leben hinzugefügt werden sollen; vorausgesetzt die Leben sind nicht voll aufgeladen. In jedem anderen Fall, also bei Schneiden des Spielers mit jedem anderen Gegnerelement, wird ihm ein Leben abgezogen. Die Veränderung der optischen Darstellung des Spielers wird in beiden Fällen durch den Aufruf der Methode `gameArea::changePlayerStyle()` realisiert. In dieser wird, abhängig von der Anzahl der Leben, die `player::setPlayerStyle()`-Methode mit dem entsprechenden Wert von 0-2 für die Art der Darstellung aufgerufen. So wurde implementiert, dass der Spieler bei Lebensverlust in zwei Abstufungen abgeschwächt dargestellt wird, sich seine Darstellung aber auch wieder verbessert, wenn er ein herunterfallendes Lebenelement 🔴 berührt und ein Leben wiederhergestellt wird. Innerhalb der `for`-Schleife wurde außerdem durch eine weitere `if`-Bedingung implementiert, dass jedes Gegner-Element, dass den unteren Spielfeldrand überschreitet, durch einen neuen zufälligen Gegner ersetzt werden soll. 
    - In der Methode `gameArea::gameIsOver()` wird die Game Over-Anzeige am Spielende konfiguriert. Sie legt die Texte sowie deren Position, Schriftart und Schriftgröße fest, setzt die Spielpunkte zurück und löscht alle vorhandenen Gegner, indem sie durch Aufruf der `element::newElement()`-Methode neue zufällige Gegner überhalb des sichtbaren Spielbereichs erzeugt. Die Zurücksetzung der Lebensanzeige und der Spielerdarstellung wurde bewusst in die bereits beschriebene Methode `gameArea::updateGame()` ausgelagert, um den anfänglichen Spielstand erst vollständig wiederherzustellen, wenn das Game Over-Timeout zuende ist. 
    - Die Methode `gameArea::setRunning()` bekommt den aktuellen Spielstatus (`running`:`true` oder `false`) übergeben und verändert anhand dessen die Farbe des Spielhintergrundes, um einen optischen Unterschied zwischen inaktivem und aktivem Spiel zu erzeugen.
    - Die Methode `gameArea::serialize()` legt die Aktion für die `gameWidget::saveGame()`-Methode fest und ist für die Speicherung des aktuellen Spielstandes zuständig. In ihr werden **chronologisch** die zu speichernden Spielinformationen mit einem QFile-Objekt in die Speicherungsdatei exportiert:
        - (Überschrift; für Dateiabfrage beim Laden benötigt)
        - aktuelle X-Position des Spielers (`playerX`)
        - aktueller Stil (`playerStyle`)
        - Y-Position, X-Position, `elementType` (jedes Gegnerelements)
        - Anzahl der Punkte (`gamePoints`)
        - Anzahl der Leben (`leben`)
    - Die Methode `gameArea::deserialize()` legt die Aktion für die `gameWidget::loadGame()`-Methode fest und liest die gespeicherten Informationen aus der Datei. Dazu wird ein Objekt der Klasse `QString` genutzt, um die Daten Zeile für Zeile auslesen zu können. Für die Verarbeitung der durch Komma getrennten Gegner-Eigenschaften wird eine `QStringList` genutzt. Da die Spielinformationen über `QString/QStringList` als Zeilen verwaltet werden, müssen sie wieder in numerische Werte umgewandelt werden. Mithilfe der in den Klassen `player` und `element` implementierten set-Methoden sowie der Zuweisung der `int`-Variablen `gamePoints` und `leben` kann der aktuelle Spielstand durch die gespeicherten Werte ersetzt werden. Durch den Aufruf der `QWidget`-Methode `update()` werden diese dann auf das aktuelle Spiel angewendet und der gespeicherte Spielzustand wiederhergestellt.
    - Hinweis: Beim Speichern bzw. Laden eines Spielzustandes zeigt der QT Creator folgende Ausgabe der Anwendung an: '*objc[901]: Class FIFinderSyncExtensionHost is implemented in both /System/Library/PrivateFrameworks/FinderKit.framework/Versions/A/FinderKit (0x7fff8fd3ac90) and /System/Library/PrivateFrameworks/FileProvider.framework/OverrideBundles/FinderSyncCollaborationFileProviderOverride.bundle/Contents/MacOS/FinderSyncCollaborationFileProviderOverride (0x1182fdcd8). One of the two will be used. Which one is undefined.*'
    Der Grund für diese Meldung konnte trotz Internetrecherche nicht vollständig ermittelt werden. Eventuell hängt das Problem mit dem Mac-Betriebssystem OSX High Sierra zusammen, da das Problem nur auf Mac-Geräten, aber nicht auf Windows-PCs auftritt (siehe: https://github.com/jarvisteach/appJar/issues/285, https://stackoverflow.com/questions/46999695/class-fifindersyncextensionhost-is-implemented-in-both-warning-in-xcode-si). Die Meldung beeinträchtigt die Funktionalität des Programms jedoch in keinster Weise. Das Speichern und Laden des Spielzustandes ist trotz der Meldung vollständig möglich.
