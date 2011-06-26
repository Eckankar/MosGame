load "MosGame";

structure M = MosGame;

M.init ();

val disp = M.Display.create_display (800, 600);

val filledRect =        M.Draw.FilledRectangle ( (100, 100), (300, 100) )
val outlineRect =       M.Draw.Rectangle ( (500, 150), (50, 100), 10)
val outlineRect2 =      M.Draw.Rectangle ( (500, 150), (50, 100), 1)
val overlappingRect =   M.Draw.FilledRectangle ( (200, 50), (100, 400) )
val circle =            M.Draw.Circle ( (500, 400), 100 )
val aacircle =          M.Draw.AntiAliasedCircle ( (600, 400), 100 )
val filledCircle =      M.Draw.FilledCircle ( (500, 450), 50 )
val overlappingCircle = M.Draw.FilledCircle ( (480, 472), 40 )

val transparentWhite = M.RGBA (255, 255, 255, 64)
val transparentHotPink = M.RGBA (255, 105, 180, 192)

val _ = M.Draw.draw_rectangle disp filledRect M.Red
val _ = M.Draw.draw_rectangle disp outlineRect M.Blue
val _ = M.Draw.draw_rectangle disp outlineRect2 M.Green
val _ = M.Draw.draw_circle disp filledCircle M.Red
val _ = M.Draw.draw_circle disp circle M.Green
val _ = M.Draw.draw_circle disp aacircle M.Cyan
val _ = M.Draw.draw_circle disp overlappingCircle transparentHotPink
val _ = M.Draw.draw_rectangle disp overlappingRect transparentWhite
val _ = M.Display.flip disp;

fun processEvents () = case M.Event.poll () of
    NONE => ()
  | SOME e => (case e of
                 M.Event.QuitEvent => quit ()
               | _ => processEvents ());

fun rep () = (processEvents () ; rep ());
rep ();
