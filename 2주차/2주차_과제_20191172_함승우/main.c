#include "Header.h"
int main(void) {
    int count, num; //count, num을 선언한다.
    scanf("%d", &count); 
//count는 첫 줄에 입력받는데, 이는 앞으로 프로그램을 행할 횟수를 의미한다.
    for (int i = 0; i < count; i++) {
        scanf("%d", &num);//최종페이지인 num을 입력받는다.
        makeCheckList(num);
//makeCheckList함수에 num을 입력해 checklist인 arr를 프린트 하게끔 만든다.
    }
    return 0;
}


