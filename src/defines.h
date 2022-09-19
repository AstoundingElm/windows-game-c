#pragma once
#define _CRT_SECURE_NO_WARNINGS
#define SDL_MAIN_HANDLED
#include <C:\Users\peter\OneDrive\Desktop\game\SDL2-2.24.0\include\SDL.h>
#include <glad/glad.h>
#include <stdint.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;

#define PINLINE static inline


#define ERROR_EXIT(...) {fprintf(stderr, __VA_ARGS__); exit(1);}
#define ERROR_RETURN(R, ...) {fprintf(stderr, __VA_ARGS__); return R;}

 static bool running = true;
