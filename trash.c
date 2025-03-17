/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:48:47 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/17 18:01:27 by dwianni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

/*
int main() {
    int id = fork();
	printf("Current ID %d Parent ID %d ID %d\n", getpid(), getppid(), id);

    return 0; 
}
*/
/*
int	main()
{
	int	fd[2];
	int pid1;
	int	pid2;

	if (pipe(fd) == - 1)
		return (1);
	printf("fd0 %d fd1 %d\n", fd[0], fd[1]);
	pid1 = fork();
	if (pid1 <0)
		return (2);
	if (pid1 ==0)
	{
		dup2(fd[1], STDOUT_FILENO);
		//dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		execlp("ping", "ping", "-c", "5", "google.com", NULL);
	}
	pid2 = fork();
	if (pid2 <0)
		return (3);
	if (pid2 ==0)
	{
		dup2(fd[0], STDIN_FILENO);
		//dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		execlp("grep", "grep", "rtt", NULL);
	}
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);

	
	return (0);
}
*/

/*
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main() {
    // Ouvrir un fichier en écriture (création si nécessaire)
    int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	printf("Fd %d\n",fd);
	if (fd == -1) {
        perror("Erreur lors de l'ouverture du fichier");
        return 1;
    }

    // Dupliquer le descripteur de fichier de sortie standard (1) vers le fichier ouvert
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("Erreur lors de la duplication du descripteur");
        return 1;
    }
	write (1, &"toto", 4);
    // À partir de maintenant, tout ce qui est écrit sur stdout sera écrit dans "output.txt"
    printf("Ce texte sera écrit dans le fichier output.txt\n");
	printf("jsdbfubsdjhgvbdshgbsdhgvjhs\n");
	printf("fvehwvfhesvfhveufvewuhfvewfvyuewvfyuewbfhewvfyuefbuyfebguyf\n");
	

    // Fermer le descripteur de fichier
    close(fd);

    return 0;
}
*/


