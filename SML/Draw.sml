structure Draw :> DRAW =
struct
    datatype rectangle = Rectangle of point * dimensions
                       | FilledRectangle of point * dimensions
    datatype circle = Circle of point * int
                    | AntiAliasedCircle of point * int
                    | FilledCircle of point * int

    val draw_pixel : Display.surface -> point -> color -> unit =
        app3 (dlsym mosgame_lib "draw_draw_pixel");

    val draw_line : Display.surface -> point -> point -> color -> bool -> unit  =
        app5 (dlsym mosgame_lib "draw_draw_line");

    val draw_rectangle : Display.surface -> rectangle -> color -> unit =
        app3 (dlsym mosgame_lib "draw_draw_rectangle");

    val draw_circle : Display.surface -> circle -> color -> unit =
        app3 (dlsym mosgame_lib "draw_draw_circle");
end;
