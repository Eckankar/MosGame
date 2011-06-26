signature IMAGE =
sig
    type surface = Surface.surface

    (* Loads the image at the given filename into a surface.
     * 
     * Supported formats: BMP, PNM (PPM/PGM/PBM), XPM, LBM, PCX, GIF, JPEG, PNG,
     * TGA, and TIFF *)
    val load : string -> surface
    (* Saves a surface to the given filename.
     *
     * Only supports saving to BMP. *)
    val save : surface -> string -> unit
end;
