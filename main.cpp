#include <iostream>
#include <dlfcn.h>

typedef void (*hello_func)();

int main() {
    // Load the shared library
    std::unique_ptr<void, decltype(&dlclose)> handle(dlopen("./libexample.so", RTLD_LAZY), dlclose);
    if (!handle) {
        std::cerr << "Error loading library: " << dlerror() << std::endl;
        return 1;
    }

    // Clear any existing errors
    dlerror();

   // Get a pointer to the `hello` function
    hello_func hello = reinterpret_cast<hello_func>(dlsym(handle.get(), "hello"));
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        std::cerr << "Error loading symbol 'hello': " << dlsym_error << std::endl;
        return 1;
    }

    // Call the `hello` function
    hello();

    return 0;
}
