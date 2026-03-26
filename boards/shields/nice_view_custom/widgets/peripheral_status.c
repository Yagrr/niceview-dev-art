/*
 *
 * Copyright (c) 2023 The ZMK Contributors
 * SPDX-License-Identifier: MIT
 *
 */

#include <zephyr/kernel.h>
#include <zephyr/random/random.h>

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(zmk, CONFIG_ZMK_LOG_LEVEL);

#include <zmk/battery.h>
#include <zmk/display.h>
#include <zmk/events/usb_conn_state_changed.h>
#include <zmk/event_manager.h>
#include <zmk/events/battery_state_changed.h>
#include <zmk/split/bluetooth/peripheral.h>
#include <zmk/events/split_peripheral_status_changed.h>
#include <zmk/usb.h>
#include <zmk/ble.h>

#include "peripheral_status.h"

#if IS_ENABLED(CONFIG_CUSTOM_ART_NINAJIRACHI)
LV_IMG_DECLARE(ninajirachi)
#endif
    
/*
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM1)
LV_IMG_DECLARE(hammerbeam1);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_CHILL)
LV_IMG_DECLARE(chill);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM2)
LV_IMG_DECLARE(hammerbeam2);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM3)
LV_IMG_DECLARE(hammerbeam3);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM4)
LV_IMG_DECLARE(hammerbeam4);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM5)
LV_IMG_DECLARE(hammerbeam5);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM6)
LV_IMG_DECLARE(hammerbeam6);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM7)
LV_IMG_DECLARE(hammerbeam7);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM8)
LV_IMG_DECLARE(hammerbeam8);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM9)
LV_IMG_DECLARE(hammerbeam9);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM10)
LV_IMG_DECLARE(hammerbeam10);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM11)
LV_IMG_DECLARE(hammerbeam11);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM12)
LV_IMG_DECLARE(hammerbeam12);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM13)
LV_IMG_DECLARE(hammerbeam13);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM14)
LV_IMG_DECLARE(hammerbeam14);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM15)
LV_IMG_DECLARE(hammerbeam15);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM16)
LV_IMG_DECLARE(hammerbeam16);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM17)
LV_IMG_DECLARE(hammerbeam17);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM18)
LV_IMG_DECLARE(hammerbeam18);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM19)
LV_IMG_DECLARE(hammerbeam19);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM20)
LV_IMG_DECLARE(hammerbeam20);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM21)
LV_IMG_DECLARE(hammerbeam21);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM22)
LV_IMG_DECLARE(hammerbeam22);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM23)
LV_IMG_DECLARE(hammerbeam23);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM24)
LV_IMG_DECLARE(hammerbeam24);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM25)
LV_IMG_DECLARE(hammerbeam25);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM26)
LV_IMG_DECLARE(hammerbeam26);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM27)
LV_IMG_DECLARE(hammerbeam27);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM28)
LV_IMG_DECLARE(hammerbeam28);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM29)
LV_IMG_DECLARE(hammerbeam29);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM30)
LV_IMG_DECLARE(hammerbeam30);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_VIM)
LV_IMG_DECLARE(vim);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_CPP)
LV_IMG_DECLARE(cpp);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_LGTM)
LV_IMG_DECLARE(lgtm);
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_SHIP_IT)
LV_IMG_DECLARE(ship_it);
#endif

#if IS_ENABLED(CONFIG_CUSTOM_ART_VIBE_CODING)
LV_IMG_DECLARE(vibe_coding);
#endif
*/

const lv_img_dsc_t *anim_imgs[] = {
#if IS_ENABLED(CONFIG_CUSTOM_ART_NINAJIRACHI)
    &ninajirachi, 
#endif
};
/*
#if IS_ENABLED(CONFIG_CUSTOM_ART_VIBE_CODING)
    &vibe_coding,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_SHIP_IT)
    &ship_it,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_LGTM)
    &lgtm,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_CPP)
    &cpp,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_VIM)
    &vim,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_CHILL)
    &chill,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM1)
    &hammerbeam1,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM2)
    &hammerbeam2,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM3)
    &hammerbeam3,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM4)
    &hammerbeam4,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM5)
    &hammerbeam5,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM6)
    &hammerbeam6,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM7)
    &hammerbeam7,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM8)
    &hammerbeam8,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM9)
    &hammerbeam9,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM10)
    &hammerbeam10,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM11)
    &hammerbeam11,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM12)
    &hammerbeam12,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM13)
    &hammerbeam13,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM14)
    &hammerbeam14,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM15)
    &hammerbeam15,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM16)
    &hammerbeam16,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM17)
    &hammerbeam17,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM18)
    &hammerbeam18,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM19)
    &hammerbeam19,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM20)
    &hammerbeam20,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM21)
    &hammerbeam21,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM22)
    &hammerbeam22,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM23)
    &hammerbeam23,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM24)
    &hammerbeam24,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM25)
    &hammerbeam25,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM26)
    &hammerbeam26,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM27)
    &hammerbeam27,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM28)
    &hammerbeam28,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM29)
    &hammerbeam29,
#endif
#if IS_ENABLED(CONFIG_CUSTOM_ART_HAMMERBEAM30)
    &hammerbeam30,
#endif
};
*/

