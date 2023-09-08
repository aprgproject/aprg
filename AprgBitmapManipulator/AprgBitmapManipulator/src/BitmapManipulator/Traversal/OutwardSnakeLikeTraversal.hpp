#pragma once

#include <Bitmap/CommonTypes.hpp>

#include <optional>

namespace alba::AprgBitmap {

class OutwardSnakeLikeTraversal {
public:
    enum class Direction { Up, Down, Left, Right };

    OutwardSnakeLikeTraversal(
        BitmapXY const& currentPoint, Direction const direction, int const lowestLeft, int const highestRight,
        int const lowestTop, int const highestBottom);

    [[nodiscard]] bool isTraversalFinished() const;
    BitmapXY getNextPoint();

private:
    static BitmapXY fixPoint(
        BitmapXY const& point, int const lowestLeft, int const highestRight, int const lowestTop,
        int const highestBottom);

    [[nodiscard]] bool isPointInCorner() const;
    [[nodiscard]] bool cannotTeleport() const;
    void gotoNextPoint();
    void move();
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void switchDirection();
    void performScheduledTeleport();
    void teleportToNextOfMostLeftAndSwitchDirection();
    void teleportToNextOfMostRightAndSwitchDirection();
    void teleportToNextOfMostTopAndSwitchDirection();
    void teleportToNextOfMostBottomAndSwitchDirection();
    BitmapXY m_currentPoint;
    Direction m_direction;
    std::optional<Direction> m_scheduledTeleportDirection;
    std::optional<Direction> m_previousMovementDirection;
    int m_lowestLeft;
    int m_highestRight;
    int m_lowestTop;
    int m_highestBottom;
    int m_lastMostLeft;
    int m_lastMostRight;
    int m_lastMostTop;
    int m_lastMostBottom;
    bool m_isStart{true};
    bool m_isFinished{false};
};

}  // namespace alba::AprgBitmap
