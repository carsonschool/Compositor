#include <smithay/backend/renderer/element/surface/WaylandSurfaceRenderElement.hpp>
#include <smithay/backend/renderer/element/texture/TextureBuffer.hpp>
#include <smithay/backend/renderer/element/texture/TextureRenderElement.hpp>
#include <smithay/backend/renderer/element/AsRenderElements.hpp>
#include <smithay/backend/renderer/ImportAll.hpp>
#include <smithay/backend/renderer/Renderer.hpp>
#include <smithay/backend/renderer/Texture.hpp>
#include <smithay/input/pointer/CursorImageStatus.hpp>
#include <smithay/render_elements.hpp>
#include <smithay/utils/Physical.hpp>
#include <smithay/utils/Point.hpp>
#include <smithay/utils/Scale.hpp>

static constexpr std::array<float, 4> CLEAR_COLOR = {0.8, 0.8, 0.9, 1.0};

template <typename T>
struct PointerElement {
    std::optional<TextureBuffer<T>> texture;
    CursorImageStatus status;
};

template <typename T>
PointerElement<T> getDefaultPointerElement() {
    return {
        std::nullopt,
        CursorImageStatus::Default
    };
}

template <typename T>
void setPointerElementStatus(PointerElement<T>& element, CursorImageStatus status) {
    element.status = status;
}

template <typename T>
void setPointerElementTexture(PointerElement<T>& element, TextureBuffer<T> texture) {
    element.texture = std::make_optional(texture);
}

template <typename R>
struct PointerRenderElement {
    using Surface = WaylandSurfaceRenderElement<R>;
    using Texture = TextureRenderElement<typename R::TextureId>;
};

template <typename T, typename R>
struct AsRenderElements<PointerElement<T>, R> {
    using RenderElement = PointerRenderElement<R>;
    std::vector<typename RenderElement::template Element> render_elements(
        const PointerElement<T>& element,
        R& renderer,
        const Point<int, Physical>& location,
        const Scale<double>& scale
    ) const;
};

template <typename T, typename R>
std::vector<typename AsRenderElements<PointerElement<T>, R>::RenderElement::template Element>
AsRenderElements<PointerElement<T>, R>::render_elements(
    const PointerElement<T>& element,
    R& renderer,
    const Point<int, Physical>& location,
    const Scale<double>& scale
) const {
    // implementation here
}