static sys_slist_t widgets = SYS_SLIST_STATIC_INIT(&widgets);

struct peripheral_status_state {
    bool connected;
};

static void draw_top(lv_obj_t *widget, lv_color_t cbuf[], const struct status_state *state) {
    lv_obj_t *canvas = lv_obj_get_child(widget, 0);

    lv_draw_label_dsc_t label_dsc;
    init_label_dsc(&label_dsc, LVGL_FOREGROUND, &lv_font_montserrat_16, LV_TEXT_ALIGN_RIGHT);
    lv_draw_rect_dsc_t rect_black_dsc;
    init_rect_dsc(&rect_black_dsc, LVGL_BACKGROUND);

    // Fill background
    lv_canvas_draw_rect(canvas, 0, 0, CANVAS_SIZE, CANVAS_SIZE, &rect_black_dsc);

    // Draw battery
    draw_battery(canvas, state);

    // Draw output status
    lv_canvas_draw_text(canvas, 0, 0, CANVAS_SIZE, &label_dsc,
                        state->connected ? LV_SYMBOL_WIFI : LV_SYMBOL_CLOSE);

    // Rotate canvas
    rotate_canvas(canvas, cbuf);
}

static void set_battery_status(struct zmk_widget_status *widget,
                               struct battery_status_state state) {
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
    widget->state.charging = state.usb_present;
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */

    widget->state.battery = state.level;

    draw_top(widget->obj, widget->cbuf, &widget->state);
}

static void battery_status_update_cb(struct battery_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_battery_status(widget, state); }
}

static struct battery_status_state battery_status_get_state(const zmk_event_t *eh) {
    return (struct battery_status_state) {
        .level = zmk_battery_state_of_charge(),
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
        .usb_present = zmk_usb_is_powered(),
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */
    };
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_battery_status, struct battery_status_state,
                            battery_status_update_cb, battery_status_get_state)

ZMK_SUBSCRIPTION(widget_battery_status, zmk_battery_state_changed);
#if IS_ENABLED(CONFIG_USB_DEVICE_STACK)
ZMK_SUBSCRIPTION(widget_battery_status, zmk_usb_conn_state_changed);
#endif /* IS_ENABLED(CONFIG_USB_DEVICE_STACK) */

static struct peripheral_status_state get_state(const zmk_event_t *_eh) {
    return (struct peripheral_status_state){.connected = zmk_split_bt_peripheral_is_connected()};
}

static void set_connection_status(struct zmk_widget_status *widget,
                                  struct peripheral_status_state state) {
    widget->state.connected = state.connected;

    draw_top(widget->obj, widget->cbuf, &widget->state);
}

static void output_status_update_cb(struct peripheral_status_state state) {
    struct zmk_widget_status *widget;
    SYS_SLIST_FOR_EACH_CONTAINER(&widgets, widget, node) { set_connection_status(widget, state); }
}

ZMK_DISPLAY_WIDGET_LISTENER(widget_peripheral_status, struct peripheral_status_state,
                            output_status_update_cb, get_state)
ZMK_SUBSCRIPTION(widget_peripheral_status, zmk_split_peripheral_status_changed);

int zmk_widget_status_init(struct zmk_widget_status *widget, lv_obj_t *parent) {
    widget->obj = lv_obj_create(parent);
    lv_obj_set_size(widget->obj, 160, 68);
    lv_obj_t *top = lv_canvas_create(widget->obj);
    lv_obj_align(top, LV_ALIGN_TOP_RIGHT, 0, 0);
    lv_canvas_set_buffer(top, widget->cbuf, CANVAS_SIZE, CANVAS_SIZE, LV_IMG_CF_TRUE_COLOR);

    lv_obj_t * art = lv_animimg_create(widget->obj);
    lv_obj_center(art);
    lv_animimg_set_src(art, (const void **) anim_imgs, sizeof(anim_imgs) / sizeof(anim_imgs[0]));
    lv_animimg_set_duration(art, CONFIG_CUSTOM_ANIMATION_SPEED);
    lv_animimg_set_repeat_count(art, LV_ANIM_REPEAT_INFINITE);
    lv_animimg_start(art);
    
    lv_obj_align(art, LV_ALIGN_TOP_LEFT, 0, 0);
    sys_slist_append(&widgets, &widget->node);
    widget_battery_status_init();
    widget_peripheral_status_init();

    return 0;
}

lv_obj_t *zmk_widget_status_obj(struct zmk_widget_status *widget) { return widget->obj; }
