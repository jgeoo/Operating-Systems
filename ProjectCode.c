#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h> 
#include <sys/wait.h>

int no_process = 0;

void gotoformat(struct stat file){
    printf("USER:\n");
                if(file.st_mode & S_IRUSR )
                    {
                         printf("Read:YES\n");
                    }
                else{
                         printf("Read:NO\n");
                    }
                if(file.st_mode & S_IWUSR )
                    {
                         printf("Write:YES\n");
                    }
                else{
                        printf("Write:NO\n");
                    }
                if(file.st_mode & S_IXUSR )
                    {
                        printf("Execution:YES\n");
                    }
                else{
                        printf("Execution:NO\n");
                    }
    printf("\nGROUP:\n");
                if(file.st_mode & S_IRGRP )
                    {
                        printf("Read:YES\n");
                    }   
                else{
                        printf("Read:NO\n");
                    }
                if(file.st_mode & S_IWGRP )
                    {
                        printf("Write:YES\n");
                    }
                else{
                        printf("Write:NO\n");
                    }
                if(file.st_mode & S_IXGRP )
                    {
                        printf("Execution:YES\n");
                    }
                else{
                        printf("Execution:NO\n");
                    }
    printf("\nOTHERS:\n");
                if(file.st_mode &  S_IROTH)
                    {   
                        printf("Read:YES\n");
                    }
                else{
                        printf("Read:NO\n");
                    }
                if(file.st_mode &   S_IWOTH )
                    {
                        printf("Write:YES\n");
                    }
                else{
                        printf("Write:NO\n");
                    }
                if(file.st_mode & S_IXOTH )
                    {
                        printf("Execution:YES\n");
                    }
                else{
                        printf("Execution:NO\n");
                    }
}
void computescore(int erorrs,int warnings,char* file){
    int score;
  
   if(erorrs == 0 && warnings == 0){
    printf("The score for the file %s is '10'\n",file);
   }
   if(erorrs >= 1){
    printf("The score for the file %s is '1'\n",file);
   }
   if(erorrs == 0 && warnings >= 10 && warnings != 0){
    printf("The score for the file %s is '2'\n",file);
   }
   if(erorrs == 0 && warnings <=10)
   {
    score = 2+8*((10-warnings)/10);
    printf("The score for the file %s is '%d'\n",file,score);
   }
    
}
void getLinkname(char* file){

    char buffer[1024];
    readlink(file,buffer,sizeof(buffer)-1);

    printf("The link name of %s is %s\n ",file,buffer);

}
void getLinksize(char* file){

    char buffer[1024];

    readlink(file,buffer,sizeof(buffer)-1);

    struct stat Target;
    lstat(buffer,&Target);

    printf("The link size of %s is %ld\n ",file,Target.st_size);

}
void check_c_files(char* dir_name){

    DIR *dir;
    struct dirent *ent;
    int count = 0;
    int len;
    dir = opendir(dir_name);

    if(dir!=NULL )
    {
        while((ent = readdir(dir)) !=NULL){
            len = strlen(ent->d_name);
                if(strcmp(ent->d_name+len -2,".c") == 0)
                    count++;

        }
        closedir(dir);
    }else{
        printf("Error opening dir\n");
    }

    printf("The number of c files is %d\n",count);

}
int check_c_files_regularfile(char* file_name){ 

    int len = strlen(file_name);
            if(strcmp(file_name+len - 2,".c") == 0)
                    return 1;

    return 0;

}
int main(int argc, char *argv[]){

    struct stat file_stat;
    int pid;
    int pipefd[2];//0->write 1->read 

    if(argc == 1){

        printf("Not enough command line arguments !");
        return EXIT_FAILURE;

    }else{

    for( int  i = 1; i < argc ;i++){
     lstat(argv[i],&file_stat);

    no_process++;
    pid  = fork();
  
            if(pid  < 0 ){

                    perror("Process for regular file  didn't start");

            }else if( pid == 0){


            if(S_ISREG(file_stat.st_mode))
                {
                char c;
                int flag = 0; 
                char link[24];
                struct tm *time = localtime(&file_stat.st_mtime);

            
                
                printf("The file  ' %s ' is a regular file",argv[i]);
                printf("\nA) Regular file\n -n (file name) \n -d (dim/size) \n -h (number of hard links \n -m (time of last modif) \n -a (acces rights) \n -l (create a symbolic link)\n\n");
                

                scanf(" %c",&c);
                
            while(flag==0){
                switch (c)
                {

                case 'n':printf("File name:%s\n",argv[i]);
                        flag++;break;
                case 'd':printf("The size of the file is %ld\n",file_stat.st_size);
                        flag++;break;
                case 'h':printf("The number of hard links is %ld\n",file_stat.st_nlink);
                        flag++; break;
                case 'm':printf("%d minutes and %d seconds have elapsed since the file has been modified", time->tm_min,time->tm_sec);
                        flag++;break;
                case 'a':gotoformat(file_stat);
                        flag++;break;
                case 'l':printf("Read the file_name for the link to be created\n");
                        scanf("%s",link);
                        symlink(argv[i],link);
                        printf("The file %s was created\n",link);
                        flag++; break;
                default:fflush(stdin);
                    printf("The option you have entered is wrong try again !!!\n");
                    scanf(" %c",&c);
                    continue;
                
                }
            }

                }
            

            else if(S_ISLNK(file_stat.st_mode)){

                printf("The file ' %s ' a symbolic link",argv[i]);
                char c;
                int flag = 0;

                printf("\n -n Link name \n-l delete link \n -d Size of link \n-z size of target \n-a acces rights \n");
                scanf(" %c",&c);
            
                    while(flag == 0){
                switch (c)
                {
                    case'n':getLinkname(argv[i]);
                            flag++; break;
                    case'l':unlink(argv[i]);
                            printf("The link was deleted\n");
                            flag++; break;
                    case'd':printf("Size of link is %ld \n",file_stat.st_size);
                            flag++; break;
                    case'z':getLinksize(argv[i]);
                            flag++; break;
                    case'a':gotoformat(file_stat);
                            flag++; break;
                    default:
                            printf("For a symbolic link the option you have entered is wrong try again !!!\n");
                            scanf(" %c",&c);
                            continue;
                    
                }
                    }
            }
            else{
                printf("The %s is not a regular/symbolic file",argv[i]);
                char c;
                int flag = 0;
                printf("\n -n Name \n -d Size \n -a Access rights \n -c Total number of .c files \n");

                scanf(" %c",&c);
                while(flag == 0){
                switch(c)
                    {
                    case'n':printf("File name is %s\n",argv[i]);
                            flag++; break;
                    case'd':printf("Size of the file is %ld\n",file_stat.st_size);
                            flag++; break;
                    case'c':check_c_files(argv[i]);
                            flag++; break;
                    case'a':gotoformat(file_stat);
                            flag++; break;
                    default:
                            printf("For a Directory the option you have entered is wrong try again !!!\n");
                            scanf(" %c",&c);
                            continue;
                        
                    
                    }
                }
                }
                exit(0);
            }
        
    if(S_ISREG(file_stat.st_mode)){
        if(pipe(pipefd) == -1){
            perror("Error with pipe\n");
            exit(EXIT_FAILURE);
        }
      no_process++;
                pid = fork();
                int warnings=0,erorrs=0;
                
                            if(pid < 0){
                                perror("Didn t start\n");
                        }else if(pid == 0){
                            if(check_c_files_regularfile(argv[i] ) == 1){
                            
                                close(pipefd[0]);

                                dup2(pipefd[1], STDOUT_FILENO);
                                execlp("./script.sh","./script.sh",argv[i],NULL);
                                exit(0);

                                }else{  
                                
                                    //printf("There are ");
                                    execlp("wc","wc","-l",argv[i],NULL);
                                    //printf("lines for the file %s\n",argv[i]);
                                    exit(0);

                                }
                            exit(0);
                        }else{
                            
                            close(pipefd[1]);
                            

                            FILE * FD = fdopen(pipefd[0],"r");

                            if(FD == NULL)
                            {
                                perror("Couldn't open the file for the pipe");
                                exit(EXIT_FAILURE);
                            }

                            fscanf(FD,"%d",&warnings);
                            fscanf(FD,"%d", &erorrs);

                            fclose(FD);
                            close(pipefd[0]);
                            if(check_c_files_regularfile(argv[i] ) == 1){
                            computescore(warnings,erorrs,argv[i]);
                            
                            }
                            
                        }
                        
    }
    if(S_ISDIR(file_stat.st_mode)){
                pid = fork();
                no_process++;
                if(pid < 0){
                            perror("Didn t start\n");
                    }else if(pid == 0){
                char director_name[256];

                strcat(director_name,argv[i]);
                strcat(director_name,"_file.txt");

                if(execlp("./filedirscript.sh","./filedirscript.sh",director_name,NULL) == -1){
                    printf("The execute command for creating a file with the Directory name failed\n");
                }

                exit(0);
            
                }

        }
    if(S_ISLNK(file_stat.st_mode)){
                no_process++;
                pid = fork();

                if(pid < 0){
                            perror("Didn t start\n");
                    }else if(pid == 0){
                        execlp("chmod","chmod","760",argv[i],NULL);
                    }

        }
        for(int i = 0;i<no_process;i++){
         int status;
                wait(&status);
            //if(WIFEXITED(status))
               // printf("The process with PID %d has ended with the exit code %d \n",getpid(),WIFEXITED(status));                
                }
    
    }
    }
         
    return 0;
    }
