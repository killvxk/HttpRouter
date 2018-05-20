# HttpRouter
Simple & fast header-only C++17 router for any HTTP server. Routes about 10-100 million URLs a second.

* Wildcards
* Parameters
* Optionals

```c++
    struct UserData {
        // pass whatever you need as user data
    } userData;

    HttpRouter<UserData *> r;

    r.add("GET", "/service/candy/:kind", [](UserData *user, std::vector<std::string_view> &args) {
        std::cout << "Now serving candy of kind " << args[0] << std::endl;
    });

    r.add("GET", "/service/shutdown", [](UserData *user, std::vector<std::string_view> &args) {
        std::cout << "Shutting down now" << std::endl;
    });

    r.route("GET", 3, "/service/candy/lollipop", 23, &userData);
```
