#include "medialayer.h"
#include <math.h>
#include <string>

medialayer::medialayer()
{
	m_window = nullptr;
	m_display = nullptr;
	m_renderer = nullptr;
	m_key = SDLK_0;

	m_imagelist.clear();

}

medialayer::~medialayer()
{
}

bool medialayer::initialize(std::string windowname, int screenx, int screeny)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
		return false;

	m_window = SDL_CreateWindow(windowname.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenx, screeny, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
		return false;

	m_screen_x = screenx;
	m_screen_y = screeny;

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr)
		return false;

	SDL_SetRenderDrawColor(m_renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	int flags = IMG_INIT_JPG;
	IMG_Init(flags);
//		return false;

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		return false;

	return true;
}

bool medialayer::uninitialize()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	Mix_Quit();
	IMG_Quit();
	SDL_Quit();

	m_renderer = nullptr;
	m_window = nullptr;

	return true;
}

bool medialayer::getscreensize(int* size_x, int* size_y)
{
	bool result = false;
	if (size_x && size_y)
	{
		*size_x = m_screen_x;
		*size_y = m_screen_y;
		result = true;
	}

	return result;
}


bool medialayer::pollevent(EVENTTYPE* eventtype)
{
	bool result = false;
	if (eventtype)
	{
		SDL_Event e;
		if (SDL_PollEvent(&e) != 0)
		{
			switch (e.type)
			{
			case SDL_QUIT:		
				*eventtype = EVENTTYPE::E_QUIT;		
				result = true;
				break;
			case SDL_KEYDOWN:	
				*eventtype = EVENTTYPE::E_KEYDOWN;	
				m_key = e.key.keysym.sym;
				result = true;
				break;
			case SDL_KEYUP:
				*eventtype = EVENTTYPE::E_KEYUP;	
				m_key = e.key.keysym.sym;
				result = true;
				break;
			case SDL_MOUSEMOTION:
				*eventtype = EVENTTYPE::E_MOUSEMOTION;
				result = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				*eventtype = EVENTTYPE::E_MOUSEBUTTONDOWN;
				result = true;
				break;
			case SDL_MOUSEBUTTONUP:
				*eventtype = EVENTTYPE::E_MOUSEBUTTONUP;
				result = true;
				break;


			default:			// unsupported SDL_Event.type
				break;
			}
		}

	}
	return result;
}

bool medialayer::geteventkey(EVENTKEY* eventkey)
{
	bool result = false;
	if (eventkey)
	{
		*eventkey = (EVENTKEY)m_key;
		result = true;
	}

	return result;
}

bool medialayer::getmouseposition(int* pos_x, int* pos_y)
{
	bool result = false;

	if(pos_x && pos_y)
	{
		SDL_GetMouseState(pos_x, pos_y);
		result = true;
	}

	return result;
}

int medialayer::getticks()
{
	return (int)SDL_GetTicks();
}

bool medialayer::sleep(int milliseconds)
{
	SDL_Delay(milliseconds);
	return true;
}

SDL_Surface* medialayer::loadSurface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface)
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, m_display->format, 0);
		SDL_FreeSurface(loadedSurface);
	}

	return optimizedSurface;
}

SDL_Texture* medialayer::loadTexture(std::string path, bool transparentbackground)
{
	SDL_Texture* outputTexture = nullptr;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface)
	{
		if (transparentbackground)
		{
			SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 255, 128, 255));
		}

		//Convert surface to texture
		outputTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		SDL_FreeSurface(loadedSurface);
	}

	return outputTexture;
}

SDL_Texture* medialayer::loadTextTexture(std::string text, SDL_Color textColor)
{
	SDL_Texture* outputTexture = nullptr;
	SDL_Surface* textSurface = TTF_RenderText_Solid(m_font, text.c_str(), textColor);
	if (textSurface)
	{
		outputTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
		SDL_FreeSurface(textSurface);
	}
	return outputTexture;
}

bool medialayer::drawline(int ax, int ay, int bx, int by, int r, int g, int b)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, 0xFF);
	SDL_RenderDrawLine(m_renderer, ax, ay, bx, by);
	return true;
}

