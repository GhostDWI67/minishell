/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trash.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dwianni <dwianni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 17:48:47 by dwianni           #+#    #+#             */
/*   Updated: 2025/03/16 15:03:20 by dwianni          ###   ########.fr       */
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
