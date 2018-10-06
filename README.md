# SS18-Semesterarbeit-CPP2-Roland
Semesterarbeit von Kim Roland im BM3-Modul Softwaretechnologie, Seminar "Objektorientierte Programmierung: C++-Programmieren-2"

## Dokumentation
Im Rahmen dieser Semesterarbeit wurden die Stufen IV, III und II der Aufgabenstellung erfolgreich realisiert.

### Projekt herunterladen
- Projekt-Masterdatei als ZIP-Ordner herunterladen und entpacken
- .pro-Datei des Projektes (SS18-Semesterarbeit-CPP2-Roland.pro) mit QT öffnen und konfigurieren
- Ausführen (Kompilieren erfolgreich getestet mit folgenden Programmversionen: Qt 5.9.2 (Clang 7.0 (Apple), 64 bit) und Qt Creator 4.4.1)
- Spielwidget öffnet sich

### Spielfunktionen

#### Spiel starten
Durch Anklicken des Buttons mit der Aufschrift "Start" in der oben linken Ecke des Spielfensters wird das Spiel gestartet. Der Button wechselt die Beschriftung zu "Pause". Über erneutes Anklicken des Buttons kann das Spiel pausiert werden.

#### Spielen
Der Spieler (schraffiertes Rechteck) kann sich mit den Pfeiltasten ⬅️ ➡️ am unteren Rand des Spielfeldes bewegen und muss den herunterfallenden Elementen (Gegnern) ausweichen. Wird der Spieler von einem Gegnerelement getroffen (die beiden Spielobjekte berühren sich), verliert der Spieler ein Leben (⚪️🔴🔴: Lebensanzeige in der oberen rechten Spielfeldecke) und das Spiel friert kurz ein. Nach dieser kurzen Spielpause startet das Spiel wieder und läuft weiter. Wenn der Spieler getroffen wurde, wird er abgeschwächt dargestellt, je nach Anzahl der noch vorhandenen Leben. Insgesamt gibt es drei verschiedene optische Darstellungen des Spielers (bei vollen Leben, bei Verlust eines Lebens, bei nur noch einem vorhandenen Leben). Außerdem ist der Spieler nach der Kollision mit einem Gegnerelement für ein paar Sekunden unverwundbar (zugunsten des besseren Spielflusses, um eine direkt darauffolgende Kollision mit einem anderen Gegnerelement zu vermeiden). Danach kann er wieder von weiteren Gegnerelementen getroffen werden. Hat der Spieler alle drei Leben verloren, wird das Spielende durch ein Game Over-Anzeige und die in dem Spieldurchgang erreichte Punktzahl angezeigt. Danach startet das Spiel erneut.
Verlorene Leben können durch die Berührung von herunterfallenden roten Kreis-Elementen 🔴, die optisch dem Aussehen der Lebensanzeige entsprechen, regeneriert werden. Bei der Kollision mit dieser Art von Elementen wird das Spiel ebenfalls kurz eingefroren, aber ein Leben hinzugefügt statt abgezogen. Die maximale Anzahl an Leben entspricht 3, bei voller Lebensanzahl können die Leben nicht weiter addiert werden.

#### Speichern und Laden
Die Buttons "Speichern" und "Laden" ermöglichen es dem Spieler, den aktuellen Spielstand für das Weiterspielen zu einem späteren Zeitpunkt zu speichern oder vor dem Spielstart einen alten gespeicherten Spielstand wieder herzustellen. Um diese Funktionen nutzen zu können, darf das Spiel nicht laufen, sondern muss pausiert sein. 
Im Rahmen der Speicherung lassen sich alle relevanten Spielinformationen speichern: die aktuelle Position des Spielers sowie seine aktuelle optische Darstellung, die Anzahl seiner vorhandenen Leben, die bisher erreichte Punktzahl sowie die Anzahl, Position und der jeweilige Element-Typ (regelt Form, Farbe und Fallgeschwindkeit) der sich momentan im Spielfeld befindenden Gegnerelemente.
Ein alter Spielstand kann sowohl direkt nach dem Start der Spielanwendung als nach dem Pausieren eines bereits gelaufenen Spiels geladen werden. Im Rahmen des Ladens werden die beschriebenen Spielinformationen vollständig wiederhergestellt und der Spieler kann durch Anklicken des "Start"-Buttons nach dem Laden genau auf diesem letzten Spielstand weiterspielen.

#### Spielende
Hat der Spieler alle drei Leben verloren, wird das Spielende durch ein Game Over-Anzeige und die in dem Spieldurchgang erreichte Punktzahl angezeigt. Danach startet das Spiel erneut. Alternativ kann die gesamte Spielanwendung auch über den Button "Ende" am unteren linken Spielfeldrand beendet werden. 

## Programm-Erläuterungen: Wichtige Klassen und Methoden


