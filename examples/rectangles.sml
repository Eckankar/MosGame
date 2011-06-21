load "MosGame";

structure M = MosGame;

M.init ();

val disp = M.Display.create_display (800, 600);

val filledRect =      M.Draw.FilledRectangle ( (100, 100), (300, 100) )
val outlineRect =     M.Draw.Rectangle ( (500, 150), (50, 100), 10)
val outlineRect2 =    M.Draw.Rectangle ( (500, 150), (50, 100), 1)
val overlappingRect = M.Draw.FilledRectangle ( (200, 50), (100, 400) )

val transparentWhite = M.RGBA (255, 255, 255, 64)

val _ = M.Draw.draw_rectangle disp filledRect M.Red
val _ = M.Draw.draw_rectangle disp outlineRect M.Blue
val _ = M.Draw.draw_rectangle disp outlineRect2 M.Green
val _ = M.Draw.draw_rectangle disp overlappingRect transparentWhite
val _ = M.Display.flip disp;

fun foo x = foo (x+0)
val _ = foo 10
