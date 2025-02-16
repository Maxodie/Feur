#pragma once


typedef Uint16 FE_KeyCode;

/*! @ingroup input
 */
#define FE_KEYCODE_UNKNOWN            -1

 /*! @} */

/*! @defgroup keys Keyboard key tokens
 *  @brief Keyboard key tokens.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  These key codes are inspired by the _USB HID Usage Tables v1.12_ (p. 53-60),
 *  but re-arranged to map to 7-bit ASCII for printable keys (function keys are
 *  put in the 256+ range).
 *
 *  The naming of the key codes follow these rules:
 *   - The US keyboard layout is used
 *   - Names of printable alphanumeric characters are used (e.g. "A", "R",
 *     "3", etc.)
 *   - For non-alphanumeric characters, Unicode:ish names are used (e.g.
 *     "COMMA", "LEFT_SQUARE_BRACKET", etc.). Note that some names do not
 *     correspond to the Unicode standard (usually for brevity)
 *   - Keys that lack a clear US mapping are named "WORLD_x"
 *   - For non-printable keys, custom names are used (e.g. "F4",
 *     "BACKSPACE", etc.)
 *
 *  @ingroup input
 *  @{
 */

 /* Printable keys */
#define FE_KEYCODE_SPACE              32
#define FE_KEYCODE_APOSTROPHE         39  /* ' */
#define FE_KEYCODE_COMMA              44  /* , */
#define FE_KEYCODE_MINUS              45  /* - */
#define FE_KEYCODE_PERIOD             46  /* . */
#define FE_KEYCODE_SLASH              47  /* / */
#define FE_KEYCODE_0                  48
#define FE_KEYCODE_1                  49
#define FE_KEYCODE_2                  50
#define FE_KEYCODE_3                  51
#define FE_KEYCODE_4                  52
#define FE_KEYCODE_5                  53
#define FE_KEYCODE_6                  54
#define FE_KEYCODE_7                  55
#define FE_KEYCODE_8                  56
#define FE_KEYCODE_9                  57
#define FE_KEYCODE_SEMICOLON          59  /* ; */
#define FE_KEYCODE_EQUAL              61  /* = */
#define FE_KEYCODE_A                  65
#define FE_KEYCODE_B                  66
#define FE_KEYCODE_C                  67
#define FE_KEYCODE_D                  68
#define FE_KEYCODE_E                  69
#define FE_KEYCODE_F                  70
#define FE_KEYCODE_G                  71
#define FE_KEYCODE_H                  72
#define FE_KEYCODE_I                  73
#define FE_KEYCODE_J                  74
#define FE_KEYCODE_K                  75
#define FE_KEYCODE_L                  76
#define FE_KEYCODE_M                  77
#define FE_KEYCODE_N                  78
#define FE_KEYCODE_O                  79
#define FE_KEYCODE_P                  80
#define FE_KEYCODE_Q                  81
#define FE_KEYCODE_R                  82
#define FE_KEYCODE_S                  83
#define FE_KEYCODE_T                  84
#define FE_KEYCODE_U                  85
#define FE_KEYCODE_V                  86
#define FE_KEYCODE_W                  87
#define FE_KEYCODE_X                  88
#define FE_KEYCODE_Y                  89
#define FE_KEYCODE_Z                  90
#define FE_KEYCODE_LEFT_BRACKET       91  /* [ */
#define FE_KEYCODE_BACKSLASH          92  /* \ */
#define FE_KEYCODE_RIGHT_BRACKET      93  /* ] */
#define FE_KEYCODE_GRAVE_ACCENT       96  /* ` */
#define FE_KEYCODE_WORLD_1            161 /* non-US #1 */
#define FE_KEYCODE_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define FE_KEYCODE_ESCAPE             256
#define FE_KEYCODE_ENTER              257
#define FE_KEYCODE_TAB                258
#define FE_KEYCODE_BACKSPACE          259
#define FE_KEYCODE_INSERT             260
#define FE_KEYCODE_DELETE             261
#define FE_KEYCODE_RIGHT              262
#define FE_KEYCODE_LEFT               263
#define FE_KEYCODE_DOWN               264
#define FE_KEYCODE_UP                 265
#define FE_KEYCODE_PAGE_UP            266
#define FE_KEYCODE_PAGE_DOWN          267
#define FE_KEYCODE_HOME               268
#define FE_KEYCODE_END                269
#define FE_KEYCODE_CAPS_LOCK          280
#define FE_KEYCODE_SCROLL_LOCK        281
#define FE_KEYCODE_NUM_LOCK           282
#define FE_KEYCODE_PRINT_SCREEN       283
#define FE_KEYCODE_PAUSE              284
#define FE_KEYCODE_F1                 290
#define FE_KEYCODE_F2                 291
#define FE_KEYCODE_F3                 292
#define FE_KEYCODE_F4                 293
#define FE_KEYCODE_F5                 294
#define FE_KEYCODE_F6                 295
#define FE_KEYCODE_F7                 296
#define FE_KEYCODE_F8                 297
#define FE_KEYCODE_F9                 298
#define FE_KEYCODE_F10                299
#define FE_KEYCODE_F11                300
#define FE_KEYCODE_F12                301
#define FE_KEYCODE_F13                302
#define FE_KEYCODE_F14                303
#define FE_KEYCODE_F15                304
#define FE_KEYCODE_F16                305
#define FE_KEYCODE_F17                306
#define FE_KEYCODE_F18                307
#define FE_KEYCODE_F19                308
#define FE_KEYCODE_F20                309
#define FE_KEYCODE_F21                310
#define FE_KEYCODE_F22                311
#define FE_KEYCODE_F23                312
#define FE_KEYCODE_F24                313
#define FE_KEYCODE_F25                314
#define FE_KEYCODE_KP_0               320
#define FE_KEYCODE_KP_1               321
#define FE_KEYCODE_KP_2               322
#define FE_KEYCODE_KP_3               323
#define FE_KEYCODE_KP_4               324
#define FE_KEYCODE_KP_5               325
#define FE_KEYCODE_KP_6               326
#define FE_KEYCODE_KP_7               327
#define FE_KEYCODE_KP_8               328
#define FE_KEYCODE_KP_9               329
#define FE_KEYCODE_KP_DECIMAL         330
#define FE_KEYCODE_KP_DIVIDE          331
#define FE_KEYCODE_KP_MULTIPLY        332
#define FE_KEYCODE_KP_SUBTRACT        333
#define FE_KEYCODE_KP_ADD             334
#define FE_KEYCODE_KP_ENTER           335
#define FE_KEYCODE_KP_EQUAL           336
#define FE_KEYCODE_LEFT_SHIFT         340
#define FE_KEYCODE_LEFT_CONTROL       341
#define FE_KEYCODE_LEFT_ALT           342
#define FE_KEYCODE_LEFT_SUPER         343
#define FE_KEYCODE_RIGHT_SHIFT        344
#define FE_KEYCODE_RIGHT_CONTROL      345
#define FE_KEYCODE_RIGHT_ALT          346
#define FE_KEYCODE_RIGHT_SUPER        347
#define FE_KEYCODE_MENU               348

