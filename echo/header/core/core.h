#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <set>
#include <map>
#include <unordered_map>
#include <queue>
#include <vector>
#include <string>
#include <memory>
#include <cassert>
#include <cstdint>
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <memory>
#include <random>
#include <intrin.h>
#include <typeindex>
#include <filesystem>
#include <thread>


//#include <function>

//GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/matrix_interpolation.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/euler_angles.hpp>

#define Vector2 glm::vec2 
#define Vector3 glm::vec3 
#define Vector4 glm::vec4
#define Matrix4 glm::mat4 
#define Matrix3 glm::mat3
#define Quaternion glm::quat
#define String std::string
#define UniformLocationCache std::unordered_map<String, int>

#define WIDTH 1280
#define HEIGHT 720

#define RED 0.2f
#define GREEN 0.3f
#define BLUE 0.5f
#define ALPHA 0.0f

#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "base.h"

