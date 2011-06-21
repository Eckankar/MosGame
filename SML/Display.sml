structure Display :> DISPLAY =
struct
    type surface = int

    val create_display : dimensions -> surface =
        app1 (dlsym mosgame_lib "display_create_display");

    val flip : surface -> unit =
        app1 (dlsym mosgame_lib "display_flip");

    val fill : surface -> color -> unit =
        app2 (dlsym mosgame_lib "display_fill");

    val set_caption : string -> unit =
        app1 (dlsym mosgame_lib "display_set_caption");

    val get_caption : unit -> string =
        app1 (dlsym mosgame_lib "display_get_caption");
end;
