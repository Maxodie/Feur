#pragma once
#pragma once

//Key Codes imported from SDL2

#define FE_KEYCODE_UNKNOWN  0

/**
 *  \name Usage page 0x07
 *
 *  These values are from usage page 0x07 (USB keyboard page).
 */
 /* @{ */

#define    FE_KEYCODE_A  4
#define    FE_KEYCODE_B  5
#define    FE_KEYCODE_C  6
#define    FE_KEYCODE_D  7
#define    FE_KEYCODE_E  8
#define    FE_KEYCODE_F  9
#define    FE_KEYCODE_G  10
#define    FE_KEYCODE_H  11
#define    FE_KEYCODE_I  12
#define    FE_KEYCODE_J  13
#define    FE_KEYCODE_K  14
#define    FE_KEYCODE_L  15
#define    FE_KEYCODE_M  16
#define    FE_KEYCODE_N  17
#define    FE_KEYCODE_O  18
#define    FE_KEYCODE_P  19
#define    FE_KEYCODE_Q  20
#define    FE_KEYCODE_R  21
#define    FE_KEYCODE_S  22
#define    FE_KEYCODE_T  23
#define    FE_KEYCODE_U  24
#define    FE_KEYCODE_V  25
#define    FE_KEYCODE_W  26
#define    FE_KEYCODE_X  27
#define    FE_KEYCODE_Y  28
#define    FE_KEYCODE_Z  29

#define    FE_KEYCODE_1  30
#define    FE_KEYCODE_2  31
#define    FE_KEYCODE_3  32
#define    FE_KEYCODE_4  33
#define    FE_KEYCODE_5  34
#define    FE_KEYCODE_6  35
#define    FE_KEYCODE_7  36
#define    FE_KEYCODE_8  37
#define    FE_KEYCODE_9  38
#define    FE_KEYCODE_0  39

#define    FE_KEYCODE_RETURN  40
#define    FE_KEYCODE_ESCAPE  41
#define    FE_KEYCODE_BACKSPACE  42
#define    FE_KEYCODE_TAB  43
#define    FE_KEYCODE_SPACE  44

#define    FE_KEYCODE_MINUS  45
#define    FE_KEYCODE_EQUALS  46
#define    FE_KEYCODE_LEFTBRACKET  47
#define    FE_KEYCODE_RIGHTBRACKET  48
#define    FE_KEYCODE_BACKSLASH  49 /**< Located at the lower left of the return
                                  *   key on ISO keyboards and at the right end
                                  *   of the QWERTY row on ANSI keyboards.
                                  *   Produces REVERSE SOLIDUS (backslash) and
                                  *   VERTICAL LINE in a US layout REVERSE
                                  *   SOLIDUS and VERTICAL LINE in a UK Mac
                                  *   layout NUMBER SIGN and TILDE in a UK
                                  *   Windows layout DOLLAR SIGN and POUND SIGN
                                  *   in a Swiss German layout NUMBER SIGN and
                                  *   APOSTROPHE in a German layout GRAVE
                                  *   ACCENT and POUND SIGN in a French Mac
                                  *   layout and ASTERISK and MICRO SIGN in a
                                  *   French Windows layout.
                                  */
#define    FE_KEYCODE_NONUSHASH  50 /**< ISO USB keyboards actually use this code
                                  *   instead of 49 for the same key but all
                                  *   OSes I've seen treat the two codes
                                  *   identically. So as an implementor unless
                                  *   your keyboard generates both of those
                                  *   codes and your OS treats them differently
                                  *   you should generate FE_KEYCODE_BACKSLASH
                                  *   instead of this code. As a user you
                                  *   should not rely on this code because SDL
                                  *   will never generate it with most (all?)
                                  *   keyboards.
                                  */
#define    FE_KEYCODE_SEMICOLON  51
#define    FE_KEYCODE_APOSTROPHE  52
#define    FE_KEYCODE_GRAVE  53 /**< Located in the top left corner (on both ANSI
                              *   and ISO keyboards). Produces GRAVE ACCENT and
                              *   TILDE in a US Windows layout and in US and UK
                              *   Mac layouts on ANSI keyboards GRAVE ACCENT
                              *   and NOT SIGN in a UK Windows layout SECTION
                              *   SIGN and PLUS-MINUS SIGN in US and UK Mac
                              *   layouts on ISO keyboards SECTION SIGN and
                              *   DEGREE SIGN in a Swiss German layout (Mac:
                              *   only on ISO keyboards) CIRCUMFLEX ACCENT and
                              *   DEGREE SIGN in a German layout (Mac: only on
                              *   ISO keyboards) SUPERSCRIPT TWO and TILDE in a
                              *   French Windows layout COMMERCIAL AT and
                              *   NUMBER SIGN in a French Mac layout on ISO
                              *   keyboards and LESS-THAN SIGN and GREATER-THAN
                              *   SIGN in a Swiss German German or French Mac
                              *   layout on ANSI keyboards.
                              */
