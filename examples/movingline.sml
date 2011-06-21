load "MosGame";

structure M = MosGame;

M.init ();

val disp = M.Display.create_display (800, 600);

datatype updown = Up | Down;
fun drawStep (1400, Down, n) = drawStep (1400, Up, n)
  | drawStep (0, Up, n) = drawStep (0, Down, n)
  | drawStep (i, dir, n) =
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

        val _ = M.Display.fill disp M.Black;
        val _ = M.Draw.draw_line disp (0, i) (i, 0) color true;
        val _ = M.Display.flip disp;
        val caption = "i = " ^ Int.toString i;
        val _ = M.Display.set_caption caption;
    in
        drawStep (if dir = Down then i+1 else i-1, dir, n+1)
    end;

val _ = drawStep (0, Down, 0);
