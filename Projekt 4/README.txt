Autoren
=======

Natalie Hube
Jannes Meyer



Allgemeines
===========

Die *.txt sind im Unterordner /data zu finden. Außerdem wurden einige C++11-Features verwendet.

Die Tastenbelegung:
Pfeil nach oben          heranzoomen
Pfeil nach unten         wegzoomen
Pfeil nach links/rechts  drehen
W                        Wireframe-Modus an/ausschalten
                         (funktioniert nur bei Flächen, nicht bei Linien)
ESC                      Programm schließen




Anmerkungen zu einzelnen Aufgaben
=================================

Exercise 4.1
------------
Init-Funktion: initLab41()
Hier werden die Punkte nicht aus einer Datei gelesen, sondern wurden direkt im Programm eingegeben.
In späteren Aufgaben sind wir erst dazu übergegangen die Punkte aus Dateien einzulesen.


Exercise 5.1
------------
Init-Funktion: initLab51()
Hier wird nur aus einem Grund ein TriangleMesh (aus der Aufgabe 7.2). Nämlich um Gouraud-Shading zu
erhalten. Die Berechnung der Normalenvektoren ist nämlich nur in TriangleMesh enthalten und nicht
in Mesh.


Exercise 6.1
------------
Init-Funktion: initLab61()
In dieser Aufgabe wird ein Polygonzug aus einer Datei eingelesen und gezeichnet. Nach viermaligem
drücken der + Taste hat man die Subdivision vier mal ausgeführt.


Exercise 6.2
------------
Init-Funktion: initLab62()


Exercise 7.1
------------
Init-Funktion: initLab71()


Exercise 7.2
------------
Init-Funktion: initLab72()
Bei dieser Aufgabe wird dem Konstruktor von TriangleMesh noch der Skalierungsfaktor 50 mitgegeben
da die Beispieldatei bunny1.txt sind zu klein und nicht erkennbar wäre.
