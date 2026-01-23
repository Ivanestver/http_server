## [2.0.1] - 2026.01.24

## Added
- noexcept to some functions to improve performance

## [2.0.0] - 2025.11.23

## Added
- Send static files as the answer.
- Application Context class that contains the app settings.
- The server is now configured through functions.
- CMake function define_library that creates a shared library: searches files, adds a library, creates an exports file, connects with binary directory.
- Using the define_library function, make all libraries as shared

### Fixed
- Some memory improvements
- The .exe, .dlls and .libs are distributed in different directories after installation.

## [1.2.0] - 2025.11.23

## Added
- Send static files as the answer.
- Application Context class that contains the app settings.
- The server is now configured through functions.

## [1.1.1] - 2025.11.23

### Fixed
- The .exe, .dlls and .libs are distributed in different directories after installation.

## [1.1.0] - 2025.11.23

### Added
- CMake function define_library that creates a shared library: searches files, adds a library, creates an exports file, connects with binary directory.
- Using the define_library function, make all libraries as shared

## [1.0.1] - 2025.11.23

### Fixed
- Some memory improvements

## [1.0.0] - 2025.11.17

### Added
- The first release of the http server. It provides:
- Setting up port to listen to.
- Routing.
- All HTTP methods support (basic).
- Writing any type of info into response.

## [0.3.0] - 2025.11.17

### Added
=======
- Add hash of String.
- Add server class that encapsulates server logic and provides functionality to set routing.

## [0.2.1] - 2025.11.17

### Added
- Hash of String.

## [0.2] - 2025.11.16

### Added
- HTTPResponse class that represents an http response to a client.
- Example to send the response back to the client connected. This example shows the code works

## [0.1.4] - 2025.11.16

### Added
- Function to receive the header keys.

## [0.1.3] - 2025.11.16

### Added
- Function to convert a status code into string.

### Fixed
- Rename the pseudonym of a header key.

## [0.1.2] - 2025.11.16

### Added
- Parsing String class into Buffer.

### Fixed
- Add inline to operator<< of Buffer.
- Add conversion of Buffer into byte array.

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