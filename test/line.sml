load "MosGame";

structure M = MosGame;

M.init ();

val disp = M.Display.create_display (1000, 20);

fun processEvents () = case M.Event.poll () of
    NONE => ()
  | SOME e => (case e of
                 M.Event.QuitEvent => quit ()
               | _ => processEvents ())

fun drawStep (1020, n) = M.Image.save disp "line-out.png"
  | drawStep (i, n) =
    let
        val step = (n div 255) mod 6
        val pos = n mod 255

        val color = case step of
            0 => M.RGB (255, pos, 0)
          | 1 => M.RGB (255-pos, 255, 0)
          | 2 => M.RGB (0, 255, pos)
          | 3 => M.RGB (0, 255-pos, 255)
          | 4 => M.RGB (pos, 0, 255)
          | 5 => M.RGB (255, 0, 255-pos)

        val _ = M.Draw.draw_line disp (0, i) (i, 0) color true;
        val _ = M.Display.flip disp;
        val _ = processEvents ();
    in
        drawStep (i+1, n+1)
    end;

val _ = drawStep (0, 0);
val _ = quit();
