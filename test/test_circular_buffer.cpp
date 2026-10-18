#include "unity/unity.h"
#include "../src/core/CircularBuffer.h"
CircularBuffer TestBuffer;
void setUp(void){

}
void tearDown(void){

}
void buffer_should_return_1(void){
    TestBuffer.write(1);
    TEST_ASSERT_EQUAL_INT(1, TestBuffer.read());
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(buffer_should_return_1);
    return UNITY_END();
}