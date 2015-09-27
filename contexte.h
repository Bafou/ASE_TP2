/*
 * contexte.h
 * Authors : Honoré NINTUNZE & Antoine PETIT
 */
#ifndef CONTEXTE_H
#define CONTEXTE_H

typedef void (func_t) (void *);

enum ctx_state_e {
  CTX_READY,
  CTX_ACTIVATED,
  CTX_TERMINATED
};

struct ctx_s {
  void *esp;
  void *ebp;
  func_t *f;
  unsigned char *stack;
  enum ctx_state_e state;
  unsigned int ctx_magic;
  #define MAGIC 0xdeadbeef
  void *args;
};

int init_ctx (struct ctx_s *ctx, int stack_size, func_t *f, void *args);

void switch_to_ctx (struct ctx_s *ctx);

#endif
