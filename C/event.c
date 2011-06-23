#include "general.h"
#include "event.h"

// ML type: unit -> unit
// Gathers events. Only needs to be called if no other event handling is done.
EXTERNML value event_pump(value null) {
    SDL_PumpEvents();

    return Val_unit;
}

// If cond is true, then it attaches a new link
// to the list at *container[index], containing Atom(tag).
//
// Note: Allocation will occur, so container must be rooted.
void attach_to_list_if(value *container, int index, int cond, int tag) {
#define Nil_tag 0
#define Cons_tag 1
#define Val_nil Atom(0)

    if (cond) {
        value link = alloc(2, Cons_tag);

        modify(&Field(link, 0), Atom(tag));
        modify(&Field(link, 1), Field(*container, index));

        modify(&Field(*container, index), link);
    }

}

// If bitfield & flag is true, then it attaches a new link
// to the list at *container[index], containing Atom(tag).
//
// Note: Allocation will occur, so container must be rooted.
void attach_to_list_if_set(value *container, int index,
                            int bitfield, int flag, int tag) {
    attach_to_list_if(container, index, bitfield & flag, tag);
}

// Parses an SDL_Event, and returns a corresponding SML event.
value Event_val(SDL_Event *event, int *success) {
    // list datatype defines:
    switch (event->type) {
        case SDL_ACTIVEEVENT: {
            *success = true;

            Push_roots(res, 1);
            res[0] = alloc(2, ActivationEvent);
            modify(&Field(res[0], 0), Val_bool(event->active.gain));
            modify(&Field(res[0], 1), Val_nil);

            attach_to_list_if_set(&res[0], 1, event->active.state,
                                  SDL_APPMOUSEFOCUS, MouseFocus);
            attach_to_list_if_set(&res[0], 1, event->active.state,
                                  SDL_APPINPUTFOCUS, InputFocus);
            attach_to_list_if_set(&res[0], 1, event->active.state,
                                  SDL_APPACTIVE, AppFocus);

            Pop_roots();
            return res[0];
        }
        case SDL_KEYDOWN:
        case SDL_KEYUP: {
            *success = true;
            Push_roots(res, 1);
            res[0] = alloc(3, KeyboardEvent);

            value state;
            if (event->key.state & SDL_PRESSED) {
                state = Atom(KeyPressed);
            } else {
                state = Atom(KeyReleased);
            }

            modify(&Field(res[0], 0), state);

            int key;
            switch (event->key.keysym.sym) {
                // oh god, don't look in here {{{
                case SDLK_BACKSPACE   : key = KeyBackspace    ; break;
                case SDLK_TAB         : key = KeyTab          ; break;
                case SDLK_CLEAR       : key = KeyClear        ; break;
                case SDLK_RETURN      : key = KeyReturn       ; break;
                case SDLK_PAUSE       : key = KeyPause        ; break;
                case SDLK_ESCAPE      : key = KeyEscape       ; break;
                case SDLK_SPACE       : key = KeySpace        ; break;
                case SDLK_EXCLAIM     : key = KeyExclaim      ; break;
                case SDLK_QUOTEDBL    : key = KeyQuoteDbl     ; break;
                case SDLK_HASH        : key = KeyHash         ; break;
                case SDLK_DOLLAR      : key = KeyDollar       ; break;
                case SDLK_AMPERSAND   : key = KeyAmpersand    ; break;
                case SDLK_QUOTE       : key = KeyQuote        ; break;
                case SDLK_LEFTPAREN   : key = KeyLeftParen    ; break;
                case SDLK_RIGHTPAREN  : key = KeyRightParen   ; break;
                case SDLK_ASTERISK    : key = KeyAsterisk     ; break;
                case SDLK_PLUS        : key = KeyPlus         ; break;
                case SDLK_COMMA       : key = KeyComma        ; break;
                case SDLK_MINUS       : key = KeyMinus        ; break;
                case SDLK_PERIOD      : key = KeyPeriod       ; break;
                case SDLK_SLASH       : key = KeySlash        ; break;
                case SDLK_0           : key = Key0            ; break;
                case SDLK_1           : key = Key1            ; break;
                case SDLK_2           : key = Key2            ; break;
                case SDLK_3           : key = Key3            ; break;
                case SDLK_4           : key = Key4            ; break;
                case SDLK_5           : key = Key5            ; break;
                case SDLK_6           : key = Key6            ; break;
                case SDLK_7           : key = Key7            ; break;
                case SDLK_8           : key = Key8            ; break;
                case SDLK_9           : key = Key9            ; break;
                case SDLK_COLON       : key = KeyColon        ; break;
                case SDLK_SEMICOLON   : key = KeySemicolon    ; break;
                case SDLK_LESS        : key = KeyLess         ; break;
                case SDLK_EQUALS      : key = KeyEquals       ; break;
                case SDLK_GREATER     : key = KeyGreater      ; break;
                case SDLK_QUESTION    : key = KeyQuestion     ; break;
                case SDLK_AT          : key = KeyAt           ; break;
                case SDLK_LEFTBRACKET : key = KeyLeftBracket  ; break;
                case SDLK_BACKSLASH   : key = KeyBackslash    ; break;
                case SDLK_RIGHTBRACKET: key = KeyRightBracket ; break;
                case SDLK_CARET       : key = KeyCaret        ; break;
                case SDLK_UNDERSCORE  : key = KeyUnderscore   ; break;
                case SDLK_BACKQUOTE   : key = KeyBackquote    ; break;
                case SDLK_a           : key = KeyA            ; break;
                case SDLK_b           : key = KeyB            ; break;
                case SDLK_c           : key = KeyC            ; break;
                case SDLK_d           : key = KeyD            ; break;
                case SDLK_e           : key = KeyE            ; break;
                case SDLK_f           : key = KeyF            ; break;
                case SDLK_g           : key = KeyG            ; break;
                case SDLK_h           : key = KeyH            ; break;
                case SDLK_i           : key = KeyI            ; break;
                case SDLK_j           : key = KeyJ            ; break;
                case SDLK_k           : key = KeyK            ; break;
                case SDLK_l           : key = KeyL            ; break;
                case SDLK_m           : key = KeyM            ; break;
                case SDLK_n           : key = KeyN            ; break;
                case SDLK_o           : key = KeyO            ; break;
                case SDLK_p           : key = KeyP            ; break;
                case SDLK_q           : key = KeyQ            ; break;
                case SDLK_r           : key = KeyR            ; break;
                case SDLK_s           : key = KeyS            ; break;
                case SDLK_t           : key = KeyT            ; break;
                case SDLK_u           : key = KeyU            ; break;
                case SDLK_v           : key = KeyV            ; break;
                case SDLK_w           : key = KeyW            ; break;
                case SDLK_x           : key = KeyX            ; break;
                case SDLK_y           : key = KeyY            ; break;
                case SDLK_z           : key = KeyZ            ; break;
                case SDLK_DELETE      : key = KeyDelete       ; break;
                case SDLK_WORLD_0     : key = KeyWorld_0      ; break;
                case SDLK_WORLD_1     : key = KeyWorld_1      ; break;
                case SDLK_WORLD_2     : key = KeyWorld_2      ; break;
                case SDLK_WORLD_3     : key = KeyWorld_3      ; break;
                case SDLK_WORLD_4     : key = KeyWorld_4      ; break;
                case SDLK_WORLD_5     : key = KeyWorld_5      ; break;
                case SDLK_WORLD_6     : key = KeyWorld_6      ; break;
                case SDLK_WORLD_7     : key = KeyWorld_7      ; break;
                case SDLK_WORLD_8     : key = KeyWorld_8      ; break;
                case SDLK_WORLD_9     : key = KeyWorld_9      ; break;
                case SDLK_WORLD_10    : key = KeyWorld_10     ; break;
                case SDLK_WORLD_11    : key = KeyWorld_11     ; break;
                case SDLK_WORLD_12    : key = KeyWorld_12     ; break;
                case SDLK_WORLD_13    : key = KeyWorld_13     ; break;
                case SDLK_WORLD_14    : key = KeyWorld_14     ; break;
                case SDLK_WORLD_15    : key = KeyWorld_15     ; break;
                case SDLK_WORLD_16    : key = KeyWorld_16     ; break;
                case SDLK_WORLD_17    : key = KeyWorld_17     ; break;
                case SDLK_WORLD_18    : key = KeyWorld_18     ; break;
                case SDLK_WORLD_19    : key = KeyWorld_19     ; break;
                case SDLK_WORLD_20    : key = KeyWorld_20     ; break;
                case SDLK_WORLD_21    : key = KeyWorld_21     ; break;
                case SDLK_WORLD_22    : key = KeyWorld_22     ; break;
                case SDLK_WORLD_23    : key = KeyWorld_23     ; break;
                case SDLK_WORLD_24    : key = KeyWorld_24     ; break;
                case SDLK_WORLD_25    : key = KeyWorld_25     ; break;
                case SDLK_WORLD_26    : key = KeyWorld_26     ; break;
                case SDLK_WORLD_27    : key = KeyWorld_27     ; break;
                case SDLK_WORLD_28    : key = KeyWorld_28     ; break;
                case SDLK_WORLD_29    : key = KeyWorld_29     ; break;
                case SDLK_WORLD_30    : key = KeyWorld_30     ; break;
                case SDLK_WORLD_31    : key = KeyWorld_31     ; break;
                case SDLK_WORLD_32    : key = KeyWorld_32     ; break;
                case SDLK_WORLD_33    : key = KeyWorld_33     ; break;
                case SDLK_WORLD_34    : key = KeyWorld_34     ; break;
                case SDLK_WORLD_35    : key = KeyWorld_35     ; break;
                case SDLK_WORLD_36    : key = KeyWorld_36     ; break;
                case SDLK_WORLD_37    : key = KeyWorld_37     ; break;
                case SDLK_WORLD_38    : key = KeyWorld_38     ; break;
                case SDLK_WORLD_39    : key = KeyWorld_39     ; break;
                case SDLK_WORLD_40    : key = KeyWorld_40     ; break;
                case SDLK_WORLD_41    : key = KeyWorld_41     ; break;
                case SDLK_WORLD_42    : key = KeyWorld_42     ; break;
                case SDLK_WORLD_43    : key = KeyWorld_43     ; break;
                case SDLK_WORLD_44    : key = KeyWorld_44     ; break;
                case SDLK_WORLD_45    : key = KeyWorld_45     ; break;
                case SDLK_WORLD_46    : key = KeyWorld_46     ; break;
                case SDLK_WORLD_47    : key = KeyWorld_47     ; break;
                case SDLK_WORLD_48    : key = KeyWorld_48     ; break;
                case SDLK_WORLD_49    : key = KeyWorld_49     ; break;
                case SDLK_WORLD_50    : key = KeyWorld_50     ; break;
                case SDLK_WORLD_51    : key = KeyWorld_51     ; break;
                case SDLK_WORLD_52    : key = KeyWorld_52     ; break;
                case SDLK_WORLD_53    : key = KeyWorld_53     ; break;
                case SDLK_WORLD_54    : key = KeyWorld_54     ; break;
                case SDLK_WORLD_55    : key = KeyWorld_55     ; break;
                case SDLK_WORLD_56    : key = KeyWorld_56     ; break;
                case SDLK_WORLD_57    : key = KeyWorld_57     ; break;
                case SDLK_WORLD_58    : key = KeyWorld_58     ; break;
                case SDLK_WORLD_59    : key = KeyWorld_59     ; break;
                case SDLK_WORLD_60    : key = KeyWorld_60     ; break;
                case SDLK_WORLD_61    : key = KeyWorld_61     ; break;
                case SDLK_WORLD_62    : key = KeyWorld_62     ; break;
                case SDLK_WORLD_63    : key = KeyWorld_63     ; break;
                case SDLK_WORLD_64    : key = KeyWorld_64     ; break;
                case SDLK_WORLD_65    : key = KeyWorld_65     ; break;
                case SDLK_WORLD_66    : key = KeyWorld_66     ; break;
                case SDLK_WORLD_67    : key = KeyWorld_67     ; break;
                case SDLK_WORLD_68    : key = KeyWorld_68     ; break;
                case SDLK_WORLD_69    : key = KeyWorld_69     ; break;
                case SDLK_WORLD_70    : key = KeyWorld_70     ; break;
                case SDLK_WORLD_71    : key = KeyWorld_71     ; break;
                case SDLK_WORLD_72    : key = KeyWorld_72     ; break;
                case SDLK_WORLD_73    : key = KeyWorld_73     ; break;
                case SDLK_WORLD_74    : key = KeyWorld_74     ; break;
                case SDLK_WORLD_75    : key = KeyWorld_75     ; break;
                case SDLK_WORLD_76    : key = KeyWorld_76     ; break;
                case SDLK_WORLD_77    : key = KeyWorld_77     ; break;
                case SDLK_WORLD_78    : key = KeyWorld_78     ; break;
                case SDLK_WORLD_79    : key = KeyWorld_79     ; break;
                case SDLK_WORLD_80    : key = KeyWorld_80     ; break;
                case SDLK_WORLD_81    : key = KeyWorld_81     ; break;
                case SDLK_WORLD_82    : key = KeyWorld_82     ; break;
                case SDLK_WORLD_83    : key = KeyWorld_83     ; break;
                case SDLK_WORLD_84    : key = KeyWorld_84     ; break;
                case SDLK_WORLD_85    : key = KeyWorld_85     ; break;
                case SDLK_WORLD_86    : key = KeyWorld_86     ; break;
                case SDLK_WORLD_87    : key = KeyWorld_87     ; break;
                case SDLK_WORLD_88    : key = KeyWorld_88     ; break;
                case SDLK_WORLD_89    : key = KeyWorld_89     ; break;
                case SDLK_WORLD_90    : key = KeyWorld_90     ; break;
                case SDLK_WORLD_91    : key = KeyWorld_91     ; break;
                case SDLK_WORLD_92    : key = KeyWorld_92     ; break;
                case SDLK_WORLD_93    : key = KeyWorld_93     ; break;
                case SDLK_WORLD_94    : key = KeyWorld_94     ; break;
                case SDLK_WORLD_95    : key = KeyWorld_95     ; break;
                case SDLK_KP0         : key = KeyKp0          ; break;
                case SDLK_KP1         : key = KeyKp1          ; break;
                case SDLK_KP2         : key = KeyKp2          ; break;
                case SDLK_KP3         : key = KeyKp3          ; break;
                case SDLK_KP4         : key = KeyKp4          ; break;
                case SDLK_KP5         : key = KeyKp5          ; break;
                case SDLK_KP6         : key = KeyKp6          ; break;
                case SDLK_KP7         : key = KeyKp7          ; break;
                case SDLK_KP8         : key = KeyKp8          ; break;
                case SDLK_KP9         : key = KeyKp9          ; break;
                case SDLK_KP_PERIOD   : key = KeyKpPeriod     ; break;
                case SDLK_KP_DIVIDE   : key = KeyKpDivide     ; break;
                case SDLK_KP_MULTIPLY : key = KeyKpMultiply   ; break;
                case SDLK_KP_MINUS    : key = KeyKpMinus      ; break;
                case SDLK_KP_PLUS     : key = KeyKpPlus       ; break;
                case SDLK_KP_ENTER    : key = KeyKpEnter      ; break;
                case SDLK_KP_EQUALS   : key = KeyKpEquals     ; break;
                case SDLK_UP          : key = KeyUp           ; break;
                case SDLK_DOWN        : key = KeyDown         ; break;
                case SDLK_RIGHT       : key = KeyRight        ; break;
                case SDLK_LEFT        : key = KeyLeft         ; break;
                case SDLK_INSERT      : key = KeyInsert       ; break;
                case SDLK_HOME        : key = KeyHome         ; break;
                case SDLK_END         : key = KeyEnd          ; break;
                case SDLK_PAGEUP      : key = KeyPageUp       ; break;
                case SDLK_PAGEDOWN    : key = KeyPageDown     ; break;
                case SDLK_F1          : key = KeyF1           ; break;
                case SDLK_F2          : key = KeyF2           ; break;
                case SDLK_F3          : key = KeyF3           ; break;
                case SDLK_F4          : key = KeyF4           ; break;
                case SDLK_F5          : key = KeyF5           ; break;
                case SDLK_F6          : key = KeyF6           ; break;
                case SDLK_F7          : key = KeyF7           ; break;
                case SDLK_F8          : key = KeyF8           ; break;
                case SDLK_F9          : key = KeyF9           ; break;
                case SDLK_F10         : key = KeyF10          ; break;
                case SDLK_F11         : key = KeyF11          ; break;
                case SDLK_F12         : key = KeyF12          ; break;
                case SDLK_F13         : key = KeyF13          ; break;
                case SDLK_F14         : key = KeyF14          ; break;
                case SDLK_F15         : key = KeyF15          ; break;
                case SDLK_NUMLOCK     : key = KeyNumLock      ; break;
                case SDLK_CAPSLOCK    : key = KeyCapsLock     ; break;
                case SDLK_SCROLLOCK   : key = KeyScrollLock   ; break;
                case SDLK_RSHIFT      : key = KeyRShift       ; break;
                case SDLK_LSHIFT      : key = KeyLShift       ; break;
                case SDLK_RCTRL       : key = KeyRCtrl        ; break;
                case SDLK_LCTRL       : key = KeyLCtrl        ; break;
                case SDLK_RALT        : key = KeyRAlt         ; break;
                case SDLK_LALT        : key = KeyLAlt         ; break;
                case SDLK_RMETA       : key = KeyRMeta        ; break;
                case SDLK_LMETA       : key = KeyLMeta        ; break;
                case SDLK_LSUPER      : key = KeyLSuper       ; break;
                case SDLK_RSUPER      : key = KeyRSuper       ; break;
                case SDLK_MODE        : key = KeyMode         ; break;
                case SDLK_COMPOSE     : key = KeyCompose      ; break;
                case SDLK_HELP        : key = KeyHelp         ; break;
                case SDLK_PRINT       : key = KeyPrint        ; break;
                case SDLK_SYSREQ      : key = KeySysReq       ; break;
                case SDLK_BREAK       : key = KeyBreak        ; break;
                case SDLK_MENU        : key = KeyMenu         ; break;
                case SDLK_POWER       : key = KeyPower        ; break;
                case SDLK_EURO        : key = KeyEuro         ; break;
                case SDLK_UNDO        : key = KeyUndo         ; break;
                // }}}
            }
            modify(&Field(res[0], 1), Atom(key));

            modify(&Field(res[0], 2), Val_nil);
            // Shift
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_LSHIFT, KeyModLShift);
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_SHIFT, KeyModShift);
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_RSHIFT, KeyModRShift);
            // Alt
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_LALT, KeyModLAlt);
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_ALT, KeyModAlt);
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_RALT, KeyModRAlt);
            // Ctrl
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_LCTRL, KeyModLCtrl);
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_CTRL, KeyModCtrl);
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_RCTRL, KeyModRCtrl);
            // Meta
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_LMETA, KeyModLMeta);
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_META, KeyModMeta);
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_RMETA, KeyModRMeta);
            // Num
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_NUM, KeyModNum);
            // Caps
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_CAPS, KeyModCaps);
            // Mode
            attach_to_list_if_set(&res[0], 2, event->key.keysym.mod,
                                  KMOD_MODE, KeyModMode);

            Pop_roots();
            return res[0];
        }
        case SDL_MOUSEMOTION: {
            *success = true;
            Push_roots(res, 1);
            res[0] = alloc(3, MouseMotionEvent);

            // First entry in the event: The position as a (x, y) tuple.
            value pos = alloc_tuple(2);
            modify(&Field(pos, 0), Val_long(event->motion.x));
            modify(&Field(pos, 1), Val_long(event->motion.y));
            modify(&Field(res[0], 0), pos);

            // Second entry in the event: The delta as a (dx, dy) tuple.
            value delta = alloc_tuple(2);
            modify(&Field(delta, 0), Val_long(event->motion.xrel));
            modify(&Field(delta, 1), Val_long(event->motion.yrel));
            modify(&Field(res[0], 1), delta);

            // Third entry in the event: List of pressed buttons.
            modify(&Field(res[0], 2), Val_nil);

            attach_to_list_if_set(&res[0], 2, event->motion.state,
                                  SDL_BUTTON(1), LeftMouseButtonDown);
            attach_to_list_if_set(&res[0], 2, event->motion.state,
                                  SDL_BUTTON(2), MiddleMouseButtonDown);
            attach_to_list_if_set(&res[0], 2, event->motion.state,
                                  SDL_BUTTON(3), RightMouseButtonDown);

            Pop_roots();
            return res[0];
        }
        case SDL_MOUSEBUTTONDOWN:
        case SDL_MOUSEBUTTONUP: {
            *success = true;
            Push_roots(res, 1);
            res[0] = alloc(3, MouseButtonEvent);

            // First entry in the event: Was the button pressed or released?
            value state;
            if (event->button.state & SDL_PRESSED) {
                state = Atom(KeyPressed);
            } else {
                state = Atom(KeyReleased);
            }
            modify(&Field(res[0], 0), state);

            // Second entry in the event: Which button was pressed?
            value button;
            switch (event->button.button) {
                case SDL_BUTTON_LEFT: button = Atom(LeftMouseButton); break;
                case SDL_BUTTON_MIDDLE: button = Atom(MiddleMouseButton); break;
                case SDL_BUTTON_RIGHT: button = Atom(RightMouseButton); break;
                case SDL_BUTTON_WHEELUP: button = Atom(MouseWheelUp); break;
                case SDL_BUTTON_WHEELDOWN: button = Atom(MouseWheelDown); break;
                default: failwith("Got an expected event->button.button in a mouse button event.");
            }
            modify(&Field(res[0], 1), button);

            // Third entry in the event: (x, y) of mouse position 
            value pos = alloc_tuple(2);
            modify(&Field(pos, 0), Val_long(event->button.x));
            modify(&Field(pos, 1), Val_long(event->button.y));
            modify(&Field(res[0], 2), pos);

            Pop_roots();
            return res[0];
        }
        case SDL_VIDEORESIZE: {
            *success = true;
            Push_roots(res, 1);

            // First entry in event: New dimensions
            value dims = alloc_tuple(2);
            modify(&Field(dims, 0), Val_long(event->resize.w));
            modify(&Field(dims, 1), Val_long(event->resize.h));
            modify(&Field(res[0], 1), dims);

            Pop_roots();
            return res[0];
        }
        case SDL_VIDEOEXPOSE:
            *success = true;
            return Atom(ExposeEvent);
        case SDL_QUIT:
            *success = true;
            return Atom(QuitEvent);
        default:
            *success = false;
            return Val_unit;
    }
    return Val_unit;
}

// ML type: unit -> event option
// Returns a pending event if available.
EXTERNML value event_poll(value null) {
    SDL_Event event;

    value ret;
    int success = false;
    while (!success) {
        if (!SDL_PollEvent(&event)) {
            return NONE;
        }

        ret = Event_val(&event, &success);
    }

    Push_roots(r, 1);
    r[0] = ret;

    value res = alloc(1, SOMEtag);
    modify(&Field(res, 0), r[0]);

    Pop_roots();

    return res;
}

// ML type: unit -> event
// Returns a pending event. If none is available, it waits for one to be so.
EXTERNML value event_wait(value null) {
    SDL_Event event;

    value ret;
    int success = false;
    while (!success) {
        SDL_WaitEvent(&event);
        ret = Event_val(&event, &success);
    }

    return ret;
}

