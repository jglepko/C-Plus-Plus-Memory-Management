#include <iostream>
#include <vector>
#include <cstdio>

File file_; // dummy

FILE * open_file(const char *) {
    std::cout << "Call to open\n";
    return &file_;
}
void close_file(FILE *) {
    std::cout << "Call to close\n";
}

class FileCloser {
    FILE * file;
public:
    FileCloser(FILE *file) : file{ file } {
    }
    ~FileCloser() {
        close_file(file);
    }
};

int read_file(FILE *, char *, int) {
    return 0;
}

void process(const std::vector<char> &) {
}

enum { N = 2048 };

void f(const char *name) {
    FILE *file = open_file(name);
    if(!file) return;
    FileCloser fc{ file };
    std::vector<char> v;
    char buf[N];
    for(int n = read_from(file, buf, N); n != 0;
        n = read_from(file, buf, N))
        v.insert(end(v), buf + 0, buf + n);
    process(v);
}

int main() {
    f("test.txt");
}