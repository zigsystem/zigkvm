#include "keymapping.h"
#include <map>
#include <rfb/keysym.h>

#define USB_HID_KEY_MOD_LCTRL 0x01
#define USB_HID_KEY_MOD_LSHIFT 0x02
#define USB_HID_KEY_MOD_LALT 0x04
#define USB_HID_KEY_MOD_LMETA 0x08
#define USB_HID_KEY_MOD_RCTRL 0x10
#define USB_HID_KEY_MOD_RSHIFT 0x20
#define USB_HID_KEY_MOD_RALT 0x40
#define USB_HID_KEY_MOD_RMETA 0x80
#define USB_HID_KEY_NONE 0x00
#define USB_HID_KEY_ERR_OVF 0x01
#define USB_HID_KEY_A 0x04
#define USB_HID_KEY_B 0x05
#define USB_HID_KEY_C 0x06
#define USB_HID_KEY_D 0x07
#define USB_HID_KEY_E 0x08
#define USB_HID_KEY_F 0x09
#define USB_HID_KEY_G 0x0a
#define USB_HID_KEY_H 0x0b
#define USB_HID_KEY_I 0x0c
#define USB_HID_KEY_J 0x0d
#define USB_HID_KEY_K 0x0e
#define USB_HID_KEY_L 0x0f
#define USB_HID_KEY_M 0x10
#define USB_HID_KEY_N 0x11
#define USB_HID_KEY_O 0x12
#define USB_HID_KEY_P 0x13
#define USB_HID_KEY_Q 0x14
#define USB_HID_KEY_R 0x15
#define USB_HID_KEY_S 0x16
#define USB_HID_KEY_T 0x17
#define USB_HID_KEY_U 0x18
#define USB_HID_KEY_V 0x19
#define USB_HID_KEY_W 0x1a
#define USB_HID_KEY_X 0x1b
#define USB_HID_KEY_Y 0x1c
#define USB_HID_KEY_Z 0x1d
#define USB_HID_KEY_1 0x1e
#define USB_HID_KEY_2 0x1f
#define USB_HID_KEY_3 0x20
#define USB_HID_KEY_4 0x21
#define USB_HID_KEY_5 0x22
#define USB_HID_KEY_6 0x23
#define USB_HID_KEY_7 0x24
#define USB_HID_KEY_8 0x25
#define USB_HID_KEY_9 0x26
#define USB_HID_KEY_0 0x27
#define USB_HID_KEY_ENTER 0x28
#define USB_HID_KEY_ESC 0x29
#define USB_HID_KEY_BACKSPACE 0x2a
#define USB_HID_KEY_TAB 0x2b
#define USB_HID_KEY_SPACE 0x2c
#define USB_HID_KEY_MINUS 0x2d
#define USB_HID_KEY_EQUAL 0x2e
#define USB_HID_KEY_LEFTBRACE 0x2f
#define USB_HID_KEY_RIGHTBRACE 0x30
#define USB_HID_KEY_BACKSLASH 0x31
#define USB_HID_KEY_HASHTILDE 0x32
#define USB_HID_KEY_SEMICOLON 0x33
#define USB_HID_KEY_APOSTROPHE 0x34
#define USB_HID_KEY_GRAVE 0x35
#define USB_HID_KEY_COMMA 0x36
#define USB_HID_KEY_DOT 0x37
#define USB_HID_KEY_SLASH 0x38
#define USB_HID_KEY_CAPSLOCK 0x39
#define USB_HID_KEY_F1 0x3a
#define USB_HID_KEY_F2 0x3b
#define USB_HID_KEY_F3 0x3c
#define USB_HID_KEY_F4 0x3d
#define USB_HID_KEY_F5 0x3e
#define USB_HID_KEY_F6 0x3f
#define USB_HID_KEY_F7 0x40
#define USB_HID_KEY_F8 0x41
#define USB_HID_KEY_F9 0x42
#define USB_HID_KEY_F10 0x43
#define USB_HID_KEY_F11 0x44
#define USB_HID_KEY_F12 0x45
#define USB_HID_KEY_SYSRQ 0x46
#define USB_HID_KEY_SCROLLLOCK 0x47
#define USB_HID_KEY_PAUSE 0x48
#define USB_HID_KEY_INSERT 0x49
#define USB_HID_KEY_HOME 0x4a
#define USB_HID_KEY_PAGEUP 0x4b
#define USB_HID_KEY_DELETE 0x4c
#define USB_HID_KEY_END 0x4d
#define USB_HID_KEY_PAGEDOWN 0x4e
#define USB_HID_KEY_RIGHT 0x4f
#define USB_HID_KEY_LEFT 0x50
#define USB_HID_KEY_DOWN 0x51
#define USB_HID_KEY_UP 0x52
#define USB_HID_KEY_NUMLOCK 0x53
#define USB_HID_KEY_KPSLASH 0x54
#define USB_HID_KEY_KPASTERISK 0x55
#define USB_HID_KEY_KPMINUS 0x56
#define USB_HID_KEY_KPPLUS 0x57
#define USB_HID_KEY_KPENTER 0x58
#define USB_HID_KEY_KP1 0x59
#define USB_HID_KEY_KP2 0x5a
#define USB_HID_KEY_KP3 0x5b
#define USB_HID_KEY_KP4 0x5c
#define USB_HID_KEY_KP5 0x5d
#define USB_HID_KEY_KP6 0x5e
#define USB_HID_KEY_KP7 0x5f
#define USB_HID_KEY_KP8 0x60
#define USB_HID_KEY_KP9 0x61
#define USB_HID_KEY_KP0 0x62
#define USB_HID_KEY_KPDOT 0x63
#define USB_HID_KEY_102ND 0x64
#define USB_HID_KEY_COMPOSE 0x65
#define USB_HID_KEY_POWER 0x66
#define USB_HID_KEY_KPEQUAL 0x67
#define USB_HID_KEY_F13 0x68
#define USB_HID_KEY_F14 0x69
#define USB_HID_KEY_F15 0x6a
#define USB_HID_KEY_F16 0x6b
#define USB_HID_KEY_F17 0x6c
#define USB_HID_KEY_F18 0x6d
#define USB_HID_KEY_F19 0x6e
#define USB_HID_KEY_F20 0x6f
#define USB_HID_KEY_F21 0x70
#define USB_HID_KEY_F22 0x71
#define USB_HID_KEY_F23 0x72
#define USB_HID_KEY_F24 0x73
#define USB_HID_KEY_OPEN 0x74
#define USB_HID_KEY_HELP 0x75
#define USB_HID_KEY_PROPS 0x76
#define USB_HID_KEY_FRONT 0x77
#define USB_HID_KEY_STOP 0x78
#define USB_HID_KEY_AGAIN 0x79
#define USB_HID_KEY_UNDO 0x7a
#define USB_HID_KEY_CUT 0x7b
#define USB_HID_KEY_COPY 0x7c
#define USB_HID_KEY_PASTE 0x7d
#define USB_HID_KEY_FIND 0x7e
#define USB_HID_KEY_MUTE 0x7f
#define USB_HID_KEY_VOLUMEUP 0x80
#define USB_HID_KEY_VOLUMEDOWN 0x81
#define USB_HID_KEY_KPCOMMA 0x85
#define USB_HID_KEY_RO 0x87
#define USB_HID_KEY_KATAKANAHIRAGANA 0x88
#define USB_HID_KEY_YEN 0x89
#define USB_HID_KEY_HENKAN 0x8a
#define USB_HID_KEY_MUHENKAN 0x8b
#define USB_HID_KEY_KPJPCOMMA 0x8c
#define USB_HID_KEY_HANGEUL 0x90
#define USB_HID_KEY_HANJA 0x91
#define USB_HID_KEY_KATAKANA 0x92
#define USB_HID_KEY_HIRAGANA 0x93
#define USB_HID_KEY_ZENKAKUHANKAKU 0x94
#define USB_HID_KEY_KPLEFTPAREN 0xb6
#define USB_HID_KEY_KPRIGHTPAREN 0xb7
#define USB_HID_KEY_LEFTCTRL 0xe0
#define USB_HID_KEY_LEFTSHIFT 0xe1
#define USB_HID_KEY_LEFTALT 0xe2
#define USB_HID_KEY_LEFTMETA 0xe3
#define USB_HID_KEY_RIGHTCTRL 0xe4
#define USB_HID_KEY_RIGHTSHIFT 0xe5
#define USB_HID_KEY_RIGHTALT 0xe6
#define USB_HID_KEY_RIGHTMETA 0xe7
#define USB_HID_KEY_MEDIA_PLAYPAUSE 0xe8
#define USB_HID_KEY_MEDIA_STOPCD 0xe9
#define USB_HID_KEY_MEDIA_PREVIOUSSONG 0xea
#define USB_HID_KEY_MEDIA_NEXTSONG 0xeb
#define USB_HID_KEY_MEDIA_EJECTCD 0xec
#define USB_HID_KEY_MEDIA_VOLUMEUP 0xed
#define USB_HID_KEY_MEDIA_VOLUMEDOWN 0xee
#define USB_HID_KEY_MEDIA_MUTE 0xef
#define USB_HID_KEY_MEDIA_WWW 0xf0
#define USB_HID_KEY_MEDIA_BACK 0xf1
#define USB_HID_KEY_MEDIA_FORWARD 0xf2
#define USB_HID_KEY_MEDIA_STOP 0xf3
#define USB_HID_KEY_MEDIA_FIND 0xf4
#define USB_HID_KEY_MEDIA_SCROLLUP 0xf5
#define USB_HID_KEY_MEDIA_SCROLLDOWN 0xf6
#define USB_HID_KEY_MEDIA_EDIT 0xf7
#define USB_HID_KEY_MEDIA_SLEEP 0xf8
#define USB_HID_KEY_MEDIA_COFFEE 0xf9
#define USB_HID_KEY_MEDIA_REFRESH 0xfa
#define USB_HID_KEY_MEDIA_CALC 0xfb

