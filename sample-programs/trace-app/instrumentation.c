#include <stdio.h>

static const char s_buf[] = "                                                 ";
static const char* s_indent = s_buf + sizeof(s_buf) - 1;
FILE* s_trace;

__attribute__((constructor, no_instrument_function))
void open_trace(void) {
    s_trace = fopen("trace.log", "w");
}

__attribute__((destructor, no_instrument_function))
void close_trace(void) {
    fclose(s_trace);
}

__attribute__((no_instrument_function))
void __cyg_profile_func_enter(void* const f, void* const caller) {
    (void) caller;
    fprintf(s_trace, "%s,%p\n", s_indent--, f);
}

__attribute__((no_instrument_function))
void __cyg_profile_func_exit(void* const f, void* const caller) {
    (void) caller, (void) f;
    s_indent++;
}
