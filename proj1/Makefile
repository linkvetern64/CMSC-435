main: main.o Polygon.o RayTracer.o Sphere.o Shape.o
	g++ -o main main.o RayTracer.o Polygon.o Sphere.o Shape.o

default: main.o run clean

main.o: main.cpp
	g++ -c main.cpp -I../common

Polygon.o: Polygon.cpp
	g++ -c Polygon.cpp -I../common

RayTracer.o: RayTracer.cpp
	g++ -c RayTracer.cpp -I../common

Shape.o: Shape.cpp
    g++ -c Shape.cpp -I../common

Sphere.o: Sphere.cpp
    g++ -c Sphere.cpp -I../common

run:
	./main

clean:
	rm *.o
	rm *.ppm