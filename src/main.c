#include <gtk/gtk.h>
#include "function.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include <time.h>

#define  TAILLE_VACHAR  255
#define TAILLE_INSERT 100
#define ip "192.168.1.37"
int main(int argc, char *argv[])

{

    GtkBuilder      *builder; 
    GtkWidget       *window;
    app_widgets     *widgets = g_slice_new(app_widgets);

    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    //get pointer to entry widgets ->entry connexion
    widgets->entry_nom = GTK_WIDGET(gtk_builder_get_object(builder, "entry_nom"));
    widgets->entry_prix = GTK_WIDGET(gtk_builder_get_object(builder, "entry_prix"));
    widgets->entry_description = GTK_WIDGET(gtk_builder_get_object(builder, "entry_description"));
    widgets->produit_add_label = GTK_WIDGET(gtk_builder_get_object(builder, "produit_add_label"));
    // builder = gtk_builder_new();
    // gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    // Update October 2019: The line below replaces the 2 lines above

    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
    g_slice_free(app_widgets, widgets);
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
void prod_up(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page5");

}
void prod_up2(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page6");

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

void finish_with_error(con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

void prod_add(GtkButton * button,GtkStack * stack){

  printf("%p\n",stack);
  gtk_stack_set_visible_child_name (stack,"page4");
  printf("Cliquez\n");

}

void rafraichir(GtkButton * button,GtkLabel * lbl_produit){
  char *test="test\ntest1";
  gtk_label_set_text(GTK_LABEL(lbl_produit), test);
  
}
void selectupdateproduct(){
  MYSQL *con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, ip, "aric", "aric","Fast-Food", 0, NULL, 0) == NULL){
      finish_with_error(con);
    }

  if (mysql_query(con, "SELECT `id`,`nom`, `prix`FROM `PRODUIT`"))
  {
      finish_with_error(con);
  }

  MYSQL_RES *result = mysql_store_result(con);

  if (result == NULL)
  {
      finish_with_error(con);
  }

  int num_fields = mysql_num_fields(result);

  MYSQL_ROW row;
  MYSQL_FIELD *field;

  while ((row = mysql_fetch_row(result)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          if (i == 0)
          {
             while(field = mysql_fetch_field(result))
             {
                printf("%s ", field->name);
             }

             printf("\n");
          }

          printf("%s  ", row[i] ? row[i] : "NULL");
      }
  }

  printf("\n");

  mysql_free_result(result);
  mysql_close(con);
}

void submit_produit_add(GtkButton * button,app_widgets * widget_produit_add){
  char  *nom = gtk_entry_get_text(GTK_ENTRY(widget_produit_add->entry_nom));
  char  *prix = gtk_entry_get_text(GTK_ENTRY(widget_produit_add->entry_prix));
  char  *description = gtk_entry_get_text(GTK_ENTRY(widget_produit_add->entry_description));
  printf("nom: %s\n",nom);
  printf("prix: %s\n",prix);
  printf("description: %s\n",description);
  InsertProduct(nom, prix, description);
}

int InsertProduct(char *nom, char *prix, char *description){
    MYSQL * con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, ip, "aric", "aric","Fast-Food", 0, NULL, 0) == NULL){
      finish_with_error(con);
    }
    printf("%s\n",nom);
    char requete [sizeof(int) + sizeof(TAILLE_VACHAR) + TAILLE_INSERT];
    sprintf(requete,"INSERT INTO `PRODUIT`( `nom`, `prix`, `description`) VALUES ('%s', '%s', '%s');",nom, prix, description);
    printf("%s\n",requete);
    if (mysql_query(con, requete)) {
        finish_with_error(con);
    } 
    mysql_close(con);
    return 1;
}

