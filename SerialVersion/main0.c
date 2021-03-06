//#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "md5.h"
//#if defined(__APPLE__)
//#  define COMMON_DIGEST_FOR_OPENSSL
//#  include <CommonCrypto/CommonDigest.h>
//#  define SHA1 CC_SHA1
//#else
//#  include <openssl/md5.h>
//#endif

//void guess0(char *word, int n) ;
void guess(int n, uint v1, uint v2, uint v3, uint v4) ;

/*char* getMD5(char *argv) ;

char *str2md5(const char *str) ;*/

//using namespace std;

int main(int argc, char **argv) {
    char* word = argv[1];//, *wordMD5;
    int length = strlen(word);
    if(argc>0) {
        printf("word\t=\t\"%s\"\n", word);
        //wordMD5 = getMD5(word);
       // printf("wordMD5\t=\t\"%s\"\n", wordMD5);

        //char* inputString = (char*) malloc(sizeof(char) * length);
        //strcpy(inputString, word);
        uint v1,v2,v3,v4;
        md5_vfy((unsigned char*)word, length, &v1, &v2, &v3, &v4);
        printf("hash for %s: %#x%x%x%x\n", word, v1,v2,v3,v4);


        uint c1 = 0, c2 = 0, c3 = 0, c4 = 0;
        //get the md5 hash of the word
        md5_vfy((unsigned char*)word,length, &c1, &c2, &c3, &c4);


        long t0 = clock();
        guess(length, v1, v2, v3, v4); //word and wordHash have different length
        long t1 = clock();

        float dt = (t1-t0)/1000000.0;
        printf("%lf sec\n", dt);
        //free(wordMD5);
        //wordMD5 = NULL;
    }
    return 0;
}


/*char *str2md5(const char *str) {
    int n, length = (int)strlen(str);
    MD5_CTX c;
    unsigned char digest[16];
    char *out = (char*)malloc(33);

    MD5_Init(&c);

    while (length > 0) {
        if (length > 512) {
            MD5_Update(&c, str, 512);
        } else {
            MD5_Update(&c, str, length);
        }
        length -= 512;
        str += 512;
    }
    
        MD5_Final(digest, &c);

    for (n = 0; n < 16; ++n) {
        snprintf(&(out[n*2]), 16*2, "%02x", (unsigned int)digest[n]);
    }

    return out;
}

char* getMD5(char *word) {
    char *output = str2md5(word);
//    printf("%s\n", output);
//    char MD5word[strlen(output)];
//    strcpy(MD5word, output);
//    free(output);
    return output;
}*/


void guess(int n, uint v1, uint v2, uint v3, uint v4) {
    char cur[n+1];
    //char* curMD5;
    int counter[n];
    int i, nr_values = 94;
    // initialize
    for (i = 0; i < n; i++) {
        counter[i] = 0;
        cur[i]=' ';
    }

    do {
        for (i = 0; i < n; i++) {
            cur[i] = (char)(counter[i]+32);
            cur[i+1] = '\0';
        }
        uint c1 = 0, c2 = 0, c3 = 0, c4 = 0;
        //get the md5 hash of the word
        md5_vfy((unsigned char*)cur, n, &c1, &c2, &c3, &c4);

        //compare hash with correct hash
        if(c1 == v1 && c2 == v2 && c3 == v3 && c4 == v4)
            printf("found hash for %s: %#x%x%x%x\n", cur, v1,v2,v3,v4);
        //free(curMD5);
        //curMD5 = NULL;
        // increment till the values overflow, starting from the last index
        i = n - 1;
        while (i >= 0) {
            counter[i]++;
            if (counter[i] < nr_values) {
                break;
            }
            counter[i] = 0;
            i--;
        }
        // quit when first index overflows
    } while (i >= 0);
    //free(curMD5);
    //curMD5 = NULL;
}




/*void guess0(char *wordMD5, int n) {
    char cur[n+1];
    char* curMD5;
    int counter[n];
    int i, nr_values = 94;
    // initialize
    for (i = 0; i < n; i++) {
        counter[i] = 0;
        cur[i]=' ';
    }

    do {
        for (i = 0; i < n; i++) {
            cur[i] = (char)(counter[i]+32);
            cur[i+1] = '\0';
        }
        curMD5 = getMD5(cur);
        //printf("cur=\"%s\"\n", cur);
        //printf("\ncur =\t\"%s\"\ncurHash =\t\"%s\"\nword =\t\"%s\"\n", cur, word);
        if(strcmp(curMD5, wordMD5)==0) {
            printf("FOUND\ncur\t=\t\"%s\"\ncurMD5\t=\t\"%s\"\n", cur, curMD5);
            break;
        }
        free(curMD5);
        curMD5 = NULL;
        // increment till the values overflow, starting from the last index
        i = n - 1;
        while (i >= 0) {
            counter[i]++;
            if (counter[i] < nr_values) {
                break;
            }
            counter[i] = 0;
            i--;
        }
        // quit when first index overflows
    } while (i >= 0);
    free(curMD5);
    curMD5 = NULL;
}*/
