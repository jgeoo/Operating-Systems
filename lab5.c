#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
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
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
                if(file.st_mode & S_IWUSR )
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
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
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
                if(file.st_mode & S_IWGRP )
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
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
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
                if(file.st_mode & S_IXOTH )
                {
                    printf("Read:YES\n");
                }
                else{
                    printf("Read:NO\n");
                }
}
void getLinkname(char* file){
    char buffer[1024];
    ssize_t len;
    len = readlink(file,buffer,sizeof(buffer)-1);
    printf("The link name of %s is %s\n ",file,buffer);
}

int main(int argc, char *argv[]){
    struct stat file_stat;
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
        printf("The file  ' %s ' is a regular file\n",argv[i]);
        printf("\nA) Regular file\n -n (file name) \n -d (dim/size) \n -h (number of hard links \n -m (time of last modif) \n -a (acces rights) \n -l (create a symbolic link)\n\n");
        scanf(" %c",&c);
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
        default:
            break;
        }
    }

    else if(S_ISLNK(file_stat.st_mode)){
        printf("The file ' %s ' a symbolic link\n",argv[i]);
        char c;
        printf("\n -n Link name \n-l delete link \n -d Size of link \n-z size of target \n-a acces rights \n");
        scanf(" %c",&c);
        switch (c)
        {
            case'n':printf("The link names is "getLinkname(argv[i]));break;
            case'l':printf("Deleted link\n",unlink(argv[i]));break;
            case'd':printf("Size of link is\n",file_stat.st_size);break;
            case'z':printf("Size of target link is\n");break;
            case'a':gotoformat(file_stat);break;
            
        }
    }
    else{
        printf("The %s is not a regular/symbolic file",argv[i]);
    }
    }
    }

    return 0;
}