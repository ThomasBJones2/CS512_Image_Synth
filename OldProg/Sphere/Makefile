cmllib = /home/thomas/Documents/ImgSynth/subversion/svnrepository/CML

Pix:
	g++ Sphere.cpp -o Sphere -lstdc++ -lglfw -lX11 -lrt -lGL -ljpeg -pthread -I$(cmllib)

clean:
	rm -rf Sphere

remake:
	make clean
	make
