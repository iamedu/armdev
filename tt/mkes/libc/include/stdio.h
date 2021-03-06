#ifndef _STDIO_H
#define _STDIO_H

#include <stddef.h>
#include <stdarg.h>

#define BUFSIZ	8192
#define _IOFBF	0
#define _IOLBF	1
#define _IONBF	2

#define L_ctermid 9
#define L_tmpnam  20

#define SEEK_SET 0
#define SEEK_CUR 1
#define SEEK_END 2

#ifndef NULL
#define NULL	0
#endif

#define EOF -1

#define P_tmpdir "/tmp"

typedef long int fpos_t;

typedef struct {
	int fd; //File descriptor
} FILE;

extern FILE *stderr;
extern FILE *stdin;
extern FILE *stdout;

void		clearerr(FILE *);
char		*ctermid(char *);
int		fclose(FILE *);
FILE		*fdopen(int, const char*);
int		feof(FILE *);
int		ferror(FILE *);
int		fflush(FILE *);
int		fgetc(FILE *);
int		fgetpos(FILE *, fpos_t *);
int		*fgets(FILE *, int, FILE *);
int		fileno(FILE *);
void		*flockfile(FILE *);
FILE		*fopen(const char *, const char	*);
int		fprintf(FILE *, const char *, ...);
int		fputc(int, FILE *);
int		fputs(const char *, FILE *);
size_t		fread(void *, size_t, size_t, FILE *);
FILE		*freopen(const char *, const char *,
			FILE *);
int		fscanf(FILE *, const char *, ...);
int		fseek(FILE *, long, int);
int		fseeko(FILE *, off_t, int);
int		fsetpos(FILE *, const fpos_t *);
long		ftell(FILE *);
off_t		ftello(FILE *);
int		ftrylockfile(FILE *);
void		funlockfile(FILE *);
size_t		fwrite(const void *, size_t, size_t, FILE *);
int		getc(FILE *);
int		getchar(void);

int		getc_unlocked(FILE *);
int		getchar_unlocked(void);

char		*gets(char *);
int		pclose(FILE *);
void		perror(const char *);
FILE		*popen(const char *, const char *);
int		printf(const char *, ...);
int		putc(int, FILE *);
int		putchar(int);
int		putc_unlocked(int, FILE *);
int		putchar_unlocked(int);
int		puts(const char *);
int		remove(const char *);
int		rename(const char *, const char *);
void		rewind(FILE *);
int		scanf(const char *, ...);
void		setbuf(FILE *, char *);
int		setvbuf(FILE *, char *, int, size_t);
int		snprintf(char *, size_t, const char *, ...);
int		sprintf(char *, const char *, ...);
int		sscanf(const char *, const char *, ...);
char		*tempnam(const char *, const char *);
FILE		*tmpfile(void);
char		*tmpnam(char *);
int		ungetc(int, FILE *);
int		vfprintf(FILE *, const char *, va_list);
int		vfscanf(FILE *, const char *, va_list);
int		vprintf(const char *, va_list);
int		vscanf(const char *, va_list);
int		vsnprintf(char *, size_t, const char *,
			va_list);
int		vsprintf(char *, const char *, va_list);
int		vsscanf(const char *, const char *,
			va_list arg);


#endif

