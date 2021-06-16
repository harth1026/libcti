#pragma once

// interface for LIBCTI

#include <string>

#ifdef WIN32
	#ifdef	__cplusplus
		#define _DLLFUNC	extern "C" __declspec(dllexport)
	#else
		#define _DLLFUNC	__declspec(dllexport)
	#endif
#else	// WIN32
	#define _DLLFUNC	
#endif

#if defined(_MSC_VER)
	#ifdef LIBCTI_EXPORTS
		#define _DLLSTDCALL
	#else
		#define _DLLSTDCALL __declspec(dllimport)
	#endif
#elif defined(__GNUC__)
	//  GCC
	#ifdef LIBCTI_EXPORTS
		#define _DLLSTDCALL __attribute__ ((visibility("default")))
	#else
		#define _DLLSTDCALL 
	#endif
#else
	//  do nothing and hope for the best?
	#define _DLLSTDCALL 
	#pragma warning Unknown dynamic link export/import semantics.
#endif


enum class EVENTTYPE
{
	E_QUIT = 0x100, /**< User-requested quit */
	/* Window events */
	E_WINDOWEVENT = 0x200, /**< Window state change */
	E_SYSWMEVENT,             /**< System specific event */

	/* Keyboard events */
	E_KEYDOWN = 0x300, /**< Key pressed */
	E_KEYUP,                  /**< Key released */
	E_TEXTEDITING,            /**< Keyboard text editing (composition) */
	E_TEXTINPUT,              /**< Keyboard text input */
	E_KEYMAPCHANGED,          /**< Keymap changed due to a system event such as an
	input language or keyboard layout change.
	*/

	/* Mouse events */
	E_MOUSEMOTION = 0x400, /**< Mouse moved */
	E_MOUSEBUTTONDOWN,        /**< Mouse button pressed */
	E_MOUSEBUTTONUP,          /**< Mouse button released */
	E_MOUSEWHEEL,             /**< Mouse wheel motion */

	/* Joystick events */
	E_JOYAXISMOTION = 0x600, /**< Joystick axis motion */
	E_JOYBALLMOTION,          /**< Joystick trackball motion */
	E_JOYHATMOTION,           /**< Joystick hat position change */
	E_JOYBUTTONDOWN,          /**< Joystick button pressed */
	E_JOYBUTTONUP,            /**< Joystick button released */
	E_JOYDEVICEADDED,         /**< A new joystick has been inserted into the system */
	E_JOYDEVICEREMOVED,       /**< An opened joystick has been removed */

	/* Game controller events */
	E_CONTROLLERAXISMOTION = 0x650, /**< Game controller axis motion */
	E_CONTROLLERBUTTONDOWN,          /**< Game controller button pressed */
	E_CONTROLLERBUTTONUP,            /**< Game controller button released */
	E_CONTROLLERDEVICEADDED,         /**< A new Game controller has been inserted into the system */
	E_CONTROLLERDEVICEREMOVED,       /**< An opened Game controller has been removed */
	E_CONTROLLERDEVICEREMAPPED,      /**< The controller mapping was updated */

	/* Touch events */
	E_FINGERDOWN = 0x700,
	E_FINGERUP,
	E_FINGERMOTION,

	/* Gesture events */
	E_DOLLARGESTURE = 0x800,
	E_DOLLARRECORD,
	E_MULTIGESTURE,

	/* Clipboard events */
	E_CLIPBOARDUPDATE = 0x900, /**< The clipboard changed */

	/* Drag and drop events */
	E_DROPFILE = 0x1000, /**< The system requests a file open */
	E_DROPTEXT,                 /**< text/plain drag-and-drop event */
	E_DROPBEGIN,                /**< A new set of drops is beginning (NULL filename) */
	E_DROPCOMPLETE,             /**< Current set of drops is now complete (NULL filename) */

	/* Audio hotplug events */
	E_AUDIODEVICEADDED = 0x1100, /**< A new audio device is available */
	E_AUDIODEVICEREMOVED,        /**< An audio device has been removed. */

	/* Render events */
	E_RENDER_TARGETS_RESET = 0x2000, /**< The render targets have been reset and their contents need to be updated */
	E_RENDER_DEVICE_RESET, /**< The device has been reset and all textures need to be recreated */

	/** Events ::E_USEREVENT through ::E_LASTEVENT are for your use,
	*  and should be allocated with E_RegisterEvents()
	*/
	E_USEREVENT = 0x8000,

	/**
	*  This last event is only for bounding internal arrays
	*/
	E_LASTEVENT = 0xFFFF
};

enum class EVENTKEY
{
    K_UNKNOWN = 0,

