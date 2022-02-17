/*----------------------------------------------------------------------------------------------------------
[FILE NAME]: std_types.h

[AUTHOR]: Manar Mohamed Salah

[DATE CREATED]: Feb 6, 2020

[DESCRIPTION]: AVR types abstraction.

-----------------------------------------------------------------------------------------------------------*/

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/* Boolean Data Type */
typedef unsigned char bool;

/* Boolean Values */
#ifndef FALSE
#define FALSE       (0u)
#endif

#ifndef TRUE
#define TRUE        (1u)
#endif

#define HIGH        (1u)
#define LOW         (0u)

/* This is used to define the void pointer to zero definition. */
#define NULL_PTR          ((void *)0)

typedef unsigned char         uint8;
typedef signed char           sint8;
typedef unsigned short        uint16;
typedef signed short          sint16;
typedef unsigned long         uint32;
typedef signed long           sint32;
typedef unsigned long long    uint64;
typedef signed long long      sint64;
typedef float                 float32;
typedef double                float64;

#endif /* STD_TYPE_H_ */
