/*
 * This file is part of the MicroPython project, http://micropython.org/
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 SummerGift <summergift2019@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include "py/runtime.h"
#include "mqtt_sample.h"

STATIC mp_obj_t add(
        mp_obj_t arg_1_obj,
        mp_obj_t arg_2_obj) {
    mp_int_t arg_1 = mp_obj_get_int(arg_1_obj);
    mp_int_t arg_2 = mp_obj_get_int(arg_2_obj);
    mp_int_t ret_val;

    /* Your code start! */

    ret_val = arg_1 + arg_2;

    /* Your code end! */

    return mp_obj_new_int(ret_val);
}
MP_DEFINE_CONST_FUN_OBJ_2(add_obj, add);

STATIC mp_obj_t mqtt_start() {
    mp_int_t ret_val;

    /* Your code start! */
    ret_val = mqtt_start_py();
    if(ret_val == 0)
    {
        rt_kprintf("mqtt_start ok\n");
    }
    else 
    {
        rt_kprintf("mqtt_start fail\n");
    }
    /* Your code end! */

    return mp_obj_new_int(ret_val);
}
MP_DEFINE_CONST_FUN_OBJ_0(mqtt_start_obj, mqtt_start);
    
STATIC mp_obj_t mqtt_publish(
        mp_obj_t arg_1_obj) {
    const char* arg_1 = mp_obj_str_get_str(arg_1_obj);
    bool ret_val;

    /* Your code start! */
    rt_kprintf("get str: %s\n",arg_1);

    if(mqtt_publish_py(arg_1))
    {
        rt_kprintf("mqtt_send_fail\n");
        ret_val = false;
    } else {
        rt_kprintf("mqtt_send_ok\n");
        ret_val = true;
    }
    /* Your code end! */

    return mp_obj_new_bool(ret_val);
}
MP_DEFINE_CONST_FUN_OBJ_1(mqtt_publish_obj, mqtt_publish);

STATIC const mp_rom_map_elem_t mp_module_userfunc_globals_table[] = {
    { MP_ROM_QSTR(MP_QSTR___name__), MP_ROM_QSTR(MP_QSTR_userfunc) },
    { MP_ROM_QSTR(MP_QSTR_add), MP_ROM_PTR(&add_obj) },
    { MP_ROM_QSTR(MP_QSTR_mqtt_start), MP_ROM_PTR(&mqtt_start_obj) },
    { MP_ROM_QSTR(MP_QSTR_mqtt_publish), MP_ROM_PTR(&mqtt_publish_obj) },
};

STATIC MP_DEFINE_CONST_DICT(mp_module_userfunc_globals, mp_module_userfunc_globals_table);

const mp_obj_module_t mp_module_userfunc = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_userfunc_globals,
};

