structure Surface :> SURFACE =
struct
    type surface = int

    val fill : surface -> color -> unit =
        app2 (dlsym mosgame_lib "surface_fill");
end;
