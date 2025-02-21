#pragma once

#include <stdlib.h>
#include "../util.h"

typedef void (*llist_func_impl)(void*, void*, int);

#define LLIST_NODE(_T) struct { _T* next; }
#define LLIST(_T) struct { _T* head; }

#define llist_prepend(_field, _plist, _node) do {                   \
    CHECK_FIELD(typeof(*_plist), head);                             \
    ((llist_func_impl)(_llist_prepend_item))                        \
    ((_plist), (_node), __builtin_offsetof(typeof(*_node), _field)) \
    } while (0);

#define llist_init_list(_plist) ({  \
    typeof(_plist) __p = _plist;    \
    __p->head = NULL;               \
})

#define llist_init_node(_pnode) ({  \
    typeof(_pnode) __p = _pnode;    \
    __p->next = NULL;               \
})


void _llist_prepend_item(void *_list, void *n, int offset) {
    LLIST(void) *list = _list;
    LLIST_NODE(void) *fn = n + offset;

    if (list->head) {
        fn->next = list->head;
    }
    list->head = fn;
}
