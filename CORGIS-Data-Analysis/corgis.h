#define _GNU_SOURCE
#define NUM_ARGS 3
#define SIZE 7

#define ENT_NUM 52
#define COUNTY 0
#define STATE 1
#define UNI 5
#define HS 6
#define AIAN 11
#define ASIAN 12
#define BLACK 13
#define HISP 14
#define NHOPI 15
#define BIRAC 16
#define WHITE 17
#define WNOTHL 18
#define MEDINC 25
#define PERCAP 26
#define INCPOV 27
#define POP2014 38

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h> 
#include <fcntl.h>
#include <stdint.h>
#include <math.h>
#include <sys/stat.h>

typedef struct arraylist arraylist;

struct arraylist{
    int capacity;
    int numitems;
    char ** data ;
};

typedef struct info info;

struct info{
    char *county;
    char *state;
    float ed_uni;
    float ed_hs;
    float eth_aian;
    float eth_asian;
    float eth_black;
    float eth_hisp;
    float eth_nhopi;
    float eth_bir;
    float eth_white;
    float eth_wnothl;
    int med_inc;
    int inc_percap;
    float inc_pov;
    int pop_2014;
};
