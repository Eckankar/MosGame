signature DISPLAY =
sig
    type surface = Surface.surface

    (* Creates a new display of the given dimensions. *)
    val create_display : dimensions -> surface
    (* Switches the double-buffers. *)
    val flip           : surface -> unit
    (* Fills the surface with the given color. *)
    val fill           : surface -> color -> unit
    (* Sets the caption of the current window. *)
    val set_caption    : string -> unit
    (* Gets the caption of the current window. *)
    val get_caption    : unit -> string
end;
