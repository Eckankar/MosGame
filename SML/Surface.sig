signature SURFACE =
sig
    type surface

    (* Fills the surface with the given color. *)
    val fill           : surface -> color -> unit
end;