#define FE_KEYCODE_LAST               FE_KEYCODE_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *  @brief Modifier key flags.
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

 /*! @brief If this bit is set one or more Shift keys were held down.
  *
  *  If this bit is set one or more Shift keys were held down.
  */
#define FE_MOD_SHIFT           0x0001
  /*! @brief If this bit is set one or more Control keys were held down.
   *
   *  If this bit is set one or more Control keys were held down.
   */
#define FE_MOD_CONTROL         0x0002
   /*! @brief If this bit is set one or more Alt keys were held down.
	*
	*  If this bit is set one or more Alt keys were held down.
	*/
#define FE_MOD_ALT             0x0004
	/*! @brief If this bit is set one or more Super keys were held down.
	 *
	 *  If this bit is set one or more Super keys were held down.
	 */
#define FE_MOD_SUPER           0x0008
	 /*! @brief If this bit is set the Caps Lock key is enabled.
	  *
	  *  If this bit is set the Caps Lock key is enabled and the @ref
	  *  FE_LOCK_KEYCODE_MODS input mode is set.
	  */
#define FE_MOD_CAPS_LOCK       0x0010
	  /*! @brief If this bit is set the Num Lock key is enabled.
	   *
	   *  If this bit is set the Num Lock key is enabled and the @ref
	   *  FE_LOCK_KEYCODE_MODS input mode is set.
	   */
#define FE_MOD_NUM_LOCK        0x0020

	   /*! @} */

	   /*! @defgroup buttons Mouse buttons
		*  @brief Mouse button IDs.
		*
		*  See [mouse button input](@ref input_mouse_button) for how these are used.
		*
		*  @ingroup input
		*  @{ */
