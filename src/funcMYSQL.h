#include <string.h>
#define  TAILLE_VACHAR  255
#define TAILLE_CHAR 100
#define TAILLE_INSERT 100
#define SELECT (sizeof(long int )+ 3 + sizeof(TAILLE_VACHAR))
#define ip "192.168.1.37"

void finish_with_error(con)
{
  fprintf(stderr, "%s\n", mysql_error(con));
  mysql_close(con);
  exit(1);
}

void UpdateProduct(char *id, char *nom, char *prix, char *description){
    MYSQL *con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, ip, "aric", "aric","Fast-Food", 0, NULL, 0) == NULL){
      finish_with_error(con);
    }
    char *req  = malloc(90 + sizeof(id) + sizeof(nom) + sizeof(prix) + sizeof(description));
    sprintf(req,"UPDATE `PRODUIT` SET `nom`='%s',`prix`='%s',`description`='%s' WHERE `PRODUIT`.`id` = %s", nom, prix, description, id);
    printf("req : %s\n",req);
    if (mysql_query(con, req))
  {
      finish_with_error(con);
  }
  free(req);
  mysql_close(con);

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
void DelProduct(char *id){
    MYSQL * con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, ip, "aric", "aric","Fast-Food", 0, NULL, 0) == NULL){
      finish_with_error(con);
    }
    char requete [sizeof(int) + 37];
    sprintf(requete,"DELETE FROM `PRODUIT` WHERE `id`=%s",id);
    printf("%s\n",requete);
    if (mysql_query(con, requete)) {
        finish_with_error(con);
    } 
    mysql_close(con);
}

char * selectproduct(char tab_product){
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
  char *resp=malloc(SELECT*tab_product + 15);
  strcpy(resp, "");
  while ((row = mysql_fetch_row(result)))
  {
      for(int i = 0; i < num_fields; i++)
      {
          if (i == 0)
          {
             while(field = mysql_fetch_field(result))
             {
                strcat(resp, field->name);
                strcat(resp, " ");
             }
             strcat(resp, "\n");
          }
          strcat(resp, row[i] ? row[i] : "NULL");
          strcat(resp, " ");
      }
  }
  strcat(resp,"\0");
  mysql_free_result(result);
  mysql_close(con);
  return resp;
}

char * selectupdateproduct(){
    char * endPtr;
    long value;
    MYSQL *con = mysql_init(NULL);
    if (con == NULL){
      fprintf(stderr, "%s\n", mysql_error(con));
      exit(1);
    }
    if (mysql_real_connect(con, ip, "aric", "aric","Fast-Food", 0, NULL, 0) == NULL){
      finish_with_error(con);
    }
    if (mysql_query(con, "SELECT COUNT(`nom`) FROM `PRODUIT`"))
    {
      finish_with_error(con);
    }
    MYSQL_RES *test = mysql_store_result(con);

    if (test == NULL)
    {
      finish_with_error(con);
    }
    MYSQL_ROW row;

    if(row=mysql_fetch_row(test)){
        value = strtol( row[0], &endPtr,0);
    }
    char *tab_product[value][3];
    char *resp = selectproduct(tab_product);
    printf("%s\n",resp);

  mysql_close(con);
  return resp;
}