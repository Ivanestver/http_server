## [0.1.1] - 2025.11.16

### Fixed
- Fixed the name of the class IHTTTPResponseStartLine: the extra 'T' is removed.
- In the own implementation of std::optional the structs in_place_t and is_swappable and the global variable in_place are hidden in the macro when c++14 and lower.

## [0.1] - 2025.11.16

### Added
- This CHANGELOG file contains all the changes applied to the project.
- Server now can accept requests and make responses.
- Only OS sockets are used. No libraries.
- A request is done as an instance of the interface IHTTPRequest.
- A request is parsed into an IHTTPRequest object given back to the coder.
- Add a default implementation of the interface IHTTPRequest.
- A response is now a raw string. It must be explicitly written into a socket.
- Add the own implementation of std::optional. It turns on by defining SERVER_USE_OWN_IMPL_OPTIONAL macro in CMakeLists.txt. However, the STL version is used by default.
- Library functions to work with sockets are wrapped by eponymous wrappers that are cross-platform.
- Socket is a distinct class with all functionality supported.
- The String class is added. It's the immutable string.