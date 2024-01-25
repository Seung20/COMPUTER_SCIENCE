#include "Header.h"

void makeCheckList(int num) {
    int arr[10] = { 0 }; //인덱스가 0부터 9인 arr를 선언하고 0으로 초기화한다 
    for (int i = 1; i <= num; i++) {
        countDigits(i, arr); 
//num은 user가 입력한 값으로, i는 1페이지 부터 num까지 0부터 9의 정수의 개수를 세어 arr에 저장한다.
    }
    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
//arr의 10가지(0부터 9까지) 인덱스에 해당하는 값을 출력한다. 이는 1부터 num까지 각 정수의 개수에 해당한다.
    }
    printf("\n");//한줄 띄고 또 다른 값을 입력받을 준비한다.
}
