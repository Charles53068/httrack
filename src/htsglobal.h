/* ------------------------------------------------------------ */
/*
HTTrack Website Copier, Offline Browser for Windows and Unix
Copyright (C) Xavier Roche and other contributors

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.


Important notes:

- We hereby ask people using this source NOT to use it in purpose of grabbing
emails addresses, or collecting any other private information on persons.
This would disgrace our work, and spoil the many hours we spent on it.


Please visit our Website: http://www.httrack.com
*/


/* ------------------------------------------------------------ */
/* File: Global #define file                                    */
/* Author: Xavier Roche                                         */
/* ------------------------------------------------------------ */

// Fichier r�unissant l'ensemble des defines

#ifndef HTTRACK_GLOBAL_DEFH
#define HTTRACK_GLOBAL_DEFH

// Version
#define HTTRACK_VERSION      "3.33-2"
#define HTTRACK_VERSIONID    "3.33.16"
#define HTTRACK_AFF_VERSION  "3.x"
//#define HTTRACK_AFF_WARNING  "This is a BETA release of WinHTTrack Website Copier ("HTTRACK_VERSION")\nPlease report any crashes, bugs or problems"

#ifndef HTS_NOINCLUDES
#ifndef _WIN32_WCE
#include <stdio.h>
#include <stdlib.h>
#else
#include <stdio.h>
#include <stdlib.h>
#ifdef HTS_CECOMPAT
#include "cecompat.h"
#else
#include "celib.h"
#endif
#endif
#endif

// D�finition plate-forme
#include "htssystem.h"
#include "htsconfig.h"

// WIN32 types
#ifdef _WIN32
#ifndef SIZEOF_LONG
#define SIZEOF_LONG 4
#define SIZEOF_LONG_LONG 8
#endif
#endif


// config.h
#ifdef _WIN32

// WIN32
#ifndef _WIN32_WCE

#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_STAT_H 1
#ifndef DLLIB
#define DLLIB 1
#endif
#ifndef HTS_INET6
#define HTS_INET6 1
#endif
#ifndef S_ISREG
#define S_ISREG(m) ((m) & _S_IFREG)
#endif

#else

// Win32CE
//#pragma runtime_checks( "s", restore )
#define HTS_SPARE_MEMORY 1
#define HTS_ALIGN 8
#define BIGSTK static
#undef DLLIB   // LoadLibrary(libssl) crashes
#define NOSTRDEBUG 1
#undef HTS_MAKE_KEYWORD_INDEX
#ifdef HTS_CECOMPAT
#define HTS_DO_NOT_USE_FTIME 1
#undef HAVE_SYS_STAT_H
#undef HAVE_SYS_TYPES_H
#else
#undef HTS_DO_NOT_USE_FTIME
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#endif

#define HTS_DLOPEN 0
#undef HTS_INET6
#ifndef S_ISREG
#define S_ISREG(m) ((m) & _S_IFREG)

#endif

#endif

#else

#include "config.h"

#ifndef FTIME
#define HTS_DO_NOT_USE_FTIME
#endif

#ifndef SETUID
#define HTS_DO_NOT_USE_UID
#endif

#ifndef HTS_LONGLONG
#ifdef SIZEOF_LONG_LONG
#if SIZEOF_LONG_LONG==8
#define HTS_LONGLONG 1
#endif
#endif

#ifndef HTS_LONGLONG
#ifdef __sun
#define HTS_LONGLONG 0
#endif
#ifdef __osf__
#define HTS_LONGLONG 0
#endif
#ifdef __linux
#define HTS_LONGLONG 1
#endif
#ifdef _WIN32
#define HTS_LONGLONG 1
#endif
#endif
#endif

#ifdef DLLIB
#define HTS_DLOPEN 1
#else
#define HTS_DLOPEN 0
#endif

#endif

// Socket windows ou socket unix
#ifdef _WIN32
#undef HTS_PLATFORM
#define HTS_PLATFORM 1
#define HTS_WIN 1

#else

#define HTS_WIN 0
#ifdef __linux
#undef HTS_PLATFORM
#define HTS_PLATFORM 3
#endif
#endif

// don't spare memory usage by default
#ifndef HTS_SPARE_MEMORY
#define HTS_SPARE_MEMORY 0
#endif

#ifndef BIGSTK 
#define BIGSTK
#endif

// compatibilit� DOS
#if HTS_WIN
#define HTS_DOSNAME 1
#else
#define HTS_DOSNAME 0
#endif

// utiliser zlib?
#ifndef HTS_USEZLIB
// autoload
#define HTS_USEZLIB 1
#endif

#ifndef HTS_INET6
#define HTS_INET6 0
#endif

// utiliser openssl?
#ifndef HTS_USEOPENSSL
// autoload
#define HTS_USEOPENSSL 1
#endif

