#ifndef MEDIALAYER_H
#define MEDIALAYER_H

#include <vector>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>


//#include <GL/glew.h>
//#include <SDL2/SDL_opengl.h>
//#include <GL/GLU.h>


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

	TTF_Font*		m_font;

	SDL_Keycode		m_key;

	std::vector<SDL_Texture*>	m_imagelist;
	std::vector<Mix_Music*>		m_musiclist;
	std::vector<Mix_Chunk*>		m_soundlist;


	SDL_Surface* loadSurface(std::string path);
	SDL_Texture* loadTexture(std::string path, bool transparentbackground);
	SDL_Texture* loadTextTexture(std::string text, SDL_Color textColor);

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
	bool setimagetodisplay(CTI_IMAGE imageref, int pos_x, int pos_y);
	bool setimagetodisplay_adv(CTI_IMAGE imageref, int pos_x, int pos_y, double angle);
	bool getimagesize(CTI_IMAGE imageref, int* size_x, int* size_y);

		// text
	bool setfont(std::string fontpath, int fontsize);
	bool settexttodisplay(std::string text, int pos_x, int pos_y, int r, int g, int b);

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

		// sound
	bool addsound(std::string wavfile, CTI_SOUND* soundref);
	bool freeallsound();
	bool freesound(CTI_SOUND soundref);
	bool playsound(CTI_SOUND soundref);

};




#endif
