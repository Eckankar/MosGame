load "MosGame";

structure M = MosGame;

M.init ();

val s = M.Image.load "examples/loadsave/test.png";

M.Image.save s "examples/loadsave/test.bmp";

M.quit ();

quit ();