bool medialayer::addimage(std::string bmpfile, CTI_IMAGE* imageref, bool transparentbackground)
{
	bool result = false;

	*imageref = (CTI_IMAGE)loadTexture(bmpfile, transparentbackground);
	if (*imageref)
	{
		m_imagelist.push_back((SDL_Texture*)*imageref);
		result = true;
	}

	return result;
}

bool medialayer::arraytoimage(uint32_t* pixels, CTI_IMAGE* imageref, int pitch)
{
	bool result = false;
	if (SDL_UpdateTexture((SDL_Texture*)*imageref, NULL, pixels, pitch) == 0)
		result = true;

	return result;
}


bool medialayer::freeallimages()
{
	for (int i = 0; i < m_imagelist.size(); i++)
	{
		SDL_DestroyTexture(m_imagelist[i]);
	}
	m_imagelist.clear();
	return true;
}

bool medialayer::freeimage(CTI_IMAGE imageref)
{
	bool result = false;
	for (int i = 0; i < m_imagelist.size(); i++)
	{
		if (m_imagelist[i] == (SDL_Texture*)imageref)
		{
			SDL_DestroyTexture(m_imagelist[i]);
			m_imagelist.erase(m_imagelist.begin() + i);
			result = true;
		}
	}

	return result;
}

bool medialayer::setimagetodisplay(CTI_IMAGE imageref, int pos_x, int pos_y)
{
	bool result = false;
	if (imageref)
	{
		SDL_Rect dstpos;

		SDL_QueryTexture((SDL_Texture*)imageref, NULL, NULL, &dstpos.w, &dstpos.h);

		dstpos.x = pos_x;
		dstpos.y = pos_y;


		SDL_RenderCopy(m_renderer, (SDL_Texture*)imageref, nullptr, &dstpos);
		result = true;
	}

	return result;
}

bool medialayer::setimagetodisplay_adv(CTI_IMAGE imageref, int pos_x, int pos_y, double angle)
{
	bool result = false;
	if (imageref)
	{
		SDL_Rect dstpos;
		SDL_QueryTexture((SDL_Texture*)imageref, NULL, NULL, &dstpos.w, &dstpos.h);

		dstpos.x = pos_x;
		dstpos.y = pos_y;
		
		SDL_RenderCopyEx(m_renderer, (SDL_Texture*)imageref, nullptr, &dstpos, angle, nullptr, SDL_FLIP_NONE);
		result = true;
	}

	return result;
}

bool medialayer::getimagesize(CTI_IMAGE imageref, int* size_x, int* size_y)
{
	bool result = false;
	if (size_x && size_y)
	{
		SDL_QueryTexture((SDL_Texture*)imageref, nullptr, nullptr, size_x, size_y);
		result = true;
	}
	return result;
}


bool medialayer::setfont(std::string fontpath, int fontsize)
{
	bool result = false;
	m_font = TTF_OpenFont(fontpath.c_str(), fontsize);
	if (m_font)
	{
		result = true;
	}
	return result;
}

bool medialayer::settexttodisplay(std::string text, int pos_x, int pos_y, int r, int g, int b)
{
	bool result = false;
	SDL_Color color;
	color.r = r;
	color.g = g;
	color.b = b;

	SDL_Texture* TexText = loadTextTexture(text, color);

	if (TexText)
	{
		SDL_Rect dstpos;

		SDL_QueryTexture(TexText, NULL, NULL, &dstpos.w, &dstpos.h);

		dstpos.x = pos_x;
		dstpos.y = pos_y;

		SDL_RenderCopy(m_renderer, TexText, nullptr, &dstpos);
		result = true;
	}

	return result;
}

bool medialayer::cleardisplay()
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0xFF);
	SDL_RenderClear(m_renderer);
	return true;
}

bool medialayer::displayimages()
{
	SDL_RenderPresent(m_renderer);
	return true;
}

bool medialayer::addmusic(std::string wavfile, CTI_MUSIC* musicref)
{
	bool result = false;

	*musicref = (CTI_MUSIC)Mix_LoadMUS(wavfile.c_str());
	if (*musicref)
	{
		m_musiclist.push_back((Mix_Music*)*musicref);
		result = true;
	}

	return result;
}

