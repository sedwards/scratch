/* compile with:
* gcc -o main main.c `pkg-config --cflags --libs gtk+-2.0
*/

#include <gdk/gdk.h>
#include <gtk/gtk.h>

gboolean
on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  switch (event->keyval)
  {
    case GDK_KEY_PRESS_MASK:
      printf("key pressed: %s\n", "p");
      break;

    default:
      return FALSE;
  }

  return FALSE;
}



gboolean button_press_cb(GtkWidget *wi, GdkEventButton *ev, gpointer user_data)
{
  GtkWidget *window;

   /* windows only supports the LMB for dragging */
//   if(ev->button != 1)
//      return FALSE;


   window = gtk_widget_get_toplevel (wi);

   /* we can use GdkEventButton to our advantage,
    * it has all the necessary components for
    * gtk_window_begin_move_drag */
   gtk_window_begin_move_drag(GTK_WINDOW(window), ev->button, ev->x_root, ev->y_root, ev->time);
   return TRUE;
}

#if 0
gboolean
gtk_button_press (GtkWidget      *widget,
                             GdkEventButton *event)
{
  GtkWidget *window;
  gboolean window_drag = FALSE;

//  if (event->type != GDK_BUTTON_PRESS)
//    return FALSE;

  window = gtk_widget_get_toplevel (widget);

  if (window)
    {
   //   gtk_widget_style_get (widget,
   //                         "window-dragging", &window_drag,
   //                         NULL);

   //   if (window_drag)
   //     {
          gtk_window_begin_move_drag (GTK_WINDOW (window),
                                      event->button,
                                      event->x_root,
                                      event->y_root,
                                      event->time);
          return TRUE;
    //    }
    }

  //return FALSE;
}
#endif

int main(int argc, char **argv)
{
   GtkWidget *win;

   /* initialize GTK+ */
   gtk_init(&argc, &argv);

   /* create a new toplevel window... */
   win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   /* ...add the ability to recieve the "button-press-event"... */
   gtk_widget_add_events(win, GDK_BUTTON_PRESS_MASK);
   /* ...connect signals... */
   g_signal_connect(win, "delete-event", G_CALLBACK(gtk_main_quit), NULL);
   g_signal_connect(win, "button-press-event", G_CALLBACK(button_press_cb), NULL);

gtk_widget_set_events(win,GDK_KEY_RELEASE_MASK);
   g_signal_connect (G_OBJECT (win), "key_press_event", G_CALLBACK (on_key_press), NULL);

//  gtk_widget_set_events(window,GDK_KEY_RELEASE_MASK);
//g_signal_connect(window,"key_release_event",G_CALLBACK(hello),NULL);


   /* ...and show the window */
   gtk_widget_show(win);



   /* enter the main loop */
   gtk_main();

   return 0;
}



#if 0

/*
 * 
 * compile command:
 * 
 * gcc keypress3.c -o keypress3  `pkg-config --libs --cflags gtk+-2.0`
 * 
 */

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>

gboolean
on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data);

int main (int argc, char *argv[])
{
  GtkWidget *window;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  g_signal_connect (G_OBJECT (window), "destroy", G_CALLBACK (gtk_main_quit), NULL);
  g_signal_connect (G_OBJECT (window), "key_press_event", G_CALLBACK (on_key_press), NULL);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}

gboolean
on_key_press (GtkWidget *widget, GdkEventKey *event, gpointer user_data)
{
  switch (event->keyval)
  {
    case GDK_p:
      printf("key pressed: %s\n", "p");
      break;
    case GDK_s:
      if (event->state & GDK_SHIFT_MASK)
      {
        printf("key pressed: %s\n", "shift + s");
      }
      else if (event->state & GDK_CONTROL_MASK)
      {
        printf("key pressed: %s\n", "ctrl + s");
      }
      else
      {
        printf("key pressed: %s\n", "s");
      }
      break;
    case GDK_m:
      if (event->state & GDK_SHIFT_MASK)
      {
        printf("key pressed: %s\n", "shift + m");
      }
      else if (event->state & GDK_CONTROL_MASK)
      {
        printf("key pressed: %s\n", "ctrl + m");
      }
      else
      {
        printf("key pressed: %s\n", "m");
      }
      break;

    default:
      return FALSE; 
  }

  return FALSE; 
}

#endif
