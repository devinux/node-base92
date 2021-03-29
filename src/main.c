#include <assert.h>
#include <stdio.h>
#include <node_api.h>
#include "base92.h"

#define PARAM_EMPTY_ERROR "One argument required - buffer or string with data to encode"
#define PARAM_TYPE_ERROR "Argument should be a buffer or a string"
#define DECLARE_NAPI_METHOD(name, func)         \
    {                                           \
        name, 0, func, 0, 0, 0, napi_default, 0 \
    }

static napi_value EncodeBase92(napi_env env, napi_callback_info info)
{
    napi_value result;
    size_t argc = 1;
    napi_value args[1];
    bool isBuffer = false;
    napi_valuetype valuetype;
    napi_get_cb_info(env, info, &argc, &args, NULL, NULL);
    napi_is_buffer(env, args[0], &isBuffer);
    napi_typeof(env, args[0], &valuetype);
    const char *str;
    if (argc < 1)
    {
        napi_throw_type_error(env, NULL, PARAM_EMPTY_ERROR);
        return NULL;
    }

    if (valuetype != napi_string && !isBuffer)
    {
        napi_throw_type_error(env, NULL, PARAM_TYPE_ERROR);
        return NULL;
    }

    if (isBuffer)
    {
        size_t buffer_length;
        const char *buffer_data;
        napi_get_buffer_info(env, args[0], (void **)(&buffer_data), &buffer_length);
        str = base92encode(buffer_data, buffer_length);
    }
    else
    {
        size_t str_length;
        size_t str_size;
        napi_get_value_string_utf8(env, args[0], NULL, 0, &str_length);
        const char *tmp = (char *)malloc(sizeof(char) * str_length + 1);
        napi_get_value_string_utf8(env, args[0], tmp, str_length + 1, &str_size);
        str = base92encode(tmp, str_length);
        free(tmp);
    }
    napi_create_string_utf8(env, str, strlen(str), &result);
    free(str);
    return result;
}

static napi_value DecodeBase92(napi_env env, napi_callback_info info)
{
    napi_value result;
    size_t argc = 1;
    napi_value args[1];
    bool isBuffer = false;
    napi_valuetype valuetype;
    napi_get_cb_info(env, info, &argc, &args, NULL, NULL);
    napi_is_buffer(env, args[0], &isBuffer);
    napi_typeof(env, args[0], &valuetype);
    const char *str;
    if (argc < 1)
    {
        napi_throw_type_error(env, NULL, PARAM_EMPTY_ERROR);
        return NULL;
    }

    if (valuetype != napi_string && !isBuffer)
    {
        napi_throw_type_error(env, NULL, PARAM_TYPE_ERROR);
        return NULL;
    }

    if (isBuffer)
    {
        size_t buffer_length;
        const char *buffer_data;
        napi_get_buffer_info(env, args[0], (void **)(&buffer_data), &buffer_length);
        printf("buffer data = %s\n", buffer_data);
        str = base92decode(buffer_data, &buffer_length);
        printf("%s\n", str);
    }
    else
    {
        size_t str_length;
        size_t str_size;
        napi_get_value_string_utf8(env, args[0], NULL, 0, &str_length);
        const char *tmp = (char *)malloc(sizeof(char) * str_length + 1);
        napi_get_value_string_utf8(env, args[0], tmp, str_length + 1, &str_size);
        str = base92decode(tmp, &str_length);
        free(tmp);
    }
    napi_create_string_utf8(env, str, strlen(str), &result);
    free(str);
    return result;
}

static napi_value Init(napi_env env, napi_value exports)
{
    napi_property_descriptor encode = DECLARE_NAPI_METHOD("encode", EncodeBase92);
    napi_property_descriptor decode = DECLARE_NAPI_METHOD("decode", DecodeBase92);

    napi_define_properties(env, exports, 1, &encode);
    napi_define_properties(env, exports, 1, &decode);
    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