#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
/*
int main() {
    int pipefd[2];  // Tableau pour les descripteurs de fichier (lecture, écriture)
    pid_t pid;

	printf("fd0 %d fd1 %d\n", pipefd[0], pipefd[1]);
    // Créer un pipe
    if (pipe(pipefd) == -1) {
        perror("Erreur lors de la création du pipe");
        return 1;
    }

    // Créer un processus enfant
    pid = fork();

    if (pid == -1) {
        perror("Erreur lors de la création du processus enfant");
        return 1;
    }

    if (pid == 0) {  // Code du processus enfant
        // Fermer le descripteur d'écriture du pipe dans l'enfant
       //close(pipefd[1]);

        char buffer[128];
        ssize_t bytesRead;

        // Lire depuis le pipe
        bytesRead = read(pipefd[0], buffer, sizeof(buffer));
        if (bytesRead == -1) {
            perror("Erreur lors de la lecture du pipe");
            return 1;
        }

        // Afficher ce qui a été lu
        printf("Enfant a lu : %s\n", buffer);

        //close(pipefd[0]);
    } else {  // Code du processus parent
        // Fermer le descripteur de lecture du pipe dans le parent
        //close(pipefd[0]);

        const char *message = "Bonjour de la part du parent !";

        // Écrire dans le pipe
        if (write(pipefd[1], message, strlen(message)) == -1) {
            perror("Erreur lors de l'écriture dans le pipe");
            return 1;
        }

        //close(pipefd[1]);
    }

    return 0;
}
*/
/*
int main() {
    int pipefd[2];  // Tableau pour les descripteurs de fichier (lecture, écriture)
    pid_t pid;

	printf("fd0 %d fd1 %d\n", pipefd[0], pipefd[1]);
    // Créer un pipe
    if (pipe(pipefd) == -1) {
        perror("Erreur lors de la création du pipe");
        return 1;
    }

    // Créer un processus enfant
    pid = fork();

    if (pid == -1) {
        perror("Erreur lors de la création du processus enfant");
        return 1;
    }

    if (pid != 0) {  // Code du processus enfant
        // Fermer le descripteur d'écriture du pipe dans l'enfant
       //close(pipefd[1]);

        char buffer[128];
        ssize_t bytesRead;

        // Lire depuis le pipe
        bytesRead = read(pipefd[0], buffer, sizeof(buffer));
        if (bytesRead == -1) {
            perror("Erreur lors de la lecture du pipe");
            return 1;
        }

        // Afficher ce qui a été lu
        printf("Le parent a lu : %s\n", buffer);

        //close(pipefd[0]);
    } else {  // Code du processus parent
        // Fermer le descripteur de lecture du pipe dans le parent
        //close(pipefd[0]);

        const char *message = "Bonjour de la part du CHILD !";
		sleep(2);
        // Écrire dans le pipe
        if (write(pipefd[1], message, strlen(message)) == -1) {
            perror("Erreur lors de l'écriture dans le pipe");
            return 1;
        }

        //close(pipefd[1]);
    }

    return 0;
}
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
/*
int main() {
    int n;

    // Demander à l'utilisateur combien de processus il veut créer
    printf("Entrez le nombre de forks à créer : ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();  // Crée un nouveau processus

        if (pid == -1) {
            // Si fork échoue
            perror("Erreur lors du fork");
            exit(1);
        } else if (pid == 0) {
            // Code exécuté par le processus fils
            printf("Je suis le processus fils numéro %d, mon PID est %d\n", i + 1, getpid());
            exit(0);  // Le processus fils se termine
        } else {
            // Code exécuté par le processus parent
            // Le processus parent attendra tous les fils avant de continuer
            // On pourrait ne pas attendre ici si on veut que les processus parents se terminent avant les fils
        }
    }

    // Attente pour s'assurer que le processus parent attend tous les fils
    for (int i = 0; i < n; i++) {
        wait(NULL);  // Attente que les processus fils se terminent
    }

    printf("Le processus parent a créé %d processus fils.\n", n);

    return 0;
}
*/
/*
int main() {
	int n;
	int i;

	n = 5;
	while(i < n)
	{
		pid_t pid = fork();
		if (pid == -1)
		{
			perror("Erreur lors du fork");
			exit(1);
		}
		else if (pid == 0)
		{
			sleep(i + 1);
			printf("Je suis le processus fils numéro %d, mon PID est %d\n", i + 1, getpid());
			exit(0);
		}
		else
		{
			sleep(2);
			printf("toto %d\n", i);
		}
		i++;
	}

    // Attente pour s'assurer que le processus parent attend tous les fils
	i = 0;
	while (i < n)
	{
		wait(NULL);
		i++;
	}
    printf("Le processus parent a créé %d processus fils.\n", n);
    return 0;
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX_ARGS 10
#define MAX_PIPES 5

void execute_pipes(char *command) {
    char *commands[MAX_PIPES + 1];  // Tableau pour stocker les différentes commandes séparées par des pipes
    int pipefds[2 * MAX_PIPES];  // Tableau pour stocker les descripteurs des pipes
    pid_t pid;
    int num_pipes = 0;

    // Diviser la commande en sous-commandes séparées par des pipes
    commands[num_pipes] = strtok(command, "|");
    while (commands[num_pipes] != NULL && num_pipes < MAX_PIPES) {
        num_pipes++;
        commands[num_pipes] = strtok(NULL, "|");
    }

    // Création des pipes nécessaires
    for (int i = 0; i < 2 * num_pipes; i++) {
        if (pipe(pipefds + i * 2) == -1) {
            perror("Erreur de pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Exécution des commandes
    for (int i = 0; i < num_pipes; i++) {
        pid = fork();

        if (pid == -1) {
            perror("Erreur de fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {  // Code du processus enfant
            char *args[MAX_ARGS];
            char *token = strtok(commands[i], " ");  // Diviser la commande en arguments
            int j = 0;
            while (token != NULL) {
                args[j++] = token;
                token = strtok(NULL, " ");
            }
            args[j] = NULL;  // Terminer le tableau d'arguments

            // Redirection de la sortie standard (stdout) vers le pipe suivant, sauf pour la dernière commande
            if (i < num_pipes - 1) {
                if (dup2(pipefds[(i + 1) * 2], STDOUT_FILENO) == -1) {
                    perror("Erreur de redirection de sortie");
                    exit(EXIT_FAILURE);
                }
            }

            // Redirection de l'entrée standard (stdin) vers le pipe précédent, sauf pour la première commande
            if (i > 0) {
                if (dup2(pipefds[(i * 2) - 2], STDIN_FILENO) == -1) {
                    perror("Erreur de redirection d'entrée");
                    exit(EXIT_FAILURE);
                }
            }

            // Fermer tous les descripteurs de pipe dans le processus enfant
            for (int j = 0; j < 2 * num_pipes; j++) {
                close(pipefds[j]);
            }

            // Exécuter la commande avec execvp()
            if (execvp(args[0], args) == -1) {
                perror("Erreur de execvp");
                exit(EXIT_FAILURE);
            }
        }
    }

    // Code du processus parent : fermer les descripteurs de pipe et attendre les processus enfants
    for (int i = 0; i < 2 * num_pipes; i++) {
        close(pipefds[i]);
    }

    // Attendre la fin de tous les processus enfants
    for (int i = 0; i < num_pipes; i++) {
        wait(NULL);
    }
}

int main() {
    char command[256];
    
    // Lire une commande avec des pipes (par exemple "ls | grep c | wc -l")
    printf("Entrez une commande avec des pipes : ");
    fgets(command, sizeof(command), stdin);
    command[strcspn(command, "\n")] = '\0';  // Supprimer le caractère de nouvelle ligne

    // Exécuter les commandes avec des pipes
    execute_pipes(command);

    return 0;
}
