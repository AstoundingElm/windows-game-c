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

//#define WHITE (vec4){1, 1, 1, 1}
#define BLACK (vec4){0, 0, 0, 1}
//#define RED (vec4){1, 0, 0, 1}
#define GREEN (vec4){0, 1, 0, 1}
#define BLUE (vec4){0, 0, 1, 1}
#define YELLOW (vec4){1, 1, 0, 1}
//#define CYAN (vec4){0, 1, 1, 1}
#define MAGENTA (vec4){1, 0, 1, 1}
//#define ORANGE (vec4){1, 0.5, 0, 1}
#define PURPLE (vec4){0.5, 0, 1, 1}
#define TURQUOISE (vec4){0, 1, 0.5, 1}
