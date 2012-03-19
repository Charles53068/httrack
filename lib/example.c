/*
    HTTrack library example
    .c file

    To Build on Windows:
    - compile everything in src/ BUT htsparse.c, compile example.c
    - multithreaded
    - avoid precompiled headers with VC

    To Build on Linux:
    make lib_linux (or "make lib_netbsd", or "make lib_default" and so on)
    cp htssystem.h src/htssystem.h
    make build_httracklib
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "src/httrack-library.h"

#include "example.h"



/*
 * Name:           main
 * Description:    main() function
 * Parameters:     None
 * Should return:  error status
*/
int main(void) {
  /* 
     First, ask for an URL 
     Note: For the test, option r2 (mirror max depth=1) and --testscan (no index, no cache, do not store, no log files)
  */
  char _argv[][256] = {"httrack_test" , "<URL>" , "-r3" , "--testscan" , ""  };
  char* argv[]      = {NULL           , NULL    , NULL  , NULL        , NULL};
  int         argc = 0;
  while(strlen(_argv[argc])) {
    argv[argc]=_argv[argc];
    argc++;
  }
  argv[argc]=NULL;
  printf("HTTrackLib test program\n");
  printf("Enter URL (example: www.foobar.com/index.html) :");
  scanf("%s",argv[1]);
  printf("Test: 1 depth\n");

  hts_init();
  htswrap_add("init",httrack_wrapper_init);
  htswrap_add("free",httrack_wrapper_uninit);
  htswrap_add("start",httrack_wrapper_start);
  htswrap_add("change-options",httrack_wrapper_chopt);
  htswrap_add("end",httrack_wrapper_end);
  htswrap_add("check-html",httrack_wrapper_checkhtml);
  htswrap_add("loop",httrack_wrapper_loop);
  htswrap_add("query",httrack_wrapper_query);
  htswrap_add("query2",httrack_wrapper_query2);
  htswrap_add("query3",httrack_wrapper_query3);
  htswrap_add("check-link",httrack_wrapper_check);
  htswrap_add("pause",httrack_wrapper_pause);
  htswrap_add("save-file",httrack_wrapper_filesave);
  htswrap_add("link-detected",httrack_wrapper_linkdetected);
  htswrap_add("transfer-status",httrack_wrapper_xfrstatus);
  htswrap_add("save-name",httrack_wrapper_savename);

  /* Then, launch the mirror */
  hts_main(argc,argv);

  /* Wait for a key */
  printf("\nPress ENTER key to exit\n");
  scanf("%s",argv[1]);

  /* That's all! */
  return 0;
}


/* CALLBACK FUNCTIONS */

/* Initialize the Winsock */
void __cdecl httrack_wrapper_init(void) {
  printf("Engine started\n");
#ifdef _WIN32
  {
    WORD   wVersionRequested;   // requested version WinSock API
    WSADATA wsadata;            // Windows Sockets API data
    int stat;
    wVersionRequested = 0x0101;
    stat = WSAStartup( wVersionRequested, &wsadata );
    if (stat != 0) {
      printf("Winsock not found!\n");
      return;
    } else if (LOBYTE(wsadata.wVersion) != 1  && HIBYTE(wsadata.wVersion) != 1) {
      printf("WINSOCK.DLL does not support version 1.1\n");
      WSACleanup();
      return;
    }
  }
#endif

}
void __cdecl httrack_wrapper_uninit(void) {
  printf("Engine exited\n");
#ifdef _WIN32
  WSACleanup();
#endif
}
int __cdecl httrack_wrapper_start(httrackp* opt) {
  printf("Start of mirror\n");
  return 1; 
}
int __cdecl httrack_wrapper_chopt(httrackp* opt) {
  return __cdecl httrack_wrapper_start(opt);
}
int  __cdecl httrack_wrapper_end(void) { 
  printf("End of mirror\n");
  return 1; 
}
int __cdecl httrack_wrapper_checkhtml(char* html,int len,char* url_adresse,char* url_fichier) {
  printf("Parsing html file: http://%s%s\n",url_adresse,url_fichier);
  return 1;
}
int __cdecl httrack_wrapper_loop(void* _back,int back_max,int back_index,int lien_n,int lien_tot,int stat_time,hts_stat_struct* stats) {
  /* printf("..httrack_wrapper_loop called\n"); */
  return 1;
}
char* __cdecl httrack_wrapper_query(char* question) {
  return "N";
}
char* __cdecl httrack_wrapper_query2(char* question) {
  return "N";
}
char* __cdecl httrack_wrapper_query3(char* question) {
  return "";
}
int __cdecl httrack_wrapper_check(char* adr,char* fil,int status) {
  printf("Link status tested: http://%s%s\n",adr,fil);
  return -1;
}
void __cdecl httrack_wrapper_pause(char* lockfile) {
}
void __cdecl httrack_wrapper_filesave(char* file) {
}
void __cdecl httrack_wrapper_savename(char* adr_complete,char* fil_complete,char* referer_adr,char* referer_fil,char* save) {
/* strcpy(save, "foo.html"); */
}
int __cdecl httrack_wrapper_linkdetected(char* link) {
  printf("Link detected: %s\n",link);
  return 1;
}
int __cdecl httrack_wrapper_xfrstatus(void* back) {
  return 1;
}

