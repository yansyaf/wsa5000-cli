# wsa5000-cli

A command-line interface (CLI) application for controlling ThinkRF WSA devices, built with Qt5 and C++ (for legacy compatibility).

## Prerequisites

- **Qt 5.12.x (x86/Win32)**
  - Download and install from [Qt Downloads](https://download.qt.io/archive/qt/5.12/5.12.12/)
  - Ensure you install the MSVC x86 (32-bit) version (e.g., `msvc2017` or `msvc2019`)
- **Visual Studio 2017/2019/2022 (x86/Win32 toolchain)**
  - Install the Desktop development with C++ workload
- **CMake 3.18 or newer**
- **wsaInterface.dll and wsaInterface.lib**
  - Provided in `rtsa/lib` (must be x86/Win32)
- **Git Bash or compatible shell** (for running `build.sh` and `run.sh`)

## Building the Project

1. Open a terminal (Git Bash or Command Prompt).
2. Create and enter a build directory:
   ```sh
   mkdir build
   cd build
   ```
3. Run the build script:
   ```sh
   ../build.sh
   ```
   This script will:
   - Configure the project for Win32/x86 using CMake
   - Build the Release version using MSBuild

   Alternatively, you can run the commands manually:
   ```sh
   cmake -G "Visual Studio 17 2022" -A Win32 ..
   cmake --build . --config Release
   ```


## Command Line Arguments

The application accepts the following command line arguments:

| Argument      | Description                                 | Example Value         |
|---------------|---------------------------------------------|----------------------|
| `-ip`         | IP address of the WSA device                | `192.168.100.1`      |
| `-mode`       | Operation mode (e.g., `rtsa`)               | `rtsa`               |
| `-atten`      | Attenuator setting in dB                    | `10`                 |
| `-fstart`     | Start frequency in Hz                       | `1000000000`         |
| `-fstop`      | Stop frequency in Hz                        | `2000000000`         |
| `-scale`      | Frequency scale in Hz                       | `1000000`            |
| `-rbw`        | Resolution bandwidth in Hz                  | `1000`               |

**Example usage:**

```sh
./Release/wsa5000-cli.exe -ip 192.168.100.1 -mode rtsa -atten 10 -fstart 1000000000 -fstop 2000000000 -scale 1000000 -rbw 1000
```

To print usage information, use:

```sh
./Release/wsa5000-cli.exe --help
```

or

```sh
./Release/wsa5000-cli.exe -h
```

If required arguments are missing, the application will print the usage information and exit.

After building, the executable will be in `build/Release/`.

- To run using the provided script:
  ```sh
  ../run.sh
  ```
- Or manually:
  ```sh
  ./Release/wsa5000-cli.exe [arguments]
  ```

## Notes
- Ensure `wsaInterface.dll` is present in the same directory as `wsa5000-cli.exe` when running.
- If you encounter Qt DLL errors, ensure your Qt5 x86 `bin` directory is in your `PATH`.
- For command-line arguments and usage, run:
  ```sh
  ./Release/wsa5000-cli.exe --help
  ```

# Author
Yan Syafri Hidayat