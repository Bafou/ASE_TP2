/*
 * pingpongpang.c
 * Authors : Honoré NINTUNZE & Antoine PETIT
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "contexte.h"


struct ctx_s ctx_ping;
struct ctx_s ctx_pong;
struct ctx_s ctx_pang;

func_t f_ping;
func_t f_pong;
func_t f_pang;

int main(int argc, char *argv[])
{
  init_ctx(&ctx_ping,16384,f_ping, NULL);
  init_ctx(&ctx_pong,16384,f_pong, NULL);
  init_ctx(&ctx_pang,16384,f_pang, NULL);
  switch_to_ctx(&ctx_ping);

  exit(EXIT_SUCCESS);
}

void f_ping(void * arg)
{
  while(1)
    {
      printf("A");
      switch_to_ctx(&ctx_pong);
      printf("B");
      switch_to_ctx(&ctx_pong);
      printf("C");
      switch_to_ctx(&ctx_pong);
    }
}

void f_pong(void * arg)
{
    while(1)
    {
      printf("1");
      switch_to_ctx(&ctx_pang);
      printf("2");
      switch_to_ctx(&ctx_pang);
    }
}

void f_pang(void * arg)
{
  int i;
  for(i = 1; i<=100;++i)
    {
      printf("x%d",i);
      switch_to_ctx(&ctx_ping);
    }
}
