#include <string.h>
#define  TAILLE_VACHAR  255
#define TAILLE_CHAR 100
#define TAILLE_INSERT 100
#define SELECT (sizeof(long int )+ 3 + sizeof(TAILLE_VACHAR))
#define ip "192.168.1.37"
#define identifiant "aric"
#define password "aric"
#define bdd "Fast-Food"
//permet de voir l'erreur de la bdd
void finish_with_error(con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}
//fonction mise a jour du produit
void UpdateProduct(char *id, char *nom, char *prix, char *description){
    MYSQL *con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, ip, identifiant, password, bdd, 0, NULL, 0) == NULL){
      finish_with_error(con);
    }
    //création, allocation de la requete
    char *req  = malloc(90 + sizeof(id) + sizeof(nom) + sizeof(prix) + sizeof(description));
    sprintf(req,"UPDATE `PRODUIT` SET `nom`='%s',`prix`='%s',`description`='%s' WHERE `PRODUIT`.`id` = %s", nom, prix, description, id);
    printf("req : %s\n",req);
    //execution de la requete
    if (mysql_query(con, req)){
      finish_with_error(con);
    }
    //libération
    free(req);
    mysql_close(con);
}
//Insérez produit
int InsertProduct(char *nom, char *prix, char *description){
    MYSQL * con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, ip, identifiant, password, bdd, 0, NULL, 0) == NULL){
      finish_with_error(con);
    }
    printf("%s\n",nom);
    //création, allocation de la requete
    char requete [sizeof(int) + sizeof(TAILLE_VACHAR) + TAILLE_INSERT];
    sprintf(requete,"INSERT INTO `PRODUIT`( `nom`, `prix`, `description`) VALUES ('%s', '%s', '%s');",nom, prix, description);
    printf("%s\n",requete);
    //execution de la requete
    if (mysql_query(con, requete)) {
        finish_with_error(con);
    }
    //libération 
    mysql_close(con);
    return 1;
}
//supression du produit
void DelProduct(char *id){
    MYSQL * con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, ip, identifiant, password, bdd, 0, NULL, 0) == NULL){
      finish_with_error(con);
    }
    //création, allocation de la requete
    char requete [sizeof(int) + 37];
    sprintf(requete,"DELETE FROM `PRODUIT` WHERE `id`=%s",id);
    printf("%s\n",requete);
    //execution de la requete
    if (mysql_query(con, requete)) {
        finish_with_error(con);
    } 
    mysql_close(con);
}
//selection des produits
char * selectproduct(char tab_product){
    MYSQL *con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, ip, identifiant, password, bdd, 0, NULL, 0) == NULL){
      finish_with_error(con);
    }
    //execution de la requete
    if (mysql_query(con, "SELECT `id`,`nom`, `prix`FROM `PRODUIT`"))
    {
      finish_with_error(con);
    }
    //récupération des résultat
    MYSQL_RES *result = mysql_store_result(con);

    if (result == NULL){
      finish_with_error(con);
    }

    int num_fields = mysql_num_fields(result);
    //pointeur rangé et colonne
    MYSQL_ROW row;
    MYSQL_FIELD *field;
    //création, allocation de la requete
    char *resp=malloc(SELECT*tab_product + 15);
    strcpy(resp, "");
    while ((row = mysql_fetch_row(result))){
      for(int i = 0; i < num_fields; i++){
        if (i == 0){
          //pour avoir le nom des champs
          while(field = mysql_fetch_field(result)){
            strcat(resp, field->name);
            strcat(resp, " ");
            }
          strcat(resp, "\n");
        }
        //pour avoir le nom des rangée par exemple burger 
        strcat(resp, row[i] ? row[i] : "NULL");
        strcat(resp, " ");
      }
    }
    //pour dire que c'est la fin de la chaine
    strcat(resp,"\0");
    //libération de la mémoire
    mysql_free_result(result);
    mysql_close(con);
    return resp;
}
//pour sélectionner des produits
char * selectupdateproduct(){
    char * endPtr;
    long value;
    MYSQL *con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, ip, identifiant, password, bdd, 0, NULL, 0) == NULL){
      finish_with_error(con);
    }
    if (mysql_query(con, "SELECT COUNT(`nom`) FROM `PRODUIT`"))
    {
      finish_with_error(con);
    }
    MYSQL_RES *test = mysql_store_result(con);

    if (test == NULL){
      finish_with_error(con);
    }
    int num_fields = mysql_num_fields(test);
    MYSQL_ROW row;
    //pour avoir les rangées
    if(row=mysql_fetch_row(test)){
      for(int i = 0; i < num_fields; i++){
      printf("%s ", row[i] ? row[i] : "NULL");
      }
    }
    //pour avoir le nombre de ligne que y a dans la table produit
    value = strtol( row[0], &endPtr,0);
    //création d'un tableau avec le nombre de ces lignes
    char *tab_product[value];
    char *resp = selectproduct(tab_product);
    printf("%s\n",resp);
    mysql_close(con);
    return resp;
}