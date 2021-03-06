#ifndef CELL_H
#define CELL_H

#include <stdio.h>

namespace model {

class Cell
{
public:
    enum class eState {
        kEmpty,
        kX,
        kO
    };
    struct Position {
        Position(size_t posX, size_t posY) : x(posX), y(posY){}
        Position() : Position{0,0} {}
        size_t x = 0;
        size_t y = 0;
    };

    Cell(size_t fieldSize);
    void SetState(eState state);
    eState GetState() const noexcept;
    const Position & GetPosition() const noexcept;
    size_t GetX() const noexcept;
    size_t GetY() const noexcept;
private:
    Cell::eState state_ = Cell::eState::kEmpty;
    static size_t globalX_;
    static size_t globalY_;
    Position position_;
};

} //namespace model
#endif // CELL_H
