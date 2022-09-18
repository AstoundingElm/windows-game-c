#pragma once

#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>
#include <string.h>
#include <string>

#define IO_READ_CHUNK_SIZE 2097152

#define IO_READ_ERROR_GENERAL "error reading file %s errno %d"
#define IO_READ_ERROR_MEMORY "not enough free memeory to read file %s"

struct shader_files{

  u32 shader_default;
  u32 texture_color;

};

static shader_files shader_files_context;


struct File{

  char * data;
  size_t len;
  bool is_valid;

};

File io_file_read(const char * path){

  File file = {.is_valid = false};

  FILE * fp = fopen(path, "rb");
  if (!fp || ferror(fp)) {
      ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
  }
  char * data  = NULL;
  char * tmp;
  size_t used = 0;
  size_t size = 0;
  size_t n;

   while (true) {
        if (used + IO_READ_CHUNK_SIZE + 1 > size) {
            size = used + IO_READ_CHUNK_SIZE + 1;

            if (size <= used) {
                free(data);
                ERROR_RETURN(file, "Input file too large: %s\n", path);
            }

            tmp = (char *)realloc(data, size);
            if (!tmp) {
                free(data);
                ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
            }
            data = tmp;
        }

        n = fread(data + used, 1, IO_READ_CHUNK_SIZE, fp);
        if (n == 0)
            break;

        used += n;
    }

    if (ferror(fp)) {
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_GENERAL, path, errno);
    }

    tmp =(char *) realloc(data, used + 1);
    if (!tmp) {
        free(data);
        ERROR_RETURN(file, IO_READ_ERROR_MEMORY, path);
    }
    data = tmp;
    data[used] = 0;

    file.data = data;
    file.len = used;
    file.is_valid = true;

    return file;
   
}


u32 render_shader_create(const char *path_vert, const char *path_frag) {
    int success;
    char log[512];

    File file_vertex = io_file_read(path_vert);
    if (!file_vertex.is_valid) {
        ERROR_EXIT("Error reading shader: %s\n", path_vert);
    }

    u32 shader_vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader_vertex, 1, (const char *const *)&file_vertex, NULL);
    glCompileShader(shader_vertex);
    glGetShaderiv(shader_vertex, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_vertex, 512, NULL, log);
        ERROR_EXIT("Error compiling vertex shader. %s\n", log);
    }

    File file_fragment = io_file_read(path_frag);
    if (!file_fragment.is_valid) {
        ERROR_EXIT("Error reading shader: %s\n", path_frag);
    }

    u32 shader_fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader_fragment, 1, (const char *const *)&file_fragment, NULL);
    glCompileShader(shader_fragment);
    glGetShaderiv(shader_fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_fragment, 512, NULL, log);
        ERROR_EXIT("Error compiling fragment shader. %s\n", log);
    }

    u32 shader = glCreateProgram();
    glAttachShader(shader, shader_vertex);
    glAttachShader(shader, shader_fragment);
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shader, 512, NULL, log);
        ERROR_EXIT("Error linking shader. %s\n", log);
    }

    free(file_vertex.data);
    free(file_fragment.data);

    return shader;
}


int io_file_write(void* buffer, size_t size, const char* path) {
    FILE* fp = fopen(path, "wb");
    if (!fp || ferror(fp))
        ERROR_RETURN(1, "Cannot write file: %s.\n", path);

    size_t chunks_written = fwrite(buffer, size, 1, fp);

    fclose(fp);

    if (chunks_written != 1)
        ERROR_RETURN(1, "Write error. "
            "Expected 1 chunk, got %zu.\n", chunks_written);

    return 0;
  
  
};

