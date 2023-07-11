#include <smithay/backend/input/key_state.hpp>
#include <smithay/desktop/layer_surface.hpp>
#include <smithay/desktop/popup_kind.hpp>
#include <smithay/input/keyboard/keyboard_target.hpp>
#include <smithay/input/keyboard/keysym_handle.hpp>
#include <smithay/input/pointer/pointer_target.hpp>
#include <smithay/seat/seat.hpp>
#include <smithay/utils/is_alive.hpp>
#include <smithay/utils/serial.hpp>
#include <smithay/wayland/seat/wayland_focus.hpp>
#include <wayland-server-backend.hpp>
#include <wayland-server-protocol.hpp>
#include <winit/event/modifiers_state.hpp>

using namespace smithay;

enum class FocusTarget {
    Window,
    LayerSurface,
    Popup,
};

struct AvWindow {
    bool alive();
};

struct LayerSurface {
    bool alive();
};

struct PopupKind {
    bool alive();
    WlSurface wl_surface();
};

template <typename BEnd>
struct Navda {
    // implementation details
};

template <typename BEnd>
struct Backend {
    // implementation details
};

template <typename BEnd>
struct PointerTarget {
    void enter(AvWindow& w, Seat<Navda<BEnd>>& seat, Navda<BEnd>& data, pointer::MotionEvent& event);
    void enter(LayerSurface& l, Seat<Navda<BEnd>>& seat, Navda<BEnd>& data, pointer::MotionEvent& event);
    void enter(WlSurface& surface, Seat<Navda<BEnd>>& seat, Navda<BEnd>& data, pointer::MotionEvent& event);
};

template <typename BEnd>
struct IsAlive {
    bool alive();
};

template <typename BEnd>
struct FocusTarget : IsAlive<BEnd>, PointerTarget<BEnd> {
    FocusTarget::FocusTarget() {}
    bool alive() {
        switch (this) {
            case FocusTarget::Window:
                return w.alive();
            case FocusTarget::LayerSurface:
                return l.alive();
            case FocusTarget::Popup:
                return p.alive();
        }
    }
    void enter(Seat<Navda<BEnd>>& seat, Navda<BEnd>& data, pointer::MotionEvent& event) {
        switch (this) {
            case FocusTarget::Window:
                PointerTarget::enter(w, seat, data, event);
                break;
            case FocusTarget::LayerSurface:
                PointerTarget::enter(l, seat, data, event);
                break;
            case FocusTarget::Popup:
                PointerTarget::enter(p.wl_surface(), seat, data, event);
                break;
        }
    }
};

template <typename BEnd>
void FocusTarget<Backend>::enter(AvWindow& w, Seat<Navda<BEnd>>& seat, Navda<BEnd>& data, pointer::MotionEvent& event) {
    // implementation details
}

template <typename BEnd>
void FocusTarget<Backend>::enter(LayerSurface& l, Seat<Navda<BEnd>>& seat, Navda<BEnd>& data, pointer::MotionEvent& event) {
    // implementation details
}

template <typename BEnd>
void FocusTarget<Backend>::enter(WlSurface& surface, Seat<Navda<BEnd>>& seat, Navda<BEnd>& data, pointer::MotionEvent& event) {
    // implementation details
}
