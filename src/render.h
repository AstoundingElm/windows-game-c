#pragma once


#include "C:/Users/peter/OneDrive/Desktop/game/SDL2-2.24.0/include/SDL.h"
#include "physics.h"
#include "window_types.h"
#include "file_utils.h"
#include "list.h"
#include "linmath/linmath.h"
#include <GL/gl.h>
struct render_types{

  u32 vao_quad;
  u32 vbo_quad;
  u32 ebo_quad;
  u32 vao_line;
  u32 vbo_line;
  mat4x4 projection;
};

struct render_data{

  vec2 pos;
  vec2 size;
  vec4 color;

};

static render_data render_data_context = {};


static render_types render_types_context;

PINLINE void render_init_line(u32 * vao, u32 * vbo){

  glGenVertexArrays(1, vao);
  glBindVertexArray(*vao);
  glGenBuffers(1, vbo);
  glBindBuffer(GL_ARRAY_BUFFER, *vbo);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(f32), NULL, GL_DYNAMIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), NULL);
  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
};


PINLINE void render_line_segment(vec2 start, vec2 end, vec2 color, render_types * render_context, shader_files * shader_context){
  glUseProgram(shader_context->shader_default);
  glLineWidth(3);

  f32 x = end[0] - start[0];
  f32 y = end[1] - start[1];
  f32 line[6] = {0, 0, 0, x, y, 0};

  mat4x4 model;
  mat4x4_translate(model, start[0], start[1], 0);

  glUniformMatrix4fv(glGetUniformLocation(shader_context->shader_default, "model"), 1, GL_FALSE, &model[0][0]);

  glUniform4fv(glGetUniformLocation(shader_context->shader_default, "color"),1, color);

  glBindTexture(GL_TEXTURE_2D, shader_context->texture_color);
  glBindVertexArray(render_context->vao_line);
  glBindBuffer(GL_ARRAY_BUFFER, render_context->vbo_line);
  glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(line), line);
  glDrawArrays(GL_LINES, 0, 2);

  glBindVertexArray(0);
  
};

PINLINE void render_quad_line(vec2 pos, vec2 size, vec4 color){

  vec2 points[4] = {
    {pos[0] - size[0] * 0.5, pos[1] - size[1] * 0.5},
    {pos[0] + size[0] * 0.5, pos[1] - size[1] * 0.5},
    {pos[0] + size[0] * 0.5, pos[1] + size[1] * 0.5},
    {pos[0] - size[0] * 0.5, pos[1] + size[1] * 0.5}};
  render_line_segment(points[0], points[1],  color, &render_types_context, &shader_files_context);
  render_line_segment(points[1], points[2],  color, &render_types_context, &shader_files_context);
  render_line_segment(points[2], points[3],  color, &render_types_context, &shader_files_context);
  render_line_segment(points[3], points[0],  color, &render_types_context, &shader_files_context);
  
};


PINLINE void render_aabb(f32 * aabb, vec4 color){

  vec2 size;
  vec2_scale(size, &aabb[2], 2);
  render_quad_line(&aabb[0], size, color);
  

};

PINLINE void render_init_shaders(shader_files * shader_context, window_types * window_context, render_types * render_context){
  shader_context->shader_default = render_shader_create("C:/Users/peter/OneDrive/Desktop/game/shaders/default.vert", "C:/Users/peter/OneDrive/Desktop/game/shaders/default.frag");

  mat4x4_ortho(render_context->projection, 0, 800, 0, 600, -2, 2);

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

PINLINE void render_init(physics_types * physics_context){

  physics_context->body_list = array_list_create(sizeof(Body), 0);
  physics_context->static_body_list = array_list_create(sizeof(Static_Body), 0);

  physics_context->gravity = -200;
  physics_context->terminal_velocity = -10000;
  tick_rate = 1.f/ iterations;
  
  render_init_quad(&render_types_context);
  render_init_line(&render_types_context.vao_line, &render_types_context.vbo_line);
  render_init_shaders(&shader_files_context, &window_types_context, &render_types_context );
  render_init_color_texture(&shader_files_context);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

};

PINLINE void render_begin(){

  glClearColor((float)0.1, (float)0.1, (float)0.0, 1);
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
