#include <system.h>

namespace Core {

    class MeshRenderer : public System {
    public:
        MeshRenderer(Game& game);
        ~MeshRenderer() = default;

        void update(float deltaTime) override;
    };

}