#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
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
   
            if(strcmp(file_name+len -2,".c") == 0)
                return 1;
    return 0;

}
int main(int argc, char *argv[]){
    struct stat file_stat;
    pid_t pid_switch, process_forcfile;
    if(argc == 1){
        printf("Not multiple cmd agr");
        return EXIT_FAILURE;
    }else{
    for( int  i = 1; i < argc ;i++){
    lstat(argv[i],&file_stat);
    if(S_ISREG(file_stat.st_mode))
    {
        char c;
        char link[24];
        struct tm *time = localtime(&file_stat.st_mtime);
        printf("The file  ' %s ' is a regular file",argv[i]);
        printf("\nA) Regular file\n -n (file name) \n -d (dim/size) \n -h (number of hard links \n -m (time of last modif) \n -a (acces rights) \n -l (create a symbolic link)\n\n");
        
        if(check_c_files_regularfile(argv[i]) == 1){
        process_forcfile = fork();
        if(process_forcfile< 0 ){
            perror("Process for regular file didn t start");
        }else if( process_forcfile== 0){
            execlp("./script.sh","./script.sh",argv[i],NULL);
             exit(EXIT_FAILURE);
        }
        }
       
        scanf(" %c",&c);
        pid_switch = fork();
        if(pid_switch < 0){
            perror("Didn t start");
        }else if(pid_switch == 0){
        switch (c)
        {
        case 'n':printf("File name:%s\n",argv[i]);break;
        case 'd':printf("The size of the file is %ld\n",file_stat.st_size);break;
        case 'h':printf("The number of hard links is %ld\n",file_stat.st_nlink);break;
        case 'm':
        printf("%d minutes and %d seconds have elapsed since the file has been modified", time->tm_min,time->tm_sec);break;
        case 'a':gotoformat(file_stat);break;
        case 'l':printf("Read the file_name for the link to be created\n");
                scanf("%s",link);
                symlink(argv[i],link);
                printf("The file %s was created\n",link);
                break;
        default:fflush(stdin);
            printf("Not a case for a regular file");
            break;
        
        }
        exit(EXIT_FAILURE);
        }
    }

    else if(S_ISLNK(file_stat.st_mode)){
        printf("The file ' %s ' a symbolic link",argv[i]);
        char c;
        printf("\n -n Link name \n-l delete link \n -d Size of link \n-z size of target \n-a acces rights \n");
        scanf(" %c",&c);
    
        switch (c)
        {
            case'n':getLinkname(argv[i]);break;
            case'l':unlink(argv[i]);
                    printf("The link was deleted\n");break;
            case'd':printf("Size of link is %ld \n",file_stat.st_size);break;
            case'z':getLinksize(argv[i]);break;
            case'a':gotoformat(file_stat);break;
            default:
                printf("Not a case for symbolic file");
                break;
            
        }
    }
    else{
        printf("The %s is not a regular/symbolic file",argv[i]);
        char c;
        printf("\n -n Name \n -d Size \n -a Access rights \n -c Total number of .c files \n");
        scanf(" %c",&c);
    
        switch(c)
        {
            case'n':printf("File name is %s\n",argv[i]);break;
            case'd':printf("Size of the file is %ld\n",file_stat.st_size);break;
            case'c':check_c_files(argv[i]);break;
            case'a':gotoformat(file_stat);break;
            default:
                printf("Not a case for a Directory");
                break;
                
            
        }
    }
    }
    }

    return 0;
}
