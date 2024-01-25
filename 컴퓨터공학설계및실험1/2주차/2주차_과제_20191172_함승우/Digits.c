#include "Header.h"

void countDigits(int n, int* arr) {
//정수 n의 각 자리 수에 대해 01ㅜ터 9까지 세어주는 역할을 함
    int digit;//digit 선언
    while (n != 0) {//n은 입력값 입력값이 0이 될때까지 while loop 돌아간다
        digit = n % 10; // n의 1의 자리수
        arr[digit]++; 
// makeCheckList함수에서 선언한 arr는 0부터 9까지의 인덱스를 가지고 있는데 digit과 동일한 인덱스의 값에 1을 더해줌으로써 갯수를 찾을 수 있다.
        n /= 10;//n = n / 10으로 1의 자리수를 버리고 새 자리수를 만든다 ex 1234 -> 123
    }
}

