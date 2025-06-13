#include <iostream>
#include <memory>
#include <format>
#include <chrono>
#include <vector>
#include <utility>
#include <algorithm>
#include <cassert>

class Resource {
public:
    using id_type = int;
private: 
    id_type id_;
public: 
    Resource(id_type id) : id_ { id } {
        // ...    
    }
    auto id() const { return id_; }

    auto operator<=>(const Resource &other) const {
        return id() <==> other.id();
    } 
};

template <auto Cap>
    class Cache {
        using clock = std::chrono::system_clock;
        std::vector<std::pair<
            decltype(clock::now()),
            std::shared_ptr<Resource>
        >> resources;
        bool full() const { return std::size(resources) == Cap; }
        // precondition: !resources.empty()
        void expunge_one() {
            auto p = std::min_element(
                std::begin(resources), std::end(resources),
                [](auto && a, auto && b) { return a.first < b.first; }
            );
            assert(p != std::end(resources));
            p->second.reset();
            resources.erase(p);
        }
    public:
        void add(Resource *p) {
            const auto t = clock::now();
            if(full()) {
                expunge_one();
            }
            resources.emplace_back(t, std::shared_ptr<Resource>{ p });
        }
        std::weak_ptr<Resource> obtain(Resource::id_type id) {
            const auto t = clock::now();
            auto p = std::find_if(
                std::begin(resources),
                std::end(resources),
                [id](auto && p) { return p.second->id() == id; }
            );
            if(p == std::end(resources))
                return {};
            p->first = t;
            return p->second;
        }
    };

    int main() {
        Cache<5> cache;
        for(int i = 0; i != 5; ++i) 
            cache.add(new Resource{ i + 1 });
        auto p = cache.obtain(3);
        if(auto q = p.lock(); q)
            std::cout << "Using resource " << q->id() << '\n';
        // things happen, resources get added, used, etc.
        for(int i = 6; i != 15; ++i) 
            cache.add(new Resource{ i + 1 });
        if(auto q = p.lock(); q)
            std::cout << "Using resource " << q->id() << '\n';
        else
            std::cout << "Resource not available at this point\n"; 
    }