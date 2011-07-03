structure Surface :> SURFACE =
struct
    type surface = Word.word
    datatype area = Full | Partial of point * dimensions

    val fill : surface -> area -> color -> unit =
        app3 (dlsym mosgame_lib "surface_fill");

    val blit : surface -> area -> surface -> point -> unit =
        app4 (dlsym mosgame_lib "surface_blit");
end;
