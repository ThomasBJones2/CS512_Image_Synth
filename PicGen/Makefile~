cmllib = ../CML

Pix:
	clear
	clear
	g++ -O3 -Wall LOS.cpp -o LOS -lstdc++ -lglfw -lX11 -lrt -lGL -ljpeg -pthread -I$(cmllib)

clean:
	rm -rf LOS

run:
	ulimit -s 512000
	./LOS

remake:
	make clean
	make