#ifndef HTS_DLOPEN
#define HTS_DLOPEN 1
#endif

#ifndef HTS_USESWF
#define HTS_USESWF 1
#endif

#if HTS_WIN
#else
#define __cdecl
#endif

#ifdef HTS_ANALYSTE_CONSOLE
#undef HTS_ANALYSTE_CONSOLE
#define HTS_ANALYSTE_CONSOLE 1
#endif

#if HTS_ANALYSTE
#else
#if HTS_WIN
#else
#undef HTS_ANALYSTE
// Analyste
#define HTS_ANALYSTE 1
#define HTS_ANALYSTE_CONSOLE 1
#endif
#endif


/* rc file */
#if HTS_WIN
#define HTS_HTTRACKRC "httrackrc"
#else

#ifndef HTS_ETCPATH
#define HTS_ETCPATH "/etc"
#endif
#ifndef HTS_BINPATH
#define HTS_BINPATH "/usr/bin"
#endif
#ifndef HTS_LIBPATH
#define HTS_LIBPATH "/usr/lib"
#endif
#ifndef HTS_PREFIX
#define HTS_PREFIX "/usr"
#endif

#define HTS_HTTRACKRC ".httrackrc"
#define HTS_HTTRACKCNF HTS_ETCPATH"/httrack.conf"

#ifdef DATADIR
#define HTS_HTTRACKDIR DATADIR"/httrack/"
#else
#define HTS_HTTRACKDIR HTS_PREFIX"/share/httrack/"
#endif

#endif

#if HTS_SPARE_MEMORY==0
/* Gestion des tables de hashage */
#define HTS_HASH_SIZE 20147
/* Taille max d'une URL */
#define HTS_URLMAXSIZE 1024
/* Taille max ligne de commande (>=HTS_URLMAXSIZE*2) */
#define HTS_CDLMAXSIZE 1024
#else
/* Gestion des tables de hashage */
#define HTS_HASH_SIZE 1023
/* Taille max d'une URL */
#define HTS_URLMAXSIZE 256
/* Taille max ligne de commande (>=HTS_URLMAXSIZE*2) */
#define HTS_CDLMAXSIZE 1024
#endif

/* Copyright (C) Xavier Roche and other contributors */
#define HTTRACK_AFF_AUTHORS "[XR&CO'2005]"
#define HTS_DEFAULT_FOOTER "<!-- Mirrored from %s%s by HTTrack Website Copier/"HTTRACK_AFF_VERSION" "HTTRACK_AFF_AUTHORS", %s -->"
#define HTTRACK_WEB "http://www.httrack.com"
#define HTS_UPDATE_WEBSITE "http://www.httrack.com/update.php3?Product=HTTrack&Version="HTTRACK_VERSIONID"&VersionStr="HTTRACK_VERSION"&Platform=%d&Language=%s"

#define H_CRLF "\x0d\x0a"
#define CRLF   "\x0d\x0a"
#if HTS_WIN
#define LF "\x0d\x0a"
#else
#define LF "\x0a"
#endif

/* �quivaut � "param�tre vide", par exemple -F (none) */
#define HTS_NOPARAM "(none)"
#define HTS_NOPARAM2 "\"(none)\""

/* maximum et minimum */
#define maximum(A,B) ( (A) > (B) ? (A) : (B) )
#define minimum(A,B) ( (A) < (B) ? (A) : (B) )

/* chaine vide? */
#define strnotempty(A) (((A)[0]!='\0') ? 1 : 0)

/* optimisation inline si possible */
#ifdef __cplusplus
#define HTS_INLINE inline
#else
#define HTS_INLINE
#endif

#ifdef _WIN32
#ifdef LIBHTTRACK_EXPORTS
#define HTSEXT_API __declspec(dllexport)
#else
#define HTSEXT_API __declspec(dllimport)
#endif
#else
#define HTSEXT_API 
#endif

#ifndef HTS_LONGLONG
#ifdef HTS_NO_64_BIT
#define HTS_LONGLONG 0
#else
#define HTS_LONGLONG 1
#endif
#endif

// long long int? (or int)
// (and int cast for system functions like malloc() )

#if HTS_LONGLONG
#ifdef LLINT_FORMAT
  typedef LLINT_TYPE LLint;
  typedef LLINT_TYPE TStamp;
  #define LLintP LLINT_FORMAT
#else
 #if HTS_WIN
  typedef __int64 LLint;
  typedef __int64 TStamp;
  #define LLintP "%I64d"
 #else
 #if HTS_PLATFORM==0
  typedef long long int LLint;
  typedef long long int TStamp;
  #define LLintP "%lld"
 #else
  typedef long long int LLint;
  typedef long long int TStamp;
  #define LLintP "%Ld"
 #endif
 #endif
#endif
#else
 typedef int LLint;
 #define LLintP "%d"
 typedef double TStamp;
#endif

