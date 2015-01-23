cmllib = /home/thomas/Documents/ImgSynth/subversion/svnrepository/CML

Pix:
	g++ Planes.cpp -o Planes -lstdc++ -lglfw -lX11 -lrt -lGL -ljpeg -pthread -I$(cmllib)

clean:
	rm -rf Planes

remake:
	make clean
	make