Rfb2vnc init_mappings() {
  std::map<int, KeyModPair> rfb2vnc;
  rfb2vnc[XK_A] = {USB_HID_KEY_A, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_B] = {USB_HID_KEY_B, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_C] = {USB_HID_KEY_C, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_D] = {USB_HID_KEY_D, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_E] = {USB_HID_KEY_E, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_F] = {USB_HID_KEY_F, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_G] = {USB_HID_KEY_G, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_H] = {USB_HID_KEY_H, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_I] = {USB_HID_KEY_I, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_J] = {USB_HID_KEY_J, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_K] = {USB_HID_KEY_K, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_L] = {USB_HID_KEY_L, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_M] = {USB_HID_KEY_M, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_N] = {USB_HID_KEY_N, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_O] = {USB_HID_KEY_O, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_P] = {USB_HID_KEY_P, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_Q] = {USB_HID_KEY_Q, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_R] = {USB_HID_KEY_R, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_S] = {USB_HID_KEY_S, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_T] = {USB_HID_KEY_T, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_U] = {USB_HID_KEY_U, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_V] = {USB_HID_KEY_V, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_W] = {USB_HID_KEY_W, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_X] = {USB_HID_KEY_X, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_Y] = {USB_HID_KEY_Y, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_Z] = {USB_HID_KEY_Z, USB_HID_KEY_MOD_LSHIFT};

  rfb2vnc[XK_a] = USB_HID_KEY_A;
  rfb2vnc[XK_b] = USB_HID_KEY_B;
  rfb2vnc[XK_c] = USB_HID_KEY_C;
  rfb2vnc[XK_d] = USB_HID_KEY_D;
  rfb2vnc[XK_e] = USB_HID_KEY_E;
  rfb2vnc[XK_f] = USB_HID_KEY_F;
  rfb2vnc[XK_g] = USB_HID_KEY_G;
  rfb2vnc[XK_h] = USB_HID_KEY_H;
  rfb2vnc[XK_i] = USB_HID_KEY_I;
  rfb2vnc[XK_j] = USB_HID_KEY_J;
  rfb2vnc[XK_k] = USB_HID_KEY_K;
  rfb2vnc[XK_l] = USB_HID_KEY_L;
  rfb2vnc[XK_m] = USB_HID_KEY_M;
  rfb2vnc[XK_n] = USB_HID_KEY_N;
  rfb2vnc[XK_o] = USB_HID_KEY_O;
  rfb2vnc[XK_p] = USB_HID_KEY_P;
  rfb2vnc[XK_q] = USB_HID_KEY_Q;
  rfb2vnc[XK_r] = USB_HID_KEY_R;
  rfb2vnc[XK_s] = USB_HID_KEY_S;
  rfb2vnc[XK_t] = USB_HID_KEY_T;
  rfb2vnc[XK_u] = USB_HID_KEY_U;
  rfb2vnc[XK_v] = USB_HID_KEY_V;
  rfb2vnc[XK_w] = USB_HID_KEY_W;
  rfb2vnc[XK_x] = USB_HID_KEY_X;
  rfb2vnc[XK_y] = USB_HID_KEY_Y;
  rfb2vnc[XK_z] = USB_HID_KEY_Z;

  rfb2vnc[XK_1] = USB_HID_KEY_1;
  rfb2vnc[XK_2] = USB_HID_KEY_2;
  rfb2vnc[XK_3] = USB_HID_KEY_3;
  rfb2vnc[XK_4] = USB_HID_KEY_4;
  rfb2vnc[XK_5] = USB_HID_KEY_5;
  rfb2vnc[XK_6] = USB_HID_KEY_6;
  rfb2vnc[XK_7] = USB_HID_KEY_7;
  rfb2vnc[XK_8] = USB_HID_KEY_8;
  rfb2vnc[XK_9] = USB_HID_KEY_9;
  rfb2vnc[XK_0] = USB_HID_KEY_0;

  rfb2vnc[XK_F1] = USB_HID_KEY_F1;
  rfb2vnc[XK_F2] = USB_HID_KEY_F2;
  rfb2vnc[XK_F3] = USB_HID_KEY_F3;
  rfb2vnc[XK_F4] = USB_HID_KEY_F4;
  rfb2vnc[XK_F5] = USB_HID_KEY_F5;
  rfb2vnc[XK_F6] = USB_HID_KEY_F6;
  rfb2vnc[XK_F7] = USB_HID_KEY_F7;
  rfb2vnc[XK_F8] = USB_HID_KEY_F8;
  rfb2vnc[XK_F9] = USB_HID_KEY_F9;
  rfb2vnc[XK_F10] = USB_HID_KEY_F10;
  rfb2vnc[XK_F11] = USB_HID_KEY_F11;
  rfb2vnc[XK_F12] = USB_HID_KEY_F12;

  rfb2vnc[XK_space] = USB_HID_KEY_SPACE;

  rfb2vnc[XK_exclam] = {USB_HID_KEY_1, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_quotedbl] = {USB_HID_KEY_APOSTROPHE, USB_HID_KEY_MOD_LSHIFT};
  // rfb2vnc[XK_numbersign] = ;
  // rfb2vnc[XK_dollar] = ;
  // rfb2vnc[XK_percent] = ;
  // rfb2vnc[XK_ampersand] = ;
  rfb2vnc[XK_apostrophe] = USB_HID_KEY_APOSTROPHE;
  // rfb2vnc[XK_parenleft] = ;
  // rfb2vnc[XK_parenright] = ;
  // rfb2vnc[XK_asterisk] = ;
  // rfb2vnc[XK_plus] = ;
  rfb2vnc[XK_comma] = USB_HID_KEY_COMMA;
  rfb2vnc[XK_minus] = USB_HID_KEY_MINUS;
  // rfb2vnc[XK_period] = ;
  // rfb2vnc[XK_slash] = ;
  rfb2vnc[XK_colon] = (USB_HID_KEY_SEMICOLON, USB_HID_KEY_MOD_LSHIFT);
  rfb2vnc[XK_semicolon] = USB_HID_KEY_SEMICOLON;
  // rfb2vnc[XK_less] = ;
  rfb2vnc[XK_equal] = USB_HID_KEY_EQUAL;
  // rfb2vnc[XK_greater] = ;
  // rfb2vnc[XK_question] = ;
  // rfb2vnc[XK_at] = ;
  rfb2vnc[XK_bracketleft] = USB_HID_KEY_LEFTBRACE;
  rfb2vnc[XK_backslash] = USB_HID_KEY_BACKSLASH;
  rfb2vnc[XK_bracketright] = USB_HID_KEY_RIGHTBRACE;
  // rfb2vnc[XK_asciicircum] = ;
  // rfb2vnc[XK_underscore] = ;
  rfb2vnc[XK_grave] = USB_HID_KEY_GRAVE;
  rfb2vnc[XK_braceleft] = {USB_HID_KEY_LEFTBRACE, USB_HID_KEY_MOD_LSHIFT};
  // rfb2vnc[XK_bar] = ;
  rfb2vnc[XK_braceright] = {USB_HID_KEY_RIGHTBRACE, USB_HID_KEY_MOD_LSHIFT};
  rfb2vnc[XK_asciitilde] = USB_HID_KEY_GRAVE;

  rfb2vnc[XK_Return] = USB_HID_KEY_ENTER;
  rfb2vnc[XK_slash] = USB_HID_KEY_SLASH;
  rfb2vnc[XK_Escape] = USB_HID_KEY_ESC;
  rfb2vnc[XK_BackSpace] = USB_HID_KEY_BACKSPACE;
  rfb2vnc[XK_Tab] = USB_HID_KEY_TAB;
  rfb2vnc[XK_Delete] = USB_HID_KEY_DELETE;
  // rfb2vnc[XK_Linefeed] = ;
  // rfb2vnc[XK_Clear] = ;
  // rfb2vnc[XK_Pause] = USB_HID_KEY_PAUSE;
  // rfb2vnc[XK_Scroll_Lock] = USB_HID_KEY_SCROLLLOCK;
  rfb2vnc[XK_Sys_Req] = USB_HID_KEY_SYSRQ;

  // rfb2vnc[XK_Select] = ;
  // rfb2vnc[XK_Print] = ;
  // rfb2vnc[XK_Execute] = ;
  rfb2vnc[XK_Insert] = USB_HID_KEY_INSERT;
  // rfb2vnc[XK_Undo] = ;
  // rfb2vnc[XK_Redo] = ;
  // rfb2vnc[XK_Menu] = ;
  // rfb2vnc[XK_Find] = ;
  // rfb2vnc[XK_Cancel] = ;
  // rfb2vnc[XK_Help] = ;
  // rfb2vnc[XK_Break] = ;
  // rfb2vnc[XK_Mode_switch] = ;
  // rfb2vnc[XK_script_switch] = ;
  // rfb2vnc[XK_Num_Lock] = ;

  rfb2vnc[XK_Home] = USB_HID_KEY_HOME;
  rfb2vnc[XK_Left] = USB_HID_KEY_LEFT;
  rfb2vnc[XK_Up] = USB_HID_KEY_UP;
  rfb2vnc[XK_Right] = USB_HID_KEY_RIGHT;
  rfb2vnc[XK_Down] = USB_HID_KEY_DOWN;
  // rfb2vnc[XK_Prior] = ;
  rfb2vnc[XK_Page_Up] = USB_HID_KEY_PAGEUP;
  // rfb2vnc[XK_Next] = ;
  rfb2vnc[XK_Page_Down] = USB_HID_KEY_PAGEDOWN;
  rfb2vnc[XK_End] = USB_HID_KEY_END;
  // rfb2vnc[XK_Begin] = ;

  rfb2vnc[XK_KP_1] = USB_HID_KEY_KP1;
  rfb2vnc[XK_KP_2] = USB_HID_KEY_KP2;
  rfb2vnc[XK_KP_3] = USB_HID_KEY_KP3;
  rfb2vnc[XK_KP_4] = USB_HID_KEY_KP4;
  rfb2vnc[XK_KP_5] = USB_HID_KEY_KP5;
  rfb2vnc[XK_KP_6] = USB_HID_KEY_KP6;
  rfb2vnc[XK_KP_7] = USB_HID_KEY_KP7;
  rfb2vnc[XK_KP_8] = USB_HID_KEY_KP8;
  rfb2vnc[XK_KP_9] = USB_HID_KEY_KP9;
  rfb2vnc[XK_KP_0] = USB_HID_KEY_KP0;

  rfb2vnc[XK_KP_Enter] = USB_HID_KEY_KPENTER;

  return rfb2vnc;
}

