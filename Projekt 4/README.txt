Autoren
=======

 - Jannes Meyer
 - Natalie Hube


Projektidee
===========

Zielsetzung waren zweierlei Dinge:

1. Alle OpenGL-Draws mit den in OpenGL 3.0 empfohlenen Methoden zu machen. Das bedeuetet, dass wir auf glBegin() und glEnd() verzichten und stattdessen Vertex Buffer Objects zum Speichern der Vertex-Daten sowie Vertex- und Fragment-Shader für die Beleuchtung verwenden. Die Vorteile davon sind eine deutlich bessere Performance und mehr Gestaltungs-Möglichkeiten als mit der Fixed-Function Pipeline.

2. Wir wollten versuchen, einen Post-Processing-Filter mittels zusätzlicher GLSL-Shader zu programmieren. Das stellte sich aber als zu umfangreich heraus (man hätte dafür in eine Textur rendern müssen und auf diese Textur dann den Shader anwenden müssen), sodass wir uns darauf beschränkt haben, erstmal eine normale Beleuchtung in GLSL zu implementieren.

3. Außerdem haben wir eine Klasse implementiert, mit der es möglich ist, parametrisierte Flächen zu zeichnen.


Erfahrungen
===========

Es war schwierig für uns, gedanklich auf das neue Modell der Programmable Rendering Pipeline umzusteigen, nachdem wir zunächst noch den Umgang Fixed-Function Pipeline gelernt und verinnerlicht haben. Leider haben wir deshalb auch nicht so viel geschafft, wie wir uns eigentlich vorgenommen hatten.



Verwendete Resourcen
====================

Wir haben dieses Buch verwendet:

 - iPhone 3D Programming: Developing Graphical Applications with OpenGL ES

    Philip Rideout, 2010, O'Reilly
    http://www.amazon.de/iPhone-Programming-Developing-Graphical-Applications/dp/0596804822/


Unser Code basiert auf ein paar Beispielen aus diesem Buch.

Die Vector-, Matrix- und Quaternion-Hilfsklassen stammen aus dem Anhang dieses Buches.