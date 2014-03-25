load "MosGame";

structure M = MosGame;

M.init ();

val disp = M.Display.create_display (100, 100);

val filledRect =        M.Draw.FilledRectangle ( (10, 10), (50, 20) )
val outlineRect =       M.Draw.Rectangle ( (30, 20), (40, 25) )
val overlappingRect =   M.Draw.FilledRectangle ( (25, 5), (15, 30) )
val circle =            M.Draw.Circle ( (50, 50), 20 )
val aacircle =          M.Draw.AntiAliasedCircle ( (70, 50), 20 )
val filledCircle =      M.Draw.FilledCircle ( (50, 60), 10 )
val overlappingCircle = M.Draw.FilledCircle ( (45, 65), 7 )

val transparentWhite = M.RGBA (255, 255, 255, 64)
val transparentHotPink = M.RGBA (255, 105, 180, 192)

val _ = M.Draw.draw_rectangle disp filledRect M.Red
val _ = M.Draw.draw_rectangle disp outlineRect M.Blue
val _ = M.Draw.draw_circle disp filledCircle M.Red
val _ = M.Draw.draw_circle disp circle M.Green
val _ = M.Draw.draw_circle disp aacircle M.Cyan
val _ = M.Draw.draw_circle disp overlappingCircle transparentHotPink
val _ = M.Draw.draw_rectangle disp overlappingRect transparentWhite
val _ = M.Display.flip disp;
val _ = M.Image.save disp "shapes-out.png";

val _ = M.quit();
val _ = quit();
