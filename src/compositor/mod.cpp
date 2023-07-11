#include <iostream>
#include <slog/slog.hpp>

#include "backend.hpp"
#include "components.hpp"
#include "drawing.hpp"
#include "focus.hpp"
#include "handlers.hpp"
#include "input.hpp"
#include "render.hpp"
#include "shell.hpp"
#include "state.hpp"

void start() {
    auto plain = std::make_shared<slog::PlainSyncDecorator>(std::cout);
    auto log = slog::Logger::root(slog::FullFormat(plain).build().fuse());

    // Env variable NAVDA_BACKEND=udev will tell the compositor to launch under udev,
    // otherwise winit backend.
    if (const char* backend = std::getenv("NAVDA_BACKEND"); backend && std::string(backend) == "udev") {
        run_udev(log);
    } else {
        run_winit(log);
    }
}

int main() {
    try {
        start();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
