#pragma once

namespace winter {

    class Timer final {

    public:

        Timer();

        void tick();

        float getTime() const;
        int getFPS() const;
        float getDelta() const;

    private:

        float lastFrame;
        float lastFps;
        int frames;
        int fps;
        float delta;

    };

}