#include "v_menu.h"

static v_menu_t *menu;
v_menu_t *v_menu_init(GtkWidget *parent)
{

    d("");
    menu = g_new(v_menu_t, 1);
    menu->button = gtk_menu_button_new();
    gtk_widget_set_halign(menu->button, GTK_ALIGN_START);
    gtk_widget_set_valign(menu->button, GTK_ALIGN_START);

    d("");
#if 0
    menu->image = gtk_image_new_from_file("assets/hamburger_menu.png");
#else
    extern unsigned char assets_hamburger_menu_png[];
    extern unsigned int assets_hamburger_menu_png_len;
    gboolean result;

    GdkPixbufLoader *loader = gdk_pixbuf_loader_new();
    result = gdk_pixbuf_loader_write(loader, assets_hamburger_menu_png, assets_hamburger_menu_png_len, NULL);
    d("%d %p(%x)", result, assets_hamburger_menu_png, assets_hamburger_menu_png_len);

    GdkPixbuf *pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);
    menu->image = gtk_image_new_from_pixbuf(pixbuf);
    result = gdk_pixbuf_loader_close(loader, NULL);
    d("%d", result);
#endif
    menu->menu = gtk_menu_new();

    menu->menu_item = gtk_menu_item_new_with_label("Option 1");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu), menu->menu_item);
    gtk_widget_show(menu->menu_item);

    menu->menu_item = gtk_menu_item_new_with_label("Option 2");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu->menu), menu->menu_item);
    gtk_widget_show(menu->menu_item);

    gtk_menu_button_set_popup(GTK_MENU_BUTTON(menu->button), menu->menu);
    gtk_button_set_image(GTK_BUTTON(menu->button), menu->image);

    gtk_container_add(GTK_CONTAINER(parent), menu->button);

    gtk_widget_show(menu->button);

    return menu;
}

void v_menu_update(void)
{
//    gtk_widget_show(menu->button);
//    gtk_widget_show(menu->image);
//    gtk_widget_show(menu->box);
}