#include <algorithm>
#include <cassert>
#include <cstdarg>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using namespace std;

const int EXIT_AC = 42;
const int EXIT_WA = 43;

typedef vector<int> vi;
typedef void (*error_fun)(const char *, ...);

ifstream judgein, judgeans;
FILE *judgemessage = NULL;
int kase, verdict = EXIT_AC;

void wrong_answer(const char *err, ...) {
	va_list pvar;
	va_start(pvar, err);
	vfprintf(judgemessage, err, pvar);
	fprintf(judgemessage, "\n");
	exit(EXIT_WA);
}

void judge_error(const char *err, ...) {
	va_list pvar;
	va_start(pvar, err);
	// if judgemessage has not been set up yet, write error to stderr
	if (!judgemessage) judgemessage = stderr;
	vfprintf(judgemessage, err, pvar);
	fprintf(judgemessage, "\n");
	assert(!"Judge Error");
}

template <typename Stream>
void openfile(Stream &stream, const char *file, const char *whoami) {
	stream.open(file);
	if (stream.fail())
		judge_error("%s: failed to open %s\n", whoami, file);
}

FILE *openfeedback(const char *feedbackdir, const char *feedback, const char *whoami) {
	int len = strlen(feedbackdir) + strlen(feedback) + 1000;
	char path[len];
	sprintf(path, "%s%s", feedbackdir, feedback);
	FILE *res = fopen(path, "w");
	if (!res)
		judge_error("%s: failed to open %s for writing", whoami, path);
	return res;
}

void get_sol(istream &in, set<string> &res, error_fun error) {
	string topping;
	while (in >> topping) {
		if (topping.length() > 15)
			error("Topping of length > 15");
		if (res.find(topping) != res.end())
			error("Repeated topping '%s'", topping.c_str());
		res.insert(topping);
		if (res.size() > 250)
			error("More than 250 toppings");
	}
}

void check_case() {
	set<string> input;
	set<string> output;
	set<string> answer;

	get_sol(cin, output, wrong_answer);
	get_sol(judgeans, answer, judge_error);
	
	int friends;
	judgein >> friends;
	for (int i = 1; i <= friends; ++i) {
		int wishes, out_sat = 0, ans_sat = 0;
		judgein >> wishes;
		for (int j = 0; j < wishes; ++j) {
			string wish;
			judgein >> wish;
			bool wanted = (wish[0] == '+');
			wish = wish.substr(1);
			input.insert(wish);
			if ((output.find(wish) == output.end()) ^ wanted)
				++out_sat;
			if ((answer.find(wish) == answer.end()) ^ wanted)
				++ans_sat;
		}
		if (3*out_sat <= wishes)
			wrong_answer("Friend %d/%d only has %d of %d wishes satisfied",	
					 i, friends, out_sat, wishes);
		if (3*ans_sat < 2*wishes)
			judge_error("Friend %d/%d only has %d of %d wishes satisfied in answer file",
						 i, friends, ans_sat, wishes);
	}
	set<string> diff;
	set_difference(output.begin(), output.end(),
				   input.begin(), input.end(),
				   std::inserter(diff, diff.begin()));
	if (!diff.empty()) {
		wrong_answer("Output has topping '%s' which does not appear in input\n",
					 diff.begin()->c_str());
	}
}

const char *USAGE = "Usage: %s judge_in judge_ans feedback_dir [options] < team_out";

int main(int argc, char **argv) {
	if(argc < 4)
		judge_error(USAGE, argv[0]);
	judgemessage = openfeedback(argv[3], "judgemessage.txt", argv[0]);
	openfile(judgein, argv[1], argv[0]);
	openfile(judgeans, argv[2], argv[0]);

	check_case();

	string buf;
	if (cin >> buf) {
		wrong_answer("Trailing output");
	}
   
	exit(verdict);
}
