#pragma once

#include <memory>
#include <string>
#include <vector>

#include "image.hpp"
#include "rect.hpp"
#include "vec2.hpp"

namespace htn {

struct Renderer;

struct Tilemap {
    struct Object {
        int id = 0;
        std::string name;
        std::string type;
        FloatRect rect;
        float rotation = 0;
    };

    struct TileLayer {
        std::string name;

        int width = 0;
        int height = 0;
        std::vector<int> data;
    };

    struct ObjectLayer {
        std::string name;
        std::vector<Object> objects;
    };

    struct Tileset {
        int first_id = 0;
        std::shared_ptr<Image> image;
    };

    Tilemap(const std::string& filename);

    void render(Renderer& renderer, Vec2f camera_offset) const;

    const std::vector<ObjectLayer>& object_layers() const;

private:
    Vec2i m_tile_size;

    std::vector<Tileset> m_tilesets;
    std::vector<TileLayer> m_tile_layers;
    std::vector<ObjectLayer> m_object_layers;
};

}  // namespace htn
