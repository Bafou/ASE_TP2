CC= gcc

all : pingpong

pingpong :ping_pong.c
	$(CC) -m32 -o pingpong contexte.c ping_pong.c

pingpongpang :ping_pong_pang.c
	$(CC) -m32 -o pingpongpang contexte.c ping_pong_pang.c
