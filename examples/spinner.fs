128 width 128 height
: t t 2 * pi * ;
: x x 0.5 - ;
: y y 0.5 - ;
: d x x * y y * + sqrt 8 pi * t sin + * ;
: a y x atan2 8 * d 2 * + ;
: o 0.5 * 0.5 + ;
0 d t + sin o a t + sin o * 0.5
