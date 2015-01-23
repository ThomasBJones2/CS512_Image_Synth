cmllib = /home/thomas/Documents/ImgSynth/subversion/svnrepository/CML

Pix:
	g++ Cylinder.cpp -o Cylinder -lstdc++ -lglfw -lX11 -lrt -lGL -ljpeg -pthread -I$(cmllib)

clean:
	rm -rf Cylinder

remake:
	make clean
	make
