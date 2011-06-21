structure Draw :> DRAW =
struct
    datatype rectangle = Rectangle of point * dimensions * int
                       | FilledRectangle of point * dimensions

    val draw_pixel : Display.surface -> point -> color -> unit =
        app3 (dlsym mosgame_lib "draw_draw_pixel");

    val draw_line : Display.surface -> point -> point -> color -> bool -> unit  =
        app5 (dlsym mosgame_lib "draw_draw_line");

    val draw_rectangle : Display.surface -> rectangle -> color -> unit =
        app3 (dlsym mosgame_lib "draw_draw_rectangle");
end;
