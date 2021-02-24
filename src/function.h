//file ou ce trouve les function et les structures
typedef struct {
    GtkWidget *entry_nom;
    GtkWidget *entry_prix;
    GtkWidget *entry_description;
    GtkWidget *produit_add_label;
    GtkWidget *entry_id;
    GtkWidget *entry_nom_up;
    GtkWidget *entry_prix_up;
    GtkWidget *entry_description_up;
    GtkWidget *entry_id_del;

} app_widgets;

//savoir si une chaine contient uniquement des chiffres
bool isDigits(char *chaine){
    //initialisation boolean
    bool isCorrect = true;
    //callculer la taille
    size_t length = size(chaine);
    //boucle verifiant chaque character.
    for( int i=0; i<length; i++ ) {
        if ( ! isdigit( chaine[i] ) ) {
            isCorrect = false;
        }
    }
        if ( isCorrect ) {
        printf( "Your text (%s) is a number\n", chaine );
        
    } else {
        printf( "Your text (%s) is not a number\n", chaine );
        
    }
    //return boolean
    return isCorrect;

}
//connaitre la taille
int size(char *chaine){

    size_t lenght = strlen( chaine );
    return lenght;
}
//verification taille(nom/description) et est-il un nombre(prix)
int verification(char *nom, char *prix, char *description)
{
    if(isDigits(prix)==true && size(nom)<=255 && size(description)<=400){
        printf("%s %s %s\n",nom,prix,description);
        return 0;
    }
    printf("erreur relancer ma ce programme");
    return 1;
}
//go to home
void home(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page1");
}
//go to commande
void commande(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page2");

}
//go to 1er pages modification
void prod_up(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page5");

}
//go to 2eme pages modification
void prod_up2(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page6");

}
//go to produit
void produit(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page3");

}
//go to page de supprsion
void prod_del(GtkButton * button,GtkStack * stack){

    printf("%p\n",stack);
    gtk_stack_set_visible_child_name (stack,"page7");

}

// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}