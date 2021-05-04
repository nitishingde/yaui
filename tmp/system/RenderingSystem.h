#ifndef YAUI_SYSTEM_RENDERINGSYSTEM_H
#define YAUI_SYSTEM_RENDERINGSYSTEM_H


#include "ISystem.h"

namespace yaui::system {
    class RenderingSystem: public ISystem {
    private:
        bool mDisplayStats = false;
        float mFps = 0;
        bool mShouldUpdateRenderPipeline = true;
        Colour mWindowBackgroundColour {64, 64, 64, 255};
        Font *mpFont = nullptr;
        Texture *mpStatsTexture = nullptr;

    private:
        void displayStats();
    public:
        explicit RenderingSystem(uint32 priorityRank);
        ~RenderingSystem() override;
        void executeJob() override;
        [[nodiscard]] String getClassName() const override;
        void displayStats(bool displayStats);
        void setWindowBackgroundColour(const Colour &colour);
        void updateRenderPipeline();
    };
}

#endif //YAUI_SYSTEM_RENDERINGSYSTEM_H
