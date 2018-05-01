128 width 128 height
: xp t pi * 4 / sin .3 * ;
: yp t pi * cos .3 * ;
: d dup * swap dup * + sqrt ;
: p y .5 - + swap x .5 - + d 1 swap - 5 pow ;
: col dup dup .2 > swap .4 < and swap .2 - 5 * * ;
xp yp p xp negate yp negate p + col
dup 4 pow dup rot swap .1 +
