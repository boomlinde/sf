: l dup * swap dup * + sqrt ;
: o rot swap l .5 - swap l .2 - ;
: a t 2 pi * * ; : b t .25 pi * * ;
: y y 2 * 1 - ; : x x 2 * 1 - ;
: z y a sin  * r@ a cos * + ;
: y y a cos * r@ a sin * - ;
: q x b cos * y b sin * - ;
: w x b sin * y b cos * + ;
: s q w z o 0 < 0.1 * + r> .05 + >r ;
0 0 -.65 >r s s s s s s s s s s s s s s
0 s s s s s s s s s s s s s r> drop
