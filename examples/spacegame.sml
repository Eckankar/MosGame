load "MosGame";

infixr $
fun a $ b = a b

structure M = MosGame;
structure E = M.Event;

val disp = M.Display.create_display (1280, 800)
val _ = M.Display.set_caption "In space, no one can see your screen"

val moveUp      = ref false
val moveDown    = ref false
val moveLeft    = ref false
val moveRight   = ref false
val rotateLeft  = ref false
val rotateRight = ref false
val shoot       = ref false

val dummyVar    = ref false

val shipPos = ref (200 - 32, 400 - 32)
val shipRot = ref 18
val bullets = ref [] : (real * real * real * real) list ref

fun X p = let val (x, _) = !p in x end
fun Y p = let val (_, y) = !p in y end
fun clamp (v, s, c) = if s < 0 then (if v > c then v else c)
                               else (if v < c then v else c)
fun modX (p, dx, c) = let val (x, y) = !p in p := (clamp(x+dx, dx, c), y) end
fun modY (p, dy, c) = let val (x, y) = !p in p := (x, clamp(y+dy, dy, c)) end

val spaceBg         = M.Image.load "examples/spacegame/space-bg.png"
val spaceShipSprite = M.Image.load "examples/spacegame/spaceship.png"
val bulletSprite    = M.Image.load "examples/spacegame/bullet.png"

fun spaceShipRot rot = let val rm = rot mod 72
                           val x  = (rm mod 6) * 64
                           val y  = (rm div 6) * 64
                       in M.Surface.Partial ((x, y), (64, 64)) end

fun handleKey state symb = (case symb of
     E.KeyUp    => moveUp
   | E.KeyDown  => moveDown
   | E.KeyLeft  => moveLeft
   | E.KeyRight => moveRight
   | E.KeyA     => rotateLeft
   | E.KeyD     => rotateRight
   | E.KeySpace => shoot
   | _          => dummyVar) := state = E.KeyPressed

fun draw () = (
  M.Surface.blit spaceBg M.Surface.Full disp (0,0);
  map (fn (bx, by, dx, dy) =>
        M.Surface.blit bulletSprite M.Surface.Full
                       disp (floor(bx)-8, floor(by)-8)) (!bullets);
  M.Surface.blit spaceShipSprite (spaceShipRot (!shipRot)) disp (!shipPos);
  M.Display.flip disp
)

fun processEvents () = case M.Event.poll () of
    NONE => ()
  | SOME e => (
        (case e of
          M.Event.QuitEvent =>
              quit ()
        | (M.Event.KeyboardEvent (state, symb, _)) =>
              handleKey state symb
        | _ => ()
        );
        processEvents ()
      )

fun outOfBounds (x, y) = x < ~10 orelse x >= 1290 orelse y < ~10 orelse y >= 810
fun spawnBullet () = let
    val rotRad = 2.0 * Math.pi * real(!shipRot) / 72.0 - Math.pi * 0.5
  in
    bullets := (real (X shipPos + 32), real(Y shipPos + 32),
                20.0 * Math.cos(rotRad), 20.0 * Math.sin(rotRad)) :: !bullets
  end

fun moveBullets ((x,y,dx,dy), bs) =
  let
    val nb = (x+dx, y+dy, dx, dy)
    val (nx, ny, _, _) = nb
  in
    if outOfBounds (floor(nx), floor(ny)) then bs else nb::bs
  end

fun updateState () = let
    val _ = if !moveUp then modY(shipPos, ~10, 0) else ()
    val _ = if !moveDown then modY(shipPos, 10, 799-64) else ()
    val _ = if !moveLeft then modX(shipPos, ~10, 0) else ()
    val _ = if !moveRight then modX(shipPos, 10, 1279-64) else ()
    val _ = if !rotateLeft then shipRot := (!shipRot + 72 - 2) mod 72 else ()
    val _ = if !rotateRight then shipRot := (!shipRot + 2) mod 72 else ()
    val _ = if !shoot then spawnBullet () else ()
    val _ = bullets := foldl moveBullets [] (!bullets)
  in
    ()
  end

fun run () = run $ draw $ updateState $ processEvents $ ()

val _ = run ()
