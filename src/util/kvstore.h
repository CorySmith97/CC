#pragma once

#include "alloc.h"
#include "type.h"
#include "strings.h"
#include "../level.h"

typedef struct kvstore kvstore_t;
typedef struct kv_entry kv_entry_t;
typedef struct any any_t;

typedef enum {
    NONE,
    I8,
    I16,
    I32,
    I64,
    U8,
    U16,
    U32,
    U64,
    F8,
    F16,
    F32,
    F64,
    BOOL,
    LEVEL,
} any_type_e;

typedef struct any {
    allocator_t allocator;
    any_type_e type;

    union {
        u8 u8_value;
        u16 u16_value;
        u32 u32_value;
        u64 u64_value;
        i8 i8_value;
        i16 i16_value;
        i32 i32_value;
        i64 i64_value;
        bool bool_value;
        f32 f32_value;
        f64 f64_value;
        v2 v2_value;
        v3 v3_value;
        string_t str_value;
        level_t level_value;
    };
}any_t;

#define any_const_i8(_v) ((any_t){.type = I8, .i8_value = (_v)})
#define any_const_i16(_v) ((any_t){.type = I16, .i16_value = (_v)})
#define any_const_i32(_v) ((any_t){.type = I32, .i32_value = (_v)})
#define any_const_i64(_v) ((any_t){.type = I64, .i64_value = (_v)})
#define any_const_u8(_v) ((any_t){.type = U8, .u8_value = (_v)})
#define any_const_u16(_v) ((any_t){.type = U16, .u16_value = (_v)})
#define any_const_u32(_v) ((any_t){.type = U32, .u32_value = (_v)})
#define any_const_u64(_v) ((any_t){.type = U64, .u64_value = (_v)})
#define any_const_bool(_v) ((any_t){.type = BOOL, .bool_value = (_v)})
#define any_const_f32(_v) ((any_t){.type = F32, .f32_value = (_v)})
#define any_const_f64(_v) ((any_t){.type = F64, .f64_value = (_v)})
#define any_const_level(_v) ((any_t){.type = LEVEL, .level_value = (_v)})


typedef struct kvstore {

} kvstore_t;


typedef struct kv_entry {
    char* key;
    any_t* value;
} kv_entry_t;
