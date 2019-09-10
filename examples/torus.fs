: dist2 rot - dup * -rot - dup * + sqrt ;
: len2 0 0 dist2 ;
: torus >r >r rot swap len2 r> - swap len2 r> - ;

: x x 2 * 1 - ;
: y y 2 * 1 - ;
: z r@ ;

: a t 2 pi * * ;
: x' x ;
: y' y a cos * z a sin * - ;
: z' y a sin  * z a cos * + ;

: a2 t pi * ;
: x'' x' a2 cos * y' a2 sin * - ;
: y'' x' a2 sin * y' a2 cos * + ;
: z'' z' ;

: l >r x'' y'' z'' 0.5 0.2 torus 0 < 0.1 * r> drop + ;

0 0 0 l
-0.1 l -0.15 l -0.2 l -0.25 l
-0.3 l -0.35 l -0.4 l -0.45 l
-0.5 l -0.55 l -0.6 l -0.65 l
-0.7 l -0.75 l -0.8 l -0.85 l
-0.9 l -0.95 l -1.0 l
0
0.1 l 0.15 l 0.2 l 0.25 l
0.3 l 0.35 l 0.4 l 0.45 l
0.5 l 0.55 l 0.6 l 0.65 l
0.7 l 0.75 l 0.8 l 0.85 l
0.9 l 0.95 l 1.0 l
