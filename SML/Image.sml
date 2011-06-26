structure Image :> IMAGE =
struct
    type surface = Surface.surface

    val load : string -> surface =
        app1 (dlsym mosgame_lib "image_load")

    val save : surface -> string -> unit =
        app2 (dlsym mosgame_lib "image_save")
end;
