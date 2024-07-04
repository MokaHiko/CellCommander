#version 460

layout(location = 0) out vec4 frag_color;

layout(location = 0) in vec3 v_position_world_space;
layout(location = 1) in vec3 v_color;
layout(location = 2) in vec2 v_uv;

layout(location = 3) in vec3 v_frag_direction;

struct DirectionalLight {
  mat4 view_proj;

  vec4 color;
  vec4 direction;
};

layout(set = 0, binding = 0) uniform SceneData {
  mat4 view;
  mat4 proj;

  uint dir_light_count;
  uint point_light_count;
  uint spot_light_count;
  uint area_light_count;
};

layout(std140, set = 0, binding = 1) readonly buffer DirectionalLights {
  DirectionalLight dir_lights[];
};

layout(set = 0, binding = 4) uniform sampler2D shadow_map;
layout(set = 1, binding = 0) uniform samplerCube material_textures;

layout(set = 2, binding = 0) uniform Material {
  vec4 diffuse_color;
  vec4 specular_color;
};

void main() {
  vec4 diffuse = texture(material_textures, v_frag_direction) * diffuse_color;
  frag_color = diffuse; 
}