bool medialayer::freeallmusic()
{
	for (int i = 0; i < m_musiclist.size(); i++)
	{
		Mix_FreeMusic(m_musiclist[i]);
	}
	m_musiclist.clear();
	return true;
}

bool medialayer::freemusic(CTI_MUSIC musicref)
{
	bool result = false;
	for (int i = 0; i < m_musiclist.size(); i++)
	{
		if (m_musiclist[i] == (Mix_Music*)musicref)
		{
			Mix_FreeMusic(m_musiclist[i]);
			m_musiclist.erase(m_musiclist.begin() + i);
			result = true;
		}
	}

	return result;
}

bool medialayer::playmusic(CTI_MUSIC musicref)
{
	bool result = false;
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic((Mix_Music*)musicref, -1);
		result = true;
	}

	return result;
}

bool medialayer::stopmusic()
{
	Mix_HaltMusic();
	return true;
}

bool medialayer::pausemusic()
{
	if (Mix_PausedMusic() == 0)
	{
		Mix_ResumeMusic();
	}

	return true;
}

bool medialayer::resumemusic()
{
	if (Mix_PausedMusic() == 1)
	{
		Mix_PauseMusic();
	}

	return true;
}

bool medialayer::addsound(std::string wavfile, CTI_SOUND* soundref)
{
	bool result = false;

	*soundref = (CTI_SOUND)Mix_LoadWAV(wavfile.c_str());
	if (*soundref)
	{
		m_soundlist.push_back((Mix_Chunk*)*soundref);
		result = true;
	}

	return result;
}

bool medialayer::freeallsound()
{
	for (int i = 0; i < m_soundlist.size(); i++)
	{
		Mix_FreeChunk(m_soundlist[i]);
	}
	m_soundlist.clear();
	return true;
}

bool medialayer::freesound(CTI_SOUND soundref)
{
	bool result = false;
	for (int i = 0; i < m_soundlist.size(); i++)
	{
		if (m_soundlist[i] == (Mix_Chunk*)soundref)
		{
			Mix_FreeChunk(m_soundlist[i]);
			m_soundlist.erase(m_soundlist.begin() + i);
			result = true;
		}
	}

	return result;
}

bool medialayer::playsound(CTI_SOUND soundref)
{
	bool result = false;
	if (soundref)
	{
		Mix_PlayChannel(-1, (Mix_Chunk*)soundref, 0);
		result = true;
	}

	return result;
}




