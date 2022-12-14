#pragma once

#include <glad/glad.h>
#include <C:\Users\peter\OneDrive\Desktop\game\SDL2-2.24.0\include\SDL.h>
#include "window_types.h"
#include "file_utils.h"
#include "linmath/linmath.h"
#include <GL/gl.h>
struct render_types{

  u32 vao_quad;
  u32 vbo_quad;
  u32 ebo_quad;

  mat4x4 projection;
};

struct render_data{

  vec2 pos;
  vec2 size;
  vec4 color;

};

static render_data render_data_context = {};


static render_types render_types_context;

PINLINE void render_init_shaders(shader_files * shader_context, window_types * window_context, render_types * render_context){
  shader_context->shader_default = render_shader_create("default.vert", "default.frag");

  mat4x4_ortho(render_context->projection, 0, window_context->window_width, 0, window_context->window_height, -2, 2);

    glUseProgram(shader_context->shader_default);
    glUniformMatrix4fv(
        glGetUniformLocation(shader_context->shader_default, "projection"),
        1,
        GL_FALSE,
       &render_context->projection[0][0]
    );

};

  void render_init_color_texture(shader_files * shader_context) {
    glGenTextures(1, &shader_context->texture_color);
    glBindTexture(GL_TEXTURE_2D, shader_context->texture_color);

    u8 solid_white[4] = {255, 255, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, solid_white);

    glBindTexture(GL_TEXTURE_2D, 0);
}

PINLINE void render_init_quad(render_types * render_context){
  f32 vertices[] = {

    0.5, 0.5, 0, 0, 0,
    0.5, -0.5, 0, 0, 1,
    -0.5, -0.5, 0, 1, 1,
    -0.5, 0.5, 0, 1, 1

  };

  u32 indices[] = {

    0, 1, 3,
    1, 2, 3,
    

  };

  glGenVertexArrays(1,&render_context->vao_quad);
  glGenBuffers(1,& render_context->vbo_quad);
  glGenBuffers(1, &render_context->ebo_quad);

  glBindVertexArray(render_context->vao_quad);
  glBindBuffer(GL_ARRAY_BUFFER, render_context->vbo_quad);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, render_context->ebo_quad);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), NULL);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void *)(3 * sizeof(f32)));
glad_glEnableVertexAttribArray(1);
  

}

PINLINE void render_init(){

  render_init_quad(&render_types_context);
  render_init_shaders(&shader_files_context, &window_types_context, &render_types_context );
  render_init_color_texture(&shader_files_context);
  

};

PINLINE void render_begin(){

  glClearColor(0.1, 0.1, 0.0, 1);
  glClear(GL_COLOR_BUFFER_BIT);

  

};

PINLINE void render_end( window_types * window_context){

  SDL_GL_SwapWindow(window_context->window);
  

};

PINLINE void render_quad(vec2 pos, vec2 size, vec4 color, shader_files* shader_context,  render_types * render_context) {
 
   glUseProgram(shader_context->shader_default);

   mat4x4 model;
   mat4x4_identity(model);
   mat4x4_translate(model, pos[0], pos[1], 0);
   
 mat4x4_scale_aniso(model, model, size[0], size[1], 1);
   
 glUniformMatrix4fv(glGetUniformLocation(shader_context->shader_default, "model"), 1, GL_FALSE,&model[0][0]);
   
  glUniform4fv(glad_glGetUniformLocation(shader_context->shader_default, "color"), 1, color);
		       
  glBindVertexArray(render_context->vao_quad);

    glBindTexture(GL_TEXTURE_2D, shader_context->texture_color);
		      // glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
  glBindVertexArray(0);

};
