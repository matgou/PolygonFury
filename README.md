# PolygonFury

This is a simple desktop-game using SDL library

# Screenshot

![screenshot-level](https://raw.githubusercontent.com/matgou/PolygonFury/master/screenshot-play.png "Screenshot Play")

# Minimum requirement :
 * Linux
 
# Build 

```bash
sudo apt-get install libsdl-console-dev libsdl-ttf2.0-dev
wget https://downloads.sourceforge.net/project/sdl-draw/SDL_draw/1.2.13/SDL_draw-1.2.13.tar.gz
tar xvf SDL_draw-1.2.13.tar.gz 
cd SDL_draw-1.2.13
./configure && make
cp src/.libs/libSDL_draw.a ../lib/
cd ..
make

```

# Run

```bash
./run.sh
```
