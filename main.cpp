// Winter'24
// Instructor: Diba Mirza
// Student name: 
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <cstring>
#include <algorithm>
#include <limits.h>
#include <iomanip>
#include <set>
#include <queue>
#include <sstream>
using namespace std;

#include "utilities.h"
#include "movies.h"

bool parseLine(string &line, string &movieName, double &movieRating);

int main(int argc, char** argv){
    if (argc < 2){
        cerr << "Not enough arguments provided (need at least 1 argument)." << endl;
        cerr << "Usage: " << argv[ 0 ] << " moviesFilename prefixFilename " << endl;
        exit(1);
    }

    ifstream movieFile (argv[1]);
 
    if (movieFile.fail()){
        cerr << "Could not open file " << argv[1];
        exit(1);
    }
  
    // Create an object of a STL data-structure to store all the movies
    MovieCollection collection;
    string line, movieName;
    double movieRating;
    // Read each file and store the name and rating
    while (getline (movieFile, line) && parseLine(line, movieName, movieRating)){
            // Use std::string movieName and double movieRating
            // to construct your Movie objects
            // cout << movieName << " has rating " << movieRating << endl;
            // insert elements into your data structure
            collection.insert(movieName, movieRating);
    }

    movieFile.close();

    if (argc == 2){
            //print all the movies in ascending alphabetical order of movie names
            collection.printAlphabetical();
            return 0;
    }

    ifstream prefixFile (argv[2]);

    if (prefixFile.fail()) {
        cerr << "Could not open file " << argv[2];
        exit(1);
    }

    vector<string> prefixes;
    while (getline (prefixFile, line)) {
        if (!line.empty()) {
            prefixes.push_back(line);
        }
    }
    prefixFile.close();
    //  For each prefix,
    //  Find all movies that have that prefix and store them in an appropriate data structure
    //  If no movie with that prefix exists print the following message
    struct PrefixResult {
        string prefix;
        string bestName;
        double bestRating;
        bool found;
    };

    vector<PrefixResult> bestMovies;

    for (const string& prefix : prefixes) {
        vector<Movie> matches = collection.findByPrefix(prefix);
        if (matches.empty()) {
                cout << "No movies found with prefix "<< prefix << endl;
                PrefixResult r;
                r.prefix = prefix;
                r.found = false;
                bestMovies.push_back(r);
        } else {
            for (const Movie & m : matches) {
                cout << m.name << ", " << fixed << setprecision(1) << m.rating << endl;
            }
            cout << endl;
            PrefixResult r;
            r.prefix = prefix;
            r.bestName = matches[0].name;
            r.bestRating = matches[0].rating;
            r.found = true;
            bestMovies.push_back(r);
        }
    }

    //  For each prefix,
    //  Print the highest rated movie with that prefix if it exists.
    for (int i = 0; i < (int)bestMovies.size(); i++){
        if (bestMovies[i].found) {
                cout << "Best movie with prefix " << bestMovies[i].prefix << " is: " <<
                 bestMovies[i].bestName << " with rating " << std::fixed << std::setprecision(1) << 
                 bestMovies[i].bestRating << endl;

        }
    }

    return 0;
}

/* Add your run time analysis for part 3 of the assignment here as commented block*/
/* 

3a: Time Complexity
==============================================================================================================
4 parameters, n = movies, m = prefixes, k = max # of movie matching prefix, l = max # of characters
data structure = std::map<string, double>
    bst on movie name, string comparisons = O(1)
    
per prefix:
    1. lower_bound(prefix) = O(l * log n)
    2. move forward collecting matches = O(kl)
    3. sort k (results) = O(k log k)

per m prefixes = O(ml(logn + klogk))
dominant term when k is small = O(ml * logn)

runtime analysis:


3b: Space Complexity
===============================================================================================================
map = O(nl)
allocation of vector per prefix = O(kl)
freed after prefx = O(kl)
bestMovies vector = O(ml)

additional space = O(ml + kl) = O((m + k) * l)
actual space = O(nl) for map, O((m + k) * l) for auxiliary

3c: Tradeoffs
===============================================================================================================
want low time complexity, so std::map allows for fast prefix search with lower_bound
a linear scan is O(nl) vs O(l log n)

space complexity is okay since O(nl) is for the map and is unavoidable
since we need to store all names

low time and space complexity was achieved. It was harder to do the time complexity because the 
sort per prefix O(K log k) can change if all/a lot of movies hsave the same prefix

*/


bool parseLine(string &line, string &movieName, double &movieRating) {
    int commaIndex = line.find_last_of(",");
    movieName = line.substr(0, commaIndex);
    movieRating = stod(line.substr(commaIndex+1));
    if (movieName[0] == '\"') {
        movieName = movieName.substr(1, movieName.length() - 2);
    }
    return true;
}