#define    FE_KEYCODE_COMMA  54
#define    FE_KEYCODE_PERIOD  55
#define    FE_KEYCODE_SLASH  56

#define    FE_KEYCODE_CAPSLOCK  57

#define    FE_KEYCODE_F1  58
#define    FE_KEYCODE_F2  59
#define    FE_KEYCODE_F3  60
#define    FE_KEYCODE_F4  61
#define    FE_KEYCODE_F5  62
#define    FE_KEYCODE_F6  63
#define    FE_KEYCODE_F7  64
#define    FE_KEYCODE_F8  65
#define    FE_KEYCODE_F9  66
#define    FE_KEYCODE_F10  67
#define    FE_KEYCODE_F11  68
#define    FE_KEYCODE_F12  69

#define    FE_KEYCODE_PRINTSCREEN  70
#define    FE_KEYCODE_SCROLLLOCK  71
#define    FE_KEYCODE_PAUSE  72
#define    FE_KEYCODE_INSERT  73 /**< insert on PC help on some Mac keyboards (but does send code 73 not 117) */

#define    FE_KEYCODE_HOME  74
#define    FE_KEYCODE_PAGEUP  75
#define    FE_KEYCODE_DELETE  76
#define    FE_KEYCODE_END  77
#define    FE_KEYCODE_PAGEDOWN  78
#define    FE_KEYCODE_RIGHT  79
#define    FE_KEYCODE_LEFT  80
#define    FE_KEYCODE_DOWN  81
#define    FE_KEYCODE_UP  82

#define    FE_KEYCODE_NUMLOCKCLEAR  83 /**< num lock on PC clear on Mac keyboards */

#define    FE_KEYCODE_KP_DIVIDE  84
#define    FE_KEYCODE_KP_MULTIPLY  85
#define    FE_KEYCODE_KP_MINUS  86
#define    FE_KEYCODE_KP_PLUS  87
#define    FE_KEYCODE_KP_ENTER  88
#define    FE_KEYCODE_KP_1  89
#define    FE_KEYCODE_KP_2  90
#define    FE_KEYCODE_KP_3  91
#define    FE_KEYCODE_KP_4  92
#define    FE_KEYCODE_KP_5  93
#define    FE_KEYCODE_KP_6  94
#define    FE_KEYCODE_KP_7  95
#define    FE_KEYCODE_KP_8  96
#define    FE_KEYCODE_KP_9  97
#define    FE_KEYCODE_KP_0  98
#define    FE_KEYCODE_KP_PERIOD  99

#define    FE_KEYCODE_NONUSBACKSLASH  100 /**< This is the additional key that ISO
                                        *   keyboards have over ANSI ones
                                        *   located between left shift and Y.
                                        *   Produces GRAVE ACCENT and TILDE in a
                                        *   US or UK Mac layout REVERSE SOLIDUS
                                        *   (backslash) and VERTICAL LINE in a
                                        *   US or UK Windows layout and
                                        *   LESS-THAN SIGN and GREATER-THAN SIGN
                                        *   in a Swiss German German or French
                                        *   layout. */
#define    FE_KEYCODE_APPLICATION  101 /**< windows contextual menu compose */
#define    FE_KEYCODE_POWER  102 /**< The USB document says this is a status flag
                               *   not a physical key - but some Mac keyboards
                               *   do have a power key. */
