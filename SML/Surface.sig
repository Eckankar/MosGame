signature SURFACE =
sig
    type surface
    type area

    (* Represents the entire area of the surface. *)
    val Full           : area
    (* Represents a partial area of the surface.
     * Input: ((x, y), (w, h))
     * Represents the area with top left corner in (x, y),
     * with width w, and height h. *)
    val Partial        : point * dimensions -> area

    (* Fills the given area of the surface with the given color. *)
    val fill           : surface -> area -> color -> unit

    (* Draws the contents of a surface onto another surface.
     * Input: source area target pos
     * Blits the part of the source specified by area onto the target,
     * with top left corner in pos. *)
    val blit           : surface -> area -> surface -> point -> unit
end;
