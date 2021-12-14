
#ifdef WIN32
#include <Windows.h>
#endif

#include <string>

#include "libcti.h"
#include "medialayer.h"
#include "debuglog.h"

#if WIN32

HKEY OpenKey(HKEY hRootKey, const char* stringKey)
{
	HKEY hKey;

	wchar_t wtext[64];
	size_t retval = 64;
	mbstowcs_s(&retval, wtext, stringKey, strlen(stringKey) + 1);
	LPWSTR ptr = wtext;

	RegOpenKeyEx(hRootKey, ptr, NULL, KEY_READ, &hKey);
	return hKey;
}

// Set the variable to some data
void SetValue(HKEY hKey, LPCTSTR lpValue, DWORD data)
{
	RegSetValueEx(hKey, lpValue, NULL, REG_DWORD, (LPBYTE)&data, sizeof(DWORD));
}

DWORD GetDWORDValue(HKEY hKey, LPCTSTR lpValue)
{
	DWORD data;
	DWORD size = sizeof(data);
	DWORD type = REG_DWORD;
	RegQueryValueEx(hKey, lpValue, NULL, &type, (LPBYTE)&data, &size);

	return data;
}

#endif



static medialayer* ml = nullptr;

debuglog			g_debuglog;
char				g_logtext[256];

bool cti_initialize(std::string windowname, int screenx, int screeny)
{
	bool result = false;

#ifdef WIN32
	HKEY hKey = OpenKey(HKEY_LOCAL_MACHINE, "SOFTWARE\\Crossturn\\libcti");
	DWORD logenable = GetDWORDValue(hKey, L"apilog.enable");

#endif
	if (logenable > 0)
	{
		g_debuglog.enablelog("c:\\temp\\libctilog.txt");

		sprintf_s(g_logtext, 256, "%s() -> windowname=%s screen=%dx%d", __func__, windowname.c_str(), screenx, screeny);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml == nullptr)
	{
		ml = new medialayer;

		if (ml)
		{
			result = ml->initialize(windowname, screenx, screeny);
		}
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_uninitialize()
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->uninitialize();
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_getscreensize(CVEC2* size)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		int cx = 0;
		int cy = 0;
		result = ml->getscreensize(&cx, &cy);
		if (result)
			*size = CVEC2(cx, cy);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	return result;
}

bool cti_pollevent(EVENTTYPE* eventtype)
{
	bool result = false;

//	if (g_debuglog.isactive())
//	{
//		sprintf_s(g_logtext, 256, "%s() ->", __func__);
//		g_debuglog.writeentrytolog(g_logtext);
//	}

	if (ml)
	{
		result = ml->pollevent(eventtype);
	}

//	if (g_debuglog.isactive())
//	{
//		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
//		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
//		g_debuglog.writeentrytolog(g_logtext);
//	}

	return result;
}

bool cti_geteventkey(EVENTKEY* eventkey)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->geteventkey(eventkey);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_getmouseposition(CVEC2* pos)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		int cx = 0;
		int cy = 0;
		result = ml->getmouseposition(&cx, &cy);
		if (result)
			*pos = CVEC2(cx, cy);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

int cti_getticks()
{
	int ms = -1;

//	if (g_debuglog.isactive())
//	{
//		sprintf_s(g_logtext, 256, "%s() ->", __func__);
//		g_debuglog.writeentrytolog(g_logtext);
//	}

	if (ml)
	{
		ms = ml->getticks();
	}

//	if (g_debuglog.isactive())
//	{
//		if (ms > 0)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
//		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
//		g_debuglog.writeentrytolog(g_logtext);
//	}
	return ms;
}

bool cti_sleep(int milliseconds)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->sleep(milliseconds);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_drawline(CVEC2 a, CVEC2 b, CCOLOR col)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->drawline(a.cx, a.cy, b.cx, b.cy, col.r, col.g, col.b);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}


bool cti_addimage(std::string bmpfile, CTI_IMAGE* imageref, bool transparentbackground)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		void* imgref = nullptr;
		result = ml->addimage(bmpfile, (CTI_IMAGE*)&imgref, transparentbackground);
		if (result)
			*imageref = imgref;

	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_arraytoimage(uint32_t* pixels, CTI_IMAGE* imageref, int pitch)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		void* imgref = nullptr;
		result = ml->arraytoimage(pixels, (CTI_IMAGE*)&imgref, pitch);
		if (result)
			*imageref = imgref;

	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_freeallimages()
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->freeallimages();
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_freeimage(CTI_IMAGE imageref)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->freeimage(imageref);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}
/*
bool cti_setimagetodisplay(CTI_IMAGE imageref, int pos_x, int pos_y)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->setimagetodisplay(imageref, pos_x, pos_y);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}
*/
bool cti_setimagetodisplay(CTI_IMAGE imageref, CVEC2 pos, CRECT* rect)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->setimagetodisplay(imageref, pos.cx, pos.cy, rect);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}
/*
bool cti_setimagetodisplay_adv(CTI_IMAGE imageref, int pos_x, int pos_y, double angle)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->setimagetodisplay_adv(imageref, pos_x, pos_y, angle);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}
*/
bool cti_setimagetodisplay_adv(CTI_IMAGE imageref, CVEC2 pos, double angle)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->setimagetodisplay_adv(imageref, pos.cx, pos.cy, angle);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

_DLLFUNC bool cti_getimagesize(CTI_IMAGE imageref, CVEC2* size)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		int cx = 0;
		int cy = 0;
		result = ml->getimagesize(imageref, &cx, &cy);
		if (result)
		{
			*size = CVEC2(cx, cy);
		}
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_cleardisplay()
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->cleardisplay();
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_displayimages()
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->displayimages();
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_addfont(std::string fontfile, int fontsize, CTI_FONT* fontref)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->addfont(fontfile, fontsize, fontref);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_freeallfonts()
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->freeallfonts();
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_freefont(CTI_FONT fontref)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->freefont(fontref);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_texttoimage(CTI_IMAGE* imageref, CTI_FONT fontref, std::string text, CCOLOR col)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->texttoimage(imageref, fontref, text, col);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_addmusic(std::string wavfile, CTI_MUSIC* musicref)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->addmusic(wavfile, musicref);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_freeallmusic()
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->freeallmusic();
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_freemusic(CTI_MUSIC musicref)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->freemusic(musicref);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_playmusic(CTI_MUSIC musicref)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->playmusic(musicref);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_stopmusic()
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->stopmusic();
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_pausemusic()
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->pausemusic();
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_resumemusic()
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->resumemusic();
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_setmusicvolume(int volume)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->setmusicvolume(volume);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_addsound(std::string wavfile, CTI_SOUND* soundref)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->addsound(wavfile, soundref);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_freeallsound()
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->freeallsound();
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_freesound(CTI_SOUND soundref)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->freesound(soundref);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_playsound(CTI_SOUND soundref)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->playsound(soundref);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}

bool cti_setsoundvolume(int volume, int channel)
{
	bool result = false;

	if (g_debuglog.isactive())
	{
		sprintf_s(g_logtext, 256, "%s() ->", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}

	if (ml)
	{
		result = ml->setsoundvolume(volume, channel);
	}

	if (g_debuglog.isactive())
	{
		if (result)	sprintf_s(g_logtext, 256, "%s() OK", __func__);
		else		sprintf_s(g_logtext, 256, "%s() NG", __func__);
		g_debuglog.writeentrytolog(g_logtext);
	}
	return result;
}


