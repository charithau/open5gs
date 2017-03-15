#ifndef __TLV_MSG_H__
#define __TLV_MSG_H__

#include "core_tlv.h"
#include "core_pkbuf.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#define TLV_MAX_HEADROOM 16
#define TLV_VARIABLE_LEN 0
#define TLV_MAX_MORE 8
#define TLV_1_OR_MORE(__v) __v[TLV_MAX_MORE]

typedef enum {
    TLV_UINT8,
    TLV_UINT16,
    TLV_UINT24,
    TLV_UINT32,
    TLV_INT8,
    TLV_INT16,
    TLV_INT24,
    TLV_INT32,
    TLV_FIXED_STR,
    TLV_VAR_STR,
    TLV_NULL,
    TLV_MORE,
    TLV_COMPOUND,
    TLV_MESSAGE,
} tlv_type_e;

typedef struct _tlv_desc_t {
    tlv_type_e ctype;
    c_uint16_t type;
    c_uint16_t length;
    c_uint8_t  instance;
    c_uint16_t vsize;
    void *child_descs[];
} tlv_desc_t;

extern tlv_desc_t tlv_desc_more1;
extern tlv_desc_t tlv_desc_more2;
extern tlv_desc_t tlv_desc_more3;
extern tlv_desc_t tlv_desc_more4;
extern tlv_desc_t tlv_desc_more5;
extern tlv_desc_t tlv_desc_more6;
extern tlv_desc_t tlv_desc_more7;
extern tlv_desc_t tlv_desc_more8;

typedef struct _tlv_header_t {
    c_uint64_t presence;
} tlv_header_t;

/* 8-bit Unsigned integer */
typedef struct _tlv_uint8_t {
    tlv_header_t h;
    c_uint8_t v;
} tlv_uint8_t;

/* 16-bit Unsigned integer */
typedef struct _tlv_uint16_t {
    tlv_header_t h;
    c_uint16_t v;
} tlv_uint16_t;

/* 24-bit Unsigned integer */
typedef struct _tlv_uint24_t {
    tlv_header_t h;
    c_uint32_t v; /* Only 3 bytes valid */
} tlv_uint24_t;

/* 32-bit Unsigned integer */
typedef struct _tlv_uint32_t {
    tlv_header_t h;
    c_uint32_t v;
} tlv_uint32_t;

/* 8-bit Signed integer */
typedef struct _tlv_int8_t {
    tlv_header_t h;
    c_int8_t v;
} tlv_int8_t;

/* 16-bit Signed integer */
typedef struct _tlv_int16t {
    tlv_header_t h;
    c_int16_t v;
} tlv_int16_t;

/* 24-bit Signed integer */
typedef struct _tlv_int24_t {
    tlv_header_t h;
    c_int32_t v; /* Only 3 bytes valid */
} tlv_int24_t;

/* 32-bit Signed integer */
typedef struct _tlv_int32_t {
    tlv_header_t h;
    c_int32_t v;
} tlv_int32_t;

/* Octets */
typedef struct _tlv_octet_t {
    tlv_header_t h;
    c_uint8_t *v;
    c_uint32_t l;
} tlv_octet_t;

/* No value */
typedef struct _tlv_null {
    tlv_header_t h;
} tlv_null_t;

#define tlv_get_value(__tlv) (__tlv).v
#define tlv_get_length(__tlv) (__tlv).l
#define tlv_set_value(__m, __value) \
    __m.v = __value; __m.h.presence = 1
#define tlv_copy_value(__t_tlv, __s_tlv) \
    (__t_tlv).h = (__s_tlv).h; (__t_tlv).v = (__s_tlv).v

#define tlv_set_octet(__m, __value, __length) \
    __m.v = __value; __m.l = __length; __m.h.presence = 1
#define tlv_copy_octet(__t_tlv, __s_tlv) \
    (__t_tlv).h = (__s_tlv).h; (__t_tlv).v = (__s_tlv).v; \
    (__t_tlv).l = (__s_tlv).l

#define tlv_set_presence(__m) __m.h.presence = 1
#define tlv_is_present(__m) __m.h.presence

CORE_DECLARE(status_t) tlv_build_msg(
        pkbuf_t **pkbuf, tlv_desc_t *desc, void *msg, int mode);

CORE_DECLARE(status_t) tlv_parse_msg(
        void *msg, tlv_desc_t *desc, pkbuf_t *pkbuf, int mode);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __TLV_MSG_H__ */
