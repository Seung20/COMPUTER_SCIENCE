cc=gcc 
cflags = -W -g
target = Starwars
objects = main.o CheckList.o Digits.o 

$(target) : $(objects)
	$(cc) $(cflags) -o $(target) $(objects)
%.o : %.c
	$(cc) $(cflags) -c -o $@ $<

main.o Digits.o CheckList.o : Header.h
.PHONY : clean
clean:
	rm $(target) $(objects)
#1 cc를 gcc로 매크로화
#2 gcc 컴파일 옵션으로 W는 추가적인 경고와, g는 디버그 정보를 추가하는 의미가 있다.
#3 빌드 대상의 이름이 Starwars이다, 실행파일의 이름이 된다.
#4 ‘objects’라는 변수를 각 오브젝트 파일의 목록으로 설정한다.
#6~7 target 파일을 위한 object 파일들이 필요하고, gcc 컴파일러를 사용하여 실행파일을 만드는 과정이다.
#8~9 $@ $<는 각각 현재 target 파일, 현재 의존성 중 첫번째 파일의 이름을 나타내고, 이를 통해서 c확장자를 가진 소스파일로 o확장자를가진 목표 파일들로 만드는 과정이다. 
#11 Header.h 파일이 변경된다면 다시 이 오브젝트 파일들도 컴파일해야 함을 알려준다.
#12 Phony는 실제 파일이 아니고, 더미 target이고, .phony를 사용해서 .phony에 clean을 정의한다.
#13~14 타겟과 오브젝트 파일들을 모두 삭제하라는 명령어이다.
