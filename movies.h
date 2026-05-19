#ifndef MOVIES_H
#define MOVIES_H
 
#include <string>
#include <vector>
#include <map>

struct Movie {
    std::string name;
    double rating;

    Movie(const std::string& n, double r) : name(n), rating(r) {}

};

struct MovieComparator {
    bool operator()(const Movie& a, const Movie& b) const {
        if (a.rating != b.rating) return a.rating > b.rating;
        return a.name < b.name;
    }
};

class MovieCollection {
public:
    void insert(const std:: string& name, double rating);
    void printAlphabetical() const;
    std::vector<Movie> findByPrefix(const std::string& prefix) const;
private:
    std::map<std::string, double> movies_;
};

#endif