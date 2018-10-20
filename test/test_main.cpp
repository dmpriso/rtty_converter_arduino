#include <Arduino.h>
#include <unity.h>

#include "us_timestamp.h"

#include "buffered_writer.h"
#include "readable_baudot_reader.h"
#include "debug_pin.h"

DebugPin pin;
BufferedWriter<128> writer(pin, 50.f);
ReadableBaudotReader reader(pin, 50.f);
const char* testString = "THE BIG BROWN FOX JUMPS OVER THE LAZY DOG.\n0123456789\nFINISHED";
const char* testStringMoving = testString;
int millisSinceLast;

void testUsTimestamp()
{
    UsTimestamp us1;
    delay(1000);
    UsTimestamp us2;

    TEST_ASSERT_INT32_WITHIN_MESSAGE(5000, 1000000, us2 - us1, "1mio us must have been elapsed");
    TEST_ASSERT_INT32_WITHIN_MESSAGE(5000, -1000000, us1 - us2, "-1mio us must have been elapsed");

    UsTimestamp usPast = us1 - 100;
    TEST_ASSERT_EQUAL_INT32_MESSAGE(100, us1 - usPast, "100us in the past");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(-100, usPast - us1, "-100us in the past");
    UsTimestamp us3 = usPast;
    us3 += 101;

    TEST_ASSERT_EQUAL_INT32_MESSAGE(1, us3 - us1, "1us in the future");
    TEST_ASSERT_EQUAL_INT32_MESSAGE(-1, us1 - us3, "-1us in the future");
    
    UsTimestamp us4 = us3;

    TEST_ASSERT_MESSAGE(us2 > us1, "checking >");
    TEST_ASSERT_MESSAGE(us2 >= us1, "checking >=");
    TEST_ASSERT_MESSAGE(us1 < us2, "checking <");
    TEST_ASSERT_MESSAGE(us1 <= us2, "checking <=");
    TEST_ASSERT_MESSAGE(us1 != us2, "checking !=");
    TEST_ASSERT_MESSAGE(!(us3 > us4), "checking > (2)");
    TEST_ASSERT_MESSAGE(!(us3 < us4), "checking < (2)");
    TEST_ASSERT_MESSAGE(us3 >= us4, "checking >= (2)");
    TEST_ASSERT_MESSAGE(us3 <= us4, "checking <= (2)");
    TEST_ASSERT_MESSAGE(us3 == us4, "checking ==");
}

void testNextChar()
{
    TEST_ASSERT_LESS_OR_EQUAL_INT32_MESSAGE(millisSinceLast + 2000, millis(), "timeout check for character");

    auto chr = reader.read();
    if (chr == 0)
        return;

    TEST_ASSERT_EQUAL_MESSAGE(chr, *testStringMoving, "checking received character");
    testStringMoving++;
    millisSinceLast = millis();
}

void setup()
{
    delay(2000);

    UNITY_BEGIN();
    RUN_TEST(testUsTimestamp);


    millisSinceLast = millis();
    writer.write(testString);
}

void loop()
{
    if (*testStringMoving == 0)
    {
        UNITY_END();
        return;
    }

    reader.loop();
    writer.loop();

    if (reader.hasData())
    {
        RUN_TEST(testNextChar);
    }
}
