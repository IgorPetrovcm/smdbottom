# include <smdbottom/procaproc.h>
# include <smdbottom/stdfds.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <errno.h>

int pout(char* options, char* pmessage)
{
    errno = 0;
    int errNum = 0;

    int outPipe[2], errPipe[2];

    if ((errNum = opening_pipes(2, outPipe, errPipe)) != 0){
        return errNum;
    }


    pid_t childProcessPID = fork();

    if (childProcessPID == -1){
        errNum = errno;
        return errNum;
    }
    else if (childProcessPID == 0){
        int copyOfOutFileDescriptorID = outPipe[1];
        int copyOfErrFileDescriptorID = errPipe[1];

        dup2(copyOfOutFileDescriptorID, STDOUT_FILENO);
        dup2(copyOfErrFileDescriptorID, STDERR_FILENO);

        execl("/bin/sh", "sh", "-c", options);

        closing_pipes(2, STDOUT_FILENO, STDERR_FILENO);
    }
    else {        
        int childProcessStatus;
        waitpid(childProcessPID, &childProcessStatus, 0);

        if (!WIFEXITED(childProcessStatus)){
            errNum = WEXITSTATUS(childProcessPID);
            return errNum;
        }

        closing_pipes(2, errPipe[1], outPipe[1]);

        int countReadErrSymbols = 0;
        char ch;
        while (read(errPipe[0], &ch, 1) > 0){
            pmessage[countReadErrSymbols] = ch;
            countReadErrSymbols++;
        }   

        if (countReadErrSymbols > 0){
            return -1;
        }

    }
    return 0;
}