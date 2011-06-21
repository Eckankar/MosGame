signature DRAW =
sig
(* Represents a rectangle to be drawn on screen *)
type rectangle

(* Creates a non-filled rectangle.
   Input: ((x, y), (w, h), t)
   The rectangle lies from (x, y) to (x+w-1, y+h-1), and has a
   border-width of t. The border lies on the inside of the rectangle. *)
val Rectangle : point * dimensions * int -> rectangle
(* Creates a filled rectangle.
   Input: ((x, y), (w, h))
   The rectangle lies from (x, y) to (x+w-1, y+h-1) *)
val FilledRectangle : point * dimensions -> rectangle

(* Draw a dot of the given color at the given point. *)
val draw_pixel : Display.surface -> point -> color -> unit

(* Draw a line segment of the given color between the first point and the second point.
   If the boolean argument is true, then the line will be antialiased. *)
val draw_line : Display.surface -> point -> point -> color -> bool -> unit;

(* Draw the given rectangle, with the given color. *)
val draw_rectangle : Display.surface -> rectangle -> color -> unit

end;
