#ifndef MEDIALAYER_H
#define MEDIALAYER_H

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


#include "libcti.h"

#define			USE_AUDIO		1

#ifdef WIN32
#include <time.h>
#elif LINUX
#include <sys/time.h>
#endif


class medialayer
{
private:
	SDL_Window*		m_window;
	SDL_Surface*	m_display;
	SDL_Renderer*	m_renderer;

	SDL_Keycode		m_key;

	std::vector<SDL_Texture*>	m_imagelist;
	std::vector<Mix_Music*>		m_musiclist;
	std::vector<Mix_Chunk*>		m_soundlist;
	std::vector<TTF_Font*>		m_fontlist;

	SDL_Surface* loadSurface(std::string path);
	SDL_Texture* loadTexture(std::string path, bool transparentbackground);

	int m_screen_x;
	int m_screen_y;

public:
	medialayer();
	~medialayer();

	// management
	bool initialize(std::string windowname, int screenx, int screeny);
	bool uninitialize();
	bool getscreensize(int* size_x, int* size_y);
	bool pollevent(EVENTTYPE* eventtype);
	bool geteventkey(EVENTKEY* eventkey);
	bool getmouseposition(int* pos_x, int* pos_y);
	int  getticks();
	bool sleep(int milliseconds);

	// graphics
		// primitives
	bool drawline(int ax, int ay, int bx, int by, int r, int g, int b);

		// bitmaps
	bool addimage(std::string bmpfile, CTI_IMAGE* imageref, bool transparentbackground);
	bool arraytoimage(uint32_t* pixels, CTI_IMAGE* imageref, int pitch);

	bool freeallimages();
	bool freeimage(CTI_IMAGE imageref);
	bool setimagetodisplay(CTI_IMAGE imageref, int pos_x, int pos_y, CRECT* srcrect=nullptr);
	bool setimagetodisplay_adv(CTI_IMAGE imageref, int pos_x, int pos_y, double angle);
	bool getimagesize(CTI_IMAGE imageref, int* size_x, int* size_y);

	bool setalphamodulation(CTI_IMAGE imageref, int value);

	// text
	bool addfont(std::string fontfile, int fontsize, CTI_FONT* fontref);
	bool freeallfonts();
	bool freefont(CTI_FONT fontref);
	bool texttoimage(CTI_IMAGE* imageref, CTI_FONT fontref, std::string text, CCOLOR col);

		// general
	bool cleardisplay();
	bool displayimages();


	// audio
		// music
	bool addmusic(std::string wavfile, CTI_MUSIC* musicref);
	bool freeallmusic();
	bool freemusic(CTI_MUSIC musicref);
	bool playmusic(CTI_MUSIC musicref);
	bool stopmusic();
	bool pausemusic();
	bool resumemusic();
	bool setmusicvolume(int volume);

		// sound
	bool addsound(std::string wavfile, CTI_SOUND* soundref);
	bool freeallsound();
	bool freesound(CTI_SOUND soundref);
	bool playsound(CTI_SOUND soundref);
	bool setsoundvolume(int volume, int channel);

};

#endif
