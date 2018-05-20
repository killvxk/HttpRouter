# HttpRouter
Simple & fast header-only C++17 router for any HTTP server. Routes about 20-90 million URLs a second.

* SIMD/zero-copy parsing
* No memory allocations
* Patterns with wildcards, parameters & optionals
* Cross-platform standard C++17

```c++
    struct UserData {
        // pass whatever you need as user data
    } userData;

    HttpRouter<UserData *> r;

    r.add("GET", "/service/candy/:kind", [](UserData *user, auto &args) {
        std::cout << "Now serving candy of kind " << args[0] << std::endl;
    });

    r.add("GET", "/service/shutdown", [](UserData *user, auto &args) {
        std::cout << "Shutting down now" << std::endl;
    });

    r.route("GET", 3, "/service/candy/lollipop", 23, &userData);
```

### Runtime dump
```
[28 million req/sec] for URL: /service/candy/lollipop
[32 million req/sec] for URL: /service/candy/gum
[32 million req/sec] for URL: /service/candy/seg_råtta
[30 million req/sec] for URL: /service/candy/lakrits
[46 million req/sec] for URL: /service/shutdown
[75 million req/sec] for URL: /
[68 million req/sec] for URL: /some_file.html
[62 million req/sec] for URL: /another_file.jpeg
Checksum: 80000000

[/service/candy/lollipop]
Now serving candy of kind lollipop
[/service/candy/gum]
Now serving candy of kind gum
[/service/candy/seg_råtta]
Now serving candy of kind seg_råtta
[/service/candy/lakrits]
Now serving candy of kind lakrits
[/service/shutdown]
Shutting down now
[/]
Serving file: 
[/some_file.html]
Serving file: some_file.html
[/another_file.jpeg]
Serving file: another_file.jpeg
```
