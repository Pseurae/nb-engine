#pragma once 

namespace tonic::input
{
enum Key : short
{
    /* Printable keys */
    TONIC_KEY_SPACE              = 32,
    TONIC_KEY_APOSTROPHE         = 39,  /* ' */
    TONIC_KEY_COMMA              = 44,  /* , */
    TONIC_KEY_MINUS              = 45,  /* - */
    TONIC_KEY_PERIOD             = 46,  /* . */
    TONIC_KEY_SLASH              = 47,  /* / */
    TONIC_KEY_0                  = 48,
    TONIC_KEY_1                  = 49,
    TONIC_KEY_2                  = 50,
    TONIC_KEY_3                  = 51,
    TONIC_KEY_4                  = 52,
    TONIC_KEY_5                  = 53,
    TONIC_KEY_6                  = 54,
    TONIC_KEY_7                  = 55,
    TONIC_KEY_8                  = 56,
    TONIC_KEY_9                  = 57,
    TONIC_KEY_SEMICOLON          = 59,  /* ; */
    TONIC_KEY_EQUAL              = 61,  /* = */
    TONIC_KEY_A                  = 65,
    TONIC_KEY_B                  = 66,
    TONIC_KEY_C                  = 67,
    TONIC_KEY_D                  = 68,
    TONIC_KEY_E                  = 69,
    TONIC_KEY_F                  = 70,
    TONIC_KEY_G                  = 71,
    TONIC_KEY_H                  = 72,
    TONIC_KEY_I                  = 73,
    TONIC_KEY_J                  = 74,
    TONIC_KEY_K                  = 75,
    TONIC_KEY_L                  = 76,
    TONIC_KEY_M                  = 77,
    TONIC_KEY_N                  = 78,
    TONIC_KEY_O                  = 79,
    TONIC_KEY_P                  = 80,
    TONIC_KEY_Q                  = 81,
    TONIC_KEY_R                  = 82,
    TONIC_KEY_S                  = 83,
    TONIC_KEY_T                  = 84,
    TONIC_KEY_U                  = 85,
    TONIC_KEY_V                  = 86,
    TONIC_KEY_W                  = 87,
    TONIC_KEY_X                  = 88,
    TONIC_KEY_Y                  = 89,
    TONIC_KEY_Z                  = 90,
    TONIC_KEY_LEFT_BRACKET       = 91,  /* [ */
    TONIC_KEY_BACKSLASH          = 92,  /* \ */
    TONIC_KEY_RIGHT_BRACKET      = 93,  /* ] */
    TONIC_KEY_GRAVE_ACCENT       = 96,  /* ` */
    TONIC_KEY_WORLD_1            = 161, /* non-US #1 */
    TONIC_KEY_WORLD_2            = 162, /* non-US #2 */

    /* Function keys */
    TONIC_KEY_ESCAPE             = 256,
    TONIC_KEY_ENTER              = 257,
    TONIC_KEY_TAB                = 258,
    TONIC_KEY_BACKSPACE          = 259,
    TONIC_KEY_INSERT             = 260,
    TONIC_KEY_DELETE             = 261,
    TONIC_KEY_RIGHT              = 262,
    TONIC_KEY_LEFT               = 263,
    TONIC_KEY_DOWN               = 264,
    TONIC_KEY_UP                 = 265,
    TONIC_KEY_PAGE_UP            = 266,
    TONIC_KEY_PAGE_DOWN          = 267,
    TONIC_KEY_HOME               = 268,
    TONIC_KEY_END                = 269,
    TONIC_KEY_CAPS_LOCK          = 280,
    TONIC_KEY_SCROLL_LOCK        = 281,
    TONIC_KEY_NUM_LOCK           = 282,
    TONIC_KEY_PRINT_SCREEN       = 283,
    TONIC_KEY_PAUSE              = 284,
    TONIC_KEY_F1                 = 290,
    TONIC_KEY_F2                 = 291,
    TONIC_KEY_F3                 = 292,
    TONIC_KEY_F4                 = 293,
    TONIC_KEY_F5                 = 294,
    TONIC_KEY_F6                 = 295,
    TONIC_KEY_F7                 = 296,
    TONIC_KEY_F8                 = 297,
    TONIC_KEY_F9                 = 298,
    TONIC_KEY_F10                = 299,
    TONIC_KEY_F11                = 300,
    TONIC_KEY_F12                = 301,
    TONIC_KEY_F13                = 302,
    TONIC_KEY_F14                = 303,
    TONIC_KEY_F15                = 304,
    TONIC_KEY_F16                = 305,
    TONIC_KEY_F17                = 306,
    TONIC_KEY_F18                = 307,
    TONIC_KEY_F19                = 308,
    TONIC_KEY_F20                = 309,
    TONIC_KEY_F21                = 310,
    TONIC_KEY_F22                = 311,
    TONIC_KEY_F23                = 312,
    TONIC_KEY_F24                = 313,
    TONIC_KEY_F25                = 314,
    TONIC_KEY_KP_0               = 320,
    TONIC_KEY_KP_1               = 321,
    TONIC_KEY_KP_2               = 322,
    TONIC_KEY_KP_3               = 323,
    TONIC_KEY_KP_4               = 324,
    TONIC_KEY_KP_5               = 325,
    TONIC_KEY_KP_6               = 326,
    TONIC_KEY_KP_7               = 327,
    TONIC_KEY_KP_8               = 328,
    TONIC_KEY_KP_9               = 329,
    TONIC_KEY_KP_DECIMAL         = 330,
    TONIC_KEY_KP_DIVIDE          = 331,
    TONIC_KEY_KP_MULTIPLY        = 332,
    TONIC_KEY_KP_SUBTRACT        = 333,
    TONIC_KEY_KP_ADD             = 334,
    TONIC_KEY_KP_ENTER           = 335,
    TONIC_KEY_KP_EQUAL           = 336,
    TONIC_KEY_LEFT_SHIFT         = 340,
    TONIC_KEY_LEFT_CONTROL       = 341,
    TONIC_KEY_LEFT_ALT           = 342,
    TONIC_KEY_LEFT_SUPER         = 343,
    TONIC_KEY_RIGHT_SHIFT        = 344,
    TONIC_KEY_RIGHT_CONTROL      = 345,
    TONIC_KEY_RIGHT_ALT          = 346,
    TONIC_KEY_RIGHT_SUPER        = 347,
    TONIC_KEY_MENU               = 348,
    TONIC_KEY_COUNT
};

enum Actions : unsigned char
{
    TONIC_ACTION_RELEASE,
    TONIC_ACTION_PRESS,
    TONIC_ACTION_REPEAT,
};

enum Mods : unsigned char
{
    TONIC_ACTION_SHIFT = 0x0001,
    TONIC_ACTION_CONTROL = 0x0002,
    TONIC_ACTION_ALT = 0x0004,
    TONIC_ACTION_SUPER = 0x0008,
    TONIC_ACTION_CAPSLOCK = 0x0010,
    TONIC_ACTION_NUMLOCK = 0x0020,
};

enum MouseButton : unsigned char
{
    TONIC_MOUSEBUTTON_LEFT,
    TONIC_MOUSEBUTTON_RIGHT,
    TONIC_MOUSEBUTTON_MIDDLE,
    TONIC_MOUSEBUTTON_COUNT,
};
}
