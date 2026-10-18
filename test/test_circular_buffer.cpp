#include "unity/unity.h"
#include "../src/core/CircularBuffer.h"
CircularBuffer TestBuffer;
void setUp(void){

}
void tearDown(void){

}
void first_test(void){
    TestBuffer.write(1);
    TEST_ASSERT_EQUAL_INT(1, TestBuffer.read());
}
void second_test(void){
    for(int i = 0; i < 1024; i++){
        TestBuffer.write(i);
        if(i == 1023){
            TEST_ASSERT_EQUAL_INT(0,TestBuffer.read());
        }
    }
}
void third_test(void){
        for(int i = 0; i < 1025; i++){
        TestBuffer.write(i);
        if(i == 1024){
            TEST_ASSERT_EQUAL_INT(1,TestBuffer.read());
        }
    }
}

int main(void){
    UNITY_BEGIN();
    RUN_TEST(first_test);
    RUN_TEST(second_test);
    RUN_TEST(third_test);
    return UNITY_END();
}