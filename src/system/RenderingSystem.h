#ifndef YAUI_SYSTEM_RENDERINGSYSTEM_H
#define YAUI_SYSTEM_RENDERINGSYSTEM_H


#include "ISystem.h"

namespace yaui::system {
    class RenderingSystem: public ISystem {
    private:
        bool mDisplayStats = false;
        Font *mpFont = nullptr;
        Texture *mpStatsTexture = nullptr;
        float mFps = 0;

    private:
        void displayStats();
    public:
        explicit RenderingSystem(uint32 priorityRank);
        ~RenderingSystem() override;
        void executeJob() override;
        [[nodiscard]] String getClassName() const override;
        void displayStats(bool displayStats);
    };
}

#endif //YAUI_SYSTEM_RENDERINGSYSTEM_H
