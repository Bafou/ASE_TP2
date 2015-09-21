#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "contexte.h"

int init_ctx (struct ctx_s *ctx, int stack_size, func_t *f, void *args) {
  ctx->stack = (unsigned char*) malloc (stack_size);
  if (ctx->stack == NULL) return 0;
  ctx->ebp = &ctx->stack[stack_size - sizeof(void *)];
  ctx->esp = &ctx->stack[stack_size - sizeof(void *)];
  ctx->state = CTX_READY;
  ctx->f = f;
  ctx->args= args;
  ctx->ctx_magic = MAGIC;
  return 1;
}

void exec_f(struct ctx_s ctx) {
  current_ctx->state = CTX_ACTIVATED;
  current_ctx->f(current_ctx->args);
  current_ctx->state = CTX_TERMINATED;
  exit(1);
}


void switch_to_ctx (struct ctx_s *ctx) {
  assert(ctx != NULL);
  assert(ctx->ctx_magic == MAGIC);
  assert(ctx->state== CTX_READY || ctx->state == CTX_ACTIVATED);
  if (current_ctx != NULL) {
    asm ("movl %%ebp, %0":"=r"(current_ctx->ebp));
    asm ("movl %%esp, %0":"=r"(current_ctx->esp));
  }
  current_ctx = ctx;
  asm("movl %0, %%ebp"::"r"(current_ctx->ebp));
  asm("movl %0, %%esp"::"r"(current_ctx->esp));
  if (current_ctx->state == CTX_READY) {
    exec_f(*current_ctx);//cette fonction ne revient jamais
  }
}
