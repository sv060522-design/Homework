#include <stdio.h>
#include <string.h>
void used_chars(const char* str, char* used)
{
    int count[26] = {0};
    for(const char* p = str; *p; p++)
    {
        char c = *p;
        if(c >= 'A' && c <= 'Z')
            c = c - 'A' + 'a';
        
        if(c >= 'a' && c <= 'z')
            count[c - 'a'] = 1;
    }
    int pos = 0;
    for(int i = 0; i < 26; i++)
    {
        if(count[i])
            used[pos++] = 'a' + i;
    }
    used[pos] = '\0';
}
int main()
{
    char s[50] = "Sapere Aude";
    char u[30];
    used_chars(s, u);
    printf("%s\n", u);
    strcpy(s, "1231$@");
    used_chars(s, u);
    printf("%s\n", u);
    strcpy(s, "The Quick Brown Fox Jumps Over The Lazy Dog!");
    used_chars(s, u);
    printf("%s\n", u);
    return 0;
}