128 width 128 height
: t t pi * 2 / ;
: l * + sin ;
: r t 1 y t + 4 l + 1.57 ;
: x x 4 * 2 - t y 3 l + ;
: v 2dup x >= swap x < * -rot swap - l ;
: a r 4 l ; : b r 1 l ;
: c r 2 l ; : d r 3 l ;
0 d a v a b v b c v c d v 0.1 0.2
