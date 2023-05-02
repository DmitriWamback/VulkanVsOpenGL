#define DEBUG_VULKAN_TEST

#define GLFW_INCLUDE_VULKAN
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "project/vk.h"
#include "project/gl.h"

int main() {
    Initialize();
}