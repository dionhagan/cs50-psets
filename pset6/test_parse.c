#include <arpa/inet.h>
#include <dirent.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <ctype.h> 

#define LimitRequestLine 8190

bool parse(const char* line, char* abs_path, char* query);

const char* line = "GET /hello.php?q=Alice HTTP/1.1\r\n";
char abs_path[LimitRequestLine + 1];
char query[LimitRequestLine + 1];

int main ()
{
   return parse(line, abs_path, query);
}

/**
 * Parses a request-line, storing its absolute-path at abs_path 
 * and its query string at query, both of which are assumed
 * to be at least of length LimitRequestLine + 1.
 */
bool parse(const char* line, char* abs_path, char* query)
{
    // PART 1: Validation
    char* begin = strchr(line, ' ') + 1;
    printf("begin:%s", begin);
    char* end = strrchr(line, ' ') + 1;
    printf("end:%s", end);
    
    // calculate size of request target via length of string after first space
    // and length of string after second space ( -1 to get rid of 2nd space)
    int beginsize = strlen(begin);
    int endsize = strlen(end);
    size_t rtsize = beginsize - endsize;
 
    //copy in the first rtsize chars in begin
    char* rtarget = malloc(rtsize * sizeof(char));
    if (rtarget == NULL)
    {
        printf("Malloc Failed!");
        return false;
    }
    strncpy(rtarget, begin, rtsize);
    printf("request-target:%s\n", rtarget);
    
    // test whether or not 3rd space exists
    if (strchr(end, ' ') != NULL)
    {
        free(rtarget);
        printf("1-400 Bad Request\n");
        return false;
    }
    
    // check if ends with "\r\n"
    char* crlf = strstr(line, "\r\n");
    char* endline = crlf + 4;
    if (crlf == NULL && (strcmp(endline, "\0") != 0))
    {
        free(rtarget);
        printf("2-400 Bad Request\n");
        return false;
    }
    
    // check if more than 1 ? in request-target
    char* qtest = strchr(rtarget, '?') + 1;
    if (qtest == NULL)
    {
        qtest="";
        printf("qtest:%s\n", qtest);
    }
    else
    {
        if (strchr(qtest, '?') != NULL)
        {
            free(rtarget);
            printf("3-400 Bad Request\n");
            return false;
        }
        printf("qtest:%s\n", qtest);
    }
    
    //check method == "GET"
    if (line[0] != 'G' || line[1] != 'E' || line[2] != 'T')
    {
        free(rtarget);
        printf("405 Method Not Allowed\n");
        return false;
    }
    
    // check request-target begins with '/'
    if (begin[0] != '/')
    {
        free(rtarget);
        printf("501 Not Implemented\n");
        return false;
    }
    
    // check if there is a " after the first space, but not after second
    if (strchr(rtarget, '\"') != NULL)
    {
        free(rtarget);
        printf("4-400 Bad Request\n");
        return false;
    }
    
    // check HTTP-version
    if (strcmp(end, "HTTP/1.1\r\n") != 0)
    {
        free(rtarget);
        printf("505 HTTP Version Not Supported");
        return false;
    }
    
    
    // PART2: separate absolute path and query
    query = strrchr(rtarget, '?') + 1;
    
    // if no question mark found, set query to empty string
    if (query  == NULL)
    {
        query = "";
    }
    printf("query:%s", query);
    
    // calculate abs_path_size via query_size and rtsize
    int query_size = strlen(query);
    int abs_path_size = rtsize - query_size - 1;
    
    strncpy(abs_path, rtarget, abs_path_size);
    printf("abs_path:%s", abs_path);
    //free rtarget and return true if no problems
    free(rtarget);
    return true;
}