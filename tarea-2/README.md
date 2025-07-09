# Tarea 1: Introducción a C++

- Curso: CC5502 Geometría Computacional
- Profesora: Nancy Hitschfeld-Kahler
- Auxiliar: Gustavo Medel
- Ayudante: Catalina Gajardo
- Estudiante: Arianne Peña

Compilación y ejecución
--------------------------------------------

Para compilar todos los archivos y tests:

    make

Para compilar y correr todos los tests automáticamente:

    make run_all

Para limpiar los archivos compilados:

    make clean

Estructura del proyecto
--------------------------------------------

- punto.hpp           : Clase Punto<T> con coordenadas x, y, z
- punto_tests.cpp     : Tests de Punto<T>

- vector.hpp          : Clase Vector<T> con operaciones geométricas
- vector_tests.cpp    : Tests de Vector<T>

- poligono.hpp        : Clase Poligono<T> con área, perímetro y orientación
- poligono_tests.cpp  : Tests de Poligono<T>

- makefile            : Reglas para compilar y correr los tests

Comentarios adicionales
--------------------------------------------

- Se usa la fórmula del área orientada (shoelace) para detectar orientación.
- Se respetan los tipos template (T) excepto cuando es necesario usar double (por ejemplo, magnitud o perímetro).
- Los tests usan assert y cubren los métodos solicitados.
