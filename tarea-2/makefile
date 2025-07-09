all: punto_tests vector_tests poligono_tests convex_hull_test

punto_tests:
	g++ punto_tests.cpp -o punto_tests

vector_tests:
	g++ vector_tests.cpp -o vector_tests

poligono_tests:
	g++ poligono_tests.cpp -o poligono_tests

convex_hull_test: convex_hull_test.cpp graham_scan.cpp gift_wrapping.cpp convex_hull_strategies.hpp
	g++ convex_hull_test.cpp graham_scan.cpp gift_wrapping.cpp -o convex_hull_test

run_all: punto_tests vector_tests poligono_tests
	./punto_tests
	./vector_tests
	./poligono_tests

run_convex_hull_test: convex_hull_test
	./convex_hull_test

visualizacion_gift:
	g++ visualizacion_gift.cpp -lsfml-graphics -lsfml-window -lsfml-system -o visualizar_gift
	
run_visualizacion_gift: visualizacion_gift
	./visualizar_gift

visualizacion_graham:
	g++ visualizacion_graham.cpp -lsfml-graphics -lsfml-window -lsfml-system -o visualizar_graham

run_visualizacion_graham: visualizacion_graham
	./visualizar_graham

generar_puntos: generar_puntos.cpp
	g++ generar_puntos.cpp -o generar_puntos

run_generar_puntos: generar_puntos
	./generar_puntos

clean:
	rm -f punto_tests vector_tests poligono_tests convex_hull_test visualizar_gift visualizar_graham
