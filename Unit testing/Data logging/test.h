/**
 * @file assert_param.h
 * @author TuanPA41
 * @brief Test for Job5: log data
 * @version 0.1
 * @date 2023-09-15
 *
 * @copyright Copyright (c) 2023
 *
 */
#ifndef _TEST_H_
#define _TEST_H_

/**
 * @brief enum status return
 *
 */

typedef enum
{
    TEST_PASS,
    TEST_FAILED,
} Test_status_t;

void test_logData(void);

#endif /* _TEST_FLASH_H_ */