/*
bool medialayer::getimagesize(void* imageref, vec2d* size)
{
	bool result = false;
	if (imageref && size)
	{
		size->setx(al_get_bitmap_width((ALLEGRO_BITMAP*)imageref));
		size->sety(al_get_bitmap_height((ALLEGRO_BITMAP*)imageref));
		result = true;
	}

	return result;
}

bool medialayer::addwave(const char* wavefile, void** waveref)
{
	bool result = false;

	if (m_wavelist.last)
	{
		m_wavelist.last->next = new wavenode;
		if (m_wavelist.last->next)
		{
			m_wavelist.last = m_wavelist.last->next;
			m_wavelist.last->wave = al_load_sample(wavefile);
			m_wavelist.last->sampid = NULL;
			if (m_imagelist.last->image)
			{
				*waveref = m_imagelist.last->image;
				result = true;
			}
		}
	}
	else  // first == NULL;
	{
		m_wavelist.first = new wavenode;

		if (m_wavelist.first)
		{
			m_wavelist.last = m_wavelist.first;
			m_wavelist.last->wave = al_load_sample(wavefile);
			m_wavelist.last->sampid = NULL;
			if (m_imagelist.last->image)
			{
				*waveref = m_wavelist.last;
				result = true;
			}
		}
	}
	return result;
}

bool medialayer::freeallwaves()
{
	m_wavelist.clearwholelist();
	return true;
}

bool medialayer::freewave(void* waveref)
{
	wavenode* node = (wavenode*)waveref;
	return m_wavelist.clearsingleitem((ALLEGRO_SAMPLE*)(node->wave));
}

bool medialayer::playwave(void* waveref, bool loop)
{
#if USE_AUDIO
	if (enable_effects)
	{
		wavenode* node = (wavenode*)waveref;
		ALLEGRO_PLAYMODE mode;
		if (loop)
			mode = ALLEGRO_PLAYMODE_LOOP;
		else
			mode = ALLEGRO_PLAYMODE_ONCE;

		al_play_sample((ALLEGRO_SAMPLE*)(node->wave), volume_main, 0.0, 1.0, mode, node->sampid);
	}
#endif 
	return true;
}

bool medialayer::stopwave(void* waveref)
{
	wavenode* node = (wavenode*)waveref;
	if (node->sampid != NULL)
	{
		al_stop_sample(node->sampid);
		node->sampid = NULL;
	}
	return true;
}

bool medialayer::loadmusic(const char* musicfile)
{
#if USE_AUDIO
	bool result = false;
	m_playingmusic = false;

	music = al_load_audio_stream(musicfile, 4, 2048);

	if (music)
	{
		result = true;
		al_attach_audio_stream_to_mixer(music, al_get_default_mixer());
		al_set_audio_stream_playing(music, false);
	}

	return result;
#else
	return true;
#endif
}

bool medialayer::freemusic()
{
	if (music)
		al_set_audio_stream_playing(music, false);
	return true;
}

bool medialayer::playmusic()
{
	bool result = false;
	if (music)
	{
		al_set_audio_stream_playing(music, true);
		result = true;
	}
	return result;
}

bool medialayer::stopmusic()
{
	if (music)
		al_set_audio_stream_playing(music, false);
	return true;
}

bool medialayer::ismusicplaying()
{
	if (al_get_audio_stream_playing(music))
	{
		return true;
	}
	return false;
}

bool medialayer::getaudiooption(bool* music, bool* effects, float* volume)
{
	// TODO
	return false;
}

bool medialayer::setaudiooption(bool music, bool effects, float volume)
{
	// TODO
	return false;
}

bool medialayer::isescapepressed()
{
	if (event_main.type == ALLEGRO_EVENT_KEY_DOWN) ///look for keyboard events
	{
		if (event_main.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
		{
			return true;
		}
	}
	return false;
}

bool medialayer::iseventmaintimer()
{
	if (event_main.type == ALLEGRO_EVENT_TIMER)
	{
		return true;
	}
	return false;
}

bool medialayer::iseventkeydown()
{
	if (event_main.type == ALLEGRO_EVENT_KEY_DOWN) ///look for keyboard events
	{
		return true;
	}
	return false;
}

bool medialayer::iseventmousemotion()
{
	if (event_main.type == ALLEGRO_EVENT_MOUSE_AXES)
	{
		return true;
	}
	return false;
}

bool medialayer::iseventmousebutton()
{
	return (event_main.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN);
}

bool medialayer::iseventdisplayclosed()
{
	return (event_main.type == ALLEGRO_EVENT_DISPLAY_CLOSE);
}

bool medialayer::showmousecursor(bool enable)
{
	if (enable)
		al_show_mouse_cursor(display);
	else
		al_hide_mouse_cursor(display);

	return true;
}

bool medialayer::getkeycode(int* keycode)
{
	if (keycode)
		*keycode = event_main.keyboard.keycode;

	return true;
}


bool medialayer::getmouseposition(vec2d* mouse)
{
	*mouse = vec2d(event_main.mouse.x, event_main.mouse.y);
	return true;
}

bool medialayer::settexttodisplay(const char* text, vec2d* pos)
{
	bool result = false;

	int pos_x = pos->getx();
	int pos_y = pos->gety();

	if (font)
	{
		al_draw_text(font, al_map_rgb(128, 128, 128), pos_x + 2, pos_y + 2, ALLEGRO_ALIGN_CENTRE, text);
		al_draw_text(font, al_map_rgb(255, 255, 255), pos_x, pos_y, ALLEGRO_ALIGN_CENTRE, text);
		result = true;
	}

	return result;
}

bool medialayer::waitforevents()
{
	al_wait_for_event(event_queue, &event_main);
	return true;
}

uint32_t medialayer::getticks()
{
	return (uint32_t)floor(al_get_time() * 1000);
}
*/


