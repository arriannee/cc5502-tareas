all: punto_tests vector_tests poligono_tests

punto_tests:
	g++ punto_tests.cpp -o punto_tests

vector_tests:
	g++ vector_tests.cpp -o vector_tests

poligono_tests:
	g++ poligono_tests.cpp -o poligono_tests


run_all: punto_tests vector_tests poligono_tests
	./punto_tests
	./vector_tests
	./poligono_tests

clean:
	rm punto_tests vector_tests poligono_tests

