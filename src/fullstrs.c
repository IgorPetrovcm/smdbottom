# include <smdbottom/fullstrs.h>
# include <errno.h>
# include <stdarg.h>
# include <string.h>

int lbufferadder(char* buffer, int count, ...)
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

char* qlastchars(char* src, char delimiter)
{
    int i;
    for (i = strlen(src) - 1; i > -1; i++){
        if (*(src + i) == delimiter){
            break;
        }
    }

    if (*(src + i) == delimiter){
        return src + i + 1;
    }
    else {
        return NULL;
    }
}