/*
#define USB_HID_KEY_HASHTILDE 0x32 // Keyboard Non-US # and ~
#define USB_HID_KEY_DOT 0x37 // Keyboard . and >
#define USB_HID_KEY_CAPSLOCK 0x39 // Keyboard Caps Lock
*/

std::map<int, int> init_mods() {
  std::map<int, int> r;
  r[XK_Shift_L] = USB_HID_KEY_MOD_LSHIFT;
  r[XK_Shift_R] = USB_HID_KEY_MOD_RSHIFT;
  r[XK_Control_L] = USB_HID_KEY_MOD_LCTRL;
  r[XK_Control_R] = USB_HID_KEY_MOD_RCTRL;
  r[XK_Meta_L] = USB_HID_KEY_MOD_LMETA;
  r[XK_Meta_R] = USB_HID_KEY_MOD_RMETA;
  r[XK_Alt_L] = USB_HID_KEY_MOD_LALT;
  r[XK_Alt_R] = USB_HID_KEY_MOD_RALT;
  r[XK_Caps_Lock] = USB_HID_KEY_CAPSLOCK;
  // r[XK_Shift_Lock]=;
  // r[XK_Super_L]=;
  // r[XK_Super_R]=;
  // r[XK_Hyper_L]=;
  // r[XK_Hyper_R]=;
  return r;
}
