#include <stdio.h>
#include <string.h>
#include <emscripten/fetch.h>
#include <janet.h>

static Janet cfun_httpget(int32_t argc, Janet *argv)
{
    janet_fixarity(argc, 1);
    const char *url = janet_getcstring(argv, 0);

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, "GET");
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_SYNCHRONOUS | EMSCRIPTEN_FETCH_REPLACE;
    emscripten_fetch_t *fetch = emscripten_fetch(&attr, url);
    if (fetch->status == 200)
    {
        JanetString res = janet_string((const uint8_t *)fetch->data, fetch->numBytes);
        emscripten_fetch_close(fetch);
        return janet_wrap_string(res);
    }
    else
    {
        printf("HTTP failure status code: %d.\n", fetch->status);
    }
    emscripten_fetch_close(fetch);
    return janet_wrap_nil();
}

int main(int argc, const char *argv[])
{
    janet_init();

    JanetTable *env = janet_core_env(NULL);

    janet_def(env, "httpget", janet_wrap_cfunction(cfun_httpget), "make HTTP request");

    const char *code = "(print (httpget `https://httpbin.org/anything`))";

    janet_dostring(env, code, "main", NULL);

    janet_deinit();
    return 0;
}
