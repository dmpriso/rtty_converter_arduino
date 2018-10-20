#include <Arduino.h>
#include <unity.h>

#include "us_timestamp.h"

void testUsTimestamp()
{
    UsTimestamp us1;
    delay(1000);
    UsTimestamp us2;

    TEST_ASSERT_INT32_WITHIN_MESSAGE(5000, 10000000, us2 - us1, "1mio us must have been elapsed");
    TEST_ASSERT_INT32_WITHIN_MESSAGE(5000, -10000000, us1 - us2, "-1mio us must have been elapsed");

    UsTimestamp usPast = us1 - 100;
    TEST_ASSERT_EQUAL_INT32_MESSAGE(100, us1 - usPast, "100us in the past");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(100, usPast - us1, "-100us in the past");
    UsTimestamp us3 = usPast;
    us3 += 101;

    TEST_ASSERT_EQUAL_INT32_MESSAGE(us3 - us1, 1, "1us in the future");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(us1 - us3, -1, "-1us in the future");

    UsTimestamp us4 = us3;
}

void setup()
{
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(testUsTimestamp);
}

void loop()
{
    UNITY_END();
}