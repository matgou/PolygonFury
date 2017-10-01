make mrproper
wget https://downloads.sourceforge.net/project/sdl-draw/SDL_draw/1.2.13/SDL_draw-1.2.13.tar.gz
tar xvf SDL_draw-1.2.13.tar.gz 
cd SDL_draw-1.2.13
./configure && make
cp src/.libs/libSDL_draw.a ../lib/
cd ..
make
