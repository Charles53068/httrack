/* ------------------------------------------------------------ */
/*
HTTrack Website Copier, Offline Browser for Windows and Unix
Copyright (C) 1998-2014 Xavier Roche and other contributors

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.

Important notes:

- We hereby ask people using this source NOT to use it in purpose of grabbing
emails addresses, or collecting any other private information on persons.
This would disgrace our work, and spoil the many hours we spent on it.

Please visit our Website: http://www.httrack.com
*/

/* ------------------------------------------------------------ */
/* File: Mini-server                                            */
/* Author: Xavier Roche                                         */
/* ------------------------------------------------------------ */

// Fichier intercepteur d'URL .h

#ifndef HTS_SERVER_DEFH
#define HTS_SERVER_DEFH

#include <sys/stat.h>
#include "htsnet.h"

/* String */
#include "htsstrings.h"

// Fonctions
void socinput(T_SOC soc, char *s, int max);
T_SOC smallserver_init_std(int *port_prox, char *adr_prox, int defaultPort);
T_SOC smallserver_init(int *port, char *adr);
int smallserver(T_SOC soc, char *url, char *method, char *data, char *path);

#define CATCH_RESPONSE \
  "HTTP/1.0 200 OK\r\n"\
  "Content-type: text/html\r\n"\
  "\r\n"\
  "<!-- Generated by HTTrack Website Copier -->\r\n"\
  "<HTML><HEAD>\r\n"\
  "<TITLE>Link caught!</TITLE>\r\n"\
  "<SCRIPT LANGUAGE=\"Javascript\">\r\n"\
  "<!--\r\n"\
  "function back() {\r\n"\
  "  history.go(-1);\r\n"\
  "}\r\n"\
  "// -->\r\n"\
  "</SCRIPT>\r\n"\
  "</HEAD>\r\n"\
  "<BODY>\r\n"\
  "<H2>Link captured into HTTrack Website Copier, you can now restore your proxy preferences!</H2>\r\n"\
  "<BR><BR>\r\n"\
  "<H3><A HREF=\"javascript:back();\">Clic here to go back</A></H3>\r\n"\
  "</BODY></HTML>"\
  "<!-- Generated by HTTrack Website Copier -->\r\n"\
  "\r\n"\

extern int NewLangStrSz;
extern coucal NewLangStr;
extern int NewLangStrKeysSz;
extern coucal NewLangStrKeys;
extern int NewLangListSz;
extern coucal NewLangList;

extern httrackp *global_opt;

/* Spaces: CR,LF,TAB,FF */
#define  is_space(c)      ( ((c)==' ') || ((c)=='\"') || ((c)==10) || ((c)==13) || ((c)==9) || ((c)==12) || ((c)==11) || ((c)=='\'') )
#define  is_realspace(c)  ( ((c)==' ')                || ((c)==10) || ((c)==13) || ((c)==9) || ((c)==12) || ((c)==11)                )
#define  is_taborspace(c) ( ((c)==' ')                                          || ((c)==9)                             )
#define  is_quote(c)      (               ((c)=='\"')                                                    || ((c)=='\'') )
#define  is_retorsep(c)   (                              ((c)==10) || ((c)==13) || ((c)==9)                                          )

#undef min
#undef max
#define min(a,b) ((a)>(b)?(b):(a))
#define max(a,b) ((a)>(b)?(a):(b))

extern void smallserver_setpinghandler(void (*fun)(void*), void*arg);
extern int smallserver_setkey(const char *key, const char *value);
extern int smallserver_setkeyint(const char *key, LLint value);
extern int smallserver_setkeyarr(const char *key, int id, const char *key2, const char *value);

int htslang_init(void);
int htslang_uninit(void);

/* Static definitions */

HTS_UNUSED static const char *gethomedir(void);
HTS_UNUSED static int linput_cpp(FILE * fp, char *s, int max);
HTS_UNUSED static int linput_trim(FILE * fp, char *s, int max);
HTS_UNUSED static int fexist(const char *s);
HTS_UNUSED static int linput(FILE * fp, char *s, int max);

HTS_UNUSED static int linputsoc(T_SOC soc, char *s, int max) {
  int c;
  int j = 0;

  do {
    unsigned char ch;

    if (recv(soc, &ch, 1, 0) == 1) {
      c = ch;
    } else {
      c = EOF;
    }
    if (c != EOF) {
      switch (c) {
      case 13:
        break;                  // sauter CR
      case 10:
        c = -1;
        break;
      case 9:
      case 12:
        break;                  // sauter ces caractères
      default:
        s[j++] = (char) c;
        break;
      }
    }
  } while((c != -1) && (c != EOF) && (j < (max - 1)));
  s[j] = '\0';
  return j;
}

