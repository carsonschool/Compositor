#include <string>
#include <wayland-server-core.h>
#include <smithay/output.h>

class Backend {
public:
    static const bool HAS_RELATIVE_MOTION = false;
    virtual std::string seat_name() = 0;
    virtual void reset_buffers(Output* output) = 0;
    virtual void early_import(WlSurface* surface) = 0;
};

#include "udev.h"
#include "winit.h"
using UdevData = udev::UdevData;
using WinitData = winit::WinitData;
using run_udev = udev::run_udev;
using run_winit = winit::run_winit;
