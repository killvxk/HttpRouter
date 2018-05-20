#include "HttpRouter.hpp"

#include <iostream>
#include <chrono>

void benchmark_routes() {
    struct UserData {
        int routed = 0;
    } userData;

    HttpRouter<UserData *> r;

    // set up a few routes
    r.add("GET", "/service/candy/:kind", [](UserData *user, auto &args) {
        user->routed++;
    });

    r.add("GET", "/service/shutdown", [](UserData *user, auto &args) {
        user->routed++;
    });

    r.add("GET", "/", [](UserData *user, auto &args) {
        user->routed++;
    });

    r.add("GET", "/:filename", [](UserData *user, auto &args) {
        user->routed++;
    });

    // run benchmark of various urls
    std::vector<std::string> test_urls = {
        "/service/candy/lollipop",
        "/service/candy/gum",
        "/service/candy/seg_råtta",
        "/service/candy/lakrits",

        "/service/shutdown",
        "/",
        "/some_file.html",
        "/another_file.jpeg"
    };

    for (std::string &test_url : test_urls) {
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000000; i++) {
            r.route("GET", 3, test_url.data(), test_url.length(), &userData);
        }
        auto stop = std::chrono::high_resolution_clock::now();
        unsigned int ms = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
        std::cout << "[" << int(10000.0 / ms) << " million req/sec] for URL: " << test_url << std::endl;
    }

    std::cout << "Checksum: " << userData.routed << std::endl << std::endl;
}

void demo_routes() {
    struct UserData {
        // pass whatever you need as user data
    } userData;

    HttpRouter<UserData *> r;

    // set up a few routes
    r.add("GET", "/service/candy/:kind", [](UserData *user, auto &args) {
        std::cout << "Now serving candy of kind " << args[0] << std::endl;
    });

    r.add("GET", "/service/shutdown", [](UserData *user, auto &args) {
        std::cout << "Shutting down now" << std::endl;
    });

    r.add("GET", "/", [](UserData *user, auto &args) {
        std::cout << "Serving index now" << std::endl;
    });

    r.add("GET", "/:filename", [](UserData *user, auto &args) {
        std::cout << "Serving file: " << args[0] << std::endl;
    });

    // run benchmark of various urls
    std::vector<std::string> test_urls = {
        "/service/candy/lollipop",
        "/service/candy/gum",
        "/service/candy/seg_råtta",
        "/service/candy/lakrits",

        "/service/shutdown",
        "/",
        "/some_file.html",
        "/another_file.jpeg"
    };

    for (std::string &test_url : test_urls) {
        std::cout << "[" << test_url << "]" << std::endl;
        r.route("GET", 3, test_url.data(), test_url.length(), &userData);
    }
}

int main() {
    benchmark_routes();
    demo_routes();
}
