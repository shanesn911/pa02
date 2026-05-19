#include "movies.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

void MovieCollection::insert(const std::string& name, double rating) {
    movies_[name] = rating;
}

void MovieCollection::printAlphabetical() const {
    for (const auto& [name, rating] : movies_) {
        std::cout << name << ", " << std::fixed << std::setprecision(1) << rating << "\n";
    }
}

std::vector<Movie> MovieCollection::findByPrefix(const std::string& prefix) const {
    std::vector<Movie> results;

    auto it = movies_.lower_bound(prefix);

    while (it != movies_.end()) {
        const std::string& name = it->first;
        if (name.size() < prefix.size() || name.substr(0, prefix.size()) != prefix) {
            break;
        }
        results.push_back(Movie(name, it->second));
        ++it;
    }

    std::sort(results.begin(), results.end(), MovieComparator{});
    return results;
}