#ifndef __LABS_CONFIG_H
#define __LABS_CONFIG_H

#define configQUEUE_SIZE        96

/*!< Signed integer types  */
typedef signed char     int8_t;
typedef signed short    int16_t;
typedef signed long     int32_t;

typedef int32_t         s32;
typedef int16_t         s16;
typedef int8_t          s8;

/*!< Unsigned integer types  */
typedef unsigned char   uint8_t;
typedef unsigned short  uint16_t;
typedef unsigned long   uint32_t;

typedef uint32_t        u32;
typedef uint16_t        u16;
typedef uint8_t         u8;

typedef enum { FALSE = 0,
               TRUE = !FALSE } bool;

typedef enum { RESET = 0,
               SET = !RESET } FlagStatus;

typedef enum { DISABLE = 0,
               ENABLE = !DISABLE } FunctionalState;

typedef enum { ERROR = 0,
               SUCCESS = !ERROR } ErrorStatus;

#define NULL            (0)
#define U8_MAX          (255)
#define S8_MAX          (127)
#define S8_MIN          (-128)
#define U16_MAX         (65535u)
#define S16_MAX         (32767)
#define S16_MIN         (-32768)
#define U32_MAX         (4294967295uL)
#define S32_MAX         (2147483647)
#define S32_MIN         (-2147483648uL)

#define CHAR_BITS_NUM   (8u)
#define SHORT_BITS_NUM  (16u)
#define LONG_BITS_NUM   (32u)

#endif /* __LABS_CONFIG_H */