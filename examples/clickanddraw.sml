load "MosGame";

structure M = MosGame;

M.init ();

val disp = M.Display.create_display (800, 600);

fun processEvents () = case M.Event.poll () of
    NONE => ()
  | SOME e =>
    (case e of
        M.Event.QuitEvent => quit ()
     | (M.Event.MouseMotionEvent ((x,y), (dx,dy), ms)) =>
         ((if List.exists (fn M.Event.LeftMouseButtonDown => true | _ => false) ms
           then
             (M.Draw.draw_line disp (x, y) (x+dx, y+dy) M.Red true;
              M.Display.flip disp)
           else ()); processEvents ())
               | _ => processEvents ())

fun a () = ( processEvents (); a () );

a ();
