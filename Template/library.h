/**
  ******************************************************************************
  * @file    library.h
  * @author  Leo Newens (LongNDT5)
  * @version
  * @date
  * @brief
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 longnguyen-leonewens (Github)
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
#ifndef LIBRARY_H_
#define LIBRARY_H_

/******************************************************************************
 * INCLUDES
 ******************************************************************************/

/******************************************************************************
 * EXPORTED TYPEDEF
 ******************************************************************************/

/**
 * @brief Struct example
 * @note  Struct shoulde be name [Module name]_[Function of Struct]TypeDef
 * @note  Struct members should capitalized every word
 */
typedef struct __Module_DoSomethingTypeDef
{
    int NumOne;                       /*!< Explain functionality */
    int NumSecond;                       /*!< Explain functionality */
    int NumThird;                       /*!< Explain functionality */
}Module_DoSomethingTypeDef;

/******************************************************************************
 * EXPORTED CONSTANTS
 ******************************************************************************/

/** @defgroup Example of constants
 * @{
 */
#define MODULE_CONST_1
#define MODULE_CONST_2
/**
 * @}
 */

/******************************************************************************
 * EXPORTED MACROS
 ******************************************************************************/

/**
 * @brief Example of macros
 */
#define MARCO(X)                  (X+3)

/******************************************************************************
 * EXPORTED VARIABLES
 ******************************************************************************/

/******************************************************************************
 * EXPORTED FUNCTIONS PROTOTYPES
 ******************************************************************************/

/******************************************************************************
 * EXPORTED FUNCTIONS
 ******************************************************************************/

#endif /* LIBRARY_H_ */
