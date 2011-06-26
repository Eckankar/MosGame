local
    fun blend (RGB (r1, g1, b1)) (RGB (r2, g2, b2)) d =
        RGB ( ((r1 * d + r2 * (255-d)) div 255),
              ((g1 * d + g2 * (255-d)) div 255),
              ((b1 * d + b2 * (255-d)) div 255) )
      | blend _ _ _ = raise Domain

    fun add (RGB (r1, g1, b1)) (RGB (r2, g2, b2)) =
        if r1+r2 < 0 orelse r1+r2 > 255 orelse
           g1+g2 < 0 orelse g1+g2 > 255 orelse
           b1+b2 < 0 orelse b1+b2 > 255 then raise Fail "Invalid color add."
        else RGB (r1+r2, g1+g2, b1+b2)
      | add _ _ = raise Domain
in
    (* Base colors *)
    val Black = RGB (0, 0, 0)
    val White = RGB (255, 255, 255)

    val Red = RGB (255, 0, 0)
    val Green = RGB (0, 255, 0)
    val Blue = RGB (0, 0, 255)

    (* Grays *)
    val Gainsboro      = blend White Black 220
    val LightGray      = blend White Black 211
    val Silver         = blend White Black 192
    val DarkGray       = blend White Black 169
    val Gray           = blend White Black 128
    val DimGray        = blend White Black 105
    val LightSlateGray = RGB (119, 136, 153)
    val SlateGray      = RGB (112, 128, 144)
    val DarkSlateGray  = RGB (47, 79, 79)

    (* Blues *)
    val Cyan = add Green Blue
    val Aqua = Cyan

    (* Yellows *)
    val Yellow = add Red Green

    (* Purples *)
    val Magenta = add Red Blue
    val Fuchsia = Magenta

end;
