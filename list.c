#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct date {
    int jours;
    int mois;
    int annee;
};

struct employe {
    int code;
    char nom[50];
    char prenom[50];
    struct date date_naissance;
    char titre[50];
    int salaire;
    struct employe* next;
};

struct list {
    struct employe* head;
};

struct list* initList() {
    struct list* liste = malloc(sizeof(struct list));
    liste->head = NULL;
    return liste;
}

void chargeFichier(struct list* liste) {
    FILE* f = fopen("employees.txt", "r");

    while (1) {
        struct employe* tmp = malloc(sizeof(struct employe));
        if (fscanf(f, "%d %s %s %d/%d/%d %s %d", &tmp->code, tmp->nom, tmp->prenom, &tmp->date_naissance.jours, &tmp->date_naissance.mois, &tmp->date_naissance.annee, tmp->titre, &tmp->salaire) != EOF) {
            tmp->next = NULL;
            Ajouter(liste, tmp);
        } else {
            free(tmp);
            break;
        }
    }
    fclose(f);
}

int isEmpty(struct list* liste) {
    return liste->head == NULL;
}

void Ajouter(struct list* liste, struct employe* emp) {
    struct employe* tmp = liste->head;
    if (isEmpty(liste)) {
        liste->head = emp;
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = emp;
    }
}

struct employe* trouverCode(struct list* liste, int code) {
    struct employe* tmp = liste->head;
    while (tmp != NULL) {
        if (tmp->code == code) {
            return tmp;
        }
        tmp = tmp->next;
    }
    return NULL;
}

void insertEmployee(struct list* liste, char* nom, char* prenom, int jours, int mois, int annee, char* titre, int salaire) {
    struct employe* emp = malloc(sizeof(struct employe));
    int random;
    do {
        random = rand() % 600 + 600;
    } while (trouverCode(liste, random) != NULL);
    emp->code = random;
    strcpy(emp->nom, nom);
    strcpy(emp->prenom, prenom);
    emp->date_naissance.jours = jours;
    emp->date_naissance.mois = mois;
    emp->date_naissance.annee = annee;
    strcpy(emp->titre, titre);
    emp->salaire = salaire;
    emp->next = NULL;
    Ajouter(liste, emp);
}

void Suprimmer(struct list* liste, int code) {
    int rep;
    printf("Es-tu sûr de vouloir supprimer cet employé ?\n1- OUI\n2- NON\n");
    scanf("%d", &rep);
    if (rep == 1) {
        struct employe* emp = trouverCode(liste, code);
        if (emp != NULL) {
            struct employe* tmp = liste->head;
            if (emp == tmp) {
                liste->head = tmp->next;
                free(emp);
            } else {
                while (tmp->next->next != NULL) {
                    if (tmp->next->code == code) {
                        tmp->next = tmp->next->next;
                        free(emp);
                        break;
                    }
                    tmp = tmp->next;
                }
            }
        } else {
            printf("N'existe pas\n");
        }
    } else {
        printf("Annulation de la suppression\n");
    }
}

void chercherCode(struct list* liste, int code) {
    struct employe* emp = trouverCode(liste, code);
    if (emp != NULL) {
        printf("%d %s %s %d/%d/%d %s %d\n", emp->code, emp->nom, emp->prenom, emp->date_naissance.jours, emp->date_naissance.mois, emp->date_naissance.annee, emp->titre, emp->salaire);
    } else {
        printf("Employee n'existe pas\n");
    }
}

void chercherNom(struct list* liste, char* nom) {
    struct employe* tmp = liste->head;
    int count = 0;
    while (tmp != NULL) {
        if (strcmp(tmp->nom, nom) == 0) {
            count = count + 1;
            printf("%d %s %s %d/%d/%d %s %d\n", tmp->code, tmp->nom, tmp->prenom, tmp->date_naissance.jours, tmp->date_naissance.mois, tmp->date_naissance.annee, tmp->titre, tmp->salaire);
        }
        tmp = tmp->next;
    }
    if (count != 0) {
        printf("Le nombre d'employés est %d\n", count);
    } else {
        printf("Employee n'existe pas\n");
    }
}

void chercherPrenom(struct list* liste, char* prenom) {
    struct employe* tmp = liste->head;
    int count = 0;
    while (tmp != NULL) {
        if (strcmp(tmp->prenom, prenom) == 0) {
            count = count + 1;
            printf("%d %s %s %d/%d/%d %s %d\n", tmp->code, tmp->nom, tmp->prenom, tmp->date_naissance.jours, tmp->date_naissance.mois, tmp->date_naissance.annee, tmp->titre, tmp->salaire);
        }
        tmp = tmp->next;
    }
    if (count != 0) {
        printf("Le nombre d'employés est %d\n", count);
    } else {
        printf("Employee n'existe pas\n");
    }
}

