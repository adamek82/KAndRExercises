#include <stdio.h>

void escape(char s[], char t[]);
void unescape(char s[], char t[]);
int string_equal(char s[], char t[]);

int main(void)
{
    char escaped[1000];
    char unescaped[1000];

    escape(escaped, "hello\nworld\t!");
    printf("escape 1: %s\n", escaped);

    escape(escaped, "path\\file");
    printf("escape 2: %s\n", escaped);

    escape(escaped, "plain text");
    printf("escape 3: %s\n", escaped);

    unescape(unescaped, "hello\\nworld\\t!");
    escape(escaped, unescaped);
    printf("unescape 1, escaped again: %s\n", escaped);

    unescape(unescaped, "path\\\\file");
    escape(escaped, unescaped);
    printf("unescape 2, escaped again: %s\n", escaped);

    unescape(unescaped, "unknown\\qescape");
    escape(escaped, unescaped);
    printf("unescape 3, escaped again: %s\n", escaped);

    unescape(unescaped, "trailing\\");
    escape(escaped, unescaped);
    printf("unescape 4, escaped again: %s\n", escaped);

    if (!string_equal(escaped, "trailing\\\\")) {
        return 1;
    }

    return 0;
}

/*
 * Copy t to s, replacing selected real characters by visible escape sequences.
 *
 * This is intentionally not a full C string-literal or printf-style escape
 * translator. For this exercise we handle only newline, tab and backslash:
 *
 *     newline    -> \n
 *     tab        -> \t
 *     backslash  -> \\
 *
 * Escaping backslash matters because otherwise the transformation would not be
 * safely reversible. For example, a real two-character string containing
 * backslash followed by n would look like the escape sequence \n after escaping.
 */
void escape(char s[], char t[])
{
    int i, j;

    for (i = 0, j = 0; t[i] != '\0'; ++i) {
        switch (t[i]) {
        case '\n':
            s[j] = '\\';
            ++j;
            s[j] = 'n';
            ++j;
            break;

        case '\t':
            s[j] = '\\';
            ++j;
            s[j] = 't';
            ++j;
            break;

        case '\\':
            s[j] = '\\';
            ++j;
            s[j] = '\\';
            ++j;
            break;

        default:
            s[j] = t[i];
            ++j;
            break;
        }
    }

    s[j] = '\0';
}

/*
 * Copy t to s, replacing visible escape sequences by real characters.
 *
 * Recognized sequences are \n, \t and \\. Unknown sequences are preserved
 * literally, including the backslash. A trailing backslash is also preserved.
 */
void unescape(char s[], char t[])
{
    int i = 0, j = 0;

    while (t[i] != '\0') {
        if (t[i] == '\\') {
            ++i;

            switch (t[i]) {
            case 'n':
                s[j] = '\n';
                ++j;
                break;

            case 't':
                s[j] = '\t';
                ++j;
                break;

            case '\\':
                s[j] = '\\';
                ++j;
                break;

            case '\0':
                s[j] = '\\';
                ++j;
                s[j] = '\0';
                return;

            default:
                s[j] = '\\';
                ++j;
                s[j] = t[i];
                ++j;
                break;
            }
        } else {
            s[j] = t[i];
            ++j;
        }

        ++i;
    }

    s[j] = '\0';
}

int string_equal(char s[], char t[])
{
    int i;

    for (i = 0; s[i] == t[i]; ++i) {
        if (s[i] == '\0') {
            return 1;
        }
    }

    return 0;
}
