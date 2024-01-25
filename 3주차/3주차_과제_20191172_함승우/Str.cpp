#include "Str.h"
#include <cstring>
#include <iostream>
using namespace std;

Str::Str(int leng) { //leng 크기의 string을 만든다.
	str = new char[leng+1]; //Null문자를 포함한 leng+1 크기의 배열을 생성한다.
				//class Str의 str
	for(int i =0; i < leng; i++){//index가 leng-1까지 공백을 넣어준다. 공백을 넣어 초기화하는 이유는 쓰레기값 때문이다.
		str[i] = ' '; // 공백으로 채운다.
	}
	str[leng] = '\0'; //마지막에 EOS 삽입
	len = leng; //입력받은 leng(str의 사이즈)를 len에 할당한다.
}//len은 항상 str의 길이를 저장하고 있어야한다.


Str::Str(char *neyong){//슬라이드의 main에 있는 Str a("I'm a girl");에 해당하는데 array를 neyong에 따라 만들고 strcpy를 사용한다.
	len = strlen(neyong);//len은 항상 str의 길이를 저장하고 있어야한다.
	str = new char[len+1];//class의 str과 len
	strcpy(str ,neyong);
}
Str::~Str(){//소멸자 delete를 사용해 str을 delete한다.
	delete[] str;
}

int Str::length(void){//string의 내용을 리턴하는 함수로, Class에서 정의한 len을 출력한다.
	return len;
}

char* Str::contents(void){ //슬라이드의 메인함수에 있는 함수로 string의 내용을 리턴한다.
	return str;
}

int Str::compare(class Str & a){ //string의 내용과 class Str타입을 비교하는 함수 // strcmp함수 사용 
	return strcmp(str, a.contents());
}

int Str::compare(char*a){//string의 내용과 char * a 타입을 비교하는 함수
	return strcmp(str, a);
}

void Str::operator=(char *a){//char *타입으로 입력 받았을 때
	delete[] str; // str을 우선 지우고
	len = strlen(a); //char * 타입이기 때문에 strlen함수를 사용하였고, len은 항상
			// str의 길이를 저장하고 있어야한다.
	str = new char[len+1]; //len의 길이에 따라 새로운 str을 만들고
	strcpy(str, a); //char *의 타입인 a를 복사한다.
}

void Str::operator=(class Str&a){//class Str타입이니
	delete[] str;//str을 우선 지운다.
	len = a.length();//class 멤버함수 중 length를 사용해서 len에 str의 길이를 저장한다.
	str = new char[len + 1];//str을 새로 만든다.
	strcpy(str, a.contents());//class type이기에 멤버 함수 contents를 사용한다.
}