void modifier(struct list* liste, int code) {
    struct employe* emp = trouverCode(liste, code);
    if (emp != NULL) {
        int salaire;
        char titre[50];
        while (1) {
            printf("Entrez le titre du poste : ");
            scanf("%s", titre);
            const char* cmpa = titre;
            if (strcmp(cmpa, "President") == 0 || strcmp(cmpa, "VP-Sales") == 0 || strcmp(cmpa, "VP-Marketing") == 0 || strcmp(cmpa, "Sales-Manager") == 0 || strcmp(cmpa, "Sales-Rep") == 0) {
                break;
            } else {
                printf("Entrez un titre de poste correct\n");
            }
        }
        printf("Entrez le salaire : ");
        scanf("%d", &salaire);
        strcpy(emp->titre, titre);
        emp->salaire = salaire;
    } else {
        printf("Employee n'existe pas\n");
    }
}

void enregistrer(struct list* liste) {
    FILE* f = fopen("employees.txt", "w");
    struct employe* tmp = liste->head;
    while (tmp != NULL) {
        fprintf(f, "%d %s %s %d/%d/%d %s %d\n", tmp->code, tmp->prenom, tmp->prenom, tmp->date_naissance.jours, tmp->date_naissance.mois, tmp->date_naissance.annee, tmp->titre, tmp->salaire);
        tmp = tmp->next;
    }
    fclose(f);
}

int main() {
    struct list* liste1 = initList();
    chargeFichier(liste1);
    int choix;
    do {
        printf(" ------------------MENU--------------- \n");
        printf("1- Ajouter un nouveau employé\n");
        printf("2- Supprimer employé\n");
        printf("3- Chercher un employé par son code\n");
        printf("4- Chercher un employé par son nom\n");
        printf("5- Chercher un employé par son prénom\n");
        printf("6- Modifier salaire et poste de l'employé\n");
        printf("7- Enregistrer dans le fichier\n");
        printf("8- Quitter\n");
        printf("Choix : ");
        scanf("%d", &choix);
        switch (choix) {
            int jours, mois, annee;
            char nom[50], prenom[50], titre[50];
            case 1: {
                printf("Entrez le nom : ");
                scanf("%s", nom);
                printf("Entrez le prénom : ");
                scanf("%s", prenom);
                printf("Entrez le jour de naissance : ");
                scanf("%d", &jours);
                printf("Entrez le mois de naissance : ");
                scanf("%d", &mois);
                printf("Entrez l'année de naissance : ");
                scanf("%d", &annee);
                while (1) {
                    printf("Entrez le titre du poste : ");
                    scanf("%s", titre);
                    if (strcmp(titre, "President") == 0 || strcmp(titre, "VP-Sales") == 0 || strcmp(titre, "VP-Marketing") == 0 || strcmp(titre, "Sales-Manager") == 0 || strcmp(titre, "Sales-Rep") == 0) {
                        break;
                    } else {
                        printf("Entrez un titre de poste correct\n");
                    }
                }
                int salaire;
                printf("Entrez le salaire : ");
                scanf("%d", &salaire);
                insertEmployee(liste1, nom, prenom, jours, mois, annee, titre, salaire);
                break;
            }
            case 2: {
                int code;
                printf("Entrez le code de l'employé : ");
                scanf("%d", &code);
                Suprimmer(liste1, code);
                break;
            }
            case 3: {
                int code;
                printf("Entrez le code de l'employé : ");
                scanf("%d", &code);
                chercherCode(liste1, code);
                break;
            }
            case 4: {
                printf("Entrez le nom de l'employé : ");
                scanf("%s", nom);
                chercherNom(liste1, nom);
                break;
            }
            case 5: {
                printf("Entrez le prénom de l'employé : ");
                scanf("%s", prenom);
                chercherPrenom(liste1, prenom);
                break;
            }
            case 6: {
                int code;
                printf("Entrez le code de l'employé : ");
                scanf("%d", &code);
                modifier(liste1, code);
                break;
            }
            case 7: {
                enregistrer(liste1);
                break;
            }
            case 8: {
                enregistrer(liste1);
                printf("QUITTER\n");
                break;
            }
            default: {
                printf("Choix invalide\n");
            }
        }
    } while (choix != 8);

    return 0;
}