    K_RETURN = '\r',
    K_ESCAPE = '\033',
    K_BACKSPACE = '\b',
    K_TAB = '\t',
    K_SPACE = ' ',
    K_EXCLAIM = '!',
    K_QUOTEDBL = '"',
    K_HASH = '#',
    K_PERCENT = '%',
    K_DOLLAR = '$',
    K_AMPERSAND = '&',
    K_QUOTE = '\'',
    K_LEFTPAREN = '(',
    K_RIGHTPAREN = ')',
    K_ASTERISK = '*',
    K_PLUS = '+',
    K_COMMA = ',',
    K_MINUS = '-',
    K_PERIOD = '.',
    K_SLASH = '/',
    K_0 = '0',
    K_1 = '1',
    K_2 = '2',
    K_3 = '3',
    K_4 = '4',
    K_5 = '5',
    K_6 = '6',
    K_7 = '7',
    K_8 = '8',
    K_9 = '9',
    K_COLON = ':',
    K_SEMICOLON = ';',
    K_LESS = '<',
    K_EQUALS = '=',
    K_GREATER = '>',
    K_QUESTION = '?',
    K_AT = '@',
    /*
       Skip uppercase letters
     */
     K_LEFTBRACKET = '[',
     K_BACKSLASH = '\\',
     K_RIGHTBRACKET = ']',
     K_CARET = '^',
     K_UNDERSCORE = '_',
     K_BACKQUOTE = '`',
     K_a = 'a',
     K_b = 'b',
     K_c = 'c',
     K_d = 'd',
     K_e = 'e',
     K_f = 'f',
     K_g = 'g',
     K_h = 'h',
     K_i = 'i',
     K_j = 'j',
     K_k = 'k',
     K_l = 'l',
     K_m = 'm',
     K_n = 'n',
     K_o = 'o',
     K_p = 'p',
     K_q = 'q',
     K_r = 'r',
     K_s = 's',
     K_t = 't',
     K_u = 'u',
     K_v = 'v',
     K_w = 'w',
     K_x = 'x',
     K_y = 'y',
     K_z = 'z',

};

class CCOLOR
{
public:
	uint8_t r;
	uint8_t g;
	uint8_t b;

	CCOLOR() { r = 0; g = 0; b = 0; }
	CCOLOR(uint8_t ar, uint8_t ag, uint8_t ab) { r = ar; g = ag; b = ab; }
	CCOLOR(const CCOLOR& c) { r = c.r; g = c.g; b = c.b; }
};

class CVEC2
{
public:
	int cx;
	int cy;

	CVEC2() { cx = 0; cy = 0; }
	CVEC2(const CVEC2& b) { cx = b.cx; cy = b.cy; }
	CVEC2(int x, int y) { cx = x, cy = y; }
	~CVEC2() {}

	CVEC2 operator+(const CVEC2& b) { return CVEC2(this->cx + b.cx, this->cy + b.cy); }
	CVEC2 operator-(const CVEC2& b) { return CVEC2(this->cx - b.cx, this->cy - b.cy); }
	CVEC2 operator*(const int b)	{ return CVEC2(this->cx * b, this->cy * b); }
	CVEC2 operator/(const int b)	{ return CVEC2(this->cx / b, this->cy / b); }
	CVEC2 operator=(const CVEC2& b) { return CVEC2(this->cx = b.cx, this->cy = b.cy); }
	bool operator==(const CVEC2& b) { return (this->cx == b.cx) && (this->cy == b.cy); }
	bool operator!=(const CVEC2& b) { return (this->cx != b.cx) || (this->cy != b.cy); }
};

typedef void* CTI_IMAGE;
typedef void* CTI_MUSIC;
typedef void* CTI_SOUND;

// MANAGEMENT

_DLLFUNC bool cti_initialize(std::string windowname, int screenx, int screeny);
_DLLFUNC bool cti_uninitialize();
_DLLFUNC bool cti_getscreensize(CVEC2* size);

_DLLFUNC bool cti_pollevent(EVENTTYPE* eventtype);
_DLLFUNC bool cti_geteventkey(EVENTKEY* eventkey);
_DLLFUNC bool cti_getmouseposition(CVEC2* pos);
_DLLFUNC int  cti_getticks();
_DLLFUNC bool cti_sleep(int milliseconds);

// GRAPHICS

_DLLFUNC bool cti_drawline(CVEC2 a, CVEC2 b, CCOLOR col);
_DLLFUNC bool cti_addimage(std::string bmpfile, CTI_IMAGE* imageref, bool transparentbackground);
_DLLFUNC bool cti_arraytoimage(uint32_t* pixels, CTI_IMAGE* imageref, int pitch);
_DLLFUNC bool cti_freeallimages();
_DLLFUNC bool cti_freeimage(CTI_IMAGE imageref);
_DLLFUNC bool cti_setimagetodisplay(CTI_IMAGE imageref, CVEC2 pos);
_DLLFUNC bool cti_setimagetodisplay_adv(CTI_IMAGE imageref, CVEC2 pos, double angle);
_DLLFUNC bool cti_getimagesize(CTI_IMAGE imageref, CVEC2* size);

_DLLFUNC bool cti_setfont(std::string fontpath, int fontsize);
_DLLFUNC bool cti_settexttodisplay(std::string text, CVEC2 pos, CCOLOR col);

_DLLFUNC bool cti_cleardisplay();
_DLLFUNC bool cti_displayimages();

// AUDIO

_DLLFUNC bool cti_addmusic(std::string wavfile, CTI_MUSIC* musicref);
_DLLFUNC bool cti_freeallmusic();
_DLLFUNC bool cti_freemusic(CTI_MUSIC musicref);
_DLLFUNC bool cti_playmusic(CTI_MUSIC musicref);
_DLLFUNC bool cti_stopmusic();
_DLLFUNC bool cti_pausemusic();
_DLLFUNC bool cti_resumemusic();

_DLLFUNC bool cti_addsound(std::string wavfile, CTI_SOUND* soundref);
_DLLFUNC bool cti_freeallsound();
_DLLFUNC bool cti_freesound(CTI_SOUND soundref);
_DLLFUNC bool cti_playsound(CTI_SOUND soundref);

