#ifndef EVENT_H_0C12771B
#define EVENT_H_0C12771B

#include "general.h"

// The events in ASCII-sorted order. (KEEP THEM THAT WAY!)
enum EVENT {
    ActivationEvent,
    ExposeEvent,
    KeyboardEvent,
    MouseButtonEvent,
    MouseMotionEvent,
    QuitEvent,
    ResizeEvent
};

// The event types in ASCII-sorted order. (KEEP THEM THAT WAY!)
enum EVENTTYPE {
    Activation,
    Expose,
    Keyboard,
    MouseButton,
    MouseMotion,
    Quit,
    Resize
};

// The event filters in ASCII-sorted order. (KEEP THEM THAT WAY!)
enum EVENTFILTER {
    AllEvents,
    EventTypes,
    NoEvents
};

// The focus types in ASCII-sorted order. (KEEP THEM THAT WAY!)
enum FOCUSTYPE {
    AppFocus,
    InputFocus,
    MouseFocus
};

// The possible key states in ASCII-sorted order. (KEEP THEM THAT WAY!)
enum KEYSTATE {
    KeyPressed,
    KeyReleased
};

// The possible key symbols in ASCII-sorted order. (KEEP THEM THAT WAY!)
enum KEYSYMBOL { // {{{
    Key0,
    Key1,
    Key2,
    Key3,
    Key4,
    Key5,
    Key6,
    Key7,
    Key8,
    Key9,
    KeyA,
    KeyAmpersand,
    KeyAsterisk,
    KeyAt,
    KeyB,
    KeyBackquote,
    KeyBackslash,
    KeyBackspace,
    KeyBreak,
    KeyC,
    KeyCapsLock,
    KeyCaret,
    KeyClear,
    KeyColon,
    KeyComma,
    KeyCompose,
    KeyD,
    KeyDelete,
    KeyDollar,
    KeyDown,
    KeyE,
    KeyEnd,
    KeyEquals,
    KeyEscape,
    KeyEuro,
    KeyExclaim,
    KeyF,
    KeyF1,
    KeyF10,
    KeyF11,
    KeyF12,
    KeyF13,
    KeyF14,
    KeyF15,
    KeyF2,
    KeyF3,
    KeyF4,
    KeyF5,
    KeyF6,
    KeyF7,
    KeyF8,
    KeyF9,
    KeyG,
    KeyGreater,
    KeyH,
    KeyHash,
    KeyHelp,
    KeyHome,
    KeyI,
    KeyInsert,
    KeyJ,
    KeyK,
    KeyKp0,
    KeyKp1,
    KeyKp2,
    KeyKp3,
    KeyKp4,
    KeyKp5,
    KeyKp6,
    KeyKp7,
    KeyKp8,
    KeyKp9,
    KeyKpDivide,
    KeyKpEnter,
    KeyKpEquals,
    KeyKpMinus,
    KeyKpMultiply,
    KeyKpPeriod,
    KeyKpPlus,
    KeyL,
    KeyLAlt,
    KeyLCtrl,
    KeyLMeta,
    KeyLShift,
    KeyLSuper,
    KeyLeft,
    KeyLeftBracket,
    KeyLeftParen,
    KeyLess,
    KeyM,
    KeyMenu,
    KeyMinus,
    KeyMode,
    KeyN,
    KeyNumLock,
    KeyO,
    KeyP,
    KeyPageDown,
    KeyPageUp,
    KeyPause,
    KeyPeriod,
    KeyPlus,
    KeyPower,
    KeyPrint,
    KeyQ,
    KeyQuestion,
    KeyQuote,
    KeyQuoteDbl,
    KeyR,
    KeyRAlt,
    KeyRCtrl,
    KeyRMeta,
    KeyRShift,
    KeyRSuper,
    KeyReturn,
    KeyRight,
    KeyRightBracket,
    KeyRightParen,
    KeyS,
    KeyScrollLock,
    KeySemicolon,
    KeySlash,
    KeySpace,
    KeySysReq,
    KeyT,
    KeyTab,
    KeyU,
    KeyUnderscore,
    KeyUndo,
    KeyUp,
    KeyV,
    KeyW,
    KeyWorld_0,
    KeyWorld_1,
    KeyWorld_10,
    KeyWorld_11,
    KeyWorld_12,
    KeyWorld_13,
    KeyWorld_14,
    KeyWorld_15,
    KeyWorld_16,
    KeyWorld_17,
    KeyWorld_18,
    KeyWorld_19,
    KeyWorld_2,
    KeyWorld_20,
    KeyWorld_21,
    KeyWorld_22,
    KeyWorld_23,
    KeyWorld_24,
    KeyWorld_25,
    KeyWorld_26,
    KeyWorld_27,
    KeyWorld_28,
    KeyWorld_29,
    KeyWorld_3,
    KeyWorld_30,
    KeyWorld_31,
    KeyWorld_32,
    KeyWorld_33,
    KeyWorld_34,
    KeyWorld_35,
    KeyWorld_36,
    KeyWorld_37,
    KeyWorld_38,
    KeyWorld_39,
    KeyWorld_4,
    KeyWorld_40,
    KeyWorld_41,
    KeyWorld_42,
    KeyWorld_43,
    KeyWorld_44,
    KeyWorld_45,
    KeyWorld_46,
    KeyWorld_47,
    KeyWorld_48,
    KeyWorld_49,
    KeyWorld_5,
    KeyWorld_50,
    KeyWorld_51,
    KeyWorld_52,
    KeyWorld_53,
    KeyWorld_54,
    KeyWorld_55,
    KeyWorld_56,
    KeyWorld_57,
    KeyWorld_58,
    KeyWorld_59,
    KeyWorld_6,
    KeyWorld_60,
    KeyWorld_61,
    KeyWorld_62,
    KeyWorld_63,
    KeyWorld_64,
    KeyWorld_65,
    KeyWorld_66,
    KeyWorld_67,
    KeyWorld_68,
    KeyWorld_69,
    KeyWorld_7,
    KeyWorld_70,
    KeyWorld_71,
    KeyWorld_72,
    KeyWorld_73,
    KeyWorld_74,
    KeyWorld_75,
    KeyWorld_76,
    KeyWorld_77,
    KeyWorld_78,
    KeyWorld_79,
    KeyWorld_8,
    KeyWorld_80,
    KeyWorld_81,
    KeyWorld_82,
    KeyWorld_83,
    KeyWorld_84,
    KeyWorld_85,
    KeyWorld_86,
    KeyWorld_87,
    KeyWorld_88,
    KeyWorld_89,
    KeyWorld_9,
    KeyWorld_90,
    KeyWorld_91,
    KeyWorld_92,
    KeyWorld_93,
    KeyWorld_94,
    KeyWorld_95,
    KeyX,
    KeyY,
    KeyZ
}; // }}}

