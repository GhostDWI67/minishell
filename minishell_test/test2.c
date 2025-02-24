/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 10:52:38 by dwianni           #+#    #+#             */
/*   Updated: 2025/02/24 11:37:52 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <curses.h>
#include <term.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <ncurses.h>  //compiler avec -lncurses

int main() {
    char termbuf[1024];

	/*
    // Charger l'entrée pour le terminal "xterm"
    if (tgetent(termbuf, "xterm") == 1) {
        printf("Les informations du terminal 'xterm' ont été chargées avec succès.\n");
    } else {
        printf("Erreur lors du chargement des informations pour 'xterm'.\n");
    }
	*/

	if (tgetent(termbuf, "xterm") == 1) {
        // Vérifier si le terminal supporte la fonctionnalité "cm" (déplacement du curseur)
        if (tgetflag("cm")) {
            printf("Le terminal supporte le déplacement du curseur.\n");
        } else {
            printf("Le terminal ne supporte pas le déplacement du curseur.\n");
        }
    }

	if (tgetent(termbuf, "xterm") == 1) {
        // Récupérer la largeur de la page du terminal (en nombre de colonnes)
        int width = tgetnum("co");
        if (width != -1) {
            printf("La largeur du terminal (en colonnes) est : %d\n", width);
        } else {
            printf("Capacité 'co' non disponible pour ce terminal.\n");
        }
    }

	char *cursor;
    
    // Charger les informations pour le terminal "xterm"
    if (tgetent(termbuf, "xterm") == 1) {
        // Récupérer la commande pour déplacer le curseur vers le haut
        cursor = tgetstr("ku", NULL);  // "ku" pour "key up" (curseur vers le haut)
        if (cursor != NULL) {
            printf("Commande pour déplacer le curseur vers le haut : %s\n", cursor);
        } else {
            printf("Capacité 'ku' non disponible pour ce terminal.\n");
        }
    }

	/*
	char *cursor_move;

    // Charger les informations pour le terminal "xterm"
    if (tgetent(termbuf, "xterm") == 1) {
        // Récupérer la commande de déplacement du curseur
        char *move_cursor = tgetstr("cm", NULL);  // "cm" pour "cursor move"
        if (move_cursor != NULL) {
            // Générer la séquence pour déplacer le curseur à la ligne 5, colonne 10
            cursor_move = tgoto(move_cursor, 15, 0);
            if (cursor_move != NULL) {
                printf("Commande pour déplacer le curseur : %s\n", cursor_move);
            } else {
                printf("Erreur lors de la génération de la commande de déplacement.\n");
            }
        }
    }
	*/

	/*
	char *clear_s;
	
	if (tgetent(termbuf, "xterm") == 1) {
        // Récupérer la commande pour effacer l'écran
        char *clear_s = tgetstr("cl", NULL);
        if (clear_s != NULL) {
            // Envoyer la séquence pour effacer l'écran
            tputs(clear_s, 1, putchar);
        } else {
            printf("Capacité 'cl' non disponible pour ce terminal.\n");
        }
    }
	*/
	char *clear_s = "ls -l";

	if (tgetent(termbuf, "xterm") == 1) {
        // Récupérer la commande pour effacer l'écran
        if (clear_s != NULL) {
            // Envoyer la séquence pour effacer l'écran
            tputs(clear_s, 1, putchar);
        } else {
            printf("Capacité 'cl' non disponible pour ce terminal.\n");
        }
	}
	
    return 0;
}
