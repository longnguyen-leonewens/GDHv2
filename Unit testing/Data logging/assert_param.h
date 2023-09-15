/**
 * @file assert_param.h
 * @author TuanPA41
 * @brief Assert check param
 * @version 0.1
 * @date 2023-09-13
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _ASSERT_PARAM_H_
#define _ASSERT_PARAM_H_

#define ASSERT(condition)\
    do{\
        if(!(condition))\
        {\
            while (1)\
            {\
                /* do nothing */\
            }\
        }\
    }while (0)

#endif /* _ASSERT_PARAM_H_ */
