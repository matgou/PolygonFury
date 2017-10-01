make mrproper
[[ $? != "0" ]] && exit 1

wget https://downloads.sourceforge.net/project/sdl-draw/SDL_draw/1.2.13/SDL_draw-1.2.13.tar.gz
[[ $? != "0" ]] && exit 1

tar xvf SDL_draw-1.2.13.tar.gz 
[[ $? != "0" ]] && exit 1

cd SDL_draw-1.2.13
[[ $? != "0" ]] && exit 1

./configure && make
[[ $? != "0" ]] && exit 1

cp src/.libs/libSDL_draw.a ../lib/
[[ $? != "0" ]] && exit 1

cd ..
[[ $? != "0" ]] && exit 1

make
[[ $? != "0" ]] && exit 1

