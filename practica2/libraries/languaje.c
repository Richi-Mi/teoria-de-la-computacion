#include <stdlib.h>
#include <stdio.h>
#include "languaje.h"

// Inicializa un lenguaje vacío
Languaje* initLanguaje() {
    Languaje *newL = malloc(sizeof(Languaje));
    newL->inicio = NULL;
    newL->length = 0;
    return newL;
}
// Libera la memoria de un lenguaje
void freeLanguaje(Languaje *lang) {
    if (!lang) return;

    LanguajeNode *aux = lang->inicio;
    while (aux != NULL) {
        LanguajeNode *temp = aux;
        freeString(temp->inicioCadena);  // Liberamos la cadena
        aux = aux->next;
        free(temp);
    }
    free(lang);
}
// Agrega una cadena al lenguaje
void addString(Languaje *lang, String *cadena) {
    if (!lang || !cadena) return;

    LanguajeNode *nodel = malloc(sizeof(LanguajeNode));
    nodel->inicioCadena = cadena;
    nodel->next = NULL;

    if (lang->inicio == NULL) {
        lang->inicio = nodel;
    } else {
        LanguajeNode *aux = lang->inicio;
        while (aux->next != NULL) {
            aux = aux->next;
        }
        aux->next = nodel;
    }
    lang->length++;
}

// Muestra todas las cadenas en el lenguaje
void showLanguaje(Languaje *lang) {
    if (!lang) { return; }
    LanguajeNode *aux = lang->inicio;
    printf("{ ");
    while (aux != NULL) {
        showString(aux->inicioCadena);
        aux->next != NULL && printf(", ");
        aux = aux->next;
    }
    printf(" }\n");
}
/**
 * Union de lenguajes.
 * consiste en agregar las cadenas del lenguaje1 y lenguaje2 
 * a un nuevo lenguaje.
 */
Languaje* languajeUnion(Languaje *l1, Languaje *l2) {
    if (!l1 || !l2) return NULL;

    Languaje *newLang = initLanguaje();
    LanguajeNode *p = l1->inicio;
    while (p != NULL) {
        addString(newLang, p->inicioCadena ); 
        p = p->next;
    }
    LanguajeNode *q = l2->inicio;
    while (q != NULL) {
        addString(newLang, q->inicioCadena ); 
        q = q->next;
    }
    return newLang;
}
/**
 * Concatenación de lenguajes.
 * Verifica que ambos lenguajes no esten vacios para posteriormente
 * ir concatenando cada cadena del lenguaje. 
 * @param l1 Primer lenguaje
 * @param l2 Segundo lenguaje
 */
Languaje* languajeConcat(Languaje *l1, Languaje *l2) {
    if (!l1 || !l2) return NULL;

    Languaje *newLang = initLanguaje();
    LanguajeNode *p = l1->inicio;
    while (p != NULL) {
        LanguajeNode *q = l2->inicio;
        while (q != NULL) {
            String *c = concat(p->inicioCadena, q->inicioCadena);
            addString(newLang, c);
            q = q->next;
        }
        p = p->next;
    }
    return newLang;
}
/**
 * Reflexión de un lenguaje
 * Consiste en invertir todas las cadenas de ese lenguaje.
 */
Languaje* invertLanguaje(Languaje *lang) {
    if (!lang) return NULL;

    Languaje *newLang = initLanguaje();
    LanguajeNode *p = lang->inicio;
    while (p != NULL) {
        String *inverted = inverseString(p->inicioCadena);
        addString(newLang, inverted);
        p = p->next;
    }
    return newLang;
}

// Potencia un lenguaje (concatena consigo mismo `p` veces)
Languaje* powLanguaje(Languaje *lang, int p) {
    if (!lang) return NULL;

    if ( p == 0 ) return initLanguaje();
    
    if ( p > 0) {
        Languaje *newLang = languajeUnion( lang, initLanguaje() );
        int i;

        for( i = 1; i < p; i++ ) {
            Languaje *aux = languajeConcat( newLang, lang );
            newLang = aux;
        }
        
        return newLang;
        
    } else {
        Languaje *invLang = invertLanguaje( lang );
        Languaje *newLang = languajeUnion( invLang, initLanguaje() );

        for (int i = 1; i < -p; i++) {
            Languaje *aux = languajeConcat( newLang, invLang );
            newLang = aux;
        }
        return newLang;
    }
}