// The possible key modifiers in ASCII-sorted order. (KEEP THEM THAT WAY!)
enum KEYMODIFIER {
    KeyModAlt,
    KeyModCaps,
    KeyModCtrl,
    KeyModLAlt,
    KeyModLCtrl,
    KeyModLMeta,
    KeyModLShift,
    KeyModMeta,
    KeyModMode,
    KeyModNum,
    KeyModRAlt,
    KeyModRCtrl,
    KeyModRMeta,
    KeyModRShift,
    KeyModShift
};

// The possible mouse states in ASCII-sorted order. (KEEP THEM THAT WAY!)
enum MOUSESTATE {
    LeftMouseButtonDown,
    MiddleMouseButtonDown,
    RightMouseButtonDown
};

// The possible mouse buttons in ASCII-sorted order. (KEEP THEM THAT WAY!)
enum MOUSEBUTTON {
    LeftMouseButton,
    MiddleMouseButton,
    MouseWheelDown,
    MouseWheelUp,
    RightMouseButton
};

// ML type: unit -> unit
// Gathers events. Only needs to be called if no other event handling is done.
EXTERNML value event_pump(value null);

// ML type: unit -> event option
// Returns a pending event if available.
EXTERNML value event_poll(value null);

// ML type: unit -> event
// Returns a pending event. If none is available, it waits for one to be so.
EXTERNML value event_wait(value null);

// ML type: eventfilter -> event list
// Gets a list of all events currently in the event queue, which match
// the given filter.
EXTERNML value event_get(value filter);

// ML type: eventfilter -> unit
// Clears all events matching the filter from the event queue.
EXTERNML value event_clear(value filter);
#endif

