load "MosGame";

structure M = MosGame;

M.init ();

val disp = M.Display.create_display (128, 128);

val man = M.Image.load "../examples/runningman/platformer_sprites_base.png"

fun frameRect n =
    let
        val x = (n mod 8) * 64;
        val y = (n div 8) * 64;
    in
        M.Surface.Partial ((x, y), (64, 64))
    end;

val _ = M.Surface.fill disp M.Surface.Full M.Red;
val _ = M.Surface.blit man (frameRect 7) disp (31, 32);
val _ = M.Display.flip disp;
val _ = M.Image.save disp "blit-out.png";
val _ = M.quit ();
quit();
