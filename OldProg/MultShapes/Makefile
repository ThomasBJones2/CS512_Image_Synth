cmllib = /home/thomas/Documents/ImgSynth/subversion/svnrepository/CML

Pix:
	g++ MultShapes.cpp -o MultShapes -lstdc++ -lglfw -lX11 -lrt -lGL -ljpeg -pthread -I$(cmllib)

clean:
	rm -rf MultShapes

remake:
	make clean
	make
