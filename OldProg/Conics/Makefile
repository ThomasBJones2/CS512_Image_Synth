cmllib = ../CML

Pix:
	g++ Conics.cpp -o Conics -lstdc++ -lglfw -lX11 -lrt -lGL -ljpeg -pthread -I$(cmllib)

clean:
	rm -rf Conics

remake:
	make clean
	make
