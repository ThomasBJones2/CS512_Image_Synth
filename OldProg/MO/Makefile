cmllib = /home/thomas/Documents/ImgSynth/subversion/svnrepository/CML

Pix:
	g++ MO.cpp -o MO -lstdc++ -lglfw -lX11 -lrt -lGL -ljpeg -pthread -I$(cmllib)

clean:
	rm -rf MO

remake:
	make clean
	make
