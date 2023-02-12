#include "streamcorr.h"
#include "cstring"
using namespace std;

bool author_messages = false;

/* Wrapper for author message printing so that they are only printed in
 * case the author_messages option was given.  If the validator should
 * always print author messages, you can just call
 * report_feedback(authormessage, ...) directly.
 */
void author_message(const char *s) {
    if (author_messages) {
        report_feedback(authormessage, s);
    }
}

/* Check one test case.  Returns false if there were no more test
 * cases to check. */
bool check_case() {
    long long D, n1, n2;
    judge_in >> D;
    if (D%4 == 2) {
        string s;
        author_out >> s;
        if (s != string("impossible"))
            report_error("Should be impossible");
    } else {
        if (!(author_out >> n1 >> n2))
            report_error("Wrong output format");
        if (n1 < 0 || n1 > D || n2 < 0 || n2 > D)
            report_error("Bad output");
        if (n2 * n2 - n1 * n1 != D)
            report_error("Bad output");
    }
    return true;
}

int main(int argc, char **argv) {
    init_io(argc, argv);
    /* Check if the author_messages option is given. */
    for (int i = 4; i < argc; ++i)
        if (!strcmp(argv[i], "author_messages"))
            author_messages = true;

    check_case();

    /* Check for trailing output in author file. */
    string trash;
    if (author_out >> trash) {
        author_message("Trailing output after last test case");
        report_error("Trailing output");
    }

    /* Yay! */
    author_message("Thank you for your great code. It was fantastic.");
    accept();
}
