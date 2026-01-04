
# wsa5000-cli

A command-line interface (CLI) application for controlling ThinkRF WSA devices, built with C++ and CMake for x86 architecture (legacy compatibility).

## Prerequisites

**Visual Studio 2017/2019/2022 (x86/Win32 toolchain)**
  - Install the Desktop development with C++ workload
**CMake 3.18 or newer**
**wsaInterface.dll and wsaInterface.lib**
  - Provided in `rtsa/lib` (must be x86/Win32)
**Git Bash or compatible shell** (for running `build.sh` and `run.sh`)

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

## Output Results

After a successful run, the application prints the peak frequency and power found in the specified range:

```
Peak Frequency: <frequency> Hz
Peak Power: <power> dBm
```

Example output:

```
Peak Frequency: 1450000000 Hz
Peak Power: -42.37 dBm
```

If an error occurs, an error message is printed and the program exits with a nonzero code.

### Using Output in External x64 Applications

- The output is plain text, so any external (x64 or x86) application can invoke this CLI tool as a subprocess and parse the output.
- For example, in Python (x64):
  ```python
  import subprocess
  result = subprocess.run([
    'wsa5000-cli.exe',
    '-ip', '192.168.100.1',
    '-mode', 'rtsa',
    '-atten', '10',
    '-fstart', '1000000000',
    '-fstop', '2000000000',
    '-scale', '1000000',
    '-rbw', '1000'
  ], capture_output=True, text=True)
  for line in result.stdout.splitlines():
    if line.startswith('Peak Frequency:'):
      freq = int(line.split(':')[1].strip().split()[0])
    if line.startswith('Peak Power:'):
      power = float(line.split(':')[1].strip().split()[0])
  print(f"Peak: {freq} Hz, {power} dBm")
  ```
- This approach works regardless of the bitness (x86/x64) of the calling application, as long as the CLI binary and its dependencies are present and compatible with the OS.
- Ensure `wsaInterface.dll` is present in the same directory as `wsa5000-cli.exe` when running.

- For command-line arguments and usage, run:
  ```sh
  ./Release/wsa5000-cli.exe --help
  ```

# Author
Yan Syafri Hidayat