#define    FE_KEYCODE_KP_EQUALS  103
#define    FE_KEYCODE_F13  104
#define    FE_KEYCODE_F14  105
#define    FE_KEYCODE_F15  106
#define    FE_KEYCODE_F16  107
#define    FE_KEYCODE_F17  108
#define    FE_KEYCODE_F18  109
#define    FE_KEYCODE_F19  110
#define    FE_KEYCODE_F20  111
#define    FE_KEYCODE_F21  112
#define    FE_KEYCODE_F22  113
#define    FE_KEYCODE_F23  114
#define    FE_KEYCODE_F24  115
#define    FE_KEYCODE_EXECUTE  116
#define    FE_KEYCODE_HELP  117
#define    FE_KEYCODE_MENU  118
#define    FE_KEYCODE_SELECT  119
#define    FE_KEYCODE_STOP  120
#define    FE_KEYCODE_AGAIN  121   /**< redo */
#define    FE_KEYCODE_UNDO  122
#define    FE_KEYCODE_CUT  123
#define    FE_KEYCODE_COPY  124
#define    FE_KEYCODE_PASTE  125
#define    FE_KEYCODE_FIND  126
#define    FE_KEYCODE_MUTE  127
#define    FE_KEYCODE_VOLUMEUP  128
#define    FE_KEYCODE_VOLUMEDOWN  129
                               /* not sure whether there's a reason to enable these */
                               /*     FE_KEYCODE_LOCKINGCAPSLOCK  130  */
                               /*     FE_KEYCODE_LOCKINGNUMLOCK  131 */
                               /*     FE_KEYCODE_LOCKINGSCROLLLOCK  132 */
#define    FE_KEYCODE_KP_COMMA  133
#define    FE_KEYCODE_KP_EQUALSAS400  134

#define    FE_KEYCODE_INTERNATIONAL1  135 /**< used on Asian keyboards see
                                            footnotes in USB doc */
#define    FE_KEYCODE_INTERNATIONAL2  136
#define    FE_KEYCODE_INTERNATIONAL3  137 /**< Yen */
#define    FE_KEYCODE_INTERNATIONAL4  138
#define    FE_KEYCODE_INTERNATIONAL5  139
#define    FE_KEYCODE_INTERNATIONAL6  140
#define    FE_KEYCODE_INTERNATIONAL7  141
#define    FE_KEYCODE_INTERNATIONAL8  142
#define    FE_KEYCODE_INTERNATIONAL9  143
#define    FE_KEYCODE_LANG1  144 /**< Hangul/English toggle */
#define    FE_KEYCODE_LANG2  145 /**< Hanja conversion */
#define    FE_KEYCODE_LANG3  146 /**< Katakana */
#define    FE_KEYCODE_LANG4  147 /**< Hiragana */
#define    FE_KEYCODE_LANG5  148 /**< Zenkaku/Hankaku */
#define    FE_KEYCODE_LANG6  149 /**< reserved */
#define    FE_KEYCODE_LANG7  150 /**< reserved */
#define    FE_KEYCODE_LANG8  151 /**< reserved */
#define    FE_KEYCODE_LANG9  152 /**< reserved */

#define    FE_KEYCODE_ALTERASE  153 /**< Erase-Eaze */
#define    FE_KEYCODE_SYSREQ  154
#define    FE_KEYCODE_CANCEL  155
#define    FE_KEYCODE_CLEAR  156
#define    FE_KEYCODE_PRIOR  157
#define    FE_KEYCODE_RETURN2  158
#define    FE_KEYCODE_SEPARATOR  159
#define    FE_KEYCODE_OUT  160
#define    FE_KEYCODE_OPER  161
#define    FE_KEYCODE_CLEARAGAIN  162
#define    FE_KEYCODE_CRSEL  163
#define    FE_KEYCODE_EXSEL  164

#define    FE_KEYCODE_KP_00  176
#define    FE_KEYCODE_KP_000  177
#define    FE_KEYCODE_THOUSANDSSEPARATOR  178
#define    FE_KEYCODE_DECIMALSEPARATOR  179
#define    FE_KEYCODE_CURRENCYUNIT  180
#define    FE_KEYCODE_CURRENCYSUBUNIT  181
#define    FE_KEYCODE_KP_LEFTPAREN  182
#define    FE_KEYCODE_KP_RIGHTPAREN  183
#define    FE_KEYCODE_KP_LEFTBRACE  184
#define    FE_KEYCODE_KP_RIGHTBRACE  185
#define    FE_KEYCODE_KP_TAB  186
#define    FE_KEYCODE_KP_BACKSPACE  187
#define    FE_KEYCODE_KP_A  188
#define    FE_KEYCODE_KP_B  189
#define    FE_KEYCODE_KP_C  190
#define    FE_KEYCODE_KP_D  191
#define    FE_KEYCODE_KP_E  192
#define    FE_KEYCODE_KP_F  193
#define    FE_KEYCODE_KP_XOR  194
#define    FE_KEYCODE_KP_POWER  195
#define    FE_KEYCODE_KP_PERCENT  196
#define    FE_KEYCODE_KP_LESS  197
#define    FE_KEYCODE_KP_GREATER  198
#define    FE_KEYCODE_KP_AMPERSAND  199
#define    FE_KEYCODE_KP_DBLAMPERSAND  200
#define    FE_KEYCODE_KP_VERTICALBAR  201
#define    FE_KEYCODE_KP_DBLVERTICALBAR  202
#define    FE_KEYCODE_KP_COLON  203
#define    FE_KEYCODE_KP_HASH  204
#define    FE_KEYCODE_KP_SPACE  205
#define    FE_KEYCODE_KP_AT  206
#define    FE_KEYCODE_KP_EXCLAM  207
#define    FE_KEYCODE_KP_MEMSTORE  208
#define    FE_KEYCODE_KP_MEMRECALL  209
#define    FE_KEYCODE_KP_MEMCLEAR  210
#define    FE_KEYCODE_KP_MEMADD  211
#define    FE_KEYCODE_KP_MEMSUBTRACT  212
#define    FE_KEYCODE_KP_MEMMULTIPLY  213
#define    FE_KEYCODE_KP_MEMDIVIDE  214
#define    FE_KEYCODE_KP_PLUSMINUS  215
#define    FE_KEYCODE_KP_CLEAR  216
#define    FE_KEYCODE_KP_CLEARENTRY  217
#define    FE_KEYCODE_KP_BINARY  218
#define    FE_KEYCODE_KP_OCTAL  219
#define    FE_KEYCODE_KP_DECIMAL  220
#define    FE_KEYCODE_KP_HEXADECIMAL  221

