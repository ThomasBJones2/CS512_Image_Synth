cmllib = ../CML

Pix:
	clear
	clear
	g++ -O3 -Wall PicGen.cpp -o PicGen -lstdc++ -lglfw -lX11 -lrt -lGL -ljpeg -pthread -I$(cmllib)

clean:
	rm -rf PicGen

run:
	ulimit -s 512000
	./LOS

remake:
	make clean
	make
