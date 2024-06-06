#/**
 #* Title: AVL Trees and Heaps
 #* Author : Ahmet Furkan KIZIL
 #* ID: 22203112
 #* Section : 3
 #* Homework : 2
 #* Description : AVL Trees and Heaps with required implementations
 #

simulator : Heap.cpp Heap.h Simulator.cpp Simulator.h Request.cpp Request.h Computer.h Computer.cpp main.cpp
	g++ Heap.cpp Simulator.cpp Request.cpp Computer.cpp main.cpp -o simulator


run : simulator
	./simulator log1.txt 5 > output1.txt
	./simulator log2.txt 15 > output2.txt
	./simulator log3.txt 46 > output3.txt
	./simulator log3.txt 17 > output4.txt