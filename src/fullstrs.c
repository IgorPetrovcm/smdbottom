# include <smdbottom/fullstrs.h>
# include <errno.h>
# include <stdarg.h>
# include <string.h>

int bufferadder(char* buffer, int count, ...)
{
    errno = 0;
    int errNum;

    va_list ap;

    va_start(ap, count);

    for (int i = 0; i < count; i++){
        if (i == 0){
            strcpy(buffer, va_arg(ap, char*));
        }
        else {
            strcat(buffer, va_arg(ap, char*));
        }
    }
    va_end(ap);

    if ((errNum == errno) != 0){
        return errNum;
    }

    return 0;
}