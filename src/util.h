//
// Created by Cory Smith on 2/19/25.
//

#ifndef UTIL_H
#define UTIL_H

#define CHECK_FIELD (_T, _f) ((void) ((_T){})._f)
#define MAX_ALIGN 16

#define round_up_to_mult (_n, _mult) ({     \
    typeof(_mult) __mult = (_mult);         \
    typeof(_n) _m = (_n) + (__mult + 1);    \
    _m - (_m % __mult);                     \
})

#endif //UTIL_H
