#pragma once

#include <Bitmap/BitmapSnippet.hpp>
#include <BitmapManipulator/PenCircles.hpp>
#include <BitmapManipulator/Traversal/BitmapSnippetTraversal.hpp>

namespace alba::AprgBitmap {

class PenCirclesDrawer {
public:
    struct ColorDetails {
        ColorDetails();
        [[nodiscard]] uint32_t getColor() const;
        [[nodiscard]] bool isEmpty() const;
        void addColor(uint32_t const color, double const weight);
        void clear();
        double totalRed{0};
        double totalGreen{0};
        double totalBlue{0};
        double totalWeight{0};
    };

    using PointToColorMap = std::map<BitmapXY, uint32_t>;
    using PointAndColorPair = std::pair<BitmapXY, uint32_t>;
    using PointToColorDetailsMap = std::map<BitmapXY, ColorDetails>;
    using PointAndColorDetailsPair = std::pair<BitmapXY, ColorDetails>;
    PenCirclesDrawer(PenCircles const& penCircles, BitmapSnippet& snippet);
    PenCirclesDrawer(PenCircles&& penCircles, BitmapSnippet& snippet);
    void draw();
    void drawUsingCirclesWithoutOverlay();
    void drawUsingCirclesWithOverlay();
    void drawUsingConnectedCircles();

private:
    void writeDrawnPointsInSnippet();
    void writeCirclesWithoutOverlay();
    void writeCirclesWithOverlay();
    void connectCirclesIfNeeded();
    void putCirclesWithoutOverlay();
    void putCirclesWithOverlay();
    void putCircleConnectionsAndRemoveProcessedCircles();

    static bool isToBeConnected(
        PenCircles::PointAndPenCircleDetailsPair const& pair1, PenCircles::PointAndPenCircleDetailsPair const& pair2);

    BitmapSnippet& m_snippet;
    BitmapSnippetTraversal m_snippetTraversal;
    PenCircles m_penCircles;
    PointToColorMap m_drawnPoints;
};

}  // namespace alba::AprgBitmap
