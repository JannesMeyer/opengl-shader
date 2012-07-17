Projektidee
===========

Zielsetzung waren zweierlei Dinge:

1. Alle OpenGL-Draw-Calls auf die neuen Methoden umzustellen. Das bedeuetet, dass wir Vertex Buffer Objects statt glBegin() und glEnd() verwenden wollen. Die VBOs gibt es in der derzeitigen Form seit OpenGL 3.0.

2. Versuchen, einen Post-Processing-Filter mittels zusätzlicher Shader, die in der Sprache GLSL geschrieben wurden, anzuwenden


Erfahrungen
===========

Es war schwierig für uns, gedanklich auf das neue Modell der Programmable Rendering Pipeline umzusteigen, nachdem wir zunächst noch den Umgang Fixed-Function Pipeline gelernt haben und schon verinnerlicht hatten.

Leider haben wir deshalb auch nicht so viel geschafft, wie wir uns eigentlich vorgenommen hatten.



Verwendete Resourcen
====================

Wir haben dieses Buch verwendet:

 - iPhone 3D Programming: Developing Graphical Applications with OpenGL ES

    Philip Rideout, 2010, O'Reilly
    http://www.amazon.de/iPhone-Programming-Developing-Graphical-Applications/dp/0596804822/


Unser Code basiert stellenweise auf den Code-Beispielen aus diesem Buch.

Die Vector-, Matrix- und Quaternion-Hilfsklassen stammen aus dem Anhang dieses Buches.