HTS_UNUSED static int check_readinput_t(T_SOC soc, int timeout) {
  if (soc != INVALID_SOCKET) {
    fd_set fds;                 // poll structures
    struct timeval tv;          // structure for select

    FD_ZERO(&fds);
    FD_SET(soc, &fds);
    tv.tv_sec = timeout;
    tv.tv_usec = 0;
    select((int) soc + 1, &fds, NULL, NULL, &tv);
    if (FD_ISSET(soc, &fds))
      return 1;
    else
      return 0;
  } else
    return 0;
}

HTS_UNUSED static int linputsoc_t(T_SOC soc, char *s, int max, int timeout) {
  if (check_readinput_t(soc, timeout)) {
    return linputsoc(soc, s, max);
  }
  return -1;
}

static const char *gethomedir(void) {
  const char *home = getenv("HOME");

  if (home)
    return home;
  else
    return ".";
}
static int linput_cpp(FILE * fp, char *s, int max) {
  int rlen = 0;

  s[0] = '\0';
  do {
    int ret;

    if (rlen > 0)
      if (s[rlen - 1] == '\\')
        s[--rlen] = '\0';       // couper \ final
    // lire ligne
    ret = linput_trim(fp, s + rlen, max - rlen);
    if (ret > 0)
      rlen += ret;
  } while((s[max(rlen - 1, 0)] == '\\') && (rlen < max));
  return rlen;
}

static int fexist(const char *s) {
  struct stat st;

  memset(&st, 0, sizeof(st));
  if (stat(s, &st) == 0) {
    if (S_ISREG(st.st_mode)) {
      return 1;
    }
  }
  return 0;
}
static int linput(FILE * fp, char *s, int max) {
  int c;
  int j = 0;

  do {
    c = fgetc(fp);
    if (c != EOF) {
      switch (c) {
      case 13:
        break;                  // sauter CR
      case 10:
        c = -1;
        break;
      case 0:
      case 9:
      case 12:
        break;                  // sauter ces caractères
      default:
        s[j++] = (char) c;
        break;
      }
    }
  } while((c != -1) && (c != EOF) && (j < (max - 1)));
  s[j] = '\0';
  return j;
}
static int linput_trim(FILE * fp, char *s, int max) {
  int rlen = 0;
  char *ls = (char *) malloc(max + 1);

  s[0] = '\0';
  if (ls) {
    char *a;

    // lire ligne
    rlen = linput(fp, ls, max);
    if (rlen) {
      // sauter espaces et tabs en fin
      while((rlen > 0) && is_realspace(ls[max(rlen - 1, 0)]))
        ls[--rlen] = '\0';
      // sauter espaces en début
      a = ls;
      while((rlen > 0) && ((*a == ' ') || (*a == '\t'))) {
        a++;
        rlen--;
      }
      if (rlen > 0) {
        memcpy(s, a, rlen);     // can copy \0 chars
        s[rlen] = '\0';
      }
    }
    //
    free(ls);
  }
  return rlen;
}

static int ehexh(char c) {
  if ((c >= '0') && (c <= '9'))
    return c - '0';
  if ((c >= 'a') && (c <= 'f'))
    c -= ('a' - 'A');
  if ((c >= 'A') && (c <= 'F'))
    return (c - 'A' + 10);
  return 0;
}

static int ehex(const char *s) {
  return 16 * ehexh(*s) + ehexh(*(s + 1));
}

HTS_UNUSED static void unescapehttp(const char *s, String * tempo) {
  size_t i;

  for(i = 0; s[i] != '\0'; i++) {
    if (s[i] == '%' && s[i + 1] == '%') {
      i++;
      StringAddchar(*tempo, '%');
    } else if (s[i] == '%') {
      char hc;

      i++;
      hc = (char) ehex(s + i);
      StringAddchar(*tempo, (char) hc);
      i++;                      // sauter 2 caractères finalement
    } else if (s[i] == '+') {
      StringAddchar(*tempo, ' ');
    } else
      StringAddchar(*tempo, s[i]);
  }
}

HTS_UNUSED static void unescapeini(char *s, String * tempo) {
  size_t i;
  char lastc = 0;

  for(i = 0; s[i] != '\0'; i++) {
    if (s[i] == '%' && s[i + 1] == '%') {
      i++;
      StringAddchar(*tempo, lastc = '%');
    } else if (s[i] == '%') {
      char hc;

      i++;
      hc = (char) ehex(s + i);
      if (!is_retorsep(hc) || !is_retorsep(lastc)) {
        StringAddchar(*tempo, lastc = (char) hc);
      }
      i++;                      // sauter 2 caractères finalement
    } else
      StringAddchar(*tempo, lastc = s[i]);
  }
}

#endif
