load "MosGame";
load "Random";

infixr $
fun a $ b = a b

structure M = MosGame;
structure E = M.Event;

val boardWidth = 30
val boardHeight = 16
val initialMines = 99

val headerHeight = 50
val tileSize = 25

val screenWidth = tileSize * boardWidth
val screenHeight = headerHeight + tileSize * boardHeight

val disp = M.Display.create_display (screenWidth, screenHeight)
val _ = M.Display.set_caption "Minesweeper"

val rng = Random.newgen ()

type coord = int * int
type screenCoord = int * int

datatype State = S of {
    revealed: (coord -> bool),
    flagged: (coord -> bool),
    flagsPlaced: int,
    hasMine: (coord -> bool),
    gameOver: bool
}

fun revealed (S state) = #revealed state
fun flagged (S state) = #flagged state
fun hasMine (S state) = #hasMine state
fun gameOver (S state) = #gameOver state
fun flagsPlaced (S state) = #flagsPlaced state

fun tileCoord (x, y) = (tileSize * x, headerHeight + tileSize * y)

val dNeighbors = [(1,1),(1,0),(1,~1),(0,1),(0,~1),(~1,1),(~1,0),(~1,~1)]

infix 6 ++
fun (x1, y1) ++ (x2, y2) = (x1+x2, y1+y2)

fun tileScore state coord =
  foldl (fn (d, a) => (if hasMine state (coord ++ d) then 1 else 0) + a)
        0 dNeighbors

fun invalidCoord (x, y) =
  x < 0 orelse y < 0 orelse x >= boardWidth orelse y >= boardHeight


