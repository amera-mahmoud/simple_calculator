/* 
 * File:   mcal_std_types.h
 * Author: FiX-DEll
 *
 * Created on February 20, 2024, 12:16 AM
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/*------------------------Include section-------------------------------*/
#include "compiler.h"
#include "std_libraries.h"

/*------------------------Data Type Declaration section-----------------*/
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef signed char     sint8;
typedef signed short    sint16;
typedef signed long     sint32;
//typedef float           float32;

typedef uint8 std_ReturnType;

/*------------------------Macro Declaration section---------------------*/
#define E_OK     (std_ReturnType)0x01
#define E_NOT_OK (std_ReturnType)0x00

/*------------------------Macro Function Declaration section------------*/
/*------------------------Function Declaration section------------------*/


#endif	/* MCAL_STD_TYPES_H */

