#!/bin/bash

# 오브젝트 파일을 저장할 디렉토리 생성 (이미 존재하는 경우 무시)
mkdir -p obj

# 현재 폴더에 있는 모든 C 파일 컴파일, 오브젝트 파일은 obj 디렉토리에 저장
for file in *.c
do
    gcc -c "$file" -o "obj/$(basename "$file" .c).o"
done

# 컴파일된 모든 o 파일로 라이브러리 파일 생성
ar rcs libquorum.a obj/*.o

# 2회 상위 디렉토리로 이동
cd ../..

# go test 캐시 클리어
go clean --testcache

# make test 명령어 실행
make test

# 다시 원래 디렉토리로 돌아옴
cd -