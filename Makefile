all: build run clean

build:
	g++ graphics/*.cpp -o main  -lGL -lGLU -lglut -lGLEW
run:
	./main
clean:
	rm main
