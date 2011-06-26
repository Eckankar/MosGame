structure Display :> DISPLAY =
struct
    type surface = Surface.surface

    val create_display : dimensions -> surface =
        app1 (dlsym mosgame_lib "display_create_display");

    val flip : surface -> unit =
        app1 (dlsym mosgame_lib "display_flip");

    val set_caption : string -> unit =
        app1 (dlsym mosgame_lib "display_set_caption");

    val get_caption : unit -> string =
        app1 (dlsym mosgame_lib "display_get_caption");
end;
