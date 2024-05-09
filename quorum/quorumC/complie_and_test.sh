#!/bin/bash

# 현재 폴더에 있는 모든 C 파일 컴파일
gcc -c *.c

# 컴파일된 모든 o 파일로 라이브러리 파일 생성
ar rcs libquorum.a *.o

# 2회 상위 디렉토리로 이동
cd ../..

# go test 캐시 클리어
go clean --testcache

# make test 명령어 실행
make test

# 다시 원래 디렉토리로 돌아옴
cd -