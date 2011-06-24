signature EVENT =
sig
    (* Represents an event the application receives. *)
    datatype event =
        (* Produced when the application gains/loses focus in some way.
         * Parameter 1: Was focus gained?
         * Parameter 2: Which things were affected *)
        ActivationEvent of bool * focustype list
        (* Produced by keypress on the keyboard.
         * Parameter 1: Was the key pressed or released?
         * Parameter 2: Which key are we talking about?
         * Parameter 3: Which modifier keys are active? *)
      | KeyboardEvent of keystate * keysymbol * keymodifier list
        (* Produced by the movement of the mouse.
         * Parameter 1: Where is the mouse now?
         * Parameter 2: Which offset did the cursor just move?
         * Parameter 3: Which buttons are currently held? *)
      | MouseMotionEvent of point * offset * mousestate list
        (* Produced by the press of a button on a mouse.
         * Parameter 1: Was the key pressed or released?
         * Parameter 2: Which button are we talking about?
         * Parameter 3: Where is the mouse? *)
      | MouseButtonEvent of keystate * mousebutton * point
      (* TODO: Joystick events. *)
        (* Produced when the window is resized.
         * Parameter 1: Resulting size of the window. *)
      | ResizeEvent of dimensions
        (* Produced when the window has been modified by an outside
         * program, and needs to be redrawn. *)
      | ExposeEvent
        (* Produced when a quit is requested.
         * NB: The window will quit as soon as you receive this event! *)
      | QuitEvent
      (* XXX: UserEvent left out for now. *)
      (* TODO: SysWMEvent. *)
    (* The different types of events that exist.
     * Used for filtering. *)
    and eventtype =
        Activation
      | Keyboard
      | MouseMotion
      | MouseButton
      | Resize
      | Expose
      | Quit
    (* When allowed to pass more than one event as filter,
     * this type is used.
     * EventTypes [e1, ..., en] represents the events of types e1, ..., en.
     * NoEvents is equivalent to an EventTypes [].
     * AllEvents is equivalent to an EventTypes containing all different event
     * types. *)
    and eventfilter =
        NoEvents
      | AllEvents
      | EventTypes of eventtype list

    (* The types of focus that exist for ActivationEvent
     * MouseFocus = focus of the mouse,
     * InputFocus = focus of input device such as keyboard,
     * AppFocus   = focus of the application. *)
    and focustype = MouseFocus | InputFocus | AppFocus
    (* State of a keypress.
     * KeyPressed  = The key has just been depressed.
     * KeyReleased = The key has just been released. *)
    and keystate = KeyPressed | KeyReleased
    (* The possible keys that can be pressed in a KeyboardEvent.
     * The meanings of the keys can be found in keysymbols-explained.txt *)
    and keysymbol =
    (* keysymbols {{{ *)
         KeyBackspace
      |  KeyTab
      |  KeyClear
      |  KeyReturn
      |  KeyPause
      |  KeyEscape
      |  KeySpace
      |  KeyExclaim
      |  KeyQuoteDbl
      |  KeyHash
      |  KeyDollar
      |  KeyAmpersand
      |  KeyQuote
      |  KeyLeftParen
      |  KeyRightParen
      |  KeyAsterisk
      |  KeyPlus
      |  KeyComma
      |  KeyMinus
      |  KeyPeriod
      |  KeySlash
      |  Key0
      |  Key1
      |  Key2
      |  Key3
      |  Key4
      |  Key5
      |  Key6
      |  Key7
      |  Key8
      |  Key9
      |  KeyColon
      |  KeySemicolon
      |  KeyLess
      |  KeyEquals
      |  KeyGreater
      |  KeyQuestion
      |  KeyAt
      |  KeyLeftBracket
      |  KeyBackslash
      |  KeyRightBracket
      |  KeyCaret
      |  KeyUnderscore
      |  KeyBackquote
      |  KeyA
      |  KeyB
      |  KeyC
      |  KeyD
      |  KeyE
      |  KeyF
      |  KeyG
      |  KeyH
      |  KeyI
      |  KeyJ
      |  KeyK
      |  KeyL
      |  KeyM
      |  KeyN
      |  KeyO
      |  KeyP
      |  KeyQ
      |  KeyR
      |  KeyS
      |  KeyT
      |  KeyU
      |  KeyV
      |  KeyW
      |  KeyX
      |  KeyY
      |  KeyZ
      |  KeyDelete
      |  KeyWorld_0
      |  KeyWorld_1
      |  KeyWorld_2
      |  KeyWorld_3
      |  KeyWorld_4
      |  KeyWorld_5
      |  KeyWorld_6
      |  KeyWorld_7
      |  KeyWorld_8
      |  KeyWorld_9
      |  KeyWorld_10
      |  KeyWorld_11
      |  KeyWorld_12
      |  KeyWorld_13
      |  KeyWorld_14
      |  KeyWorld_15
      |  KeyWorld_16
      |  KeyWorld_17
      |  KeyWorld_18
      |  KeyWorld_19
      |  KeyWorld_20
      |  KeyWorld_21
      |  KeyWorld_22
      |  KeyWorld_23
      |  KeyWorld_24
      |  KeyWorld_25
      |  KeyWorld_26
      |  KeyWorld_27
      |  KeyWorld_28
      |  KeyWorld_29
      |  KeyWorld_30
      |  KeyWorld_31
      |  KeyWorld_32
      |  KeyWorld_33
      |  KeyWorld_34
      |  KeyWorld_35
      |  KeyWorld_36
      |  KeyWorld_37
      |  KeyWorld_38
      |  KeyWorld_39
      |  KeyWorld_40
      |  KeyWorld_41
      |  KeyWorld_42
      |  KeyWorld_43
      |  KeyWorld_44
      |  KeyWorld_45
      |  KeyWorld_46
      |  KeyWorld_47
      |  KeyWorld_48
      |  KeyWorld_49
      |  KeyWorld_50
      |  KeyWorld_51
      |  KeyWorld_52
      |  KeyWorld_53
      |  KeyWorld_54
      |  KeyWorld_55
      |  KeyWorld_56
      |  KeyWorld_57
      |  KeyWorld_58
      |  KeyWorld_59
      |  KeyWorld_60
      |  KeyWorld_61
      |  KeyWorld_62
      |  KeyWorld_63
      |  KeyWorld_64
      |  KeyWorld_65
      |  KeyWorld_66
      |  KeyWorld_67
      |  KeyWorld_68
      |  KeyWorld_69
      |  KeyWorld_70
      |  KeyWorld_71
      |  KeyWorld_72
      |  KeyWorld_73
      |  KeyWorld_74
      |  KeyWorld_75
      |  KeyWorld_76
      |  KeyWorld_77
      |  KeyWorld_78
      |  KeyWorld_79
      |  KeyWorld_80
      |  KeyWorld_81
      |  KeyWorld_82
      |  KeyWorld_83
      |  KeyWorld_84
      |  KeyWorld_85
      |  KeyWorld_86
      |  KeyWorld_87
      |  KeyWorld_88
      |  KeyWorld_89
      |  KeyWorld_90
      |  KeyWorld_91
      |  KeyWorld_92
      |  KeyWorld_93
      |  KeyWorld_94
      |  KeyWorld_95
      |  KeyKp0
      |  KeyKp1
      |  KeyKp2
      |  KeyKp3
      |  KeyKp4
      |  KeyKp5
      |  KeyKp6
      |  KeyKp7
      |  KeyKp8
      |  KeyKp9
      |  KeyKpPeriod
      |  KeyKpDivide
      |  KeyKpMultiply
      |  KeyKpMinus
      |  KeyKpPlus
      |  KeyKpEnter
      |  KeyKpEquals
      |  KeyUp
      |  KeyDown
      |  KeyRight
      |  KeyLeft
      |  KeyInsert
      |  KeyHome
      |  KeyEnd
      |  KeyPageUp
      |  KeyPageDown
      |  KeyF1
      |  KeyF2
      |  KeyF3
      |  KeyF4
      |  KeyF5
      |  KeyF6
      |  KeyF7
      |  KeyF8
      |  KeyF9
      |  KeyF10
      |  KeyF11
      |  KeyF12
      |  KeyF13
      |  KeyF14
      |  KeyF15
      |  KeyNumLock
      |  KeyCapsLock
      |  KeyScrollLock
      |  KeyRShift
      |  KeyLShift
      |  KeyRCtrl
      |  KeyLCtrl
      |  KeyRAlt
      |  KeyLAlt
      |  KeyRMeta
      |  KeyLMeta
      |  KeyLSuper
      |  KeyRSuper
      |  KeyMode
      |  KeyCompose
      |  KeyHelp
      |  KeyPrint
      |  KeySysReq
      |  KeyBreak
      |  KeyMenu
      |  KeyPower
      |  KeyEuro
      |  KeyUndo (* }}} end keysymbols *)
    (* Modifications that can be made on a keypress.
     * The meanings correspond to the keys in keysymbol.
     *
     * If KeyModLX or KeyModRX is active, then KeyModX should be, too. *)
    and keymodifier =
        KeyModLShift | KeyModRShift | KeyModShift
      | KeyModLCtrl  | KeyModRCtrl  | KeyModCtrl
      | KeyModLAlt   | KeyModRAlt   | KeyModAlt
      | KeyModLMeta  | KeyModRMeta  | KeyModMeta
      | KeyModNum    | KeyModCaps   | KeyModMode
    (* The state of a mouse button. *)
    and mousestate =
        LeftMouseButtonDown
      | MiddleMouseButtonDown
      | RightMouseButtonDown
    (* A mouse button *)
    and mousebutton =
        LeftMouseButton | MiddleMouseButton | RightMouseButton
      | MouseWheelUp    | MouseWheelDown

    (* Gathers events.
     * Only needs to be called if no other event handling is done. *)
    val pump : unit -> unit;

    (* Returns a pending event, if avilable. *)
    val poll : unit -> event option;

    (* Returns a pending event.
     * If none is available, it waits for one to be so. *)
    val wait : unit -> event;

    (* Gets a list of all events currently in the event queue, which
     * match the given filter. *)
    val get : eventfilter -> event list

    (* Clears all events matching the filter from the event queue. *)
    val clear : eventfilter -> unit;

end;
