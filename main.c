
#include <stdbool.h>

#include "v_common.h"
#include "v_pdf.h"
#include "v_menu.h"

#define PDF_FILE "/usr/share/sample.pdf"
#define SWIPE_MARGIN (50)

static void button_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    v_menu_t *menu = (v_menu_t*)data;
    // d("%p", menu);
}

static void draw_callback(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    GdkPoint size;
    v_status_t status;

//    d("");
    status = v_pdf_getsize(&size.x, &size.y);
    ERR_RETn(status);
//    d("%d, %d", size.x, size.y);

//    cairo_set_source_rgb(cr, 0.678, 0.847, 0.902);
//    cairo_paint(cr);
#if 0
    cairo_rectangle(cr, 0, 24, size.x, size.y);
    cairo_clip(cr);
#endif

    cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_RGB24, size.x, size.y);
    unsigned char *surface_data = cairo_image_surface_get_data(surface);
    int rowstride = cairo_image_surface_get_stride(surface);

//    d("stride:%d", rowstride);
    status = v_pdf_getsize(&size.x, &size.y);
//    d("%d, %d", size.x, size.y);
    status = v_pdf_alloc_pixel_data(surface_data, 0, rowstride, (pdf_scale_t){1, 1});
    ERR_RETn(status);

    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);
    cairo_surface_destroy(surface);

    v_pdf_release_pixel_data();

error_return:
    return;
}

// static gboolean motion_notify_event(GtkWidget *widget, GdkEventMotion *event, gpointer data)
static gboolean motion_notify_event(GtkWidget *widget, GdkEventButton *event, gpointer data)
{
    static gdouble start_x = -1;
    static gdouble start_y = -1;
    gdouble dx, dy;

    ERR_RETn(event->button != MOUSE_BUTTON_LEFT);

    if (event->type == GDK_BUTTON_PRESS)
    {
        // d("push %x %x (%.2f,%.2f)", event->button, event->state, event->x, event->y);
        start_x = event->x;
        start_y = event->y;
    }
    else if (event->type == GDK_BUTTON_RELEASE)
    {
        // d("release %x %x (%.2f,%.2f)", event->button, event->state, event->x, event->y);
        dx = event->x - start_x;
        dy = event->y - start_y;
        if (abs(dx) < abs(dy))
        {
        }
        else
        {
            if (dx < -SWIPE_MARGIN)
            {
                d("left swiped");
            }
            else if (dx > SWIPE_MARGIN)
            {
                d("right swiped");
            }
        }
    }

error_return:
    return TRUE;
}

static void activate(GtkApplication *app, gpointer user_data)
{
    GtkWidget *window;
    GtkDrawingArea *drawing_area;
    GdkPoint size;

    v_status_t status;

    status = v_pdf_init();
    ERR_RETn(status);

    status = v_pdf_open(PDF_FILE);
    ERR_RETn(status);

    int page_count = v_pdf_pagecount();

    status = v_pdf_getsize(&size.x, &size.y);
    ERR_RETn(status);

    window = gtk_application_window_new(app);
    gtk_window_set_default_size(GTK_WINDOW(window), size.x, size.y);
    gtk_window_set_decorated(GTK_WINDOW(window), FALSE);

    GtkWidget *overlay = gtk_overlay_new();
    gtk_container_add(GTK_CONTAINER(window), overlay);

    // Create a drawing area and set the draw callback
    drawing_area = (GtkDrawingArea *)gtk_drawing_area_new();
    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), (GtkWidget *)drawing_area);
    gtk_widget_set_events((GtkWidget *)drawing_area, gtk_widget_get_events((GtkWidget *)drawing_area) | GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK);
    g_signal_connect(G_OBJECT(drawing_area), "button-press-event", G_CALLBACK(motion_notify_event), NULL);
    g_signal_connect(G_OBJECT(drawing_area), "button-release-event", G_CALLBACK(motion_notify_event), NULL);

    g_signal_connect((GtkWidget *)drawing_area, "draw", G_CALLBACK(draw_callback), NULL);

    GtkWidget *container = gtk_fixed_new();
    gtk_widget_set_size_request(container, 24, 24);

    gtk_overlay_add_overlay(GTK_OVERLAY(overlay), container);
    gtk_widget_set_halign(container, GTK_ALIGN_START);
    gtk_widget_set_valign(container, GTK_ALIGN_START);

    v_menu_t *menu = v_menu_init(container);
    g_signal_connect(container, "draw", G_CALLBACK(button_callback), menu);
    gtk_widget_show_all(window);

error_return:
    return;
}

int main(int argc, char **argv)
{
    GtkApplication *app;
    int status;

    app = gtk_application_new("A.B", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
