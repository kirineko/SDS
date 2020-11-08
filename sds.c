#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sds
{
    int len;
    int free;
    char buf[];
} sds;


sds* sdsnew(const char *init)
{
    int length = sizeof(sds) + strlen(init) + 1;
    sds* str = (sds*)malloc(length);
    str->len = strlen(init);
    str->free = 0;
    memcpy(str->buf, init, str->len);
    str->buf[str->len] = '\0';
    return str;
}

int sdslen(sds* str)
{
    return str->len;
}

sds* sdscat(sds* str1, const char* str2)
{
    if (str1->free >= strlen(str2)) {
        memcpy(str1->buf + sdslen(str1), str2, strlen(str2));
        str1->buf[sdslen(str1) + strlen(str2)] = '\0';
        str1->len += strlen(str2);
        str1->free -= strlen(str2);
        return str1;
    } else {
        int old_len = sdslen(str1);
        int new_len = old_len + strlen(str2);
        int new_mem = sizeof(sds) + new_len * 2 + 1;
        sds* new_str1 = realloc(str1, new_mem);

        new_str1->len = new_len;
        new_str1->free = new_len;
        memcpy(new_str1->buf + old_len, str2, strlen(str2));
        new_str1->buf[old_len + strlen(str2)] = '\0';
        return new_str1;
    }
}

sds* sdstrim(sds* str, const char* cset)
{
    char *start, *end, *sp, *ep;

    start = sp = str->buf;
    end = ep = str->buf + sdslen(str) - 1;

    while (sp <= end && strchr(cset, *sp)) sp++;
    while (ep > start && strchr(cset, *ep)) ep--;

    int len = (sp > ep) ? 0 : (ep - sp + 1);
    if (str->buf != sp) memmove(str->buf, sp, len);
    str->buf[len] = '\0';

    str->free = str->free+(str->len-len);
    str->len = len;
    return str;
}

int sdscmp(sds* s1, sds* s2) {
    size_t l1, l2, minlen;
    int cmp;

    l1 = sdslen(s1);
    l2 = sdslen(s2);
    minlen = (l1 < l2) ? l1 : l2;
    cmp = memcmp(s1->buf,s2->buf,minlen);
    if (cmp == 0) return l1-l2;
    return cmp;
}

int main()
{
    sds* str = sdsnew("hello redis");
    printf("%d\n", sdslen(str));
    printf("%d\n", str->free);
    printf("%s\n", str->buf);
    
    sds* new_str = sdscat(str, " design and implement");
    printf("%d\n", sdslen(new_str));
    printf("%d\n", new_str->free);
    printf("%s\n", new_str->buf);

    sds* str_trim = sdstrim(new_str, "ht");
    printf("%d\n", sdslen(new_str));
    printf("%d\n", new_str->free);
    printf("%s\n", new_str->buf);


    sds* str1 = sdsnew("hello redis");
    sds* str2 = sdsnew("hello world");
    printf("%d\n", sdscmp(str1, str2));

    return 0;
}
