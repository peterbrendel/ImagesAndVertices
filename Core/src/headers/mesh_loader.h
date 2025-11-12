#pragma once
#include <unordered_map>
#include <string>
#include <components.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

namespace Core {
    class MeshLoader {
    public:
        MeshLoader() = default;
        ~MeshLoader() = default;
        static std::shared_ptr<Components::Mesh> loadMesh(const char* path);

    private:
        static std::unordered_map<std::string, std::shared_ptr<Components::Mesh>> loadedMeshes;
    };
}
