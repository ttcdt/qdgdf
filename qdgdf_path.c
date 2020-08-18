/*

    Quick and Dirty Game Development Framework (QDGDF)

    Angel Ortega <angel@triptico.com> et al.

    This software is released into the public domain.
    NO WARRANTY. See file LICENSE for details.

*/

#include <string.h>

#ifdef CONFOPT_UNISTD_H
#include <unistd.h>
#endif

#ifdef CONFOPT_SYS_TYPES_H
#include <sys/types.h>
#endif

#ifdef CONFOPT_PWD_H
#include <pwd.h>
#endif

extern const char * _qdgdf_embedded_tar_start;
extern const char * _qdgdf_embedded_tar_end;

static FILE *find_in_embedded_tar(const char *fn)
{
    FILE *f = NULL;
    const char *tar = _qdgdf_embedded_tar_start;

    while (tar && !f && tar < _qdgdf_embedded_tar_end && *tar) {
        long f_size;

        sscanf(&tar[124], "%lo", &f_size);

        if (strcmp(fn, tar))
            tar += (1 + ((f_size + 511) / 512)) * 512;
        else {
            /* found: create temporary file */
            if ((f = tmpfile())) {
                fwrite(tar + 512, f_size, 1, f);
                fseek(f, 0, 0);
            }
        }
    }

    return f;
}


static char *_path_find(const char *path, const char *file)
/* finds file in path; returns full path if found, NULL instead */
{
    char *cpath;
    char *ret = NULL;
    char *ptr1;

    /* no path? nothing to do */
    if (path == NULL && *path == '\0')
        return NULL;

    cpath = strdup(path);
    ptr1 = cpath;

    for (;;) {
        char tmp[150];
        char *ptr2;

        if ((ptr2 = strchr(ptr1, ';')) != NULL)
            *ptr2 = '\0';

        snprintf(tmp, sizeof(tmp) - 1, "%s/%s", ptr1, file);
        tmp[sizeof(tmp) - 1] = '\0';

        if (access(tmp, R_OK) == 0) {
            ret = strdup(tmp);
            break;
        }

        if (ptr2 == NULL)
            break;

        ptr1 = ptr2 + 1;
    }

    free(cpath);

    return ret;
}


static FILE *_path_fopen(const char *path, const char *file, char *mode)
/* file opening function with optional seek path */
{
    FILE *f = NULL;
    char *ptr;

    if ((f = find_in_embedded_tar(file)) == NULL) {
        if ((ptr = _path_find(path, file)) != NULL) {
            f = fopen(ptr, mode);
            free(ptr);
        }

        if (f == NULL)
            f = fopen(file, mode);
    }

    return f;
}


#if defined(CONFOPT_DDRAW) || defined(CONFOPT_DSOUND)
#include <shlobj.h>
#endif

static char *_home_dir(void)
/* returns a writable home directory */
{
    char *ptr;
    static char tmp[2048] = "";

#ifdef CONFOPT_WIN32

    LPITEMIDLIST pidl;

    /* get the 'My Documents' folder */
    SHGetSpecialFolderLocation(NULL, CSIDL_PERSONAL, &pidl);
    SHGetPathFromIDList(pidl, tmp);
    strcat(tmp, "\\");

#endif

#if defined(CONFOPT_PWD_H) && defined(CONFOPT_SYS_TYPES_H) && defined(CONFOPT_UNISTD_H)

    struct passwd *p;

    /* get home dir from /etc/passwd entry */
    if (tmp[0] == '\0' && (p = getpwuid(getpid())) != NULL) {
        strcpy(tmp, p->pw_dir);
        strcat(tmp, "/");
    }

#endif

    /* still none? try the ENV variable $HOME */
    if (tmp[0] == '\0' && (ptr = getenv("HOME")) != NULL) {
        strcpy(tmp, ptr);
        strcat(tmp, "/");
    }

    return tmp;
}


static char *_app_dir(void)
{
    static char tmp[1048] = "";

#ifdef CONFOPT_WIN32

    HKEY hkey;
    LPITEMIDLIST pidl;

    /* get the 'Program Files' folder (can fail) */
    tmp[0] = '\0';
    if (SHGetSpecialFolderLocation(NULL, CSIDL_PROGRAM_FILES, &pidl) ==
        S_OK)
        SHGetPathFromIDList(pidl, tmp);

    /* if it's still empty, get from the registry */
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                     "SOFTWARE\\Microsoft\\Windows\\CurrentVersion",
                     0, KEY_QUERY_VALUE, &hkey) == ERROR_SUCCESS) {
        int n = sizeof(tmp);

        if (RegQueryValueEx(hkey, "ProgramFilesDir",
                            NULL, NULL, tmp,
                            (LPDWORD) & n) != ERROR_SUCCESS)
            tmp[0] = '\0';
    }

    if (tmp[0] != '\0')
        strcat(tmp, "\\");
#endif

    /* still none? get the configured directory */
    if (tmp[0] == '\0')
        strcpy(tmp, CONFOPT_PREFIX "/share/");

    return tmp;
}
