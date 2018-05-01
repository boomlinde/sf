128 width 128 height
: n .5 - 2 * ;
: z y n 2 * / 1 mod ;
: m 2 * 2 mod floor ;
: c t + m swap m + 2 mod 0 = ;
x n z 2 z c y n abs *
