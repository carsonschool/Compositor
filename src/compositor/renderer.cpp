#include <smithay/backend/renderer/damage.hpp>
#include <smithay/backend/renderer/element/surface.hpp>
#include <smithay/backend/renderer/element/utils.hpp>
#include <smithay/backend/renderer/renderer.hpp>
#include <smithay/desktop/space.hpp>
#include <smithay/output/output.hpp>
#include <smithay/render_elements.hpp>
#include <smithay/utils/geometry.hpp>
#include <smithay/utils/physical.hpp>
#include <smithay/utils/rectangle.hpp>
#include <slog/slog.hpp>

using namespace smithay::backend::renderer;
using namespace smithay::desktop;
using namespace smithay::output;
using namespace smithay::utils;

using CustomRenderElements = RenderElements<PointerRenderElement, WaylandSurfaceRenderElement, AvWindowRenderElement>;

template<typename R>
using OutputRenderElements = RenderElements<PointerRenderElement, WaylandSurfaceRenderElement, AvWindowRenderElement>;

template<typename R>
std::pair<std::optional<std::vector<Rectangle<int32_t, Physical>>>, RenderElementStates> render_output(
    const Output& output,
    const Space<AvWindow>& space,
    const std::vector<CustomRenderElements>& custom_elements,
    R& renderer,
    DamageTrackedRenderer& damage_tracked_renderer,
    size_t age,
    const slog::Logger& log
) {
    return damage_tracked_renderer.render(
        output,
        space,
        custom_elements,
        renderer,
        age,
        log
    );
}
