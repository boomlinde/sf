128 width 128 height
: ' .5 - 2 * ;
: d x ' dup * y ' dup * + sqrt ;
: p 2 * pi * cos .5 * .5 + ;
: col dup dup p swap 1 3 / + p rot 2 3 / + p ;
y ' x ' atan2 pi 2 * / t + d t 2 pi * * sin * + col
