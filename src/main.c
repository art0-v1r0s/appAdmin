#include <gtk/gtk.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql.h>
#include<stdbool.h>
#include<ctype.h>
#include "funcMYSQL.h"
#include "function.h"

#define  TAILLE_VACHAR  255
#define TAILLE_CHAR 100
#define TAILLE_INSERT 100
#define SELECT (sizeof(long int )+ 3 + sizeof(TAILLE_VACHAR))
#define ip "192.168.1.37"
#define identifiant "aric"
#define password "aric"
#define bdd "Fast-Food"

int main(int argc, char *argv[])

{

    GtkBuilder      *builder; 
    GtkWidget       *window;
    //allocation de la memoire
    app_widgets     *widgets = g_slice_new(app_widgets);
    
    gtk_init(&argc, &argv);
    builder = gtk_builder_new_from_file("glade/window_main.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    //get pointer to entry widgets ->entry connexion
    //association variable struct to identifiant du widget de la page
    widgets->entry_nom = GTK_WIDGET(gtk_builder_get_object(builder, "entry_nom"));
    widgets->entry_nom_up = GTK_WIDGET(gtk_builder_get_object(builder, "entry_nom_up"));
    widgets->entry_prix = GTK_WIDGET(gtk_builder_get_object(builder, "entry_prix"));
    widgets->entry_prix_up = GTK_WIDGET(gtk_builder_get_object(builder, "entry_prix_up"));
    widgets->entry_description = GTK_WIDGET(gtk_builder_get_object(builder, "entry_description"));
    widgets->entry_description_up = GTK_WIDGET(gtk_builder_get_object(builder, "entry_description_up"));
    widgets->produit_add_label = GTK_WIDGET(gtk_builder_get_object(builder, "produit_add_label"));
    widgets->entry_id = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id"));
    widgets->entry_id_del = GTK_WIDGET(gtk_builder_get_object(builder, "entry_id_del"));
    // builder = gtk_builder_new();
    // gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    // Update October 2019: The line below replaces the 2 lines above

    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(window);                
    gtk_main();
    //liberer l'alocation
    g_slice_free(app_widgets, widgets);
    return 0;
}



//ajouter un produit
void prod_add(GtkButton * button,GtkStack * stack){
  printf("%p\n",stack);
  //go to page ajouter produit
  gtk_stack_set_visible_child_name (stack,"page4");
  printf("Cliquez\n");

}

//rafraichir pour permettre de voir les produit dans le label 1er page de modification
void rafraichir(GtkButton * button,GtkLabel * lbl_produit){
  char *test=selectupdateproduct();
  gtk_label_set_text(GTK_LABEL(lbl_produit), test);
  
}
//rafraichir pour permettre de voir les produit dans le label dans delete
void rafraichir_del(GtkButton * button,GtkLabel * lbl_produit){
  char *test=selectupdateproduct();
  printf("%s\n",test);
  gtk_label_set_text(lbl_produit,test);
}
//rafraichir pour permettre de voir les produit dans le label  2eme page de modification
void rafraichir_up2(GtkButton * button,app_widgets * widget_produit_up){
  //recuperation de l'id entrez
  char *id = gtk_entry_get_text(GTK_ENTRY(widget_produit_up->entry_id));
  //initialisation du compteur 
  //int count = 0;
  //vérification si l'id est bien un nombre et count est différent de 1
  printf("id :%s\n",id);
  //récupération du pointeur de mysql
  MYSQL *con = mysql_init(NULL);
  //vérification si le pointeur est null
  if (con == NULL){
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(1);
  }
  //connection a la bdd
  if (mysql_real_connect(con, ip, identifiant, password, bdd, 0, NULL, 0) == NULL){
    finish_with_error(con);
  }
  //création, allocation de la  requete
  char *req  = malloc(63 + sizeof(id));
  sprintf(req,"SELECT `nom`, `prix`, `description` FROM `PRODUIT` WHERE id=%s",id);
  printf("req : %s\n",req);
  //permet d'executer la requete
  if (mysql_query(con, req))
  {
    finish_with_error(con);
  }
  //récupère le résultat
  MYSQL_RES *result = mysql_store_result(con);
  //vérification
  if (result == NULL)
  {
  finish_with_error(con);
  }
  //stocke nombre de colonne
  int num_fields = mysql_num_fields(result);
  // pointeur de ligne
  MYSQL_ROW row;
  //écrit sur le gtk_entry
  while ((row = mysql_fetch_row(result))){
    for(int i = 0; i < num_fields; i++){
      if(i==0){
        gtk_entry_set_text (widget_produit_up->entry_nom_up,row[i] ? row[i] : "NULL");
        printf("1 :%s\n",row[i]);
      }else if (i==1) {
        gtk_entry_set_text (widget_produit_up->entry_prix_up,row[i] ? row[i] : "NULL");
        printf("2 :%s\n",row[i]);
      }else if (i==2) {
        gtk_entry_set_text (widget_produit_up->entry_description_up,row[i] ? row[i] : "NULL");
        printf("3 :%s\n",row[i]);
      }
    }
    printf("\n");
  }
  //libération 
  mysql_free_result(result);
  free(req);
  free(row);
  mysql_close(con);
}

//mise a jour produit
void update_produit(GtkButton * button,app_widgets * widget_update){
  int count = 0;
  char *id = gtk_entry_get_text(GTK_ENTRY(widget_update->entry_id));
  char  *nom = gtk_entry_get_text(GTK_ENTRY(widget_update->entry_nom_up));
  char  *prix = gtk_entry_get_text(GTK_ENTRY(widget_update->entry_prix_up));
  char  *description = gtk_entry_get_text(GTK_ENTRY(widget_update->entry_description_up));
  //vérification que les données sont bonnes
  while(verification(nom,prix,description)== 0 && count == 1){
    //ajout du produit
    UpdateProduct(id, nom, prix, description);
    count++;
  }
  printf("id: %s\n",id);
  printf("nom: %s\n",nom);
  printf("prix: %s\n",prix);
  printf("description: %s\n",description);
}


//insère produit
void submit_produit_add(GtkButton * button,app_widgets * widget_produit_add){
  //recuperation des données
  char  *nom = gtk_entry_get_text(GTK_ENTRY(widget_produit_add->entry_nom));
  char  *prix = gtk_entry_get_text(GTK_ENTRY(widget_produit_add->entry_prix));
  char  *description = gtk_entry_get_text(GTK_ENTRY(widget_produit_add->entry_description));
  int count = 0;
  printf("nom: %s\n",nom);
  printf("prix: %s\n",prix);
  printf("description: %s\n",description);
  //vérification des données
  while(verification(nom,prix,description)== 0 && count != 1){
    //insérer un produit
    InsertProduct(nom, prix, description);
    count++;
  }
}

//supprimez un produit
void del_produit(GtkButton * button,app_widgets * widget_produit_del){
  char *id = gtk_entry_get_text(GTK_ENTRY(widget_produit_del->entry_id_del));
  printf("id:%s\n",id);
  //vérifiacation des données
  //suppression du pr
  DelProduct(id);
}



