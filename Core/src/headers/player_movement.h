#include <system.h>
#include <keyboard.h>

namespace Core {

    class PlayerMovement : public System {
    public:
        PlayerMovement(Game& game);

        ~PlayerMovement();
        void update(float deltaTime) override;
    private:
        Keyboard* keyboard;
    };

}