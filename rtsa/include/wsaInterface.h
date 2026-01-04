#ifndef WSAInterface_H
#define WSAInterface_H
# include <windows.h>

extern "C" {
	#include "wsa_lib.h"
	#include "wsa_api.h"
	}

#define MAX_SAMPLES_PER_PACKET 65520
///////////////////////////////////////////////////////////////////////////////

// connect/disconnect functions
 __declspec(dllexport) int16_t __stdcall  wsaConnect(int64_t *wsa_handle, char *ip);
  __declspec(dllexport) int16_t __stdcall  wsaDisconnect(int64_t wsa_handle);

__declspec(dllexport) int16_t __stdcall wsaReadData(int64_t wsa_handle,
												int16_t *i16_data, 
												int16_t *q16_data,
												int32_t *i32_data,
												uint32_t timeout,
												uint32_t *stream_id,
												uint8_t *spectral_inversion,
												int32_t *samples_per_packet,
												uint32_t *timestamp_sec,
												uint64_t *timestamp_psec,
												int16_t *reference_level,
												int64_t *bandwidth,
												int64_t *center_frequency);

// set scpi command
__declspec(dllexport) int16_t __stdcall wsaSetSCPI(int64_t wsa_handle, LPSTR command);

// query scpi command
__declspec(dllexport) LPSTR __stdcall wsaGetSCPI(int64_t wsa_handle, LPSTR command);

// return error string
__declspec(dllexport) LPSTR __stdcall wsaErrorMessage(int16_t error_code);

// allocate memory for sweep
__declspec(dllexport) int16_t __stdcall wsaGetSweepSize(int64_t wsa_handle, 
													uint64_t fstart, 
													uint64_t fstop, 
													uint32_t rbw, 
													LPSTR mode,
													int32_t attenuator,
													uint32_t *sweep_size);

// capture spectral data
__declspec(dllexport) int16_t __stdcall wsaCaptureSpectrum(int64_t wsa_handle, 
														uint64_t fstart, 
														uint64_t fstop, 
														uint32_t rbw, 
														LPSTR mode, 
													    int32_t attenuator,
														float *spectral_data);


// get size required for the FFT buffer
__declspec(dllexport) int16_t __stdcall wsaGetFFTSize(int32_t samples_per_packet,
														int32_t stream_id, 
														int32_t *array_size);
// get size required for the FFT buffer
__declspec(dllexport) int16_t __stdcall wsaComputeFFT(int32_t samples_per_packet,
													int32_t fft_size,
													uint32_t stream_id,
													int16_t reference_level,
													uint8_t spectral_inversion,
													int16_t * i16_buffer,
													int16_t * q16_buffer,
													int32_t * i32_buffer,
													float * fft_buffer);

__declspec(dllexport) int16_t __stdcall wsaPeakFind(int64_t wsa_handle,
					uint64_t fstart, 
					uint64_t fstop, 
					uint32_t rbw, 
					char *mode,
					float ref_offset,
					int32_t attenuator,
					uint64_t *peak_freq,
					float *peak_power);

__declspec(dllexport) int16_t __stdcall wsaChannelPower(int64_t wsa_handle,
					uint64_t fstart, 
					uint64_t fstop, 
					uint32_t rbw, 
					char *mode,
					float ref_offset,
					int32_t attenuator,
					float *channel_power);

__declspec(dllexport) int16_t __stdcall wsaOccupiedBandwidth(int64_t wsa_handle,
					uint64_t fstart, 
					uint64_t fstop, 
					uint32_t rbw, 
					float occupied_percentage,
					char *mode,
					int32_t attenuator,
					uint64_t *occupied_bw);

#endif //WSAInterface.DLL
