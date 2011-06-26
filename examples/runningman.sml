load "MosGame";

structure M = MosGame;

M.init ();

val disp = M.Display.create_display (128, 128);
M.Display.set_caption "The Running Man";

fun processEvents () = case M.Event.poll () of
    NONE => ()
  | SOME e => (case e of
                 M.Event.QuitEvent => quit ()
               | _ => processEvents ())

val man = M.Image.load "examples/runningman/platformer_sprites_base.png"

fun frameRect n =
    let
        val x = (n mod 8) * 64;
        val y = (n div 8) * 64;
    in
        M.Surface.Partial ((x, y), (64, 64))
    end;

val frame_start = 4;
val frame_end = frame_start + 8;
val frame_delay = Time.fromMilliseconds (1000 div 8);

fun draw i t =
    if i >= frame_end then draw frame_start t
    else if Time.< (Time.now (), t) then draw i t
    else (
        M.Surface.fill disp M.Surface.Full M.Black;
        M.Surface.blit man (frameRect i) disp (32, 32);
        M.Display.flip disp;
        processEvents ();
        draw (i+1) (Time.+ (Time.now (), frame_delay))
    );

draw frame_start (Time.now ())
