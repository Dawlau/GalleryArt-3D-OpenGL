#! /bin/bash

g++ *.cpp -o main -lSOIL -lGL -lGLU -lglut -lGLEW && ./main
rm main