#include <iostream>
#include <vector>

template <class F> class scoped_finalizer {
    F f;
public:
    scoped_finalizer(const scoped_finalizer&) = delete;
    scoped_finalizer& operator=
        (const scoped_finalizer&) = delete;
    scoped_finalizer(F f) : f{ f } {
    }
    ~scoped_finalizer() {
        f();
    }
};

#include <cstdio>

FILE file_;

FILE * open_file(const char *) {
    std::cout << "Call to open\n";
    return &file_;
}
void close_file(FILE *) {
    std::cout << "Call to close\n";
}

int read_from(FILE *, char *, int ) {
    return 0;
}

void process(const std::vector<char> &) {
}

enum { N = 2048 }

void f(const char *name) {
    FILE *file = open_file(name);
    if(!file) return; // failure
    auto sf = scoped_finalizer{ [&file] {
        close_file(file);
    } };
    std::vector<char> v;
    char buf[N];
    for(int n = read_from(file, buf, N); n != 0;
        n = read_from(file, buf, N))
       v.insert(end(V), buf + 0, buf + n);
    process(v);
} // implicit close_file(file) through sf's destructor

int main() {
    f("test.txt");
}