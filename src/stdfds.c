# include <smdbottom/stdfds.h>
# include <unistd.h>
# include <errno.h>
# include <stdarg.h>

int opening_pipes(int count, ...)
{
    errno = 0;
    int errNum;

    va_list ap;

    va_start(ap, count);
    for (int i = 0; i < count; i++){
        pipe(va_arg(ap, int*));
    }
    va_end(ap);

    if ((errNum = errno) != 0){
        return errNum;
    }

    return 0;
}

int closing_pipes(int count, ...)
{
    errno = 0;
    int errNum;

    va_list ap;

    va_start(ap, count);
    for (int i = 0; i < count; i++){
        close(va_arg(ap, int));
    }
    va_end(ap);

    if ((errNum = errno) != 0){
        return errNum;
    }

    return 0;
}