#define    FE_KEYCODE_LCTRL  224
#define    FE_KEYCODE_LSHIFT  225
#define    FE_KEYCODE_LALT  226 /**< alt option */
#define    FE_KEYCODE_LGUI  227 /**< windows command (apple) meta */
#define    FE_KEYCODE_RCTRL  228
#define    FE_KEYCODE_RSHIFT  229
#define    FE_KEYCODE_RALT  230 /**< alt gr option */
#define    FE_KEYCODE_RGUI  231 /**< windows command (apple) meta */

#define    FE_KEYCODE_MODE  257    /**< I'm not sure if this is really not covered
                                 *   by any of the above but since there's a
                                 *   special KMOD_MODE for it I'm adding it here
                                 */

                                 /* @} *//* Usage page 0x07 */

                                 /**
                                  *  \name Usage page 0x0C
                                  *
                                  *  These values are mapped from usage page 0x0C (USB consumer page).
                                  */
                                  /* @{ */

#define    FE_KEYCODE_AUDIONEXT  258
#define    FE_KEYCODE_AUDIOPREV  259
#define    FE_KEYCODE_AUDIOSTOP  260
#define    FE_KEYCODE_AUDIOPLAY  261
#define    FE_KEYCODE_AUDIOMUTE  262
#define    FE_KEYCODE_MEDIASELECT  263
#define    FE_KEYCODE_WWW  264
#define    FE_KEYCODE_MAIL  265
#define    FE_KEYCODE_CALCULATOR  266
#define    FE_KEYCODE_COMPUTER  267
#define    FE_KEYCODE_AC_SEARCH  268
#define    FE_KEYCODE_AC_HOME  269
#define    FE_KEYCODE_AC_BACK  270
#define    FE_KEYCODE_AC_FORWARD  271
#define    FE_KEYCODE_AC_STOP  272
#define    FE_KEYCODE_AC_REFRESH  273
#define    FE_KEYCODE_AC_BOOKMARKS  274

    /* @} *//* Usage page 0x0C */

    /**
     *  \name Walther keys
     *
     *  These are values that Christian Walther added (for mac keyboard?).
     */
     /* @{ */

#define    FE_KEYCODE_BRIGHTNESSDOWN  275
#define    FE_KEYCODE_BRIGHTNESSUP  276
#define    FE_KEYCODE_DISPLAYSWITCH  277 /**< display mirroring/dual display switch video mode switch */

#define    FE_KEYCODE_KBDILLUMTOGGLE  278
#define    FE_KEYCODE_KBDILLUMDOWN  279
#define    FE_KEYCODE_KBDILLUMUP  280
#define    FE_KEYCODE_EJECT  281
#define    FE_KEYCODE_SLEEP  282

#define    FE_KEYCODE_APP1  283
#define    FE_KEYCODE_APP2  284

    /* @} *//* Walther keys */

    /**
     *  \name Usage page 0x0C (additional media keys)
     *
     *  These values are mapped from usage page 0x0C (USB consumer page).
     */
     /* @{ */

#define    FE_KEYCODE_AUDIOREWIND  285
#define    FE_KEYCODE_AUDIOFASTFORWARD  286

    /* @} *//* Usage page 0x0C (additional media keys) */

    /* Add any other keys here. */