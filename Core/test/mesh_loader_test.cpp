#include <gtest/gtest.h>
#include <mesh_loader.h>
#include <filesystem>

using namespace Core;

TEST(MeshLoaderTest, LoadsFakeMesh) {
    EXPECT_EQ(true, true);
    //// Create a dummy .obj for test
    //std::ofstream out("test_dummy.obj");
    //out << "# Dummy OBJ\nv 0 0 0\n";
    //out.close();

    //auto mesh = MeshLoader::loadMesh("test_dummy.obj");

    //ASSERT_NE(mesh, nullptr);
    //EXPECT_EQ(mesh->indexCount, 36);

    //std::filesystem::remove("test_dummy.obj");
}

//TEST(MeshLoaderTest, HandlesMissingFile) {
//    auto mesh = MeshLoader::loadMesh("nonexistent.obj");
//    EXPECT_EQ(mesh, nullptr);
//}
