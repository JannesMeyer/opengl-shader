Autoren
=======

Natalie Hube
Jannes Meyer



Allgemeines
===========

Die *.txt sind im Unterordner /data zu finden. Au�erdem wurden einige C++11-Features verwendet.

Die Tastenbelegung:
Pfeil nach oben          heranzoomen
Pfeil nach unten         wegzoomen
Pfeil nach links/rechts  drehen
W                        Wireframe-Modus an/ausschalten
                         (funktioniert nur bei Fl�chen, nicht bei Linien)
ESC                      Programm schlie�en




Anmerkungen zu einzelnen Aufgaben
=================================

Exercise 4.1
------------
Init-Funktion: initLab41()
Hier werden die Punkte nicht aus einer Datei gelesen, sondern wurden direkt im Programm eingegeben.
In sp�teren Aufgaben sind wir erst dazu �bergegangen die Punkte aus Dateien einzulesen.


Exercise 5.1
------------
Init-Funktion: initLab51()
Hier wird nur aus einem Grund ein TriangleMesh (aus der Aufgabe 7.2). N�mlich um Gouraud-Shading zu
erhalten. Die Berechnung der Normalenvektoren ist n�mlich nur in TriangleMesh enthalten und nicht
in Mesh.


Exercise 6.1
------------
Init-Funktion: initLab61()
In dieser Aufgabe wird ein Polygonzug aus einer Datei eingelesen und gezeichnet. Nach viermaligem
dr�cken der + Taste hat man die Subdivision vier mal ausgef�hrt.


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
da die Beispieldatei bunny1.txt sind zu klein und nicht erkennbar w�re.
