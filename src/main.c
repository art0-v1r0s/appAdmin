#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include <time.h>
int main(int argc, char *argv[])

{
    MYSQL *con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, "192.168.1.37", "aric", "aric","Fast-Food", 0, NULL, 0) == NULL){
      finish_with_error(con);
    }

    GtkBuilder      *builder; 
    GtkWidget       *window;

    gtk_init(&argc, &argv);

    // builder = gtk_builder_new();
    // gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    // Update October 2019: The line below replaces the 2 lines above
    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();

    return 0;
}

void home(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page1");
}
void commande(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page2");

}
void produit(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page3");

}
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}

void finish_with_error(MYSQL *con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}