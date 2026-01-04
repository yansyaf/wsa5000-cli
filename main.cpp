/**
 * Author: Yan Syafri Hidayat
 * 
 **/ 

#include "rtsa/include/wsaInterface.h"
#include "rtsa/include/wsa_error.h"
#include <cstdio>
#include <cstring>
#include <cstdlib>

// This is a simple example of a command line interface (CLI) application
// that connects to a WSA device over Ethernet, configures it for RTSA mode,
// and performs a peak search within a specified frequency range.
//
// Command line arguments:
// -ip <device_ip>        : IP address of the WSA device
// -mode <mode>          : Operation mode (e.g., "rtsa")
// -atten <attenuator>   : Attenuator setting in dB
// -fstart <start_freq>  : Start frequency in Hz
// -fstop <stop_freq>    : Stop frequency in Hz
// -scale <scale>        : Frequency scale in Hz
// -rbw <rbw>            : Resolution bandwidth in Hz
//
// example usage:
// wsa5000.exe -ip 192.168.100.1 -mode rtsa -atten 10 -fstart 1000000000 -fstop 2000000000 -scale 1000000 -rbw 1000
// 
// print usage information if --help or -h is provided

#define WSA_OK 0

int main(int argc, char *argv[]) {


    // The device instance
    int64_t wsaHandle;
    int16_t result;
    LPSTR scpi_result;

    // Device settings
    char *d_ip = nullptr;
    char *d_mode = nullptr;
    int32_t attenuator = 0;
    uint64_t d_fstart = 0;
    uint64_t d_fstop = 0;
    uint64_t d_scale = 0;
    uint32_t d_rbw = 0;

    // Peak search results
    uint64_t peak_freq = 0;
    float peak_power = 0.0f;

    // Verbose flag
    bool verbose = false;


    // if argument is --help or -h, print usage
    if (argc == 2 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-h") == 0)) {
        printf("Usage: %s -ip <device_ip> -mode <mode> -atten <attenuator> -fstart <start_freq> -fstop <stop_freq> -scale <scale> -rbw <rbw> [--verbose]\n", argv[0]);
        printf("  --verbose : Print detailed process information.\n");
        return 0;
    }

    // parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--verbose") == 0) {
            verbose = true;
        } else if (strcmp(argv[i], "-ip") == 0 && i + 1 < argc) {
            d_ip = argv[++i];
        } else if (strcmp(argv[i], "-mode") == 0 && i + 1 < argc) {
            d_mode = argv[++i];
        } else if (strcmp(argv[i], "-atten") == 0 && i + 1 < argc) {
            attenuator = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-fstart") == 0 && i + 1 < argc) {
            d_fstart = strtoull(argv[++i], nullptr, 10);
        } else if (strcmp(argv[i], "-fstop") == 0 && i + 1 < argc) {
            d_fstop = strtoull(argv[++i], nullptr, 10);
        } else if (strcmp(argv[i], "-scale") == 0 && i + 1 < argc) {
            d_scale = strtoull(argv[++i], nullptr, 10);
        } else if (strcmp(argv[i], "-rbw") == 0 && i + 1 < argc) {
            d_rbw = static_cast<uint32_t>(atoi(argv[++i]));
        }
    }

    // abort and print error if arguments are missing
    if (!d_ip || !d_mode || !attenuator || !d_fstart || !d_fstop || !d_scale || !d_rbw) {
        printf("Usage: %s -ip <device_ip> -mode <mode> -atten <attenuator> -fstart <start_freq> -fstop <stop_freq> -scale <scale> -rbw <rbw> [--verbose]\n", argv[0]);
        printf("  --verbose : Print detailed process information.\n");
        return -1;
    }

    // parse command line arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-ip") == 0 && i + 1 < argc) {
            d_ip = argv[++i];
        } else if (strcmp(argv[i], "-mode") == 0 && i + 1 < argc) {
            d_mode = argv[++i];
        } else if (strcmp(argv[i], "-atten") == 0 && i + 1 < argc) {
            attenuator = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-fstart") == 0 && i + 1 < argc) {
            d_fstart = strtoull(argv[++i], nullptr, 10);
        } else if (strcmp(argv[i], "-fstop") == 0 && i + 1 < argc) {
            d_fstop = strtoull(argv[++i], nullptr, 10);
        } else if (strcmp(argv[i], "-scale") == 0 && i + 1 < argc) {
            d_scale = strtoull(argv[++i], nullptr, 10);
        } else if (strcmp(argv[i], "-rbw") == 0 && i + 1 < argc) {
            d_rbw = static_cast<uint32_t>(atoi(argv[++i]));
        }
    }

    if (verbose) printf("Connecting to device at %s...\n", d_ip);
    result = wsaConnect(&wsaHandle, d_ip);
    if (result != WSA_OK) {
        printf("Failed to connect to device at %s\n", d_ip);
        return -1;
    }

    if (verbose) printf("Resetting device...\n");
    result = wsaSetSCPI(wsaHandle, (LPSTR)"RESET");
    result = wsaSetSCPI(wsaHandle, (LPSTR)"*RST");
    result = wsaSetSCPI(wsaHandle, (LPSTR)":SYSTEM:ABORT");
    scpi_result = wsaGetSCPI(wsaHandle, (LPSTR)":SYSTEM:LOCK:REQUEST? ACQ");
    if (result != WSA_OK) {
        printf("Failed to reset device\n");
        wsaDisconnect(wsaHandle);
        return -1;
    }

    if (verbose) {
        printf("Finding peak signal in range %llu Hz - %llu Hz, RBW: %u Hz, Atten: %d dB, Mode: %s...\n",
            d_fstart, d_fstop, d_rbw, attenuator, d_mode);
    }
    result = wsaPeakFind(wsaHandle,    // wsa_handle,
                        d_fstart,      // fstart,
                        d_fstop,       // fstop,
                        d_rbw,         // rbw,
                        d_mode,        // mode,
                        0.0f,          // ref_offset,
                        attenuator,    // attenuator,
                        &peak_freq,    // peak_freq,
                        &peak_power);  // peak_power);

    if (result != WSA_OK) {
        printf("Peak find failed with error code: %d\n", result);
        wsaDisconnect(wsaHandle);
        return -1;
    }

    if (verbose) printf("Peak search complete.\n");
    printf("Peak Frequency: %llu Hz\n", peak_freq);
    printf("Peak Power: %.2f dBm\n", peak_power);

    if (verbose) printf("Disconnecting from device.\n");
    wsaDisconnect(wsaHandle);
    
    return 0;
}