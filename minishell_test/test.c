/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 15:48:26 by dwianni           #+#    #+#             */
/*   Updated: 2025/02/24 11:14:16 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h> // compile avec  -lreadline -lhistory
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <term.h>



int main() {
    
	/*
	char *input;

    while (1) {
        // Demander à l'utilisateur de saisir une commande
        input = readline("Entrez une commande : ");
        
        if (input != NULL) {
            // Ajouter un texte préfixe à l'entrée de l'utilisateur
            char *modified_input = "Préfixe: ";
            rl_replace_line(modified_input, 0);  // Remplacer la ligne actuelle par "Préfixe: "
            
            // Redessiner l'écran pour afficher la ligne modifiée
            //rl_redisplay();  // Redessiner la ligne

            // Afficher la ligne modifiée
            //printf("Ligne modifiée : %s\n", modified_input);
			//printf("Ligne modifiée input : %s\n", input);
            
            // Ajouter la ligne modifiée à l'historique
            add_history(modified_input);
            
            // Libérer la mémoire allouée par readline
            free(input);
        }
    }


	pid_t pid = fork();

	if (pid == -1) {
		perror("Échec de fork");
		return 1;
	} else if (pid == 0) {
		// Code du processus enfant
		printf("Je suis le processus enfant, mon PID est %d\n", getpid());
		sleep(2);  // Simuler un travail dans le processus enfant
		printf("Le processus enfant se termine\n");
	} else {
		// Code du processus parent
		printf("Je suis le processus parent, mon PID est %d, mon enfant a le PID %d\n", getpid(), pid);
		
		// Attendre que le processus enfant se termine
		wait(NULL);
		printf("Le processus parent a attendu la fin de l'enfant\n");
	}
	

	pid_t pid = fork();
	if (pid == 0) {
    // Processus enfant
 	   exit(0);
	} else {
	    // Processus parent
    	int status;
	    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        printf("Le processus enfant s'est terminé avec le code %d\n", WEXITSTATUS(status));
    }
}


pid_t pid = fork();
if (pid == 0) {
	// Processus enfant : exemple de travail
	printf("Processus enfant en cours...\n");
	sleep(2);  // Simule un travail
	exit(0);   // Le processus enfant se termine normalement
} else {
	// Processus parent
	int status;
	struct rusage usage;
	
	// Attendre la fin du processus enfant
	pid_t child_pid = wait4(pid, &status, 0, &usage);
	
	if (child_pid == -1) {
		perror("wait4 échoué");
		return 1;
	}

	// Vérifier l'état de terminaison du processus enfant
	if (WIFEXITED(status)) {
		printf("Le processus enfant s'est terminé avec le code %d\n", WEXITSTATUS(status));
	} else if (WIFSIGNALED(status)) {
		printf("Le processus enfant a été tué par le signal %d\n", WTERMSIG(status));
	}

	// Afficher les informations sur l'utilisation des ressources
	printf("Temps CPU utilisateur utilisé par l'enfant : %ld secondes\n", usage.ru_utime.tv_sec);
	printf("Temps CPU système utilisé par l'enfant : %ld secondes\n", usage.ru_stime.tv_sec);
	printf("Mémoire maximale utilisée par l'enfant : %ld Ko\n", usage.ru_maxrss);
}
*/
/*
	char buf[1024];
    if (getcwd(buf, sizeof(buf)) != NULL) {
        printf("Répertoire actuel : %s\n", buf);
    } else {
        perror("getcwd échoué");
    }	

	if (chdir("/tmp") == 0) {
        printf("Répertoire de travail modifié avec succès.\n");
    } else {
        perror("chdir échoué");
    }
	
	if (getcwd(buf, sizeof(buf)) != NULL) {
        printf("Répertoire actuel : %s\n", buf);
    } else {
        perror("getcwd échoué");
    }	
*/
/*
    char *argv[] = {"/bin/ls", "-l", NULL};
    char *envp[] = {NULL};

    // Remplace le programme actuel par "ls -l"
    if (execve(argv[0], argv, envp) == -1) {
        perror("execve échoué");
    }

    return 0; // Ne sera pas atteint si execve réussit
}
*/
/*
	int pipefd[2];
    if (pipe(pipefd) == -1) {
        perror("pipe échoué");
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {  // Processus enfant
        close(pipefd[0]);  // Ne lit pas du pipe
        const char *message = "Bonjour du processus enfant";
        write(pipefd[1], message, strlen(message) + 1);
        close(pipefd[1]);
    } else {  // Processus parent
        close(pipefd[1]);  // Ne écrit pas dans le pipe
        char buffer[100];
        read(pipefd[0], buffer, sizeof(buffer));
        printf("Le parent a reçu : %s\n", buffer);
        close(pipefd[0]);
    }
*/
/*
	DIR *dir = opendir("/tmp");
    if (dir == NULL) {
        perror("opendir échoué");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("Nom du fichier : %s\n", entry->d_name);
    }

    closedir(dir);
*/

	int	fd = open ("test.txt", O_RDONLY);
	
	if (fd == -1)
	{
		perror("yfeyufguey ");
		return 0;
	}

	if (isatty(0)) {  // Vérifier si stdout est un terminal
		printf("fd est un terminal.\n");
	} else {
		printf("fd n'est pas un terminal.\n");
	}	
	
	char *tty = ttyname(0);  // Obtenir le nom du terminal associé à stdout
    if (tty != NULL) {
        printf("Nom du terminal : %s\n", tty);
    } else {
        printf("Ce descripteur ne fait pas référence à un terminal.\n");
    }

	int slot = ttyslot();  // Obtenir l'identifiant du terminal
    if (slot != -1) {
        printf("L'identifiant du terminal est : %d\n", slot);
    } else {
        printf("Aucun terminal associé.\n");
    }

	struct winsize w;
    if (ioctl(0, TIOCGWINSZ, &w) == -1) {  // Obtenir la taille du terminal
        perror("ioctl échoué");
        exit(1);
    }

    printf("Largeur du terminal : %d, Hauteur : %d\n", w.ws_col, w.ws_row);

    // Récupérer la variable d'environnement PATH
    char *path = getenv("PATH");
    if (path != NULL) {
        printf("La variable PATH est : %s\n", path);
    } else {
        printf("La variable d'environnement PATH n'est pas définie.\n");
    }

	/*
	struct termios term;
    
    // Récupérer les paramètres actuels du terminal
    tcgetattr(STDIN_FILENO, &term);
    
    // Modifier le mode d'entrée pour qu'il soit non canonique
    term.c_lflag &= ~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW, &term);

    printf("Mode non canonique activé.\n");
	*/

	
    return 0;
}
