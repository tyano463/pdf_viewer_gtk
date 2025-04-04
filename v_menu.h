#ifndef __V_MENU_H__
#define __V_MENU_H__

#include "v_common.h"

typedef struct
{
    GtkWidget *button;
    GtkWidget *menu;
    GtkWidget *menu_item;
    GtkWidget *image;
} v_menu_t;

v_menu_t *v_menu_init(GtkWidget *window);
void v_menu_update(void);

#endif