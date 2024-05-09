#!/bin/bash

# 현재 폴더에 있는 각 C 파일을 컴파일하고 개별 라이브러리로 만듦
for file in *.c
do
    # 파일 이름에서 .c 확장자 제거
    name=$(basename "$file" .c)
    
    # C 파일 컴파일
    gcc -c "$file"
    
    # 컴파일된 오브젝트 파일로 라이브러리 파일 생성
    ar rcs "lib$name.a" "$name.o"
done

# 2회 상위 디렉토리로 이동
cd ../..

# make test 명령어 실행
make test

# 다시 원래 디렉토리로 돌아옴
cd -