#define FE_MOUSE_BUTTON_1         0
#define FE_MOUSE_BUTTON_2         1
#define FE_MOUSE_BUTTON_3         2
#define FE_MOUSE_BUTTON_4         3
#define FE_MOUSE_BUTTON_5         4
#define FE_MOUSE_BUTTON_6         5
#define FE_MOUSE_BUTTON_7         6
#define FE_MOUSE_BUTTON_8         7
#define FE_MOUSE_BUTTON_LAST      FE_MOUSE_BUTTON_8
#define FE_MOUSE_BUTTON_LEFT      FE_MOUSE_BUTTON_1
#define FE_MOUSE_BUTTON_RIGHT     FE_MOUSE_BUTTON_2
#define FE_MOUSE_BUTTON_MIDDLE    FE_MOUSE_BUTTON_3
		/*! @} */

		/*! @defgroup joysticks Joysticks
		 *  @brief Joystick IDs.
		 *
		 *  See [joystick input](@ref joystick) for how these are used.
		 *
		 *  @ingroup input
		 *  @{ */
#define FE_JOYSTICK_1             0
#define FE_JOYSTICK_2             1
#define FE_JOYSTICK_3             2
#define FE_JOYSTICK_4             3
#define FE_JOYSTICK_5             4
#define FE_JOYSTICK_6             5
#define FE_JOYSTICK_7             6
#define FE_JOYSTICK_8             7
#define FE_JOYSTICK_9             8
#define FE_JOYSTICK_10            9
#define FE_JOYSTICK_11            10
#define FE_JOYSTICK_12            11
#define FE_JOYSTICK_13            12
#define FE_JOYSTICK_14            13
#define FE_JOYSTICK_15            14
#define FE_JOYSTICK_16            15
#define FE_JOYSTICK_LAST          FE_JOYSTICK_16
		 /*! @} */

		 /*! @defgroup gamepad_buttons Gamepad buttons
		  *  @brief Gamepad buttons.
		  *
		  *  See @ref gamepad for how these are used.
		  *
		  *  @ingroup input
		  *  @{ */
#define FE_GAMEPAD_BUTTON_A               0
#define FE_GAMEPAD_BUTTON_B               1
#define FE_GAMEPAD_BUTTON_X               2
#define FE_GAMEPAD_BUTTON_Y               3
#define FE_GAMEPAD_BUTTON_LEFT_BUMPER     4
#define FE_GAMEPAD_BUTTON_RIGHT_BUMPER    5
#define FE_GAMEPAD_BUTTON_BACK            6
#define FE_GAMEPAD_BUTTON_START           7
#define FE_GAMEPAD_BUTTON_GUIDE           8
#define FE_GAMEPAD_BUTTON_LEFT_THUMB      9
#define FE_GAMEPAD_BUTTON_RIGHT_THUMB     10
#define FE_GAMEPAD_BUTTON_DPAD_UP         11
#define FE_GAMEPAD_BUTTON_DPAD_RIGHT      12
#define FE_GAMEPAD_BUTTON_DPAD_DOWN       13
#define FE_GAMEPAD_BUTTON_DPAD_LEFT       14
#define FE_GAMEPAD_BUTTON_LAST            FE_GAMEPAD_BUTTON_DPAD_LEFT

#define FE_GAMEPAD_BUTTON_CROSS       FE_GAMEPAD_BUTTON_A
#define FE_GAMEPAD_BUTTON_CIRCLE      FE_GAMEPAD_BUTTON_B
#define FE_GAMEPAD_BUTTON_SQUARE      FE_GAMEPAD_BUTTON_X
#define FE_GAMEPAD_BUTTON_TRIANGLE    FE_GAMEPAD_BUTTON_Y
		  /*! @} */

		  /*! @defgroup gamepad_axes Gamepad axes
		   *  @brief Gamepad axes.
		   *
		   *  See @ref gamepad for how these are used.
		   *
		   *  @ingroup input
		   *  @{ */
#define FE_GAMEPAD_AXIS_LEFT_X        0
#define FE_GAMEPAD_AXIS_LEFT_Y        1
#define FE_GAMEPAD_AXIS_RIGHT_X       2
#define FE_GAMEPAD_AXIS_RIGHT_Y       3
#define FE_GAMEPAD_AXIS_LEFT_TRIGGER  4
#define FE_GAMEPAD_AXIS_RIGHT_TRIGGER 5
#define FE_GAMEPAD_AXIS_LAST          FE_GAMEPAD_AXIS_RIGHT_TRIGGER