#ifdef LFS_FLAG
typedef LLint INTsys;
#define INTsysP LLintP
#ifdef __linux
#define HTS_FSEEKO
#endif
#else
typedef int INTsys;
#define INTsysP "%d"
#endif

/* Default alignement */
#ifndef HTS_ALIGN
#define HTS_ALIGN (sizeof(void*))
#endif

/* IPV4, IPV6 and various unified structures */
#define HTS_MAXADDRLEN 64

#if HTS_WIN
#else
#define __cdecl 
#endif

/* mode pour mkdir ET chmod (acc�s aux fichiers) */
#define HTS_PROTECT_FOLDER (S_IRUSR|S_IWUSR|S_IXUSR)
#if HTS_ACCESS
#define HTS_ACCESS_FILE (S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH)
#define HTS_ACCESS_FOLDER (S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH)
#else
#define HTS_ACCESS_FILE (S_IRUSR|S_IWUSR)
#define HTS_ACCESS_FOLDER (S_IRUSR|S_IWUSR|S_IXUSR)
#endif

/* v�rifier la d�claration des variables pr�processeur */
#ifndef HTS_DOSNAME
#error | HTS_DOSNAME Has not been defined.
#error | Set it to 1 if you are under DOS, 0 under Unix.
#error | Example: place this line in you source, before includes:
#error | #define HTS_DOSNAME 0
#error
#error
#endif
#ifndef HTS_ACCESS
/* Par d�faut, acc�s � tous les utilisateurs */
#define HTS_ACCESS 1
#endif

/* fflush sur stdout */
#define io_flush { fflush(stdout); fflush(stdin); }



/* HTSLib */

// Cache DNS, acc�l�re les r�solution d'adresses
#define HTS_DNSCACHE 1

// ID d'une pseudo-socket locale pour les file://
#define LOCAL_SOCKET_ID -500000

// taille de chaque buffer (10 sockets 650 ko)
#if HTS_SPARE_MEMORY==0
#define TAILLE_BUFFER 65536
#else
#define TAILLE_BUFFER 8192
#endif

#if HTS_WIN
#else
// use pthreads.h

#ifndef THREADS
#define HTS_DO_NOT_USE_PTHREAD
#endif

#ifdef HTS_DO_NOT_USE_PTHREAD
#define USE_PTHREAD 0
#else
#define USE_PTHREAD 1
#endif
#endif

#if HTS_WIN
#define USE_BEGINTHREAD 1
#else
#if USE_PTHREAD
#define USE_BEGINTHREAD 1
#else
/* sh*t.. */
#define USE_BEGINTHREAD 0
#endif
#endif

#ifdef _DEBUG
// trace mallocs
//#define HTS_TRACE_MALLOC
#ifdef HTS_TRACE_MALLOC
typedef unsigned long int t_htsboundary;
typedef struct mlink {
  char* adr;
  int len;
  int id;
  struct mlink* next;
} mlink;
static const t_htsboundary htsboundary = 0xDEADBEEF;
#endif
#endif

/* strxxx debugging */
#ifndef NOSTRDEBUG
#define STRDEBUG 1
#endif


/* ------------------------------------------------------------ */
/* Debugging                                                    */
/* ------------------------------------------------------------ */

// d�buggage types
#define DEBUG_SHOWTYPES 0
// backing debug
#define BDEBUG 0
// chunk receive
#define CHUNKDEBUG 0
// realloc links debug
#define MDEBUG 0
// cache debug
#define DEBUGCA 0
// DNS debug
#define DEBUGDNS 0
// savename debug
#define DEBUG_SAVENAME 0
// debug robots
#define DEBUG_ROBOTS 0
// debug hash
#define DEBUG_HASH 0
// V�rification d'int�grit�
#define DEBUG_CHECKINT 0
// nbr sockets debug
#define NSDEBUG 0

// d�buggage HTSLib
#define HDEBUG 0
// surveillance de la connexion
#define CNXDEBUG 0
// debuggage cookies
#define DEBUG_COOK 0
// d�buggage hard..
#define HTS_WIDE_DEBUG 0
// debuggage deletehttp et cie
#define HTS_DEBUG_CLOSESOCK 0
// debug tracage m�moire
#define MEMDEBUG 0

// htsmain
#define DEBUG_STEPS 0


// D�buggage de contr�le
#if HTS_DEBUG_CLOSESOCK
#define _HTS_WIDE 1
#endif
#if HTS_WIDE_DEBUG
#define _HTS_WIDE 1
#endif
#if _HTS_WIDE
extern FILE* DEBUG_fp;
#define DEBUG_W(A)  { if (DEBUG_fp==NULL) DEBUG_fp=fopen("bug.out","wb"); fprintf(DEBUG_fp,":>"A); fflush(DEBUG_fp); }
#undef _
#define _ ,
#endif



#endif

