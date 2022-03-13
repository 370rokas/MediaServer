# Media Server
![Cmake-Ubuntu](https://github.com/370rokas/MediaServer/actions/workflows/cmake-ubuntu.yml/badge.svg)
![CodeCov-Master](https://codecov.io/gh/370rokas/MediaServer/branch/master/graph/badge.svg)

**Author:** 370rokas

**License:** [MIT License](license.md)

**Description:** A simple **UNFINISHED** Media Server written in C++.

## 🔨 Dependencies
```shell
$ SQLite3
```

## 🔧 Installation
### Build using CMake
```shell
# Download the repository
$ git clone https://github.com/370rokas/MediaServer

# Configure CMakeLists.txt to your liking:
# You might want to change the BUILD_LOCATION

# If you are building on a Windows environment
# Change CMAKE_PREFIX_PATH to the path of desired a SQLite3 installation

# Build the project using CMake
$ cmake .
```
### Use pre-built binaries
Pre-built binaries of stable versions will be available in the Releases section of the GitHub repository.

## ✨ Usage
```shell
# Run the executable file
$ ./WuseMediaServer.exe
```

## 📓 Todo
- Fix ``cmake-windows.yml`` action;
- Expose the server to an HTTPS api;
- Write tests and add code coverage analysis;

## 🤝 Contributing

Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## 📝 License
This project is licensed under the [MIT license](license.md).