fun reveal (state as S { revealed, flagged, hasMine, gameOver, flagsPlaced })
           coord =
  if revealed coord orelse flagged coord orelse invalidCoord coord
  then state
  else let
    val state' = S { revealed = fn c => c = coord orelse revealed c,
                     gameOver = hasMine coord,
                     flagged = flagged, hasMine = hasMine,
                     flagsPlaced = flagsPlaced }
  in
      (* if you click on a 0 square; spread out *)
      if not (hasMine coord) andalso tileScore state coord = 0
      then foldl (fn (d,s') => reveal s' (coord ++ d)) state'
                 dNeighbors
      else state'
  end

fun toggleFlag
      (state as S { revealed, flagged, hasMine, gameOver, flagsPlaced })
      coord =
  if revealed coord orelse invalidCoord coord
  then state
  else S { flagged = fn c =>
              if c = coord
              then not (flagged c)
              else flagged c,
           flagsPlaced = flagsPlaced + (if flagged coord then ~1 else 1),
           revealed = revealed, hasMine = hasMine, gameOver = gameOver }

val mine = M.Image.load "examples/minesweeper/mine.png"
val flag = M.Image.load "examples/minesweeper/flag.png"

val numbers = map (fn n =>
  M.Image.load $ "examples/minesweeper/" ^ Int.toString n ^ ".png") $
    List.tabulate(8, fn n => n+1)

fun number n = List.nth (numbers, n-1)

local
  fun digits_ n = n mod 10 :: (if n > 9 then digits_ (n div 10) else [])
in
  fun digits 0 = [0]
    | digits n = rev $ digits_ n
end

val uiText = M.Image.load "examples/minesweeper/uitext.png"

datatype UIRange = UIRange of int * int

fun uiRange s w = UIRange (s, w)

fun uiRangeArea (UIRange (s, w)) = M.Surface.Partial ((s, 0), (w, headerHeight))

val uiMines = uiRange 0 97

fun uiDigit 0 = uiRange 99 23
  | uiDigit 1 = uiRange 122 20
  | uiDigit 2 = uiRange 143 21
  | uiDigit 3 = uiRange 164 17
  | uiDigit 4 = uiRange 182 17
  | uiDigit 5 = uiRange 199 19
  | uiDigit 6 = uiRange 219 16
  | uiDigit 7 = uiRange 236 18
  | uiDigit 8 = uiRange 253 18
  | uiDigit 9 = uiRange 273 16

val uiSlash = uiRange 292 22

datatype UIText =
  UIMines | UISlash | UISpace of int | UIDigit of int

val uiTextNumber = map UIDigit o digits

fun uiRangeFromText UIMines = uiMines
  | uiRangeFromText (UIDigit n) = uiDigit n
  | uiRangeFromText (UISpace _) = raise Domain
  | uiRangeFromText UISlash = uiSlash

fun uiTextWidth (UISpace n) = n
  | uiTextWidth e =
      let
          val (UIRange (_,w)) = uiRangeFromText e
      in
        w
      end

fun generateMap mines =
    let
        fun gen f 0 = f
          | gen f n =
            let
                val x = Random.range (0, boardWidth) rng
                val y = Random.range (0, boardHeight) rng
            in
                if f (x, y)
                then gen f n
                else gen (fn (x', y') =>
                            (x' = x andalso y' = y) orelse f (x', y')
                         ) (n-1)
            end
    in
        gen (fn _ => false) initialMines
    end

val initialState = S {
    revealed = fn _ => false,
    flagged = fn _ => false,
    hasMine = generateMap (),
    gameOver = false,
    flagsPlaced = 0
}

val allTiles =
  List.concat $ List.tabulate (boardWidth, fn x =>
                  List.tabulate (boardHeight, fn y => (x, y) ) )

local
  fun renderUIText [] _ = ()
    | renderUIText (UISpace n :: es) offset =
        renderUIText es (offset + n)
    | renderUIText (e :: es) offset =
        let
          val area = uiRangeArea $ uiRangeFromText e
          val _ = M.Surface.blit uiText area disp (offset, 0)
        in
          renderUIText es (offset + uiTextWidth e)
        end
in
  fun drawHeader state =
    let
      val headerArea = M.Surface.Partial ((0, 0), (screenWidth, headerHeight))
      val _ = M.Surface.fill disp headerArea M.White
      val textToDraw =
        [UISpace 20, UIMines, UISpace 50] @
        uiTextNumber (flagsPlaced state) @
        [UISlash] @
        uiTextNumber initialMines
    in
      renderUIText textToDraw 0
    end
end

fun tileFromScreenCoord (x, y) =
  if y < headerHeight
  then NONE
  else SOME (x div tileSize, (y - headerHeight) div tileSize)

fun drawTile state coord =
  let
    val color =
      if revealed state coord then
        (if hasMine state coord then M.Red else M.Gainsboro)
      else M.Silver
    val pos = tileCoord coord
    val tileArea = M.Surface.Partial (pos, (tileSize, tileSize))
    val _ = M.Surface.fill disp tileArea color
    val tileBorder = M.Draw.Rectangle (pos, (tileSize, tileSize))
    val _ = M.Draw.draw_rectangle disp tileBorder M.Black
    val score = tileScore state coord
    fun draw img = M.Surface.blit img M.Surface.Full disp pos
  in
    if revealed state coord
    then (
      if hasMine state coord
      then draw mine
      else (
        if score > 0
        then draw $ number score
        else ()
      )
    ) else (
      if flagged state coord
      then draw flag
      else ()
    )
  end

fun drawBody state = (
  app (drawTile state) allTiles
);

fun draw state =
    let
        val _ = M.Surface.fill disp M.Surface.Full M.LightGray;
        val _ = drawHeader state
        val _ = drawBody state
        val _ = M.Display.flip disp
    in
        state
    end

fun handleClick state pos =
  if gameOver state then state
  else case tileFromScreenCoord pos of
      NONE => state
    | SOME coord =>
        if not $ revealed state coord
        then reveal state coord
        else state

fun handleRightClick state pos =
  if gameOver state then state
  else case tileFromScreenCoord pos of
      NONE => state
    | SOME coord =>
        if not $ revealed state coord
        then toggleFlag state coord
        else state

fun processEvents state = case M.Event.poll () of
    NONE => state
  | SOME e => (
        processEvents $ (case e of
          M.Event.QuitEvent =>
              ( quit (); state )
        | M.Event.MouseButtonEvent
            (M.Event.KeyPressed, M.Event.LeftMouseButton, pos) =>
              handleClick state pos
        | M.Event.MouseButtonEvent
            (M.Event.KeyPressed, M.Event.RightMouseButton, pos) =>
              handleRightClick state pos
        | _ => state)
      )

fun run state = run $ draw $ processEvents $ state

val _ = run initialState
